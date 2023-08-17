/*	$OpenBSD: regnum.h,v 1.3 1999/01/27 04:46:06 imp Exp $	*/

/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
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
 *	from: Utah Hdr: reg.h 1.1 90/07/09
 *	@(#)reg.h	8.2 (Berkeley) 1/11/94
 */

#ifndef _MIPS_REGNUM_H_
#define _MIPS_REGNUM_H_

#define STAND_ARG_SIZE		16
#define STAND_FRAME_SIZE	24
#define STAND_RA_OFFSET		20  


#if 0
/*
 * Location of the saved registers relative to ZERO.
 * Usage is p->p_regs[XX].
 */
#define ZERO	0
#define AST	1
#define V0	2
#define V1	3
#define A0	4
#define A1	5
#define A2	6
#define A3	7
#define T0	8
#define T1	9
#define T2	10
#define T3	11
#define T4	12
#define T5	13
#define T6	14
#define T7	15
#define S0	16
#define S1	17
#define S2	18
#define S3	19
#define S4	20
#define S5	21
#define S6	22
#define S7	23
#define T8	24
#define T9	25
#define K0	26
#define K1	27
#define GP	28
#define SP	29
#define S8	30
#define RA	31
#define	SR	32
#define	PS	SR	/* alias for SR */
#define MULLO	33
#define MULHI	34
#define BADVADDR 35
#define CAUSE	36
#define	PC	37

#define	NUMSAVEREGS 38		/* Number of registers saved in trap */

#define AUXBASE (FPBASE + NUMFPREGS)
#define	COUNT	(AUXBASE+0)
#define	COMPARE	(AUXBASE+1)
#define	WATCHLO	(AUXBASE+2)
#define	WATCHHI	(AUXBASE+3)
#define	WATCHM	(AUXBASE+4)
#define	WATCH1	(AUXBASE+5)
#define	WATCH2	(AUXBASE+6)
#define	LLADR	(AUXBASE+7)
#define	ECC	(AUXBASE+8)
#define	CACHER	(AUXBASE+9)
#define	TAGLO	(AUXBASE+10)
#define	TAGHI	(AUXBASE+11)
#define	WIRED	(AUXBASE+12)
#define	PGMSK	(AUXBASE+13)
#define	ENTLO0	(AUXBASE+14)
#define	ENTLO1	(AUXBASE+15)
#define	ENTHI	(AUXBASE+16)
#define CONTX	(AUXBASE+17)
#define	XCONTX	(AUXBASE+18)
#define INDEX	(AUXBASE+19)
#define	RANDOM	(AUXBASE+20)
#define	CONFIG	(AUXBASE+21)
#define	ICR	(AUXBASE+22)
#define	IPLLO	(AUXBASE+23)
#define	IPLHI	(AUXBASE+24)
#define	PRID	(AUXBASE+25)
#define	PCOUNT	(AUXBASE+26)
#define	PCTRL	(AUXBASE+27)
#define	ERRPC	(AUXBASE+28)
#define NUMAUXREG 29

#endif /* !_MIPS_REGNUM_H_ */ 
#endif 

#define ZERO 0 
#define RA   1  
#define TP   2 
#define SP   3 
#define A0   4  
#define A1   5 
#define A2   6 
#define A3   7 
#define A4   8 
#define A5   9 
#define A6   10 
#define A7   11 
#define T0   12 
#define T1   13 
#define T2   14
#define T3   15 
#define T4   16 
#define T5   17 
#define T6   18 
#define T7   19 
#define T8   20  
#define X    21 
#define FP   22 
#define S0   23
#define S1   24
#define S2   25
#define S3   26
#define S4   27
#define S5   28
#define S6   29
#define S7   30
#define S8   31  

#define CRMD 32 
#define PRMD 33
#define ECTL 34
#define ESTAT 35 
#define ERA  36
#define BADV 37 
#define EENTRY 38 
#define LLBCTL 39 
#define TLBIDX 40
#define TLBEHI 41
#define TLBELO0 42
#define TLBELO1 43 


