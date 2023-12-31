/*	$Id: generic_poll.c,v 1.1.1.1 2006/09/14 01:59:08 root Exp $ */

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

#include <sys/types.h>
#include <stdio.h>
#include <sys/device.h>
#include <stdlib.h>

#include <machine/cpu.h>
#include <machine/pio.h>

#include <pmon.h>

volatile int spl;

struct poll_handle {
	struct poll_handle *next;
	int	level;
	int	(*func) __P((void *));
	void	*arg;
};

struct poll_handle *poll_list;

void *
tgt_poll_register(level, func, arg)
	 int level;
	 int(*func) __P((void *));
	 void *arg;
{
	struct poll_handle *newpoll;

	newpoll = malloc(sizeof(struct poll_handle));
	if(newpoll == NULL) {
		printf("tgt_poll_register failed!");
		return(NULL);
	}
	newpoll->level = level;
	newpoll->func = func;
	newpoll->arg = arg;
	newpoll->next = poll_list;
	poll_list = newpoll;

    printf("\nIn register function level is %d, func address is %x, arg addresss is %x, newpoll address is %x\n", level, func, arg, newpoll);

	return(newpoll);
}

void
tgt_poll()
{
	struct poll_handle *nextpoll;

	if(spl != 0) {
		return;
	}

	spl = 7;

	nextpoll = poll_list;

	while(nextpoll) { 
        //printf("\nIn tgt_poll function, nextpoll address is %x, func address is %x\n", nextpoll, *nextpoll->func);
		(*nextpoll->func)(nextpoll->arg);
		nextpoll = nextpoll->next;
	}

	spl = 0;
}
