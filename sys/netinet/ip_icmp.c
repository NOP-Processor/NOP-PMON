/*	$OpenBSD: ip_icmp.c,v 1.18 1999/09/26 23:59:15 deraadt Exp $	*/
/*	$NetBSD: ip_icmp.c,v 1.19 1996/02/13 23:42:22 christos Exp $	*/

/*
 * Copyright (c) 1982, 1986, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)ip_icmp.c	8.2 (Berkeley) 1/4/94
 */

/*
%%% portions-copyright-nrl-95
Portions of this software are Copyright 1995-1998 by Randall Atkinson,
Ronald Lee, Daniel McDonald, Bao Phan, and Chris Winters. All Rights
Reserved. All rights under this copyright have been assigned to the US
Naval Research Laboratory (NRL). The NRL Copyright Notice and License
Agreement Version 1.1 (January 17, 1995) applies to these portions of the
software.
You should have received a copy of the license with this software. If you
didn't get a copy, you may request one from <license@ipv6.nrl.navy.mil>.
*/

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/proc.h>

#include <vm/vm.h>
#include <sys/sysctl.h>

#include <net/if.h>
#include <net/route.h>

#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip_var.h>
#include <netinet/icmp_var.h>

#include <machine/stdarg.h>



/*
 * ICMP routines: error generation, receive packet processing, and
 * routines to turnaround packets back to the originator, and
 * host table maintenance routines.
 */

int	icmpmaskrepl = 0;
int	icmpbmcastecho = 0;
#ifdef ICMPPRINTFS
int	icmpprintfs = 0;
#endif

extern	struct protosw inetsw[];

/*
 * Generate an error packet of type error
 * in response to bad packet ip.
 *
 * The ip packet inside has ip_off and ip_len in host byte order.
 */
void
icmp_error(n, type, code, dest, destifp)
	struct mbuf *n;
	int type, code;
	n_long dest;
	struct ifnet *destifp;
{
	register struct ip *oip = mtod(n, struct ip *), *nip;
	register unsigned oiplen = oip->ip_hl << 2;
	register struct icmp *icp;
	struct mbuf *m, m0;
	unsigned icmplen;

#ifdef ICMPPRINTFS
	if (icmpprintfs)
		printf("icmp_error(%x, %d, %d)\n", oip, type, code);
#endif
	if (type != ICMP_REDIRECT)
		icmpstat.icps_error++;
	/*
	 * Don't send error if not the first fragment of message.
	 * Don't error if the old packet protocol was ICMP
	 * error message, only known informational types.
	 */
	if (oip->ip_off &~ (IP_MF|IP_DF))
		goto freeit;
	if (oip->ip_p == IPPROTO_ICMP && type != ICMP_REDIRECT &&
	  n->m_len >= oiplen + ICMP_MINLEN &&
	  !ICMP_INFOTYPE(((struct icmp *)((caddr_t)oip + oiplen))->icmp_type)) {
		icmpstat.icps_oldicmp++;
		goto freeit;
	}
	/* Don't send error in response to a multicast or broadcast packet */
	if (n->m_flags & (M_BCAST|M_MCAST))
		goto freeit;
	/*
	 * First, formulate icmp message
	 */
	m = m_gethdr(M_DONTWAIT, MT_HEADER);
	if (m == NULL)
		goto freeit;
	icmplen = oiplen + min(8, oip->ip_len);
	m->m_len = icmplen + ICMP_MINLEN;
	MH_ALIGN(m, m->m_len);
	icp = mtod(m, struct icmp *);
	if ((u_int)type > ICMP_MAXTYPE)
		panic("icmp_error");
	icmpstat.icps_outhist[type]++;
	icp->icmp_type = type;
	if (type == ICMP_REDIRECT)
		icp->icmp_gwaddr.s_addr = dest;
	else {
		icp->icmp_void = 0;
		/* 
		 * The following assignments assume an overlay with the
		 * zeroed icmp_void field.
		 */
		if (type == ICMP_PARAMPROB) {
			icp->icmp_pptr = code;
			code = 0;
		} else if (type == ICMP_UNREACH &&
		    code == ICMP_UNREACH_NEEDFRAG && destifp)
			icp->icmp_nextmtu = htons(destifp->if_mtu);
	}

	icp->icmp_code = code;
	bcopy((caddr_t)oip, (caddr_t)&icp->icmp_ip, icmplen);
	nip = &icp->icmp_ip;
	nip->ip_off = htons(nip->ip_off);
	nip->ip_len = htons(nip->ip_len);

	m0.m_next = NULL;			/* correct nip->ip_sum */
	m0.m_data = (char *)nip;
	m0.m_len = nip->ip_hl << 2;
	nip->ip_sum = 0;
	nip->ip_sum = in_cksum(&m0, nip->ip_hl << 2);

	/*
	 * Now, copy old ip header (without options)
	 * in front of icmp message.
	 */
	if (m->m_data - sizeof(struct ip) < m->m_pktdat)
		panic("icmp len");
	m->m_data -= sizeof(struct ip);
	m->m_len += sizeof(struct ip);
	m->m_pkthdr.len = m->m_len;
	m->m_pkthdr.rcvif = n->m_pkthdr.rcvif;
	nip = mtod(m, struct ip *);
	bcopy((caddr_t)oip, (caddr_t)nip, sizeof(struct ip));
	nip->ip_off = htons(nip->ip_off);
	nip->ip_len = m->m_len;
	nip->ip_hl = sizeof(struct ip) >> 2;
	nip->ip_p = IPPROTO_ICMP;
	nip->ip_tos = 0;
	icmp_reflect(m);

freeit:
	m_freem(n);
}

static struct sockaddr_in icmpsrc = { sizeof (struct sockaddr_in), AF_INET };
static struct sockaddr_in icmpdst = { sizeof (struct sockaddr_in), AF_INET };
static struct sockaddr_in icmpgw = { sizeof (struct sockaddr_in), AF_INET };
struct sockaddr_in icmpmask = { 8, 0 };

/*
 * Process a received ICMP message.
 */
void
#if __STDC__
icmp_input(struct mbuf *m, ...)
#else
icmp_input(m, va_alist)
	struct mbuf *m;
	va_dcl
#endif
{
	register struct icmp *icp;
	register struct ip *ip = mtod(m, struct ip *);
	int icmplen = ip->ip_len;
	register int i;
	struct in_ifaddr *ia;
	void *(*ctlfunc) __P((int, struct sockaddr *, void *));
	int code;
	extern u_char ip_protox[];
	int hlen;
	va_list ap;

	va_start(ap, m);
	hlen = va_arg(ap, int);
	va_end(ap);

	/*
	 * Locate icmp structure in mbuf, and check
	 * that not corrupted and of at least minimum length.
	 */
#ifdef ICMPPRINTFS
	if (icmpprintfs) {
		char buf[4*sizeof "123"];

		strcpy(buf, inet_ntoa(ip->ip_dst));
		printf("icmp_input from %s to %s, len %d\n",
			inet_ntoa(ip->ip_src), buf, icmplen);
	}
#endif
	if (icmplen < ICMP_MINLEN) {
		icmpstat.icps_tooshort++;
		goto freeit;
	}
	i = hlen + min(icmplen, ICMP_ADVLENMIN);
	if (m->m_len < i && (m = m_pullup(m, i)) == 0)  {
		icmpstat.icps_tooshort++;
		return;
	}
	ip = mtod(m, struct ip *);
	m->m_len -= hlen;
	m->m_data += hlen;
	icp = mtod(m, struct icmp *);
	if (in_cksum(m, icmplen)) {
		icmpstat.icps_checksum++;
		goto freeit;
	}
	m->m_len += hlen;
	m->m_data -= hlen;

#ifdef ICMPPRINTFS
	/*
	 * Message type specific processing.
	 */
	if (icmpprintfs)
		printf("icmp_input, type %d code %d\n", icp->icmp_type,
		    icp->icmp_code);
#endif
	if (icp->icmp_type > ICMP_MAXTYPE)
		goto raw;
	icmpstat.icps_inhist[icp->icmp_type]++;
	code = icp->icmp_code;
	switch (icp->icmp_type) {

	case ICMP_UNREACH:
		switch (code) {
		case ICMP_UNREACH_NET:
		case ICMP_UNREACH_HOST:
		case ICMP_UNREACH_PROTOCOL:
		case ICMP_UNREACH_PORT:
		case ICMP_UNREACH_SRCFAIL:
			code += PRC_UNREACH_NET;
			break;

		case ICMP_UNREACH_NEEDFRAG:
#ifdef INET6
			if (icp->icmp_nextmtu) {
				extern int ipv6_trans_mtu
				    __P((struct mbuf **, int, int));
				struct mbuf *m0 = m;

				/*
				 * Do cool v4-related path MTU, for now,
				 * only v6-in-v4 can handle it.
				 */
				if (icmplen >= ICMP_V6ADVLENMIN &&
				    icmplen >= ICMP_V6ADVLEN(icp) &&
				    icp->icmp_ip.ip_p == IPPROTO_IPV6) {
					/*
					 * ipv6_trans_mtu returns 1 if
					 * the mbuf is still intact.
					 */
					if (ipv6_trans_mtu(&m0,icp->icmp_nextmtu,
					    hlen + ICMP_V6ADVLEN(icp))) {
						m = m0;
						goto raw;
					} else
						return;
				}
			}
#endif /* INET6 */
			code = PRC_MSGSIZE;
			break;
				
		case ICMP_UNREACH_NET_UNKNOWN:
		case ICMP_UNREACH_NET_PROHIB:
		case ICMP_UNREACH_TOSNET:
			code = PRC_UNREACH_NET;
			break;

		case ICMP_UNREACH_HOST_UNKNOWN:
		case ICMP_UNREACH_ISOLATED:
		case ICMP_UNREACH_HOST_PROHIB:
		case ICMP_UNREACH_TOSHOST:
		case ICMP_UNREACH_FILTER_PROHIB:
		case ICMP_UNREACH_HOST_PRECEDENCE:
		case ICMP_UNREACH_PRECEDENCE_CUTOFF:
			code = PRC_UNREACH_HOST;
			break;

		default:
			goto badcode;
		}
		goto deliver;

	case ICMP_TIMXCEED:
		if (code > 1)
			goto badcode;
		code += PRC_TIMXCEED_INTRANS;
		goto deliver;

	case ICMP_PARAMPROB:
		if (code > 1)
			goto badcode;
		code = PRC_PARAMPROB;
		goto deliver;

	case ICMP_SOURCEQUENCH:
		if (code)
			goto badcode;
		code = PRC_QUENCH;
	deliver:
		/*
		 * Problem with datagram; advise higher level routines.
		 */
		if (icmplen < ICMP_ADVLENMIN || icmplen < ICMP_ADVLEN(icp) ||
		    icp->icmp_ip.ip_hl < (sizeof(struct ip) >> 2)) {
			icmpstat.icps_badlen++;
			goto freeit;
		}
		if (IN_MULTICAST(icp->icmp_ip.ip_dst.s_addr))
			goto badcode;
		NTOHS(icp->icmp_ip.ip_len);
#ifdef INET6
		/* Get more contiguous data for a v6 in v4 ICMP message. */
		if (icp->icmp_ip.ip_p == IPPROTO_IPV6) {
			if (icmplen < ICMP_V6ADVLENMIN || 
			    icmplen < ICMP_V6ADVLEN(icp)) {
				icmpstat.icps_badlen++;
				goto freeit;
			} else {
				if (!(m = m_pullup(m, (ip->ip_hl << 2) +
				    ICMP_V6ADVLEN(icp)))) {
					icmpstat.icps_tooshort++;
					return;
				}
				ip = mtod(m, struct ip *);
				icp = (struct icmp *)(m->m_data + (ip->ip_hl << 2));
			}
		}
#endif /* INET6 */
#ifdef ICMPPRINTFS
		if (icmpprintfs)
			printf("deliver to protocol %d\n", icp->icmp_ip.ip_p);
#endif
		icmpsrc.sin_addr = icp->icmp_ip.ip_dst;
		ctlfunc = inetsw[ip_protox[icp->icmp_ip.ip_p]].pr_ctlinput;
		if (ctlfunc)
			(*ctlfunc)(code, sintosa(&icmpsrc), &icp->icmp_ip);
		break;

	badcode:
		icmpstat.icps_badcode++;
		break;

	case ICMP_ECHO:
		if (!icmpbmcastecho &&
		    (m->m_flags & (M_MCAST | M_BCAST)) != 0) {
			icmpstat.icps_bmcastecho++;
			break;
		}
		icp->icmp_type = ICMP_ECHOREPLY;
		goto reflect;

	case ICMP_TSTAMP:
		if (!icmpbmcastecho &&
		    (m->m_flags & (M_MCAST | M_BCAST)) != 0) {
			icmpstat.icps_bmcastecho++;
			break;
		}
		if (icmplen < ICMP_TSLEN) {
			icmpstat.icps_badlen++;
			break;
		}
		icp->icmp_type = ICMP_TSTAMPREPLY;
		icp->icmp_rtime = iptime();
		icp->icmp_ttime = icp->icmp_rtime;	/* bogus, do later! */
		goto reflect;
		
	case ICMP_MASKREQ:
		if (icmpmaskrepl == 0)
			break;
		/*
		 * We are not able to respond with all ones broadcast
		 * unless we receive it over a point-to-point interface.
		 */
		if (icmplen < ICMP_MASKLEN) {
			icmpstat.icps_badlen++;
			break;
		}
		if (ip->ip_dst.s_addr == INADDR_BROADCAST ||
		    ip->ip_dst.s_addr == INADDR_ANY)
			icmpdst.sin_addr = ip->ip_src;
		else
			icmpdst.sin_addr = ip->ip_dst;
		ia = ifatoia(ifaof_ifpforaddr(sintosa(&icmpdst),
		    m->m_pkthdr.rcvif));
		if (ia == 0)
			break;
		icp->icmp_type = ICMP_MASKREPLY;
		icp->icmp_mask = ia->ia_sockmask.sin_addr.s_addr;
		if (ip->ip_src.s_addr == 0) {
			if (ia->ia_ifp->if_flags & IFF_BROADCAST)
				ip->ip_src = ia->ia_broadaddr.sin_addr;
			else if (ia->ia_ifp->if_flags & IFF_POINTOPOINT)
				ip->ip_src = ia->ia_dstaddr.sin_addr;
		}
reflect:
		ip->ip_len += hlen;	/* since ip_input deducts this */
		icmpstat.icps_reflect++;
		icmpstat.icps_outhist[icp->icmp_type]++;
		icmp_reflect(m);
		return;

	case ICMP_REDIRECT:
		if (code > 3)
			goto badcode;
		if (icmplen < ICMP_ADVLENMIN || icmplen < ICMP_ADVLEN(icp) ||
		    icp->icmp_ip.ip_hl < (sizeof(struct ip) >> 2)) {
			icmpstat.icps_badlen++;
			break;
		}
		/*
		 * Short circuit routing redirects to force
		 * immediate change in the kernel's routing
		 * tables.  The message is also handed to anyone
		 * listening on a raw socket (e.g. the routing
		 * daemon for use in updating its tables).
		 */
		icmpgw.sin_addr = ip->ip_src;
		icmpdst.sin_addr = icp->icmp_gwaddr;
#ifdef	ICMPPRINTFS
		if (icmpprintfs) {
			char buf[4 * sizeof "123"];
			strcpy(buf, inet_ntoa(icp->icmp_ip.ip_dst));

			printf("redirect dst %s to %s\n",
			    buf, inet_ntoa(icp->icmp_gwaddr));
		}
#endif
		icmpsrc.sin_addr = icp->icmp_ip.ip_dst;
		rtredirect(sintosa(&icmpsrc), sintosa(&icmpdst),
		    (struct sockaddr *)0, RTF_GATEWAY | RTF_HOST,
		    sintosa(&icmpgw), (struct rtentry **)0);
		pfctlinput(PRC_REDIRECT_HOST, sintosa(&icmpsrc));
		break;

	/*
	 * No kernel processing for the following;
	 * just fall through to send to raw listener.
	 */
	case ICMP_ECHOREPLY:
	case ICMP_ROUTERADVERT:
	case ICMP_ROUTERSOLICIT:
	case ICMP_TSTAMPREPLY:
	case ICMP_IREQREPLY:
	case ICMP_MASKREPLY:
	default:
		break;
	}

raw:
	rip_input(m, 0);
	return;

freeit:
	m_freem(m);
}

/*
 * Reflect the ip packet back to the source
 */
void
icmp_reflect(m)
	struct mbuf *m;
{
	register struct ip *ip = mtod(m, struct ip *);
	register struct in_ifaddr *ia;
	struct in_addr t;
	struct mbuf *opts = 0;
	int optlen = (ip->ip_hl << 2) - sizeof(struct ip);

	if (!in_canforward(ip->ip_src) &&
	    ((ip->ip_src.s_addr & IN_CLASSA_NET) !=
	     htonl(IN_LOOPBACKNET << IN_CLASSA_NSHIFT))) {
		m_freem(m);	/* Bad return address */
		goto done;	/* ip_output() will check for broadcast */
	}
	t = ip->ip_dst;
	ip->ip_dst = ip->ip_src;
	/*
	 * If the incoming packet was addressed directly to us,
	 * use dst as the src for the reply.  Otherwise (broadcast
	 * or anonymous), use the address which corresponds
	 * to the incoming interface.
	 */
	for (ia = in_ifaddr.tqh_first; ia; ia = ia->ia_list.tqe_next) {
		if (t.s_addr == ia->ia_addr.sin_addr.s_addr)
			break;
		if ((ia->ia_ifp->if_flags & IFF_BROADCAST) &&
		    t.s_addr == ia->ia_broadaddr.sin_addr.s_addr)
			break;
	}
	icmpdst.sin_addr = t;
	if (ia == (struct in_ifaddr *)0)
		ia = ifatoia(ifaof_ifpforaddr(sintosa(&icmpdst),
		    m->m_pkthdr.rcvif));
	/*
	 * The following happens if the packet was not addressed to us,
	 * and was received on an interface with no IP address.
	 */
	if (ia == (struct in_ifaddr *)0)
		ia = in_ifaddr.tqh_first;
	t = ia->ia_addr.sin_addr;
	ip->ip_src = t;
	ip->ip_ttl = MAXTTL;

	if (optlen > 0) {
		register u_char *cp;
		int opt, cnt;
		u_int len;

		/*
		 * Retrieve any source routing from the incoming packet;
		 * add on any record-route or timestamp options.
		 */
		cp = (u_char *) (ip + 1);
		if ((opts = ip_srcroute()) == 0 &&
		    (opts = m_gethdr(M_DONTWAIT, MT_HEADER))) {
			opts->m_len = sizeof(struct in_addr);
			mtod(opts, struct in_addr *)->s_addr = 0;
		}
		if (opts) {
#ifdef ICMPPRINTFS
		    if (icmpprintfs)
			    printf("icmp_reflect optlen %d rt %d => ",
				optlen, opts->m_len);
#endif
		    for (cnt = optlen; cnt > 0; cnt -= len, cp += len) {
			    opt = cp[IPOPT_OPTVAL];
			    if (opt == IPOPT_EOL)
				    break;
			    if (opt == IPOPT_NOP)
				    len = 1;
			    else {
				    len = cp[IPOPT_OLEN];
				    if (len <= 0 || len > cnt)
					    break;
			    }
			    /*
			     * Should check for overflow, but it "can't happen"
			     */
			    if (opt == IPOPT_RR || opt == IPOPT_TS || 
				opt == IPOPT_SECURITY) {
				    bcopy((caddr_t)cp,
					mtod(opts, caddr_t) + opts->m_len, len);
				    opts->m_len += len;
			    }
		    }
		    /* Terminate & pad, if necessary */
		    if ((cnt = opts->m_len % 4) != 0) {
			    for (; cnt < 4; cnt++) {
				    *(mtod(opts, caddr_t) + opts->m_len) =
					IPOPT_EOL;
				    opts->m_len++;
			    }
		    }
#ifdef ICMPPRINTFS
		    if (icmpprintfs)
			    printf("%d\n", opts->m_len);
#endif
		}
		/*
		 * Now strip out original options by copying rest of first
		 * mbuf's data back, and adjust the IP length.
		 */
		ip->ip_len -= optlen;
		ip->ip_hl = sizeof(struct ip) >> 2;
		m->m_len -= optlen;
		if (m->m_flags & M_PKTHDR)
			m->m_pkthdr.len -= optlen;
		optlen += sizeof(struct ip);
		bcopy((caddr_t)ip + optlen, (caddr_t)(ip + 1),
			 (unsigned)(m->m_len - sizeof(struct ip)));
	}
	m->m_flags &= ~(M_BCAST|M_MCAST);
	icmp_send(m, opts);
done:
	if (opts)
		(void)m_free(opts);
}

/*
 * Send an icmp packet back to the ip level,
 * after supplying a checksum.
 */
void
icmp_send(m, opts)
	register struct mbuf *m;
	struct mbuf *opts;
{
	register struct ip *ip = mtod(m, struct ip *);
	register int hlen;
	register struct icmp *icp;

	hlen = ip->ip_hl << 2;
	m->m_data += hlen;
	m->m_len -= hlen;
	icp = mtod(m, struct icmp *);
	icp->icmp_cksum = 0;
	icp->icmp_cksum = in_cksum(m, ip->ip_len - hlen);
	m->m_data -= hlen;
	m->m_len += hlen;
#ifdef ICMPPRINTFS
	if (icmpprintfs) {
		char buf[4 * sizeof "123"];

		strcpy(buf, inet_ntoa(ip->ip_dst));
		printf("icmp_send dst %s src %s\n",
		    buf, inet_ntoa(ip->ip_src));
	}
#endif
	(void) ip_output(m, opts, NULL, 0, NULL, NULL);
}

n_time
iptime()
{
	struct timeval atv;
	u_long t;

	microtime(&atv);
	t = (atv.tv_sec % (24*60*60)) * 1000 + atv.tv_usec / 1000;
	return (htonl(t));
}

int
icmp_sysctl(name, namelen, oldp, oldlenp, newp, newlen)
	int *name;
	u_int namelen;
	void *oldp;
	size_t *oldlenp;
	void *newp;
	size_t newlen;
{

	/* All sysctl names at this level are terminal. */
	if (namelen != 1)
		return (ENOTDIR);

	switch (name[0]) {
	case ICMPCTL_MASKREPL:
		return (sysctl_int(oldp, oldlenp, newp, newlen, &icmpmaskrepl));
	case ICMPCTL_BMCASTECHO:
		return (sysctl_int(oldp, oldlenp, newp, newlen, &icmpbmcastecho));
	default:
		return (ENOPROTOOPT);
	}
	/* NOTREACHED */
}
