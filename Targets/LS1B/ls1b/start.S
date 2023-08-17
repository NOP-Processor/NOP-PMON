/*	$Id: start.S,v 1.1.1.1 2006/09/14 01:59:08 root Exp $ */

/*
 * Copyright (c) 2001 Opsycon AB  (www.opsycon.se)
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
 *	This product includes software developed by Opsycon AB, Sweden.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */ 

#ifndef _KERNEL
#define _KERNEL
#endif 

#include <asm.h>  
#include "pmon/dev/ns16550.h"
#include "target/fcr.h"

#define	PRINTSTR(x) \
	.section .rodata;98: .asciz x; .text; la a0, 98b; bl stringserial

#define	DELAY(count)	\
	li v0, count;	\
99:			\
	addi.w	v0, v0, -1; \
	bne 	v0, zero, 99b

	.globl	_start
	.globl	start
	.globl	__main
_start:
start:
	.globl	stack
stack = start - 0x4000		/* Place PMON stack below PMON start in RAM */ 

    li.w      t0, 0x1c000380 
    csrwr   t0, csr_eentry 
    la      sp, stack  

    li.w      t1, 0xa0000009  //uncache window
    csrwr   t1, csr_dmw0 
    li.w      t1, 0x00000009  //cache window   cache attribute is set after 
    csrwr   t1, csr_dmw1
    li.w      t1, 0x10 
    li.w      t2, 0x18 
    csrxchg t1, t2, csr_crmd

    //pcaddu12i t0, 0  
    //addi.w  t0, t0, 20
    //li      t1, 0xa0000000 
    //or      t0, t0, t1 
    //jirl    zero, t0, 0      //zero to zero window is useless  

    bl      locate 
    
uncached:
    nop

.org 0x380 
exc_common:
    PRINTSTR("\r\nCRMD=")
    csrrd   a0, csr_crmd
    bl      hexserial  

    PRINTSTR("\r\nESTAT=")
    csrrd   a0, csr_estat
    bl      hexserial  

    PRINTSTR("\r\nERA=")
    csrrd   a0, csr_era
    bl      hexserial  

    PRINTSTR("\r\nBADV=")
    csrrd   a0, csr_badv
    bl      hexserial 

    PRINTSTR("\r\nEENTRY=")
    csrrd   a0, csr_eentry
    bl      hexserial  

1:
    b 1b  

locate: 
    la      s0, uncached 
    sub.w   s0, ra, s0

    li.w      t0, 0x33333333 
    li.w      a0, 0xbfd0f010 
    st.w    t0, a0, 0  
    //la      s0, uncached 
    //sub.w   s0, ra, s0  

/*spi speed*/
    li.w      t0, 0xbfe80000 
    li.w      t1, 0x17 
    st.b    t1, t0, 4

/*disable all gpio*/
    li.w      a0, 0xbfd01000
    st.w    zero, a0, 0xc0 
    st.w    zero, a0, 0xc4  

    li.w      a0, 0 
    bl      initserial 

    PRINTSTR("\r\nPMON2000 LOONGARCH Initializing. Standby...\r\n")
    PRINTSTR(" CPUID=0x")
    csrrd   a0, csr_cpuid 
    bl      hexserial  
    PRINTSTR("\r\n") 

    bne     s0, zero, 1f
    li.w      a0, 128 
    bl      initmips 
1: 
    //li      t1, 0x00000009
    //csrwr   t1, csr_dmw1
    //li      t1, 0x8 
    //li      t2, 0x18 
    //csrxchg t1, t2, csr_crmd
//    PRINTSTR("\r\n s0 is not zero\r\n") 
//2:
//    b 2b


do_caches: 
    li.w      s7, 0       /*no L2 cache*/ 
    li.w      s8, 0       /*no L3 cache*/
    
    bl      cache_init
    PRINTSTR("\r\nCache init over\r\n")
    
    li.w      t1, 0x00000019   /*open cache window*/
    csrwr   t1, csr_dmw1

bootnow:
#define	FCALL_PRINTSTR(x) \
	.section .rodata;98: .asciz x; .text; la a0, 98b; la t0, stringserial; add.w t0, t0, s0;jirl ra, t0, 0	

#undef BL
#define BL(x) \
    la      t0, x;  \
    add.w   t0, t0, s0; \
    jirl    ra, t0, 0;  

//#define SET_WINDOW \
//    li      t1, 0xa0000009; \
//    csrwr   t1, csr_dmw0;   \
//    li      t1, 0x88000019; \
//    csrwr   t1, csr_dmw1; \
//    li      t1, 0x10; \
//    li      t2, 0x18; \
//    csrxchg t1, t2, csr_crmd; 
//
//#define CLOSE_WINDOW
//    li      t1, 0x8;    \
//    li      t2, 0x18;    \
//    csrxchg t1, t2, csr_crmd;

/*copy copy program to sdram to make copy fast*/

    PRINTSTR("\r\nstart copy copy program\r\n")

    li.w      t1, 0x00000009
    csrwr   t1, csr_dmw1

    la      t0, 121f 
    add.w   t0, t0, s0 
    la      t1, 122f 
    add.w   t1, t1, s0 

    li.w      t2, 0x00000000 
1:
    ld.w    t3, t0, 0 
    st.w    t3, t2, 0 
    addi.w  t0, t0, 4
    addi.w  t2, t2, 4 
    bge     t1, t0, 1b 

    PRINTSTR("\r\ncopy program copy over\r\n")  

    PRINTSTR("\r\nstart copy all program\r\n") 
    la      t4, start 
    la      t5, _edata  
    la      t6, init_bss
    li.w      t0, 0x00000000 
    jirl    zero, t0, 0

121: 
    //li      t1, 0x00000009   //uncache window 
    //csrwr   t1, csr_dmw0 
    //li      t1, 0x88000019   //cache window 
    //csrwr   t1, csr_dmw1
    //li      t1, 0x10 
    //li      t2, 0x18 
    //csrxchg t1, t2, csr_crmd  

    //li        t1, 0x20         //fetch inst cached; load/store uncached
    //li        t2, 0x1e0        //da mode
    //csrxchg   t1, t2, csr_crmd 
    
    //li      t1, 0x00000019   //cache window 
    //csrwr   t1, csr_dmw1 

	//FCALL_PRINTSTR("Copy PMON to execute location...\r\n")
	//FCALL_PRINTSTR("  start = 0x")
	//la	a0, start
	//BL(hexserial)
	//FCALL_PRINTSTR("\r\n  s0 = 0x")
	//move	a0, s0
	//BL(hexserial)

	//FCALL_PRINTSTR("\r\n  _edata = 0x")
	//la	a0, _edata
	//BL(hexserial)

	//FCALL_PRINTSTR("\r\n  _end = 0x")
	//la	a0, _end
	//BL(hexserial)
	//FCALL_PRINTSTR("\r\n")

    //la      a0, start  
    move    a0, t4
    add.w   a1, a0, s0 
    //la      a2, _edata  
    move    a2, t5
    //sub.w   t1, a2, a0 
    //srli.w  t1, t1, 2 

    move    t0, a0 
    move    t1, a1 
    move    t2, a2

    /*copy text section*/ 
    li.w      t4, 0xffff
1:
    and     t3, t0, t4
    bne     t3, zero, 2f 
    move    a0, t0 
    //BL(hexserial) 
    li.w      a0, '\r' 
    //BL(tgt_putchar) 
2:
    ld.w    t3, t1, 0 
    st.w    t3, t0, 0 
    addi.w  t0, t0, 4 
    addi.w  t1, t1, 4 
    bne     t2, t0, 1b 

	//FCALL_PRINTSTR("\ncopy text section done.\r\n")  

    li.w      t1, 0x00000019   //cache window 
    csrwr   t1, csr_dmw1 

    jirl    zero, t6, 0
 
init_bss:
	PRINTSTR("\ncopy text section done.\r\n")  
	PRINTSTR("\nstart clear bss.\r\n")  
    /*Clear BSS*/ 
    la      a0, _edata 
    la      a2, _end 
2:  st.w    zero, a0, 0
    addi.w  a0, a0, 4
    bne     a2, a0, 2b  
	PRINTSTR("\nbss clear over.\r\n")  

	//FCALL_PRINTSTR("Copy PMON to execute location done.\r\n")
	//FCALL_PRINTSTR("sp=");
	//move a0, sp
	//BL(hexserial)

    //li      t1, 0xa0000009      //uncache window 
    //csrwr   t1, csr_dmw0 
    //li      t1, 0x88000009      //cache window  0x1c is useless
    //csrwr   t1, csr_dmw1   
    //li      t1, 0x10 
    //li      t2, 0x18            //open pg mode
    //csrxchg t1, t2, csr_crmd  

    li.w      s2, 0x08000000  //Lc add 128M 
    move    a0, s2 
    srli.w  a0, a0, 20  

    la      t0, initmips 
    jirl    zero, t0, 0 

122:
    stuck:
        b   stuck 

/*
1:
    b 1b
*/

/* Clear the TLB. Normally called from start.S*/ 

LEAF(CPU_TLBClear)
    b   CPU_TLBInit 

LEAF(CPU_TLBInit) 
    li.w      a3, 0x80000000  
    li.w      a4, 0
    li.w      a2, 32 
1:
    li.w      a0, 0x1c000000  
    csrwr   a0, csr_tlbehi 
    csrwr   zero, csr_tlbelo0 
    csrwr   zero, csr_tlbelo1 

    or      a5, a3, a4
    csrwr   a5, csr_tlbidx 
    addi.w  a4, a4, 1 
    tlbwr  

    bne     a4, a2, 1b 
TLBInit_finish:
    jirl    zero, ra, 0

cache_init:
    li.w      t1, 256  
    li.w      t0, 0x0
1:  
    cacop   0x0, t0, 0x0  #0 way  icache
    cacop   0x0, t0, 0x1  #1 way  icache
    cacop   0x1, t0, 0x0  #0 way  dcache
    cacop   0x1, t0, 0x1  #1 way  dcache 
    addi.w  t1, t1, -1 
    srli.w  t0, t0, 4
    addi.w  t0, t0, 1 
    slli.w  t0, t0, 4
    blt     zero, t1, 1b 
cache_init_finish:
    jirl    zero, ra, 0

LEAF(stringserial) 
    move    a2, ra 
    add.w   a1, a0, s0
    ld.b    a0, a1, 0 
1:
    beq     a0, zero, 2f 
    addi.w  a1, a1, 1 
    bl      tgt_putchar 
    ld.b    a0, a1, 0 
    b       1b 
2:
    jirl    zero, a2, 0 



LEAF(hexserial) 
    move    a2, ra 
    move    a1, a0 
    li.w      a3, 7 
1: 
    slli.w  a4, a3, 2 
    srl.w   a0, a1, a4 
    andi    a0, a0, 0xf 
    la      t0, hexchar 
    add.w   t0, t0, s0
    add.w   t0, t0, a0 
    ld.b    a0, t0, 0
    bl      tgt_putchar  
    addi.w  a3, a3, -1 
    bge     a3, zero, 1b 

    jirl    zero, a2, 0

LEAF(tgt_testchar)  
    li.w      t0, COM1_BASE_ADDR 
1:
    ld.b    t1, t0, NS16550_LSR 
    andi    v0, t1, LSR_TXRDY 
    jirl    zero, ra, 0

LEAF(tgt_getchar) 
    li.w      t0, COM1_BASE_ADDR 
1:
    ld.b    t1, t0, NS16550_LSR 
    andi    t1, t1, LSR_TXRDY 
    beq     t1, zero, 1b 
    ld.b    v0, t0, NS16550_DATA 
    jirl    zero, ra, 0

LEAF(tgt_putchar) 
    li.w      t0, COM1_BASE_ADDR 
1:
    ld.b    t1, t0, NS16550_LSR 
    andi    t1, t1, LSR_TXRDY 
    beq     t1, zero, 1b 

    st.b    a0, t0, NS16550_DATA 
    jirl    zero, ra, 0

LEAF(initserial) 
    li.w      t0, COM1_BASE_ADDR    #COM1_BASE_ADDR:0xbfe001e0 
1:
	li.w	    t1, FIFO_ENABLE|FIFO_RCV_RST|FIFO_XMT_RST|FIFO_TRIGGER_4 
	st.b	t1, t0, NS16550_FIFO

##set baud rate
    li.w      t1, CFCR_DLAB
    st.b    t1, t0, NS16550_CFCR
	//li	    t1, 0x23 //Lc modify Baut 57600
	li.w	    t1, 0x12 //Lc modify Baut 57600
	st.b	t1, t0, NS16550_DATA 
    srli.w  t1, t1, 8 
    st.b    t1, t0, NS16550_IER 
    li.w      t1, CFCR_8BITS 
    st.b    t1, t0, NS16550_CFCR  

##CODE 1: end
    li.w      t1, CFCR_8BITS 
    st.b    t1, t0, NS16550_CFCR
	li.w	    t1, MCR_DTR|MCR_RTS 
    st.b    t1, t0, NS16550_MCR 
    li.w      t1, 0x0 
    st.b    t1, t0, NS16550_IER  

    jirl    zero, ra, 0   

.section .rodata 
hexchar:
    .ascii "0123456789abcdef"



