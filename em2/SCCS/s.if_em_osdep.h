h55981
s 00020/00005/00168
d D 1.2 07/05/30 00:52:03 mrym 2 1
c 2.4.0
e
s 00173/00000/00000
d D 1.1 06/07/29 22:12:45 mrym 1 0
c date and time created 06/07/29 22:12:45 by mrym
e
u
U
f e 0
t
T
I 1
/*
 * %W% %E%
D 2
 * Copyright (c) 2006 Masayuki Murayama.  All rights reserved.
E 2
I 2
 * Copyright (c) 2006-2007 Masayuki Murayama.  All rights reserved.
E 2
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer. 
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 * 
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

/**************************************************************************

Copyright (c) 2001-2006, Intel Corporation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 3. Neither the name of the Intel Corporation nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/

#ifndef _SOLARIS_OS_H_
#define _SOLARIS_OS_H_

#include <sys/types.h>
#include <sys/debug.h>
#include <sys/errno.h>
#include <sys/dditypes.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
I 2
#include <sys/ethernet.h>
E 2

#include <sys/pci.h>

#include "gem.h"
#include "mii.h"

#define usec_delay(x)		drv_usecwait(x)
#define msec_delay(x)		drv_usecwait(1000*(x))
#define msec_delay_irq(x)	drv_usecwait(1000*(x))

/************/

/* TODO: Should we be paranoid about delaying in interrupt context? */

#define MSGOUT(S, A, B)     printf(S "\n", A, B)
#define DEBUGFUNC(F)        DEBUGOUT(F);
#if DBG
	#define DEBUGOUT(S)         printf(S "\n")
	#define DEBUGOUT1(S,A)      printf(S "\n",A)
	#define DEBUGOUT2(S,A,B)    printf(S "\n",A,B)
	#define DEBUGOUT3(S,A,B,C)  printf(S "\n",A,B,C)
	#define DEBUGOUT7(S,A,B,C,D,E,F,G)  printf(S "\n",A,B,C,D,E,F,G)
#else
	#define DEBUGOUT(S)
	#define DEBUGOUT1(S,A)
	#define DEBUGOUT2(S,A,B)
	#define DEBUGOUT3(S,A,B,C)
	#define DEBUGOUT7(S,A,B,C,D,E,F,G)
#endif

#define FALSE               B_FALSE
#define TRUE                B_TRUE
#define CMD_MEM_WRT_INVALIDATE          0x0010  /* BIT_4 */
#define PCI_COMMAND_REGISTER            PCIR_COMMAND

#define E1000_WRITE_FLUSH(a) E1000_READ_REG(a, STATUS)

/* Read from an absolute offset in the adapter's memory space */
#define E1000_READ_OFFSET(hw, offset) \
    INL((struct gem_dev *)(hw)->back, offset)

/* Write to an absolute offset in the adapter's memory space */
#define E1000_WRITE_OFFSET(hw, offset, value) \
    OUTL((struct gem_dev *)(hw)->back, offset, value)

/* Convert a register name to its offset in the adapter's memory space */
#define E1000_REG_OFFSET(hw, reg) \
    ((hw)->mac_type >= em_82543 ? E1000_##reg : E1000_82542_##reg)

/* Register READ/WRITE macros */

#define E1000_READ_REG(hw, reg) \
    INL((struct gem_dev *)(hw)->back, \
        ((hw)->mac_type >= em_82543 ? E1000_##reg : E1000_82542_##reg))

#define E1000_WRITE_REG(hw, reg, value) \
    OUTL((struct gem_dev *)(hw)->back, \
        ((hw)->mac_type >= em_82543 ? E1000_##reg : E1000_82542_##reg), \
	value)

#define E1000_READ_REG_ARRAY(hw, reg, index) \
    INL((struct gem_dev *)(hw)->back, \
        ((hw)->mac_type >= em_82543 ? E1000_##reg : E1000_82542_##reg) \
        + ((index) << 2))

#define E1000_WRITE_REG_ARRAY(hw, reg, index, value) \
    OUTL((struct gem_dev *)(hw)->back, \
        ((hw)->mac_type >= em_82543 ? E1000_##reg : E1000_82542_##reg) \
        + ((index) << 2), value)

#define E1000_READ_REG_ARRAY_DWORD E1000_READ_REG_ARRAY
#define E1000_WRITE_REG_ARRAY_DWORD E1000_WRITE_REG_ARRAY

#define E1000_WRITE_REG_ARRAY_BYTE(hw, reg, index, value) \
    OUTB((struct gem_dev *)(hw)->back, \
        ((hw)->mac_type >= em_82543 ? E1000_##reg : E1000_82542_##reg \
        + index), value)

#define E1000_WRITE_REG_ARRAY_WORD(hw, reg, index, value) \
    OUTW((struct gem_dev *)(hw)->back, \
        ((hw)->mac_type >= em_82543 ? E1000_##reg : E1000_82542_##reg \
        + (index << 1)), value)

I 2
#define	HW_EMDEV(hw)	((struct em_dev *) \
		(((struct gem_dev *) (hw)->back)->private))

E 2
#define E1000_READ_ICH8_REG(hw, reg) \
D 2
    INL((struct gem_dev *)(hw)->back, reg)
E 2
I 2
	em_flash_read((void *)(hw), reg)
E 2

#define E1000_READ_ICH8_REG16(hw, reg) \
D 2
    INW((struct gem_dev *)(hw)->back, reg)
E 2
I 2
	em_flash_readw((void *)(hw), reg)
E 2

#define E1000_WRITE_ICH8_REG(hw, reg, value) \
D 2
    OUTL((struct gem_dev *)(hw)->back, reg, value)
E 2
I 2
	em_flash_write((void *)(hw), reg, value)
E 2

#define E1000_WRITE_ICH8_REG16(hw, reg, value) \
D 2
    OUTW((struct gem_dev *)(hw)->back, reg, value)
E 2
I 2
	em_flash_writew((void *)(hw), reg, value)
E 2

I 2
#define E1000_READ_ICH_FLASH_REG	E1000_READ_ICH8_REG
#define E1000_READ_ICH_FLASH_REG16	E1000_READ_ICH8_REG16
#define E1000_WRITE_ICH_FLASH_REG	E1000_WRITE_ICH8_REG
#define E1000_WRITE_ICH_FLASH_REG16	E1000_WRITE_ICH8_REG16

E 2
#undef SEC

I 2
struct em_hw;
uint16_t em_flash_readw(struct em_hw *hw, unsigned long port);
void em_flash_writew(struct em_hw *hw, unsigned long port, uint16_t value);
uint32_t em_flash_read(struct em_hw *hw, unsigned long port);
void em_flash_write(struct em_hw *hw, unsigned long port, uint32_t value);

E 2
#endif  /* _SOLARIS_OS_H_ */

E 1
