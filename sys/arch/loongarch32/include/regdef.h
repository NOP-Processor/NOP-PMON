/*	$OpenBSD: regdef.h,v 1.3 1999/01/27 04:46:06 imp Exp $	*/

/*
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell. This file is derived from the MIPS RISC
 * Architecture book by Gerry Kane.
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
 *	@(#)regdef.h	8.1 (Berkeley) 6/10/93
 */
#if 0
#ifndef _MIPS_REGDEF_H_
#define _MIPS_REGDEF_H_

#define zero	$0	/* always zero */
#define AT	$at	/* assembler temp */
#define v0	$2	/* return value */
#define v1	$3
#define a0	$4	/* argument registers */
#define a1	$5
#define a2	$6
#define a3	$7
#define t0	$8	/* temp registers (not saved across subroutine calls) */
#define t1	$9
#define t2	$10
#define t3	$11
#define t4	$12
#define t5	$13
#define t6	$14
#define t7	$15
#define s0	$16	/* saved across subroutine calls (callee saved) */
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24	/* two more temp registers */
#define t9	$25
#define k0	$26	/* kernel temporary */
#define k1	$27
#define gp	$28	/* global pointer */
#define sp	$29	/* stack pointer */
#define s8	$30	/* one more callee saved */
#define ra	$31	/* return address */

#endif /* !_MIPS_REGDEF_H_ */ 
#endif  

#ifndef _SYS_REGDEF_H
#define _SYS_REGDEF_H

# define zero	$r0
# define ra	$r1
# define tp	$r2
# define sp	$r3
# define a0	$r4
# define a1	$r5
# define a2	$r6
# define a3	$r7
# define a4	$r8
# define a5	$r9
# define a6	$r10
# define a7	$r11
# define v0	$r4
# define v1	$r5 
# define t0	$r12
# define t1	$r13
# define t2	$r14
# define t3	$r15
# define t4	$r16
# define t5	$r17
# define t6	$r18
# define t7	$r19
# define t8	$r20
# define x	$r21
# define fp	$r22
# define s0	$r23
# define s1	$r24
# define s2	$r25
# define s3	$r26
# define s4	$r27
# define s5	$r28
# define s6	$r29
# define s7	$r30
# define s8	$r31

#define csr_crmd      0x0
#define csr_prmd      0x1
#define csr_euen      0x2
#define csr_ectl      0x4
#define csr_estat     0x5
#define csr_era       0x6
#define csr_badv      0x7
#define csr_eentry     0xc
#define csr_tlbidx    0x10
#define csr_tlbehi    0x11
#define csr_tlbelo0    0x12
#define csr_tlbelo1    0x13
#define csr_asid      0x18
#define csr_pgdl      0x19
#define csr_pgdh      0x1a
#define csr_pgd       0x1b
#define csr_cpuid    0x20
#define csr_save0     0x30
#define csr_save1     0x31
#define csr_save2     0x32
#define csr_save3     0x33
#define csr_tid       0x40
#define csr_tval      0x42
#define csr_ticlr     0x44
#define csr_llbctl    0x60
#define csr_tlbrentry 0x88
#define csr_ctag      0x98
#define csr_dmw0      0x180
#define csr_dmw1      0x181

#endif /* _SYS_REGDEF_H */
