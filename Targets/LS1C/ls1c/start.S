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
#include <regnum.h>
#include <cpu.h>
#include <pte.h>

#include "pmon/dev/ns16550.h"
#include "target/prid.h"
#include "target/sbd.h"
#include "target/fcr.h"
#include "target/via686b.h"
#include "target/i8254.h"
#include "target/isapnpreg.h"
/* #include "sys/arch/mips/include/cpu.h" */

#define DEBUG_LOCORE

#ifndef BOOT_FROM_EJTAG      
#define  BOOT_FROM_EJTAG
#endif
#undef BOOT_FROM_EJTAG

#ifdef DEBUG_LOCORE
#define	TTYDBG(x) \
	.rdata;98: .asciz x; .text; la a0, 98b; bal stringserial; nop
#	.rdata; .align 2; 98: .asciz x; .text; la a0, 98b; bal stringserial; nop
#else
#define TTYDBG(x)
#endif

#define	PRINTSTR(x) \
	.rdata;98: .asciz x; .text; la a0, 98b; bal stringserial; nop
#	.rdata; .align 2; 98: .asciz x; .text; la a0, 98b; bal stringserial; nop

#define	FCALL_PRINTSTR(x) \
	.rdata;98: .asciz x; .text; la a0, 98b; la v0, stringserial; addu v0,s0;jalr v0; nop	

#undef BAL
#define BAL(x) \
	la v0,x; \
	addu v0,s0; \
	jalr v0; \
	nop;



/* Delay macro */
#define	DELAY(count)	\
	li v0, count;	\
99:			\
	bnez	v0, 99b;\
	addiu	v0, -1

#define tmpsize		s1
#define msize		s2
#define bonito		s4
#define dbg			s5
#define sdCfg		s6

#define CP0_CONFIG $16
#define CP0_TAGLO  $28
#define CP0_TAGHI  $29

#define Index_Store_Tag_D			0x09
#define Index_Invalidate_I			0x00
#define Index_Writeback_Inv_D			0x01

/*
 *   Register usage:
 *
 *	s0	link versus load offset, used to relocate absolute adresses.
 *	s1	free
 *	s2	memory size.
 *	s3	free.
 *	s4	Bonito base address.
 *	s5	dbg.
 *	s6	sdCfg.
 *	s7	rasave.
 *	s8	L3 Cache size.
 */

#define	DSR_ADDR	0xa1000000   /* 0x80100000 */

	.set	noreorder
    .set mips32
	.globl	_start
	.globl	start
	.globl	__main
_start:
start:
	.globl	stack
stack = start - 0x4000		/* Place PMON stack below PMON start in RAM */

/* NOTE!! Not more that 16 instructions here!!! Right now it's FULL! */
	mtc0	zero, COP_0_STATUS_REG
	mtc0	zero, COP_0_CAUSE_REG
	li	t0, SR_BOOT_EXC_VEC	/* Exception to Boostrap Location */
	mtc0	t0, COP_0_STATUS_REG
	la	sp, stack
	la	gp, _gp

	
#config pll div for cpu and sdram
	li	t0, 0xbfe78030
	li	t1, 0x2
	sw	t1, 0x4(t0)

	li	t1, (0x80000008 | (PLL_M << 8) | (0x3 << 2) | SDRAM_DIV)
	sw	t1, 0x0(t0)

	li	t1, (0x8003 | (CPU_DIV << 8 ))  //cpu div 
	sw	t1, 0x4(t0)
	
	/*  config 50M hz  cam_clk */
#if 0
	li  t1,	0x908c83bf
	sw 	t1,	0x4(t0)
#endif
	DELAY(2000)

#include "sdram_cfg.S"
    li  t1, 0xbfd00410
    li  a1, SD_PARA0		
	sw  a1, 0x0(t1)
    
	li  a1, SD_PARA1
#	li 	a1, 0x24e
    sw  a1, 0x4(t1)
	DELAY(1000)

	/* sunyoung_yg: 20150702 */
#if	(NAND_BOOT | SDIO_BOOT)

	#if SDIO_BOOT
		#include "sdio_boot.S"
	#endif
	#if	NAND_BOOT
		#include "nand_boot.S"
	#endif
	/*     end       */
1:	la	t0, start
	la	t1, real_bin
	sub	t1, t0

	li	t0, 0x81000000 #DSR_ADDR 	#0xa1000000
	add	t1, t0
	jr	t1
	nop
real_bin:
#endif

	bal	uncached		/* Switch to uncached address space */
	nop

	bal	locate			/* Get current execute address */
	nop

uncached:
	or	ra, UNCACHED_MEMORY_ADDR
	j	ra
	nop

LEAF(tgt_putchar)
	nop
	la	v0, COM_BASE
1:
	lbu	v1, NSREG(NS16550_LSR)(v0)
	and	v1, LSR_TXRDY
	beqz	v1, 1b
	nop

	sb	a0, NSREG(NS16550_DATA)(v0)
	j	ra
	nop	
END(tgt_putchar)

LEAF(stringserial)
	nop
	move	a2, ra
	addu	a1, a0, s0
	lbu	a0, 0(a1)
1:
	beqz	a0, 2f
	nop
	bal	tgt_putchar
	addiu	a1, 1
	b	1b
	lbu	a0, 0(a1)

2:
	j	a2
	nop
END(stringserial)

LEAF(hexserial_lr)
	move	a2, ra
	move	a1, a0
	li	a3, 7
1:
	rol	a0, a1, 4
	move	a1, a0
	and	a0, 0xf
	la	v0, hexchar
	addu	v0, s0
	addu	v0, a0
	bal	tgt_putchar
	lbu	a0, 0(v0)

	bnez	a3, 1b
	addu	a3, -1

	li a0,'\r'
	bal	tgt_putchar
	nop

	li a0,'\n'
	bal	tgt_putchar
	nop

	j	a2
	nop
END(hexserial)

v380_msg:
	.asciz	"\r\nPANIC! Unexpected General exception!\r\nepc,cause,status,errorpc:\r\n"
hexchar:
	.ascii	"0123456789abcdef"

	.org 0x380
	li	a0,0x10000000 /*test from 0xbfcxxxxx or 0xff20xxxx */
	and	a0,ra
	bnez	a0,1f
	la	a0,_start
	li	s0,0xbfc00000
	subu	s0,a0
1:
	la	a0, v380_msg
	bal	stringserial
	nop
	mfc0	a0, COP_0_EXC_PC
	bal	hexserial_lr
	nop
	mfc0	a0, COP_0_CAUSE_REG
	bal	hexserial_lr
	nop
	mfc0	a0, COP_0_STATUS_REG
	bal	hexserial_lr
	nop
	mfc0	a0, COP_0_ERROR_PC
	bal	hexserial_lr
	nop
1:
    b   1b
    nop

    .org 0x400
	.word read
	.word write
	.word open
	.word close
	.word nullfunction
	.word printf
	.word vsprintf
	.word nullfunction
	.word nullfunction
	.word getenv
	.word nullfunction
	.word nullfunction
	.word nullfunction
	.word nullfunction


/*
 *  We get here from executing a bal to get the PC value of the current execute
 *  location into ra. Check to see if we run from ROM or if this is ramloaded.
 */
locate:
	la	s0,	uncached
	subu	s0,ra,s0

	#bal	CPU_TLBClear
	#nop
	li	t0,SR_BOOT_EXC_VEC | SR_COP_1_BIT  #enable  float lpu#
	mtc0	t0,COP_0_STATUS_REG
    mtc0    zero,COP_0_CAUSE_REG
	.set noreorder

#if  (SPI_BOOT)
	/*spi speed*/
	li  t0, 0xbfe80000
	li  t1, 0x1f	// div 4, fast_read + burst_en + memory_en double I/O 模式 部分SPI flash可能不支持
	sb  t1, 0x4(t0)	// sfc_param
	li  t1, 0x05
	sb  t1, 0x6(t0)

#endif

####### config serial uart pad ######
##### uart 0 gpio74/75 mux 2 #####

	li	t1, 0xbfd011c0		
	lw	t2, 0x8(t1)
	li  t3,	~(0x3<<10)
	and t2, t2,	t3
	sw	t2, 0x8(t1)

	li	t1, 0xbfd011d0		
	lw	t2, 0x8(t1)
	li  t3,	(0x3<<10)
	or t2, t2,	t3
	sw	t2, 0x8(t1)

	li	t1, 0xbfd011e0		
	lw	t2, 0x8(t1)
	li  t3,	~(0x3<<10)
	and t2, t2,	t3
	sw	t2, 0x8(t1)

	li	t1, 0xbfd011f0		
	lw	t2, 0x8(t1)
	li  t3,	~(0x3<<10)
	and t2, t2,	t3
	sw	t2, 0x8(t1)

	li	t1, 0xbfd01200		
	lw	t2, 0x8(t1)
	li  t3,	~(0x3<<10)
	and t2, t2,	t3
	sw	t2, 0x8(t1)

##### uart2/3 config mux gpio #####
	li	t1, 0xbfd011c0		#
	li	t2, 0x0
	sw	t2, 0x4(t1)

	li	t1, 0xbfd011d0		
	li	t2, 0x36			#gpio 34,35 for uart3 ,gpio36,37 for uart2
	sw	t2, 0x4(t1)

	li	t1, 0xbfd011e0		
	li	t2, 0x0
	sw	t2, 0x4(t1)

	li	t1, 0xbfd011f0		
	li	t2, 0x0
	sw	t2, 0x4(t1)

	li	t1, 0xbfd01200		
	li	t2, 0x0
	sw	t2, 0x4(t1)


	/* disable all gpio */
    li  t1, 0xbfd00000
    sw  zero, 0x10c0(t1)
    sw  zero, 0x10c4(t1)
    sw  zero, 0x10c8(t1)
/**************************************************************************
 *config gpio 38 is gpio, no default func, so uart0 rx can receive 
 *因为旧的1C300A芯片上uart0rx的默认管教是gpio38，而在1C300B上，
 ×gpio38没有引出到芯片外，故需要将其设置位gpio功能。（下面的几行代码）
 *
 ***************************************************************************/
	li  t1,	0xbfd010c0
	li  t3, 0x40
	sw  t3, 0x4(t1)


	bal	initserial
	nop

	PRINTSTR("\r\n sdram init done \r\n")
	PRINTSTR("\r\sd_freq=")
	li	a0,SD_FREQ
	bal	hexserial
	nop
	PRINTSTR("\r\nSDRAM_PARAM_DIV_NUM=")
	li	a0,SDRAM_PARAM_DIV_NUM
	bal	hexserial
	nop
	PRINTSTR("\r\nPLL_M=")
	li	a0,PLL_M
	bal	hexserial
	nop

	PRINTSTR("\r\n 0xbfd00414 = ")
	li  t1, 0xbfd00410
    lw a0, 0x4(t1)
    bal hexserial
    nop
    
    PRINTSTR("\r\n 0xbfd00410 = ")
	lw a0, 0x0(t1)    
    bal hexserial
    nop


	PRINTSTR("\r\nuncached=")
	la	a0,uncached
	bal	hexserial
	nop

	PRINTSTR("\r\nra=")
	la	a0,uncached
	add a0, a0, s0
	bal	hexserial
	nop

	PRINTSTR("\r\ns0=")
    add a0, s0, 0
	bal	hexserial
	nop
	
	PRINTSTR("\r\nstart=")
	la a0,start
	bal	hexserial
	nop
	PRINTSTR("\r\nlocate=")
	la a0,locate
	bal	hexserial
	nop


	PRINTSTR("\r\nPMON2000 MIPS Initializing. Standby...\r\n")

	PRINTSTR("ERRORPC=")
	mfc0	a0, COP_0_ERROR_PC
	bal	hexserial
	nop

	PRINTSTR(" CONFIG, select 1=")
    .set mips32
    mfc0    t5, CP0_CONFIG, 1
    add a0, t5, 0
    bal hexserial
    nop

#	mfc0	a0, COP_0_CONFIG
#	bal	hexserial
#	nop

	PRINTSTR("\r\n")
	
	PRINTSTR(" PRID=")
	mfc0	a0, COP_0_PRID
	bal	hexserial
	nop
	PRINTSTR("\r\n")

	

	bnez s0,1f
	nop
    li a0,64  /*Mhz*/
	jal initmips
	nop
1:

	
set_msize:
        li      msize,0x04000000 #64MB
#        li      msize,0x02000000  #32MB

/********* init caches *******/
do_caches:
	TTYDBG("Init caches...\r\n")

	li	s7, 0                   /* no L2 cache */
	li	s8, 0                   /* no L3 cache */

	TTYDBG("godson1 caches found\r\n")
    bal     cache_init
    nop

	mfc0   a0, COP_0_CONFIG
	and    a0, a0, ~((1<<12) | 7)
	or     a0, a0, 2
	mtc0   a0, COP_0_CONFIG

	TTYDBG("Init caches done, cfg = ")
	mfc0	a0, COP_0_CONFIG
	bal	hexserial
	nop
	TTYDBG("\r\n")

/*copy copy program to sdram to make copy fast*/
#if (SPI_BOOT)
	la t0,121f
	addu t0,s0
	la t1,122f
	addu t1,s0
	
	li t2,0xa0000000
1:
	lw  v0,(t0)
	sw v0,(t2)
	addu t0,4
	addu t2,4
	ble t0,t1,1b
	nop

	li t0,0xa0000000
   	jr t0	
	nop		

.align 3
/* run in sdram */
121: 
	FCALL_PRINTSTR("Copy PMON to execute location...\r\n")
	la	a0, start
	addu a1,a0,s0
	la	a2, _edata
        or      a0, 0xa0000000
        or      a2, 0xa0000000
	subu	t1, a2, a0
	srl	t1, t1, 2

	move	t0, a0
	move	t1, a1
	move	t2, a2

	/* copy text section */
1:	and	t3,t0,0x0000ffff
	bnez	t3,2f
	nop
	move	a0,t0
	BAL(hexserial)
	nop
	li	a0,'\r'
	BAL(tgt_putchar)
	nop
2:	lw	t3, 0(t1)
	nop
	sw	t3, 0(t0)
	addu	t0, 4
	addu	t1, 4
	bne	t2, t0, 1b
	nop
	FCALL_PRINTSTR("\ncopy text section done.\r\n")
	
#endif
	/* Clear BSS */
	la	a0, _edata
	la	a2, _end
2:	sw	zero, 0(a0)
	bne	a2, a0, 2b
	addu	a0, 4


	FCALL_PRINTSTR("Copy PMON to execute location done.\r\n")
	FCALL_PRINTSTR("sp=");
	move a0, sp
	BAL(hexserial)
	nop

	li	a0, 0
	sw	a0, CpuTertiaryCacheSize /* Set L3 cache size */

	move	a0,msize
	srl	a0,20

	la	v0, initmips
#	addu v0, s0  /* no add*/ 
	jalr	v0
	nop

.align 3
122:

stuck:
	b	stuck
	nop

/*
 *  Clear the TLB. Normally called from start.S.
 */
#if __mips64
#define MTC0 dmtc0
#else 
#define MTC0 mtc0
#endif


LEAF(CPU_TLBClear)
	li	a3, 0			# First TLB index.

	li	a2, PG_SIZE_4K
	MTC0   a2, COP_0_TLB_PG_MASK   # Whatever...

1:
	MTC0   zero, COP_0_TLB_HI	# Clear entry high.
	MTC0   zero, COP_0_TLB_LO0	# Clear entry low0.
	MTC0   zero, COP_0_TLB_LO1	# Clear entry low1.

	mtc0    a3, COP_0_TLB_INDEX	# Set the index.
	addiu	a3, 1
	li	a2, 64
	nop
	nop
	tlbwi				# Write the TLB

	bne	a3, a2, 1b
	nop

	jr	ra
	nop
END(CPU_TLBClear)

/*
 *  Set up the TLB. Normally called from start.S.
 */
LEAF(CPU_TLBInit)
	li	a3, 0			# First TLB index.

	li	a2, PG_SIZE_16M
	MTC0   a2, COP_0_TLB_PG_MASK   # All pages are 16Mb.

1:
	and	a2, a0, PG_SVPN
	MTC0   a2, COP_0_TLB_HI	# Set up entry high.

	move	a2, a0
	srl	a2, a0, PG_SHIFT 
	and	a2, a2, PG_FRAME
	ori	a2, PG_IOPAGE
	MTC0   a2, COP_0_TLB_LO0	# Set up entry low0.
	addu	a2, (0x01000000 >> PG_SHIFT)
	MTC0   a2, COP_0_TLB_LO1	# Set up entry low1.

	mtc0    a3, COP_0_TLB_INDEX	# Set the index.
	addiu	a3, 1
	li	a2, 0x02000000
	subu	a1, a2
	nop
	tlbwi				# Write the TLB

	bgtz	a1, 1b
	addu	a0, a2			# Step address 32Mb.

	jr	ra
	nop
END(CPU_TLBInit)


LEAF(outstring)
	move	a2, ra
	move	a1, a0
	lbu	a0, 0(a1)
1:
	beqz	a0, 2f
	nop
	bal	tgt_putchar
	addiu	a1, 1
	b	1b
	lbu	a0, 0(a1)

2:
	j	a2
	nop
END(outstring)

LEAF(hexserial)
	nop
	move	a2, ra
	move	a1, a0
	li	a3, 7
1:
	rol	a0, a1, 4
	move	a1, a0
	and	a0, 0xf
	la	v0, hexchar
	addu	v0, s0
	addu	v0, a0
	bal	tgt_putchar
	lbu	a0, 0(v0)

	bnez	a3, 1b
	addu	a3, -1

	j	a2
	nop
END(hexserial)

LEAF(tgt_testchar)
	la	v0, COM_BASE
1:
	lbu	v1, NSREG(NS16550_LSR)(v0)
	and	v0,v1, LSR_RXRDY
	jr ra
	nop
END(tgt_testchar)

LEAF(tgt_getchar)
	la	v0, COM_BASE
1:
	lbu	v1, NSREG(NS16550_LSR)(v0)
	and	v1, LSR_RXRDY
	beqz	v1, 1b
	nop
	lb	v0, NSREG(NS16550_DATA)(v0)
	jr ra
	nop
END(tgt_getchar)


/* baud rate definitions, matching include/termios.h */
#define B0      0
#define B50     50      
#define B75     75
#define B110    110
#define B134    134
#define B150    150
#define B200    200
#define B300    300
#define B600    600
#define B1200   1200
#define B1800   1800
#define B2400   2400
#define B4800   4800
#define B9600   9600
#define B19200  19200
#define B38400  38400
#define B57600  57600
#define B115200 115200

LEAF(initserial)
	la	v0, COM_BASE
1:
	li	v1, FIFO_ENABLE|FIFO_RCV_RST|FIFO_XMT_RST|FIFO_TRIGGER_1
	sb	v1, NSREG(NS16550_FIFO)(v0)
	li	v1, CFCR_DLAB
	sb	v1, NSREG(NS16550_CFCR)(v0)
 	li	v1, SD_FREQ*1000000/(16*CONS_BAUD)
	sb	v1, NSREG(NS16550_DATA)(v0)
	srl	v1, 8
	sb	v1, NSREG(NS16550_IER)(v0)
	li	v1, CFCR_8BITS
	sb	v1, NSREG(NS16550_CFCR)(v0)
	li	v1, MCR_DTR|MCR_RTS
	sb	v1, NSREG(NS16550_MCR)(v0)
	li	v1, 0x0
	sb	v1, NSREG(NS16550_IER)(v0)
        
        #disable all interrupt
        li      v1, 0x0
        sb      v1, NSREG(NS16550_IER)(v0)
	j	ra
	nop
END(initserial)

__main:
	j	ra
	nop


	.rdata
transmit_pat_msg:
	.asciz	"\r\nInvalid transmit pattern.  Must be DDDD or DDxDDx\r\n"
v200_msg:
	.asciz	"\r\nPANIC! Unexpected TLB refill exception!\r\n"
v280_msg:
	.asciz	"\r\nPANIC! Unexpected XTLB refill exception!\r\n"
v400_msg:
	.asciz	"\r\nPANIC! Unexpected Interrupt exception!\r\n"
v480_msg:
	.asciz	"\r\nPANIC! You have been in the Ejtag Debug MOde Trap is 0!\r\n"

	.text
	.align	2
/*
 *   I2C Functions used in early startup code to get SPD info from
 *   SDRAM modules. This code must be entirely PIC and RAM independent.
 */






LEAF(nullfunction)
	jr ra
	nop
END(nullfunction)




	.ent		cache_init
	.global	cache_init
	.set		noreorder
cache_init:
	move t1, ra
####part 2####
cache_detect_4way:
	.set	mips32
	mfc0	t4, CP0_CONFIG,1
	lui		v0, 0x7		//v0 = 0x7 << 16
	and		v0, t4, v0    
	srl		t3, v0, 16    //t3 = v0 >> 16  Icache组相联数 IA

	li		t5, 0x800 		//32*64
	srl		v1, t4,22		//v1 = t4 >> 22
	andi	v1, 7			//Icache每路的组数 64x2^S IS
	sll		t5, v1			//InstCacheSetSize
	sll		t5, t3			//t5 InstCacheSize


	andi	v0, t4, 0x0380
	srl		t7, v0, 7		//DA

	li		t6, 0x800 #32*64
	srl		v1, t4,13
	andi	v1, 7			//DS
	sll		t6, v1  #DataCacheSetSize
	sll		t6, t7  #t5 DataCacheSize

####part 3####
#	.set	mips3
	lui		a0, 0x8000			//a0 = 0x8000 << 16
	addu	a1, $0, t5
	addu	a2, $0, t6
cache_init_d2way:
/******************************/	//lxy
//	addiu	t3, t3, 1
//	li	t4, 0
//5:
/******************************/
#a0=0x80000000, a1=icache_size, a2=dcache_size
#a3, v0 and v1 used as local registers
	mtc0	$0, CP0_TAGHI
	addu	v0, $0, a0		//v0 = 0 + a0
	addu	v1, a0, a2		//v1 = a0 + a2
1:	slt		a3, v0, v1		//a3 = v0 < v1 ? 1 : 0
	beq		a3, $0, 1f		//if (a3 == 0) goto 1f
	nop
	mtc0	$0, CP0_TAGLO
	cache	Index_Store_Tag_D, 0x0(v0)	# 1 way
4:	beq		$0, $0, 1b
	addiu	v0, v0, 0x20
1:
cache_flush_i2way:
	addu	v0, $0, a0
	addu	v1, a0, a1
1:	slt		a3, v0, v1
	beq		a3, $0, 1f
	nop
	cache	Index_Invalidate_I, 0x0(v0)	# 1 way
4:	beq		$0, $0, 1b
	addiu	v0, v0, 0x20
1:
cache_flush_d2way:
	addu	v0, $0, a0
	addu	v1, a0, a2
1:	slt		a3, v0, v1
	beq		a3, $0, 1f
	nop
	cache	Index_Writeback_Inv_D, 0x0(v0) 	#1 way
4:	beq		$0, $0, 1b
	addiu	v0, v0, 0x20
/******************************/	//lxy
//	addiu	t4, t4, 1
//	addiu	a0, a0, 1
//	slt		t5, t4, t3
//	bne		t5, $0, 5b
//	nop
/******************************/
//	.set	mips0

1:
cache_init_finish:
	jr	t1
	nop
	.set	reorder
	.end	cache_init



#####################################################
#if 0 
LEAF(ENABLE_CACHE)
#		".set mips2;\n" \
     mfc0   $4,$16
     and    $4,$4,0xfffffff8
     or     $4,$4,0x3
     mtc0   $4,$16
	 jr	ra
	 nop
END(ENABLE_CACHE)

LEAF(FLUSH_CACHE2)
#   .set mips3;\n" \
	mfc0	$3, $15 #;			# read processor ID register;\n" \
 	li		$2, 0x6303 #;				#godson2f prid;\n" \
 	beq		$2, $3, godson_2f #;\n" \
 	nop #;\n" \
	li		$2, 0x6302 #;				#godson2e prid;\n" \
	bne	$2, $3,11f #;\n" \
	nop #;\n" \
# godson2e;\n" \
    godson_2f: #" \
	li	  $2, 0x80000000 #;\n" \
    addu  $3,$2,512*1024/4 #;\n" \
10:\n" \
	cache	3, 0($2) #;\n" \
	cache	3, 1($2) #;\n" \
	cache	3, 2($2) #;\n" \
	cache	3, 3($2) #;\n" \
	addu	$2, 32   #;\n" \
	bne	    $2,$3, 10b #;\n" \
	nop  #;\n" \
11:
	jr ra
	nop
END(FLUSH_CACHE2)	

#ifndef WAYBIT
#define WAYBIT 0
#endif
#define WAY__(x) #x
#define WAY_(x,y) WAY__((x<<y))
#define WAY(x) WAY_(x,WAYBIT)
LEAF(FLUSH_CACHE)

		.set mips3 
        li    $5,0x81000000 #;\n" 
        addu  $6,$5, 16384   #;\n" 
1:  
        cache  1," WAY(0) "($5) #;\n" 
        cache  1," WAY(1) "($5) #;\n" 
        cache  1," WAY(2) "($5) #;\n" 
        cache  1," WAY(3) "($5) #;\n" 
        cache  0," WAY(0) "($5) #;\n" 
        cache  0," WAY(1) "($5) #;\n" 
        cache  0," WAY(2) "($5) #;\n" 
        cache  0," WAY(3) "($5) #;\n" 
        add    $5,$5,32         #;\n" 
        bne    $5,$6,1b         #;\n" 
        nop                     #;\n" 
# replace	   
		cache  1,	0($5) #;\n" 
        cache  1,	1($5) #;\n" 
        cache  1,	2($5) #;\n" 
        cache  1,	3($5) #;\n" 
        cache  0,	0($5) #;\n" 
        cache  0,	1($5) #;\n" 
        cache  0,	2($5) #;\n" 
        cache  0,	3($5) #;\n" 
		add    $5,$5,32         #;\n" 
        bne    $5,$6,1b         #;\n" 
        nop           

		lui	a0, 0x8000
		addu	a1, $0, t5
		addu	a2, $0, t6
#a0=0x80000000, a1=icache_size, a2=dcache_size
#a3, v0 and v1 used as local registers
		mtc0	$0, CP0_TAGHI
		addu	v0, $0, a0
		cache	Index_Invalidate_I, 0x0(v0)	# 1 way
	
		mtc0	$0, CP0_TAGLO
		addu	v0, $0, a0
		cache	Index_Invalidate_I, 0x0(v0)	# 1 way
#	cache	Index_Store_Tag_D, 0x0(v0)	# 1 way
	
		li		a1,	0
		mtc0  	a1, CP0_TAGHI
		mtc0  	a1, CP0_TAGLO
/* ################################################ */
#a0=0x80000000, a1=icache_size, a2=dcache_size
#a3, v0 and v1 used as local registers
		li		a0,	0x80000000
		li		a1,	16384
		li		a2,	16384

    	mtc0   $0, CP0_TAGHI
    	
		addu   v0, $0, a0  ###??? $0 = 0
	    addu   v1, a0, a2
	1:  slt a3, v0, v1
		beq a3, $0, 1f
		nop
		mtc0   $0, CP0_TAGLO
		cache Index_Store_Tag_D, 0x0(v0)
	    mtc0   $0, CP0_TAGLO
		cache Index_Store_Tag_D, 0x1(v0)
	    mtc0   $0, CP0_TAGLO
		cache   Index_Store_Tag_D, 0x2(v0)
	    mtc0   $0, CP0_TAGLO
		cache   Index_Store_Tag_D, 0x3(v0)
	    beq $0, $0, 1b   ###???
		addiu v0, v0, 0x10
1:		jr	ra
		nop
##		.set mips0;\n" 
END(FLUSH_CACHE)
#endif

##include "gmac_test.S"
