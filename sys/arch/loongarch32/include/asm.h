/*      $OpenBSD: asm.h,v 1.2 1998/03/16 09:03:02 pefo Exp $	*/

/*
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
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
 *	Copyright (C) 1989 Digital Equipment Corporation.
 *	Permission to use, copy, modify, and distribute this software and
 *	its documentation for any purpose and without fee is hereby granted,
 *	provided that the above copyright notice appears in all copies.
 *	Digital Equipment Corporation makes no representations about the
 *	suitability of this software for any purpose.  It is provided "as is"
 *	without express or implied warranty.
 */

#ifndef _MIPS_ASM_H
#define _MIPS_ASM_H

#ifndef _LIBC
#include <machine/regdef.h>
#else
#include <regdef.h>
#endif

#ifndef ABICALLS
#define	ABICALLS	.abicalls
#endif

#if defined(ABICALLS) && !defined(_KERNEL)
	ABICALLS
#endif

#define RCSID(x)

/*
 * Define how to access unaligned data word 
 */
#if defined(__MIPSEL__)
#define LWLO    lwl
#define LWHI    lwr
#define	SWLO	swl
#define	SWHI	swr
#else
#if defined(__MIPSEB__)
#define LWLO    lwr
#define LWHI    lwl
#define	SWLO	swr
#define	SWHI	swl
#else
#endif
#endif

/*
 * Code for setting gp reg if abicalls are used.
 */
#if defined(ABICALLS) && !defined(_KERNEL)
#define	ABISETUP
#else
#define	ABISETUP
#endif

/*
 * Define -pg profile entry code.
 */
#if defined(GPROF) || defined(PROF)
#define	MCOUNT			\
	addi.w  	sp, sp, -32;	\
	.cprestore 16;		        \
	st.w	    ra, sp, 28;	    \
	st.w    	gp, sp, 24;	    \
	.set	noat;		\
	.set	noreorder;	\
	bl	_mcount;	\
	addi.w 	sp, sp, -8;	\
	ld.w	ra, sp, 28;	\
	addi.w 	sp, sp, 32;	\
	.set reorder;		\
	.set	at;
#else
#define	MCOUNT
#endif

/*
 * LEAF(x)
 *
 *	Declare a leaf routine.
 */ 

#define LEAF(x)			\
	.align	3;		\
	.globl x;		\
x: ;				\
	ABISETUP		\
	MCOUNT

#define	ALEAF(x)		\
	.globl	x;		\
x:

/*
 * NLEAF(x)
 *
 *	Declare a non-profiled leaf routine.
 */
#define NLEAF(x)		\
	.align	3;		\
	.globl x;		\
	.ent x, 0;		\
x: ;				\
	.frame sp, 0, ra;	\
	ABISETUP

/*
 * NON_LEAF(x)
 *
 *	Declare a non-leaf routine (a routine that makes other C calls).
 */
#define NON_LEAF(x, fsize, retpc) \
	.align	3;		\
	.globl x;		\
	.ent x, 0;		\
x: ;				\
	.frame sp, fsize, retpc; \
	ABISETUP		\
	MCOUNT

/*
 * NNON_LEAF(x)
 *
 *	Declare a non-profiled non-leaf routine
 *	(a routine that makes other C calls).
 */
#define NNON_LEAF(x, fsize, retpc) \
	.align	3;		\
	.globl x;		\
	.ent x, 0;		\
x: ;				\
	.frame sp, fsize, retpc	\
	ABISETUP

/*
 * END(x)
 *
 *	Mark end of a procedure.
 */
#define END(x) \
	.end x
/*
 * Macros to panic and printf from assembly language.
 */
#define PANIC(msg) \
	la	a0, 9f; \
	MSG(msg); \
	bl	panic

#define	PRINTF(msg) \
	la	a0, 9f; \
	MSG(msg);  \
	bl	printf

#define	MSG(msg) \
	.rdata; \
9:	.asciiz	msg; \
	.text

#define ASMSTR(str) \
	.asciiz str; \
	.align	3

/*
 * Macros to construct mfc0 and mtc0 instructions for sel != 0 cases
 *
 * The following macros are defined to aid the SR71000 porting
 * effort until such time as the toolchain is proven
 * to support MIPS64 op encodings.
 */
#define MFC0Sel(reg,c0reg,sel) \
        .word   (0x40000000 | reg << 16 | c0reg << 11 | sel)
#define MTC0Sel(reg,c0reg,sel) \
        .word   (0x40800000 | reg << 16 | c0reg << 11 | sel)
#define DMFC0Sel(reg,c0reg,sel) \
        .word   (0x40200000 | reg << 16 | c0reg << 11 | sel)
#define DMTC0Sel(reg,c0reg,sel) \
        .word   (0x40a00000 | reg << 16 | c0reg << 11 | sel)

#endif /* !_MIPS_ASM_H */
