h58026
s 00333/00157/03825
d D 1.5 13/11/22 01:34:19 mrym 5 4
c 2.6.1 (I217 tested)
e
s 02696/01038/01286
d D 1.4 12/07/29 22:50:30 mrym 4 3
c 2.6.0
e
s 00204/00116/02120
d D 1.3 07/05/30 00:51:06 mrym 3 2
c 2.4.0
e
s 00387/00144/01849
d D 1.2 06/09/19 23:15:32 mrym 2 1
c 2.3.0
e
s 01993/00000/00000
d D 1.1 06/07/29 22:03:17 mrym 1 0
c date and time created 06/07/29 22:03:17 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 3
 *  em_gem.c : Intel 8254x giga ethernet MAC driver for Solaris
E 3
I 3
D 4
 *  em_gem.c : Intel 8254x gigabit ethernet MAC driver for Solaris
E 4
I 4
 *  em_gem.c : Intel 8254x/8257x/8258x gigabit ethernet MAC driver for Solaris
E 4
E 3
 *
D 3
 * Copyright (c) 2006 Masayuki Murayama.  All rights reserved.
E 3
I 3
D 4
 * Copyright (c) 2006-2007 Masayuki Murayama.  All rights reserved.
E 3
 * 
E 4
I 4
D 5
 * Copyright (c) 2006-2011 Masayuki Murayama.  All rights reserved.
E 5
I 5
 * Copyright (c) 2006-2013 Masayuki Murayama.  All rights reserved.
E 5
 *
E 4
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 4
 * 
E 4
I 4
 *
E 4
 * 1. Redistributions of source code must retain the above copyright notice,
D 4
 *    this list of conditions and the following disclaimer. 
 * 
E 4
I 4
 *    this list of conditions and the following disclaimer.
 *
E 4
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 4
 *    and/or other materials provided with the distribution. 
 * 
E 4
I 4
 *    and/or other materials provided with the distribution.
 *
E 4
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 4
 *    specific prior written permission. 
 * 
E 4
I 4
 *    specific prior written permission.
 *
E 4
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

/* Original copyright of FreeBSD em driver */

/**************************************************************************

D 4
Copyright (c) 2001-2006, Intel Corporation
E 4
I 4
Copyright (c) 2001-2009, Intel Corporation
E 4
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

#pragma	ident	"%W% %E%"

/*
D 4
 CHANGE LOG:

E 4
I 4
 * TODO:
 * fix e1000_osdep.c
 * prepare two different version of em_init_chip for new and legacy chipset
E 4
 */

/*
D 4
 TODO:
D 2
fix VLAN
fix interrupt mask for 82547 workaround
fix tx fifo control for 82547 workaround
E 2
I 2
fix VLAN - done
fix interrupt mask for 82547 workaround - done
fix tx fifo control for 82547 workaround - done
E 2

 */

/*
E 4
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 4
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 4
#include <sys/kmem.h>
D 4
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 4
#include <sys/modctl.h>
#include <sys/errno.h>
D 4
#include <sys/dditypes.h>
E 4
#include <sys/ddi.h>
#include <sys/sunddi.h>
D 4

E 4
#include <sys/byteorder.h>
D 4

E 4
I 4
#include <sys/ethernet.h>
E 4
#include <sys/pci.h>
D 4
#include "mii.h"
E 4
I 4

#include "gem_mii.h"
E 4
#include "gem.h"
D 4
#include "if_em_hw.h"
E 4
I 4
#include "e1000_api.h"
E 4

I 4
#include "e1000_osdep.h"

E 4
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

D 4
char	ident[] = "i8254x driver v" VERSION;
E 4
I 4
char	ident[] = "i8254x driver v" VERSION ;
E 4

/* Debugging support */
#ifdef DEBUG_LEVEL
static int em_debug = DEBUG_LEVEL;
D 4
# if DEBUG_LEVEL > 4
#    define	CONS	"^"
#  else
#    define	CONS	"!"
#  endif
#define	DPRINTF(n, args)	if (em_debug>(n)) cmn_err args
E 4
I 4
#if DEBUG_LEVEL > 4
#define	CONS	"^"
E 4
#else
#define	CONS	"!"
I 4
#endif
#define	DPRINTF(n, args)	if (em_debug > (n)) cmn_err args
#else
#define	CONS	"!"
E 4
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
#define	ONESEC			(drv_usectohz(1*1000000))

#define	ROUNDUP(x, a)		(((x) + (a) - 1) & ~((a) - 1))
D 4
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))
E 4
I 4
#define	roundup2(x, a)		ROUNDUP(x, a)
E 4

#ifdef MAP_MEM
D 4
#define	FLSHB(dp,reg)		INB(dp, reg)
#define	FLSHW(dp,reg)		INW(dp, reg)
#define	FLSHL(dp,reg)		INL(dp, reg)
E 4
I 4
#define	FLSHB(dp, reg)		INB(dp, reg)
#define	FLSHW(dp, reg)		INW(dp, reg)
#define	FLSHL(dp, reg)		INL(dp, reg)
E 4
#else
D 4
#define	FLSHB(dp,reg)
#define	FLSHW(dp,reg)
#define	FLSHL(dp,reg)
E 4
I 4
#define	FLSHB(dp, reg)
#define	FLSHW(dp, reg)
#define	FLSHL(dp, reg)
E 4
#endif /* MAP_MEM */

D 4
#ifdef sun4u
#define	LE64(x)	ddi_swap64(x)
#define	LE32(x)	ddi_swap32(x)
#define	LE16(x)	ddi_swap16(x)
#else
#define	LE64(x)	((uint64_t) (x))
#define	LE32(x)	((uint32_t) (x))
#define	LE16(x)	((uint16_t) (x))
#endif
E 4
I 4
#define	offsetof(t, m)	((long)&(((t *)0)->m))
E 4

I 5
#define	CONFIG_LEM

E 5
D 4
#define	offsetof(t, m)	((long) &(((t *) 0)->m))
E 4
I 4
/* Tunables */
E 4

/*
D 4
 * Our configuration
E 4
I 4
 * E1000_TXD: Maximum number of Transmit Descriptors
 * Valid Range: 80-256 for 82542 and 82543-based adapters
 *              80-4096 for others
 * Default Value: 256
 *   This value is the number of transmit descriptors allocated by the driver.
 *   Increasing this value allows the driver to queue more transmits. Each
 *   descriptor is 16 bytes.
 *   Since TDLEN should be multiple of 128bytes, the number of transmit
 *   desscriptors should meet the following condition.
 *      (num_tx_desc * sizeof (struct e1000_tx_desc)) % 128 == 0
E 4
 */
D 4
/* number of tx and rx descriptors are multiple of 8 */
#ifndef	TX_BUF_SIZE
#define	TX_BUF_SIZE	256
#endif
#ifndef	TX_RING_SIZE
#define	TX_RING_SIZE	256
#endif
#if TX_RING_SIZE > 256
#  error "TX_RING_SIZE > 256"
#endif
E 4
I 4
#define	EM_MIN_TXD		80
#define	EM_MAX_TXD_82543	256
#define	EM_MAX_TXD		4096
#define	EM_DEFAULT_TXD		EM_MAX_TXD_82543
E 4

D 4
#ifndef	RX_RING_SIZE
#define	RX_RING_SIZE	256
E 4
I 4
/*
 * E1000_RXD - Maximum number of receive Descriptors
 * Valid Range: 80-256 for 82542 and 82543-based adapters
 *              80-4096 for others
 * Default Value: 256
 *   This value is the number of receive descriptors allocated by the driver.
 *   Increasing this value allows the driver to buffer more incoming packets.
 *   Each descriptor is 16 bytes.  A receive buffer is also allocated for each
 *   descriptor. The maximum MTU size is 16110.
 *   Since TDLEN should be multiple of 128bytes, the number of transmit
 *   desscriptors should meet the following condition.
 *      (num_tx_desc * sizeof (struct e1000_tx_desc)) % 128 == 0
 */
#define	EM_MIN_RXD		80
#define	EM_MAX_RXD_82543	256
#define	EM_MAX_RXD		4096
#define	EM_DEFAULT_RXD		EM_MAX_RXD_82543

/*
 * EM_TIDV - Transmit Interrupt Delay Value
 * Valid Range: 0-65535 (0=off)
 * Default Value: 64
 *   This value delays the generation of transmit interrupts in units of
 *   1.024 microseconds. Transmit interrupt reduction can improve CPU
 *   efficiency if properly tuned for specific network traffic. If the
 *   system is reporting dropped transmits, this value may be set too high
 *   causing the driver to run out of available transmit descriptors.
 */
#define	EM_TIDV				64

/*
 * EM_TADV - Transmit Absolute Interrupt Delay Value
 * (Not valid for 82542/82543/82544)
 * Valid Range: 0-65535 (0=off)
 * Default Value: 64
 *   This value, in units of 1.024 microseconds, limits the delay in which a
 *   transmit interrupt is generated. Useful only if E1000_TIDV is non-zero,
 *   this value ensures that an interrupt is generated after the initial
 *   packet is sent on the wire within the set amount of time.  Proper tuning,
 *   along with E1000_TIDV, may improve traffic throughput in specific
 *   network conditions.
 */
#define	EM_TADV				64

/*
 * EM_RDTR - Receive Interrupt Delay Timer (Packet Timer)
 * Valid Range: 0-65535 (0=off)
 * Default Value: 0
 *   This value delays the generation of receive interrupts in units of 1.024
 *   microseconds.  Receive interrupt reduction can improve CPU efficiency if
 *   properly tuned for specific network traffic. Increasing this value adds
 *   extra latency to frame reception and can end up decreasing the throughput
 *   of TCP traffic. If the system is reporting dropped receives, this value
 *   may be set too high, causing the driver to run out of available receive
 *   descriptors.
 *
 *   CAUTION: When setting E1000_RDTR to a value other than 0, adapters
 *            may hang (stop transmitting) under certain network conditions.
 *            If this occurs a WATCHDOG message is logged in the system
 *            event log. In addition, the controller is automatically reset,
 *            restoring the network connection. To eliminate the potential
 *            for the hang ensure that E1000_RDTR is set to 0.
 */
#define	EM_RDTR				0

/*
 * Receive Interrupt Absolute Delay Timer (Not valid for 82542/82543/82544)
 * Valid Range: 0-65535 (0=off)
 * Default Value: 64
 *   This value, in units of 1.024 microseconds, limits the delay in which a
 *   receive interrupt is generated. Useful only if E1000_RDTR is non-zero,
 *   this value ensures that an interrupt is generated after the initial
 *   packet is received within the set amount of time.  Proper tuning,
 *   along with E1000_RDTR, may improve traffic throughput in specific network
 *   conditions.
 */
#define	EM_RADV				64

/*
 * Inform the stack about transmit checksum offload capabilities.
 */
#define	E1000_CHECKSUM_FEATURES		(CSUM_TCP | CSUM_UDP)

#ifdef E1000_TSO
/*
 * Inform the stack about transmit segmentation offload capabilities.
 */
#define	E1000_TCPSEG_FEATURES		CSUM_TSO
E 4
#endif
D 4
#ifndef	RX_BUF_SIZE
#define	RX_BUF_SIZE	(RX_RING_SIZE - 1)
#endif
#if RX_RING_SIZE > 256
#  error "RX_RING_SIZE > 256"
#endif
E 4

D 4
#define	EM_TIDV		64
#define	EM_TADV		64
#define	EM_RDTR		0
#define	EM_RADV		64
#ifdef CONFIG_OO
#define	MAXTXFRAGS	1
E 4
I 4
/*
 * This parameter controls the duration of transmit watchdog timer.
 */
#define	E1000_TX_TIMEOUT		5	/* set to 5 seconds */

/*
 * This parameter controls when the driver calls the routine to reclaim
 * transmit descriptors.
 */
#define	E1000_TX_CLEANUP_THRESHOLD	(adapter->num_tx_desc / 8)
#define	E1000_TX_OP_THRESHOLD		(adapter->num_tx_desc / 32)

/*
 * This parameter controls whether or not autonegotation is enabled.
 *              0 - Disable autonegotiation
 *              1 - Enable  autonegotiation
 */
#define	DO_AUTO_NEG			1

/*
 * This parameter control whether or not the driver will wait for
 * autonegotiation to complete.
 *              1 - Wait for autonegotiation to complete
 *              0 - Don't wait for autonegotiation to complete
 */
#define	WAIT_FOR_AUTO_NEG_DEFAULT	0

/* Tunables -- End */

#define	AUTONEG_ADV_DEFAULT	\
	(ADVERTISE_10_HALF | ADVERTISE_10_FULL | \
	ADVERTISE_100_HALF | ADVERTISE_100_FULL | \
	ADVERTISE_1000_FULL)

#define	AUTO_ALL_MODES		0

/* PHY master/slave setting */
#define	E1000_MASTER_SLAVE		e1000_ms_hw_default

#define	E1000_VENDOR_ID			0x8086
#define	E1000_FLASH			0x0014 /* Flash memory on ICH8 */

#define	E1000_JUMBO_PBA			0x00000028
#define	E1000_DEFAULT_PBA		0x00000030
#define	E1000_SMARTSPEED_DOWNSHIFT	3
#define	E1000_SMARTSPEED_MAX		15
#define	E1000_MAX_INTR			10

#define	MAX_NUM_MULTICAST_ADDRESSES	128
#define	PCI_ANY_ID			(~0U)
#define	ETHER_ALIGN			2
#define	E1000_TX_BUFFER_SIZE		((uint32_t)1514)
#define	E1000_FC_PAUSE_TIME		0x0680
#define	EM_EEPROM_APME			0x400
#define	EM_82544_APME			0x0004

/*
 * TDBA/RDBA should be aligned on 16 byte boundary. But TDLEN/RDLEN should be
 * multiple of 128 bytes. So we align TDBA/RDBA on 128 byte boundary. This will
 * also optimize cache line size effect. H/W supports up to cache line size 128.
 */
#define	E1000_DBA_ALIGN			128

#define	SPEED_MODE_BIT (1<<21)		/* On PCI-E MACs only */

/* PCI Config defines */
#define	E1000_BAR_TYPE(v)		((v) & E1000_BAR_TYPE_MASK)
#define	E1000_BAR_TYPE_MASK		0x00000001
#define	E1000_BAR_TYPE_MMEM		0x00000000
#define	E1000_BAR_TYPE_IO		0x00000001
#define	E1000_BAR_MEM_TYPE(v)		((v) & E1000_BAR_MEM_TYPE_MASK)
#define	E1000_BAR_MEM_TYPE_MASK		0x00000006
#define	E1000_BAR_MEM_TYPE_32BIT	0x00000000
#define	E1000_BAR_MEM_TYPE_64BIT	0x00000004

/* additional macros from if_e1000.h */
#define	E1000_TX_HEAD_ADDR_SHIFT	7
#define	E1000_PBA_BYTES_SHIFT	0xA

I 5
#define	PCIR_EXPRESS_DEVICE_CTL		0x8
#define	PCIR_EXPRESS_LINK_CAP		0xc
#define	PCIR_EXPRESS_LINK_CTL		0x10
#define	PCIM_EXP_CTL_MAX_READ_REQUEST	0x7000
#define	PCIM_EXP_CTL_MAX_PAYLOAD	0x00e0
#define	PCIM_LINK_CAP_ASPM		0x00000c00

E 5
/* ========================================================== */
/*
 *  Tunable default values.
 */
/* ========================================================== */

#define	E1000_TICKS_TO_USECS(ticks)	((1024 * (ticks) + 500) / 1000)
#define	E1000_USECS_TO_TICKS(usecs)	((1000 * (usecs) + 512) / 1024)
#define	M_TSO_LEN	66		/* mbuf with just hdr and TSO pkthdr */

#define EM_MAX_SCATTER		32
#define EM_VFTA_SIZE		128
#define EM_TSO_SIZE		(65535 + sizeof(struct ether_vlan_header))
#define EM_TSO_SEG_SIZE		4096	/* Max dma segment size */
#define EM_MSIX_MASK		0x01F00000 /* For 82574 use */
#define EM_MSIX_LINK		0x01000000 /* For 82574 use */
#define ETH_ZLEN		60
#define ETH_ADDR_LEN		6
#define CSUM_OFFLOAD		7	/* Offload bits in mbuf flag */

/*
 * 82574 has a nonstandard address for EIAC
 * and since its only used in MSIX, and in
 * the em driver only 82574 uses MSIX we can
 * solve it just using this define.
 */
#define	EM_EIAC	0x000DC

static int e1000_tx_int_delay_dflt = E1000_TICKS_TO_USECS(EM_TIDV);
static int e1000_rx_int_delay_dflt = E1000_TICKS_TO_USECS(EM_RDTR);
static int e1000_tx_abs_int_delay_dflt = E1000_TICKS_TO_USECS(EM_TADV);
static int e1000_rx_abs_int_delay_dflt = E1000_TICKS_TO_USECS(EM_RADV);
static int em_rxd = EM_DEFAULT_RXD;
static int em_txd = EM_DEFAULT_TXD;
static int e1000_smart_pwr_down = FALSE;

/* How many packets rxeof tries to clean at a time */
static int e1000_rx_process_limit = 100;

/*
 * Our configuration
 */
#ifdef GEM_CONFIG_TX_DIRECT
#define	MAXTXFRAGS	(min(GEM_MAXTXFRAGS, 8))	/* LSO is not supported */
E 4
#else
D 4
#define	MAXTXFRAGS	GEM_MAXTXFRAGS
E 4
I 4
#define	MAXTXFRAGS	1
E 4
#endif
#define	MAXRXFRAGS	1

I 2
#ifdef CONFIG_USE_TXDWB
E 2
D 4
#define	OUR_INTR_BITS	(E1000_IMS_RXT0 | E1000_IMS_TXDW | \
			 E1000_IMS_RXDMT0 | E1000_IMS_RXSEQ | E1000_IMS_LSC)
E 4
I 4
#define	OUR_INTR_BITS	\
	(E1000_IMS_RXT0 | E1000_IMS_TXDW | \
	| E1000_IMS_RXSEQ | E1000_IMS_RXO | E1000_IMS_LSC)
E 4
I 2
#else
D 4
#define	OUR_INTR_BITS	(E1000_IMS_RXT0 | E1000_ICR_TXQE | \
			 E1000_IMS_RXDMT0 | E1000_IMS_RXSEQ | E1000_IMS_LSC)
E 4
I 4
#define	OUR_INTR_BITS	\
	(E1000_IMS_RXT0 | E1000_ICR_TXQE | \
	E1000_IMS_RXDMT0 | E1000_IMS_RXSEQ | E1000_IMS_RXO | E1000_IMS_LSC)
E 4
#endif
E 2

I 2
#define	EM_FIFO_HDR	0x10

I 4
#define	EM_CORE_LOCK(adapter)
#define	EM_CORE_UNLOCK(adapter)

E 4
E 2
static int	em_tx_copy_thresh = 256;
static int	em_rx_copy_thresh = 256;

D 4
#define E1000_TICKS_TO_USECS(ticks)     ((1024 * (ticks) + 500) / 1000)
#define E1000_USECS_TO_TICKS(usecs)     ((1000 * (usecs) + 512) / 1024)
E 4
I 4
#define	E1000_TICKS_TO_USECS(ticks)	((1024 * (ticks) + 500) / 1000)
#define	E1000_USECS_TO_TICKS(usecs)	((1000 * (usecs) + 512) / 1024)
E 4
D 2
#if 0
E 2
I 2
#if 1
E 2
static int em_tx_int_delay_dflt = E1000_TICKS_TO_USECS(EM_TIDV);
static int em_rx_int_delay_dflt = E1000_TICKS_TO_USECS(EM_RDTR);
static int em_tx_abs_int_delay_dflt = E1000_TICKS_TO_USECS(EM_TADV);
static int em_rx_abs_int_delay_dflt = E1000_TICKS_TO_USECS(EM_RADV);
#else
static int em_tx_int_delay_dflt = 0;
static int em_rx_int_delay_dflt = E1000_TICKS_TO_USECS(EM_RDTR);
static int em_tx_abs_int_delay_dflt = 0;
static int em_rx_abs_int_delay_dflt = E1000_TICKS_TO_USECS(EM_RADV);
#endif
D 3
#ifdef CONFIG_PCIE
E 3
I 3

E 3
static int em_smart_pwr_down = B_FALSE;
I 4
static int global_quad_port_a = 0;
E 4
D 3
#endif
E 3

/*
 * Chip dependant MAC state
 */
struct em_dev {
D 4
	/* private data for em_hw module */
	struct em_hw		hw;
E 4
I 4
	/* private data for e1000_hw module */
	struct e1000_hw		hw;
E 4

	/* memory maps for registers */
I 4
	ddi_acc_handle_t	reg_ha;
E 4
	void			*io_base;
	ddi_acc_handle_t	io_ha;
	ddi_acc_handle_t	conf_ha;
I 3
D 4
	void			*flash_base;
E 4
	ddi_acc_handle_t	flash_ha;
E 3

	uint32_t		tx_fifo_head;
	uint32_t		tx_head_addr;
I 4
	uint32_t		tx_fifo_size;
E 4
D 2
	uint32_t		tx_fifo_size;
E 2
I 2
	uint32_t		tx_fifo_thresh;
	boolean_t		tx_fifo_full;
	int			tx_fifo_reset_cnt;
	timeout_id_t		txfifo_watcher_id;
E 2

I 2
	boolean_t		nic_active;
	int			tx_head;
	int			tx_tail;
	int			tx_tail_real;
D 4

E 2
	uint32_t		part_num;
E 4
	boolean_t		pcix_82544;

	int			tx_int_delay;
	int			rx_int_delay;
	int			tx_abs_int_delay;
	int			rx_abs_int_delay;

	/* register shadows */
	uint32_t		our_intr_mask;
	uint32_t		rctl;

	uint32_t		txd_cmd;
D 5
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
I 5
#if defined(CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
D 4
	int			tx_cksum_ctx;
# define	TX_CTX_NONE	0
# define	TX_CTX_TCP	1
# define	TX_CTX_UDP	2
E 4
I 4
	struct e1000_context_desc	tx_ctx;
E 4
#endif
D 3

E 3
I 3
	uint32_t		pba;
I 4

	size_t			dev_spec_size;
	int			smartspeed;

	int			min_frame_size;
	int			max_frame_size;

	/* workarea for multicast */
	uint8_t			mta[GEM_MAXMC * ETHERADDRL];

	uint8_t			pcie_offset;
	uint8_t			pme_offset;
#ifdef CONFIG_NEW_EM
	boolean_t		msix;
#endif
I 5
#ifdef CONFIG_SEPARETE_PHY
E 5
	int32_t			(*setup_link)();
I 5
#endif
E 5
	boolean_t		has_manage;
	uint32_t		wol;
	boolean_t		has_amt;

	struct e1000_hw_stats	stats;
I 5

	uint16_t		fc;
E 5
E 4
E 3
};

/* ======================================================== */
D 2
 
E 2
I 2
D 4
/* local operations */ 
E 4
I 4
/* local operations */
E 4
static void em_txfifo_watcher(void *arg);
static int em_82547_tx_fifo_reset(struct gem_dev *dp);
static void em_txfifo_restart(struct gem_dev *dp);
I 4
static int em_enable_phy_wakeup(struct em_dev *adapter);
static void em_mii_config_param(struct gem_dev *dp);
E 4

E 2
/* mii operations */
static void  em_mii_sync(struct gem_dev *);
static uint16_t  em_mii_read(struct gem_dev *, uint_t);
static void em_mii_write(struct gem_dev *, uint_t, uint16_t);
/* nic operations */
static int em_reset_chip(struct gem_dev *);
D 3
static void em_init_chip(struct gem_dev *);
static void em_start_chip(struct gem_dev *);
E 3
I 3
static int em_init_chip(struct gem_dev *);
static int em_start_chip(struct gem_dev *);
E 3
static int em_stop_chip(struct gem_dev *);
D 3
static void em_set_media(struct gem_dev *);
static void em_set_rx_filter(struct gem_dev *);
static void em_get_stats(struct gem_dev *);
E 3
I 3
static int em_set_media(struct gem_dev *);
static int em_set_rx_filter(struct gem_dev *);
static int em_get_stats(struct gem_dev *);
E 3
static int em_attach_chip(struct gem_dev *);

/* descriptor operations */
static int em_tx_desc_write(struct gem_dev *dp, int slot,
D 4
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq);
E 4
I 4
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t intreq);
E 4
static void em_tx_start(struct gem_dev *dp, int slot, int frags);
static void em_rx_desc_write(struct gem_dev *dp, int slot,
D 4
		    ddi_dma_cookie_t *dmacookie, int frags);
E 4
I 4
    ddi_dma_cookie_t *dmacookie, int frags);
E 4
static void em_rx_start(struct gem_dev *dp, int slot, int frags);
D 4
static uint_t em_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 4
I 4
#ifdef GEM_CONFIG_TX_HEAD_PTR
static uint_t em_tx_desc_head(struct gem_dev *);
#else
static uint_t em_tx_desc_stat(struct gem_dev *, int, int);
#endif
E 4
static uint64_t em_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);

static void em_tx_desc_init(struct gem_dev *dp, int slot);
static void em_rx_desc_init(struct gem_dev *dp, int slot);

/* interrupt handler */
D 4
static u_int em_interrupt(struct gem_dev *dp);
E 4
I 4
static uint_t em_interrupt(struct gem_dev *dp);
E 4

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr em_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr em_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t em_dma_attr_buf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	0, /* patched later */	/* dma_attr_align */
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	0, /* patched later */	/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t em_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
D 4
	16,			/* dma_attr_align */
E 4
I 4
	E1000_DBA_ALIGN,	/* dma_attr_align */
E 4
	0xffffffff,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/* ======================================================== */
/*
 * HW manupilation routines
 */
/* ======================================================== */
I 4
uint8_t
e1000_reg_read8(struct e1000_hw *hw, unsigned long port)
{
	struct em_dev	*lp = hw->back;

	return (ddi_get8(lp->reg_ha,
	    (uint8_t *)(((long)hw->hw_addr) + port)));
}

uint16_t
e1000_reg_read16(struct e1000_hw *hw, unsigned long port)
{
	struct em_dev	*lp = hw->back;

	return (ddi_get16(lp->reg_ha,
	    (uint16_t *)(((long)hw->hw_addr) + port)));
}

E 4
uint32_t
D 4
em_io_read(struct em_hw *hw, unsigned long port)
E 4
I 4
e1000_reg_read32(struct e1000_hw *hw, unsigned long port)
E 4
{
D 4
	struct gem_dev	*dp = (struct gem_dev *) hw->back;
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = hw->back;
E 4

D 3
	return ddi_get32(lp->io_ha,
			(uint32_t *) (((long) lp->io_base) + port));
E 3
I 3
D 4
	return (ddi_get32(lp->io_ha,
			(uint32_t *) (((long) lp->io_base) + port)));
E 4
I 4
	return (ddi_get32(lp->reg_ha,
	    (uint32_t *)(((long)hw->hw_addr) + port)));
E 4
E 3
}

void
D 4
em_io_write(struct em_hw *hw, unsigned long port, uint32_t value)
E 4
I 4
e1000_reg_write8(struct e1000_hw *hw, unsigned long port, uint8_t value)
E 4
{
D 2
	struct gem_dev *dp = (struct gem_dev *) hw->back;
E 2
I 2
D 4
	struct gem_dev	*dp = (struct gem_dev *) hw->back;
E 2
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = hw->back;
E 4

D 4
	ddi_put32(lp->io_ha,
		(uint32_t *) (((long) lp->io_base) + port), value);
E 4
I 4
	ddi_put8(lp->reg_ha,
	    (uint8_t *)(((long)hw->hw_addr) + port), value);
E 4
}

I 3
D 4
uint16_t
em_flash_readw(struct em_hw *hw, unsigned long port)
E 4
I 4
void
e1000_reg_write16(struct e1000_hw *hw, unsigned long port, uint16_t value)
E 4
{
D 4
	struct gem_dev	*dp = (struct gem_dev *) hw->back;
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = hw->back;
E 4

D 4
	return (ddi_get16(lp->flash_ha,
			(uint16_t *) (((long) lp->flash_base) + port)));
E 4
I 4
	ddi_put16(lp->reg_ha,
	    (uint16_t *)(((long)hw->hw_addr) + port), value);
E 4
}

E 3
void
I 3
D 4
em_flash_writew(struct em_hw *hw, unsigned long port, uint16_t value)
E 4
I 4
e1000_reg_write32(struct e1000_hw *hw, unsigned long port, uint32_t value)
E 4
{
D 4
	struct gem_dev	*dp = (struct gem_dev *) hw->back;
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = hw->back;
E 4

D 4
	ddi_put16(lp->flash_ha,
		(uint16_t *) (((long) lp->flash_base) + port), value);
E 4
I 4
	ddi_put32(lp->reg_ha,
	    (uint32_t *)(((long)hw->hw_addr) + port), value);
E 4
}

uint32_t
D 4
em_flash_read(struct em_hw *hw, unsigned long port)
E 4
I 4
e1000_io_read32(struct e1000_hw *hw, unsigned long port)
E 4
{
D 4
	struct gem_dev	*dp = (struct gem_dev *) hw->back;
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = hw->back;
E 4

D 4
	return (ddi_get32(lp->flash_ha,
			(uint32_t *) (((long) lp->flash_base) + port)));
E 4
I 4
	ddi_put32(lp->io_ha,
	    (uint32_t *)((long)lp->io_base), port);
	return (ddi_get32(lp->io_ha,
	    (uint32_t *)(((long)lp->io_base) + 4)));
E 4
}

void
D 4
em_flash_write(struct em_hw *hw, unsigned long port, uint32_t value)
E 4
I 4
e1000_io_write32(struct e1000_hw *hw, unsigned long port, uint32_t value)
E 4
{
D 4
	struct gem_dev	*dp = (struct gem_dev *) hw->back;
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = hw->back;
E 4

D 4
	ddi_put32(lp->flash_ha,
		(uint32_t *) (((long) lp->flash_base) + port), value);
E 4
I 4
	ddi_put32(lp->io_ha,
	    (uint32_t *)((long)lp->io_base), port);
	ddi_put32(lp->io_ha,
	    (uint32_t *)(((long)lp->io_base) + 4), value);
E 4
}

D 4
void
E 3
em_pci_clear_mwi(struct em_hw *hw)
E 4
I 4
uint16_t
e1000_flash_read16(struct e1000_hw *hw, unsigned long port)
E 4
{
D 4
	struct gem_dev	*dp = (struct gem_dev *) hw->back;
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = hw->back;
E 4

D 4
	pci_config_put16(lp->conf_ha, PCI_CONF_COMM,
		lp->hw.pci_cmd_word & ~PCI_COMM_MEMWR_INVAL);
E 4
I 4
	return (ddi_get16(lp->flash_ha,
	    (uint16_t *)(((intptr_t)hw->flash_address) + port)));
E 4
}

D 4
void
em_pci_set_mwi(struct em_hw *hw)
E 4
I 4
uint32_t
e1000_flash_read32(struct e1000_hw *hw, unsigned long port)
E 4
{
D 4
	struct gem_dev	*dp = (struct gem_dev *) hw->back;
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = hw->back;
E 4

D 4
	pci_config_put16(lp->conf_ha, PCI_CONF_COMM,
		lp->hw.pci_cmd_word | PCI_COMM_MEMWR_INVAL);
E 4
I 4
	return (ddi_get32(lp->flash_ha,
	    (uint32_t *)(((intptr_t)hw->flash_address) + port)));
E 4
}

void
D 4
em_read_pci_cfg(struct em_hw *hw, uint32_t reg, uint16_t *valp)
E 4
I 4
e1000_flash_write16(struct e1000_hw *hw, unsigned long port, uint16_t value)
E 4
{
D 4
	struct gem_dev	*dp = (struct gem_dev *) hw->back;
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = hw->back;
E 4

D 4
	*valp = pci_config_get16(lp->conf_ha, reg);
E 4
I 4
	ddi_put16(lp->flash_ha,
	    (uint16_t *)(((intptr_t)hw->flash_address) + port), value);
E 4
}

void
D 4
em_write_pci_cfg(struct em_hw *hw, uint32_t reg, uint16_t *valp)
E 4
I 4
e1000_flash_write32(struct e1000_hw *hw, unsigned long port, uint32_t value)
E 4
{
D 4
	struct gem_dev	*dp = (struct gem_dev *) hw->back;
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = hw->back;
E 4

D 4
	pci_config_put16(lp->conf_ha, reg, *valp);
E 4
I 4
	ddi_put32(lp->flash_ha,
	    (uint32_t *)(((intptr_t)hw->flash_address) + port), value);
E 4
}

I 3
D 4
/*
 * We may eventually really do this, but its unnecessary
 * for now so we just return unsupported.
 */
int32_t
em_read_pcie_cap_reg(struct em_hw *hw, uint32_t reg, uint16_t *value)
E 4
I 4
static void
em_enable_vlans(struct gem_dev *dp)
E 4
{
D 4
	return (0);
E 4
I 4
	struct e1000_hw	*hw = &((struct em_dev *)dp->private)->hw;
	uint32_t	ctrl;

	E1000_WRITE_REG(hw, E1000_VET, 0x8100);

	ctrl = E1000_READ_REG(hw, E1000_CTRL);
	ctrl |= E1000_CTRL_VME;
	E1000_WRITE_REG(hw, E1000_CTRL, ctrl);
E 4
}
E 3

static void
I 4
em_disable_vlans(struct gem_dev *dp)
{
	struct em_dev	*lp = dp->private;
	uint32_t	ctrl;

	ctrl = E1000_READ_REG(&lp->hw, E1000_CTRL);
	ctrl &= ~E1000_CTRL_VME;
	E1000_WRITE_REG(&lp->hw, E1000_CTRL, ctrl);
}
static void
E 4
em_enable_intr(struct gem_dev *dp)
{
D 4
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = dp->private;
E 4

D 2
	E1000_WRITE_REG(&lp->hw, IMS, (IMS_ENABLE_MASK));
E 2
I 2
D 4
	E1000_WRITE_REG(&lp->hw, IMS, lp->our_intr_mask);
E 4
I 4
	if (lp->msix) {
		E1000_WRITE_REG(&lp->hw, EM_EIAC, EM_MSIX_MASK);
		lp->our_intr_mask |= EM_MSIX_MASK;
	}
	E1000_WRITE_REG(&lp->hw, E1000_IMS, lp->our_intr_mask);
E 4
E 2
}

D 4
/* HW routine */
E 4
static void
em_disable_intr(struct gem_dev *dp)
{
D 4
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = dp->private;
E 4

D 4
	/*
	 * The first version of 82542 had an errata where when link was
	 * forced it would stay up even up even if the cable was disconnected.
	 * Sequence errors were used to detect the disconnect and then the
	 * driver would unforce the link.
	 * This code in the in the ISR.  For this to work correctly the
	 * Sequence error interrupt had to be enabled all the time.
	 */

	if (lp->hw.mac_type == em_82542_rev2_0) {
		E1000_WRITE_REG(&lp->hw, IMC, (0xffffffff & ~E1000_IMC_RXSEQ));
E 4
I 4
	if (lp->msix) {
		E1000_WRITE_REG(&lp->hw, EM_EIAC, 0);
E 4
	}
D 4
	else {
		E1000_WRITE_REG(&lp->hw, IMC, 0xffffffff);
	}
E 4
I 4
	E1000_WRITE_REG(&lp->hw, E1000_IMC, 0xffffffffU);
E 4
}

D 4
static int
em_reset_chip(struct gem_dev *dp)
E 4
I 4
void
e1000_write_pci_cfg(struct e1000_hw *hw, uint32_t reg, uint16_t *valp)
E 4
{
D 4
	uint32_t	err;
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = hw->back;
E 4

D 3
	DPRINTF(4, (CE_CONT, CONS "%s: %s called", dp->name, __func__));
E 3
I 3
D 4
	DPRINTF(0, (CE_CONT, CONS "%s: %s called", dp->name, __func__));
E 4
I 4
	pci_config_put16(lp->conf_ha, reg, *valp);
}
E 4
E 3

D 4
	if (lp->hw.back == NULL) {
		/* first call, patch back */
		lp->hw.back = (void *) dp;
E 4
I 4
void
e1000_read_pci_cfg(struct e1000_hw *hw, uint32_t reg, uint16_t *valp)
{
	struct em_dev	*lp = hw->back;
E 4
D 3
		return (GEM_SUCCESS);
E 3
I 3

D 4
		/* minimum setup */
		em_get_bus_info(&lp->hw);	
E 4
I 4
	*valp = pci_config_get16(lp->conf_ha, reg);
}

void
e1000_pci_set_mwi(struct e1000_hw *hw)
{
	struct em_dev	*lp = hw->back;

	pci_config_put16(lp->conf_ha, PCI_CONF_COMM,
	    lp->hw.bus.pci_cmd_word | PCI_COMM_MEMWR_INVAL);
}

void
e1000_pci_clear_mwi(struct e1000_hw *hw)
{
	struct em_dev	*lp = hw->back;

	pci_config_put16(lp->conf_ha, PCI_CONF_COMM,
	    lp->hw.bus.pci_cmd_word & ~PCI_COMM_MEMWR_INVAL);
}
/*
 * Read the PCI Express capabilities
 */
int32_t
e1000_read_pcie_cap_reg(struct e1000_hw *hw, uint32_t reg, uint16_t *value)
{
	int32_t		error = E1000_SUCCESS;
	struct em_dev	*lp = hw->back;

	if (lp->pcie_offset != 0) {
		e1000_read_pci_cfg(&lp->hw, lp->pcie_offset + reg, value);
	} else {
		ASSERT(E1000_NOT_IMPLEMENTED != 0);
		error = E1000_NOT_IMPLEMENTED;
E 4
E 3
	}

D 4
	em_disable_intr(dp);
E 4
I 4
	return (error);
}
#if 0
int32_t
e1000_alloc_zeroed_dev_spec_struct(struct e1000_hw *hw, uint32_t size)
{
	int32_t		error = 0;
	struct em_dev	*lp = hw->back;
E 4

I 3
D 4
	lp->nic_active = B_FALSE;
E 3
	if (em_reset_hw(&lp->hw) != E1000_SUCCESS) {
		return (GEM_FAILURE);
E 4
I 4
	hw->dev_spec = kmem_alloc(size, KM_NOSLEEP);
	if (hw->dev_spec == NULL) {
		error = ENOMEM;
E 4
	}
I 4
	bzero(hw->dev_spec, size);
E 4

D 3
#ifdef CONFIG_PCIE
	/* Set up smart power down as default off on newer adapters */
	if (!em_smart_pwr_down &&
	    (lp->hw.mac_type == em_82571 ||
	     lp->hw.mac_type == em_82572)) {
		uint16_t phy_tmp = 0;
		/* speed up time to link by disabling smart power down */
		em_read_phy_reg(&lp->hw, IGP02E1000_PHY_POWER_MGMT,
			   &phy_tmp);
		phy_tmp &= ~IGP02E1000_PM_SPD;
		em_write_phy_reg(&lp->hw, IGP02E1000_PHY_POWER_MGMT,
			    phy_tmp);
	}
#endif
	lp->tx_fifo_head = 0;
I 2
	lp->tx_fifo_full = B_FALSE;
E 2

I 2
	lp->nic_active = B_FALSE;

E 3
E 2
D 4
	return (GEM_SUCCESS);
E 4
I 4
	lp->dev_spec_size = size;

	return (error);
E 4
}

I 2
D 4
static void 
em_enable_vlans(struct gem_dev *dp)
E 4
I 4
void
e1000_free_dev_spec_struct(struct e1000_hw *hw)
E 4
{
D 4
	struct em_dev	*lp = (struct em_dev *)dp->private;
	uint32_t	ctrl;
E 4
I 4
	struct em_dev	*lp = hw->back;
E 4

D 4
	E1000_WRITE_REG(&lp->hw, VET, 0x8100);

	ctrl = E1000_READ_REG(&lp->hw, CTRL);
	ctrl |= E1000_CTRL_VME; 
	E1000_WRITE_REG(&lp->hw, CTRL, ctrl);
E 4
I 4
	ASSERT(lp->dev_spec_size != 0);
	if (hw->dev_spec != NULL) {
		kmem_free(hw->dev_spec, lp->dev_spec_size);
		hw->dev_spec = NULL;
		lp->dev_spec_size = 0;
	}
E 4
}
I 4
#endif
E 4

I 4
#define	MAX_INTS_PER_SEC	8000
#define	DEFAULT_ITR		1000000000/(MAX_INTS_PER_SEC * 256)

E 4
E 2
static void
em_initialize_receive_unit(struct gem_dev *dp)
{
I 5
	uint64_t	bus_addr;
E 5
	uint32_t	reg_rctl;
	uint32_t	reg_rxcsum;
D 4
	struct em_dev	*lp = (struct em_dev *)dp->private;
E 4
I 4
D 5
	struct em_dev	*lp = dp->private;
	struct e1000_hw	*hw = &lp->hw;
E 5
I 5
	struct em_dev	*adapter = dp->private;
	struct e1000_hw	*hw = &adapter->hw;
E 5
E 4

D 4
	DPRINTF(0, (CE_CONT, "%s: %s: begin", dp->name, __func__));
E 4
I 4
	DPRINTF(0, (CE_CONT, CONS "%s %s: begin", dp->name, __func__));
E 4

	/*
D 4
	 * Make sure receives are disabled while setting up
	 * the descriptor ring.
E 4
I 4
	 * Make sure receives are disabled while setting
	 * up the descriptor ring
E 4
	 */
D 4
	E1000_WRITE_REG(&lp->hw, RCTL, 0);
E 4
I 4
	reg_rctl = E1000_READ_REG(hw, E1000_RCTL);
I 5
#ifdef CONFIG_NEW_EM
	/* Do not disable if ever enabled on this hardware */
	if ((hw->mac.type != e1000_82574) && (hw->mac.type != e1000_82583)) {
		E1000_WRITE_REG(hw, E1000_RCTL, reg_rctl & ~E1000_RCTL_EN);
	}
#else
E 5
	E1000_WRITE_REG(hw, E1000_RCTL, reg_rctl & ~E1000_RCTL_EN);
E 4
D 5

D 4
	/* Set the Receive Delay Timer Register */
	E1000_WRITE_REG(&lp->hw, RDTR, lp->rx_int_delay | E1000_RDT_FPDB);
E 4
I 4
	if (hw->mac.type >= e1000_82540) {
		E1000_WRITE_REG(hw, E1000_RADV, lp->rx_abs_int_delay);
E 5
I 5
#endif
	if (adapter->hw.mac.type >= e1000_82540) {
		E1000_WRITE_REG(&adapter->hw, E1000_RADV,
		    adapter->rx_abs_int_delay);
E 5
		/*
		 * Set the interrupt throttling rate. Value is calculated
		 * as DEFAULT_ITR = 1/(MAX_INTS_PER_SEC * 256ns)
		 */
D 5
		E1000_WRITE_REG(hw, E1000_ITR, DEFAULT_ITR);
E 5
I 5
		E1000_WRITE_REG(&adapter->hw, E1000_ITR, DEFAULT_ITR);
E 5
	}
E 4

D 4
	if(lp->hw.mac_type >= em_82540) {
		E1000_WRITE_REG(&lp->hw, RADV, lp->rx_abs_int_delay);
E 4
I 4
#ifdef CONFIG_NEW_EM
	/*
	** When using MSIX interrupts we need to throttle
	** using the EITR register (82574 only)
	*/
D 5
	if (hw->mac.type == e1000_82574 && lp->msix) {
E 5
I 5
	if (hw->mac.type == e1000_82574) {
E 5
		int	i;
		for (i = 0; i < 4; i++) {
			E1000_WRITE_REG(hw, E1000_EITR_82574(i),
			    DEFAULT_ITR);
		}
D 5
	}
E 4

D 4
		/* Set the interrupt throttling rate.  Value is calculated
		 * as DEFAULT_ITR = 1/(MAX_INTS_PER_SEC * 256ns) */
#define MAX_INTS_PER_SEC        8000
#define DEFAULT_ITR             1000000000/(MAX_INTS_PER_SEC * 256)
		E1000_WRITE_REG(&lp->hw, ITR, DEFAULT_ITR);
	}       
E 4
I 4
	/* Disable accelerated ackknowledge */
	if (hw->mac.type == e1000_82574) {
E 5
I 5
		/* Disable accelerated acknowledge */
E 5
		E1000_WRITE_REG(hw, E1000_RFCTL, E1000_RFCTL_ACK_DIS);
	}
I 5
#ifdef notyet
	if (ifp->if_capenable & IFCAP_RXCSUM) {
		rxcsum = E1000_READ_REG(hw, E1000_RXCSUM);
		rxcsum |= (E1000_RXCSUM_IPOFL | E1000_RXCSUM_TUOFL);
		E1000_WRITE_REG(hw, E1000_RXCSUM, rxcsum);
	}
E 5
#endif
I 5
	/*
	 * TEMPORARY WORKAROUND: on some systems with 82573
	 * long latencies are observed, like Lenovo X60. This
	 * change eliminates the problem, but since having positive
	 * values in RDTR is a known source of problems on other
	 * platforms another solution is being sought.
	 */
	if (hw->mac.type == e1000_82573)
		E1000_WRITE_REG(hw, E1000_RDTR, 0x20);
#endif
E 5
E 4

	/* Setup the Base and Length of the Rx Descriptor Ring */
D 4
	E1000_WRITE_REG(&lp->hw, RDLEN, 
			RX_RING_SIZE * sizeof(struct em_rx_desc));
	E1000_WRITE_REG(&lp->hw, RDBAH, (uint32_t) (dp->rx_ring_dma >> 32));
	E1000_WRITE_REG(&lp->hw, RDBAL, (uint32_t) dp->rx_ring_dma);
E 4
I 4
D 5
	E1000_WRITE_REG(hw, E1000_RDLEN(0),
	    dp->gc.gc_rx_ring_size * sizeof (struct e1000_rx_desc));
	E1000_WRITE_REG(hw, E1000_RDBAH(0),
	    (uint32_t)(dp->rx_ring_dma >> 32));
	E1000_WRITE_REG(hw, E1000_RDBAL(0),
	    (uint32_t)dp->rx_ring_dma);
E 5
I 5
	bus_addr = dp->rx_ring_dma;
	E1000_WRITE_REG(&adapter->hw, E1000_RDLEN(0),
	     dp->gc.gc_rx_ring_size * sizeof(struct e1000_rx_desc));
	E1000_WRITE_REG(&adapter->hw, E1000_RDBAH(0),
	    (u32)(bus_addr >> 32));
	E1000_WRITE_REG(&adapter->hw, E1000_RDBAL(0),
	    (u32)bus_addr);
E 5
E 4

D 4
	/* Setup the HW Rx Head and Tail Descriptor Pointers */
	E1000_WRITE_REG(&lp->hw, RDT, 0);
	E1000_WRITE_REG(&lp->hw, RDH, 0);
E 4
I 4
#ifdef CONFIG_NEW_EM
I 5
#ifdef notdef
	E1000_WRITE_REG(hw, E1000_RDT(0), dp->gc.gc_rx_ring_size - 1);
#endif

E 5
	/* Set early receive threshold on appropriate hw */
	if (((hw->mac.type == e1000_ich9lan) ||
	    (hw->mac.type == e1000_pch2lan) ||
	    (hw->mac.type == e1000_ich10lan)) &&
	    (dp->mtu > ETHERMTU)) {
		u32 rxdctl = E1000_READ_REG(hw, E1000_RXDCTL(0));
		E1000_WRITE_REG(hw, E1000_RXDCTL(0), rxdctl | 3);
		E1000_WRITE_REG(hw, E1000_ERT, 0x100 | (1 << 13));
	}
E 4

D 4
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 4
I 4
D 5
	if (hw->mac.type == e1000_pch2lan) {
E 5
I 5
	if (adapter->hw.mac.type == e1000_pch2lan) {
E 5
		if (dp->mtu > ETHERMTU) {
			e1000_lv_jumbo_workaround_ich8lan(hw, TRUE);
		} else {
			e1000_lv_jumbo_workaround_ich8lan(hw, FALSE);
		}
	}
#endif
	/* Setup the Receive Control Register */
	reg_rctl &= ~(3 << E1000_RCTL_MO_SHIFT);
	reg_rctl |= E1000_RCTL_EN | E1000_RCTL_BAM | E1000_RCTL_LBM_NO |
	    E1000_RCTL_RDMTS_HALF |
D 5
	    (hw->mac.mc_filter_type << E1000_RCTL_MO_SHIFT);
E 5
I 5
	    (adapter->hw.mac.mc_filter_type << E1000_RCTL_MO_SHIFT);
E 5

D 5
#ifdef CONFIG_NEW_EM
	if (hw->mac.type >= e1000_82571) {
		/* Strip the CRC */
		reg_rctl |= E1000_RCTL_SECRC;

		/* Make sure VLAN Filters are off */
		reg_rctl &= ~E1000_RCTL_VFE;
		reg_rctl &= ~E1000_RCTL_SBP;
	}
E 5
I 5
#ifdef CONFIG_NO_RXCRC
	/* Strip the CRC */
	reg_rctl |= E1000_RCTL_SECRC;
E 5
#endif
I 5
	/* Make sure VLAN Filters are off */
	reg_rctl &= ~E1000_RCTL_VFE;
E 5

D 5
	if (e1000_tbi_sbp_enabled_82543(hw)) {
E 5
I 5
	if (e1000_tbi_sbp_enabled_82543(&adapter->hw)) {
E 5
		reg_rctl |= E1000_RCTL_SBP;
	} else {
		reg_rctl &= ~E1000_RCTL_SBP;
	}

	switch (dp->rx_buf_len) {
	case 2048:
		reg_rctl |= E1000_RCTL_SZ_2048;
		break;

	case 4096:
		reg_rctl |= E1000_RCTL_SZ_4096 |
		    E1000_RCTL_BSEX | E1000_RCTL_LPE;
		break;

	case 8192:
	case 9234:
		reg_rctl |= E1000_RCTL_SZ_8192 |
		    E1000_RCTL_BSEX | E1000_RCTL_LPE;
		break;

	case 16384:
		reg_rctl |= E1000_RCTL_SZ_16384 |
		    E1000_RCTL_BSEX | E1000_RCTL_LPE;
		break;

	default:
		cmn_err(CE_WARN, "!%s: incorrect rx buffer size:%d",
		    dp->name, dp->rx_buf_len);
		reg_rctl |= E1000_RCTL_SZ_2048;
		break;
	}

	if (dp->mtu > ETHERMTU) {
		reg_rctl |= E1000_RCTL_LPE;
	} else {
		reg_rctl &= ~E1000_RCTL_LPE;
	}

E 4
	/* Enable 82543 Receive Checksum Offload for TCP and UDP */
D 4
	if (lp->hw.mac_type >= em_82543) {
		reg_rxcsum = E1000_READ_REG(&lp->hw, RXCSUM);
E 4
I 4
	if ((hw->mac.type >= e1000_82543) &&
	    (dp->misc_flag & GEM_VLAN_HARD)) {
		reg_rxcsum = E1000_READ_REG(hw, E1000_RXCSUM);
E 4
		reg_rxcsum |= (E1000_RXCSUM_IPOFL | E1000_RXCSUM_TUOFL);
D 4
		E1000_WRITE_REG(&lp->hw, RXCSUM, reg_rxcsum);
E 4
I 4
		E1000_WRITE_REG(hw, E1000_RXCSUM, reg_rxcsum);
E 4
	}
D 4
#endif
E 4
I 4

D 5
	/*
	 * TEMPORARY WORKAROUND: on some systems with 82573
	 * long latencies are observed, like Lenovo X60. This
	 * change eliminates the problem, but since having positive
	 * values in RDTR is a known source of problems on other
	 * platforms another solution is being sought.
	 */
	if (hw->mac.type == e1000_82573) {
		E1000_WRITE_REG(hw, E1000_RDTR, 0x20);
	}
E 5
E 4
	/* Enable Receives */
D 4
	E1000_WRITE_REG(&lp->hw, RCTL, lp->rctl);
E 4
I 4
	E1000_WRITE_REG(hw, E1000_RCTL, reg_rctl);

	DPRINTF(1, (CE_CONT, "!%s: %s: rx_buf_len:%d, rctl:0x%x",
	    dp->name, __func__, dp->rx_buf_len, reg_rctl));

	/*
	 * Setup the HW Rx Head and
	 * Tail Descriptor Pointers
	 */
	E1000_WRITE_REG(hw, E1000_RDH(0), 0);
	E1000_WRITE_REG(hw, E1000_RDT(0), 0);	/* empty */

D 5
	lp->rctl = reg_rctl;
E 5
I 5
	adapter->rctl = reg_rctl;
E 5
E 4
}

static void
D 4
em_initialize_transmit_unit(struct gem_dev *dp)
E 4
I 4
D 5
em_initialize_transmit_unit(struct gem_dev *dp)		/* ok */
E 5
I 5
em_initialize_transmit_unit(struct gem_dev *dp)
E 5
E 4
{
D 4
	uint32_t	reg_tctl;
	uint32_t	reg_tarc;
	uint32_t	reg_tipg = 0;
	struct em_dev	*lp = (struct em_dev *)dp->private;
E 4
I 4
	uint32_t	tctl, tarc, tipg = 0;
D 5
	struct em_dev	*lp = dp->private;
	struct e1000_hw	*hw = &lp->hw;
E 5
I 5
	struct em_dev	*adapter = dp->private;
	struct e1000_hw	*hw = &adapter->hw;
E 5
E 4

D 4
	DPRINTF(0, (CE_CONT, "%s: %s: begin", dp->name, __func__));

E 4
I 4
	DPRINTF(0, (CE_CONT, CONS "%s: %s: begin", dp->name, __func__));
E 4
	/* Setup the Base and Length of the Tx Descriptor Ring */
D 4
	E1000_WRITE_REG(&lp->hw, TDLEN, 
				TX_RING_SIZE * sizeof(struct em_tx_desc));
	E1000_WRITE_REG(&lp->hw, TDBAH, (uint32_t) (dp->tx_ring_dma >> 32));
	E1000_WRITE_REG(&lp->hw, TDBAL, (uint32_t) dp->tx_ring_dma);
E 4
I 4
	E1000_WRITE_REG(hw, E1000_TDLEN(0),
	    dp->gc.gc_tx_ring_size * sizeof (struct e1000_tx_desc));
	E1000_WRITE_REG(hw, E1000_TDBAH(0),
	    (uint32_t)(dp->tx_ring_dma >> 32));
	E1000_WRITE_REG(hw, E1000_TDBAL(0), (uint32_t)dp->tx_ring_dma);
E 4

	/* Setup the HW Tx Head and Tail descriptor pointers */
D 4
	E1000_WRITE_REG(&lp->hw, TDT, 0);
	E1000_WRITE_REG(&lp->hw, TDH, 0);
E 4
I 4
	E1000_WRITE_REG(hw, E1000_TDT(0), 0);
	E1000_WRITE_REG(hw, E1000_TDH(0), 0);
E 4

D 4
	DPRINTF(0, (CE_CONT, "%s: %s: Base = %x, Length = %x", 
			dp->name, __func__,
			E1000_READ_REG(&lp->hw, TDBAL),
			E1000_READ_REG(&lp->hw, TDLEN)));
E 4
I 4
	DPRINTF(2, (CE_CONT, CONS "%s %s: Base = 0x%x, Length = 0x%x",
	    dp->name, __func__,
	    E1000_READ_REG(hw, E1000_TDBAL(0)),
	    E1000_READ_REG(hw, E1000_TDLEN(0))));
E 4

	/* Set the default values for the Tx Inter Packet Gap timer */
D 4
	switch (lp->hw.mac_type) {
	case em_82542_rev2_0:
	case em_82542_rev2_1:
		reg_tipg = DEFAULT_82542_TIPG_IPGT;
		reg_tipg |= DEFAULT_82542_TIPG_IPGR1 << E1000_TIPG_IPGR1_SHIFT;
		reg_tipg |= DEFAULT_82542_TIPG_IPGR2 << E1000_TIPG_IPGR2_SHIFT;
E 4
I 4
	switch (hw->mac.type) {
	case e1000_82542:
		tipg = DEFAULT_82542_TIPG_IPGT;
		tipg |= DEFAULT_82542_TIPG_IPGR1 << E1000_TIPG_IPGR1_SHIFT;
		tipg |= DEFAULT_82542_TIPG_IPGR2 << E1000_TIPG_IPGR2_SHIFT;
E 4
		break;

D 4
	case em_80003es2lan:
		reg_tipg = DEFAULT_82543_TIPG_IPGR1;
		reg_tipg |=
		    DEFAULT_80003ES2LAN_TIPG_IPGR2 << E1000_TIPG_IPGR2_SHIFT;
                break;
E 4
I 4
	case e1000_80003es2lan:
		tipg = DEFAULT_82543_TIPG_IPGR1;
		tipg |= DEFAULT_80003ES2LAN_TIPG_IPGR2 <<
		    E1000_TIPG_IPGR2_SHIFT;
		break;
E 4

	default:
D 4
		if (lp->hw.media_type == em_media_type_fiber) {
			reg_tipg = DEFAULT_82543_TIPG_IPGT_FIBER;
E 4
I 4
D 5
		if (hw->phy.media_type == e1000_media_type_fiber ||
		    hw->phy.media_type == e1000_media_type_internal_serdes) {
E 5
I 5
		if ((adapter->hw.phy.media_type == e1000_media_type_fiber) ||
		    (adapter->hw.phy.media_type ==
		    e1000_media_type_internal_serdes))
E 5
			tipg = DEFAULT_82543_TIPG_IPGT_FIBER;
E 4
D 5
		} else {
E 5
I 5
		else
E 5
D 4
			reg_tipg = DEFAULT_82543_TIPG_IPGT_COPPER;
E 4
I 4
			tipg = DEFAULT_82543_TIPG_IPGT_COPPER;
E 4
D 5
		}
E 5
D 4
		reg_tipg |= DEFAULT_82543_TIPG_IPGR1 << E1000_TIPG_IPGR1_SHIFT;
		reg_tipg |= DEFAULT_82543_TIPG_IPGR2 << E1000_TIPG_IPGR2_SHIFT;
E 4
I 4
		tipg |= DEFAULT_82543_TIPG_IPGR1 << E1000_TIPG_IPGR1_SHIFT;
		tipg |= DEFAULT_82543_TIPG_IPGR2 << E1000_TIPG_IPGR2_SHIFT;
E 4
	}

D 4
	E1000_WRITE_REG(&lp->hw, TIPG, reg_tipg);
	E1000_WRITE_REG(&lp->hw, TIDV, lp->tx_int_delay);
	if (lp->hw.mac_type >= em_82540) {
		E1000_WRITE_REG(&lp->hw, TADV, lp->tx_abs_int_delay);
E 4
I 4
D 5
	E1000_WRITE_REG(hw, E1000_TIPG, tipg);
	E1000_WRITE_REG(hw, E1000_TIDV,
	    lp->tx_int_delay > 0 ? lp->tx_int_delay : 1);
E 5
I 5
	E1000_WRITE_REG(&adapter->hw, E1000_TIPG, tipg);
	E1000_WRITE_REG(&adapter->hw, E1000_TIDV,
	    adapter->tx_int_delay > 0 ? adapter->tx_int_delay : 1);

E 5
	if (hw->mac.type >= e1000_82540) {
D 5
		E1000_WRITE_REG(hw, E1000_TADV, lp->tx_abs_int_delay);
E 5
I 5
		E1000_WRITE_REG(&adapter->hw, E1000_TADV,
		    adapter->tx_abs_int_delay);
E 5
E 4
	}
D 4

	/* Do adapter specific tweaks before we enable the transmitter */
        if (lp->hw.mac_type == em_82571 || lp->hw.mac_type == em_82572) {
                reg_tarc = E1000_READ_REG(&lp->hw, TARC0);
                reg_tarc |= (1 << 25);
                E1000_WRITE_REG(&lp->hw, TARC0, reg_tarc);
                reg_tarc = E1000_READ_REG(&lp->hw, TARC1);
                reg_tarc |= (1 << 25);
		reg_tarc &= ~(1 << 28);
                E1000_WRITE_REG(&lp->hw, TARC1, reg_tarc);
        } else if (lp->hw.mac_type == em_80003es2lan) {
                reg_tarc = E1000_READ_REG(&lp->hw, TARC0);
                reg_tarc |= 1;
                if (lp->hw.media_type == em_media_type_internal_serdes)
                        reg_tarc |= (1 << 20);
                E1000_WRITE_REG(&lp->hw, TARC0, reg_tarc);
                reg_tarc = E1000_READ_REG(&lp->hw, TARC1);
                reg_tarc |= 1;
                E1000_WRITE_REG(&lp->hw, TARC1, reg_tarc);
E 4
I 4
D 5
	if (hw->mac.type == e1000_82571 ||
	    hw->mac.type == e1000_82572) {
		tarc = E1000_READ_REG(hw, E1000_TARC(0));
E 5
I 5
	if (adapter->hw.mac.type == e1000_82571 ||
	    adapter->hw.mac.type == e1000_82572) {
		tarc = E1000_READ_REG(&adapter->hw, E1000_TARC(0));
E 5
		tarc |= SPEED_MODE_BIT;
D 5
		E1000_WRITE_REG(hw, E1000_TARC(0), tarc);
E 5
I 5
		E1000_WRITE_REG(&adapter->hw, E1000_TARC(0), tarc);
E 5
	} else if (hw->mac.type == e1000_80003es2lan) {
D 5
		tarc = E1000_READ_REG(hw, E1000_TARC(0));
E 5
I 5
		tarc = E1000_READ_REG(&adapter->hw, E1000_TARC(0));
E 5
		tarc |= 1;
D 5
		E1000_WRITE_REG(hw, E1000_TARC(0), tarc);
		tarc = E1000_READ_REG(hw, E1000_TARC(1));
E 5
I 5
		E1000_WRITE_REG(&adapter->hw, E1000_TARC(0), tarc);
		tarc = E1000_READ_REG(&adapter->hw, E1000_TARC(1));
E 5
		tarc |= 1;
D 5
		E1000_WRITE_REG(hw, E1000_TARC(1), tarc);
E 5
I 5
		E1000_WRITE_REG(&adapter->hw, E1000_TARC(1), tarc);
E 5
E 4
	}

I 5
	/* Setup Transmit Descriptor Base Settings */
	adapter->txd_cmd = E1000_TXD_CMD_IFCS;
	if (adapter->tx_int_delay > 0)
		adapter->txd_cmd |= E1000_TXD_CMD_IDE;

E 5
	/* Program the Transmit Control Register */
D 4
	reg_tctl = E1000_TCTL_PSP | E1000_TCTL_EN |
		   (E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT);
	if (lp->hw.mac_type >= em_82571) {
		reg_tctl |= E1000_TCTL_MULR;
E 4
I 4
D 5
	tctl = E1000_READ_REG(hw, E1000_TCTL);
E 5
I 5
	tctl = E1000_READ_REG(&adapter->hw, E1000_TCTL);
E 5
	tctl &= ~E1000_TCTL_CT;
	tctl = E1000_TCTL_PSP | E1000_TCTL_RTLC | E1000_TCTL_EN |
	    (E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT);

D 5
	if (hw->mac.type >= e1000_82571) {
E 5
I 5
	if (adapter->hw.mac.type >= e1000_82571)
E 5
		tctl |= E1000_TCTL_MULR;
E 4
D 5
	}
E 5
I 5

E 5
D 4
	if (dp->full_duplex) {
		reg_tctl |= E1000_FDX_COLLISION_DISTANCE << E1000_COLD_SHIFT;
E 4
I 4
	/* This write will effectively turn on the transmit unit. */
D 5
	E1000_WRITE_REG(hw, E1000_TCTL, tctl);
E 5
I 5
	E1000_WRITE_REG(&adapter->hw, E1000_TCTL, tctl);
E 5

D 5
	/* Setup Transmit Descriptor Base Settings */
	lp->txd_cmd = E1000_TXD_CMD_IFCS;
	if (lp->tx_int_delay > 0) {
		lp->txd_cmd |= E1000_TXD_CMD_IDE;
	}
E 5
}

/*
 * Bit of a misnomer, what this really means is
 * to enable OS management of the system... aka
 * to disable special hardware management features 
 */
static void
em_init_manageability(struct gem_dev *dp)
{
	struct em_dev *adapter = dp->private;

	/* A shared code workaround */
#define E1000_82542_MANC2H E1000_MANC2H
	if (adapter->has_manage) {
		int manc2h = E1000_READ_REG(&adapter->hw, E1000_MANC2H);
		int manc = E1000_READ_REG(&adapter->hw, E1000_MANC);

		/* disable hardware interception of ARP */
		manc &= ~(E1000_MANC_ARP_EN);

                /* enable receiving management packets to the host */
		manc |= E1000_MANC_EN_MNG2HOST;
#define E1000_MNG2HOST_PORT_623 (1 << 5)
#define E1000_MNG2HOST_PORT_664 (1 << 6)
		manc2h |= E1000_MNG2HOST_PORT_623;
		manc2h |= E1000_MNG2HOST_PORT_664;
		E1000_WRITE_REG(&adapter->hw, E1000_MANC2H, manc2h);
		E1000_WRITE_REG(&adapter->hw, E1000_MANC, manc);
	}
}

/*
 * Give control back to hardware management
 * controller if there is one.
 */
static void
em_release_manageability(struct gem_dev *dp)
{
	struct em_dev *adapter = dp->private;

	if (adapter->has_manage) {
		int manc = E1000_READ_REG(&adapter->hw, E1000_MANC);

		/* re-enable hardware interception of ARP */
		manc |= E1000_MANC_ARP_EN;
		manc &= ~E1000_MANC_EN_MNG2HOST;

		E1000_WRITE_REG(&adapter->hw, E1000_MANC, manc);
	}
}

/*
 * em_get_hw_control sets the {CTRL_EXT|FWSM}:DRV_LOAD bit.
 * For ASF and Pass Through versions of f/w this means
 * that the driver is loaded. For AMT version type f/w
 * this means that the network i/f is open.
 */
static void
em_get_hw_control(struct gem_dev *dp)
{
	struct em_dev *adapter = dp->private;
	u32 ctrl_ext, swsm;

	if (adapter->hw.mac.type == e1000_82573) {
		swsm = E1000_READ_REG(&adapter->hw, E1000_SWSM);
		E1000_WRITE_REG(&adapter->hw, E1000_SWSM,
		    swsm | E1000_SWSM_DRV_LOAD);
		return;
	}
	/* else */
	ctrl_ext = E1000_READ_REG(&adapter->hw, E1000_CTRL_EXT);
	E1000_WRITE_REG(&adapter->hw, E1000_CTRL_EXT,
	    ctrl_ext | E1000_CTRL_EXT_DRV_LOAD);
	return;
}

/*
 * em_release_hw_control resets {CTRL_EXT|FWSM}:DRV_LOAD bit.
 * For ASF and Pass Through versions of f/w this means that
 * the driver is no longer loaded. For AMT versions of the
 * f/w this means that the network i/f is closed.
 */
static void
em_release_hw_control(struct gem_dev *dp)
{
	struct em_dev *adapter = dp->private;
	u32 ctrl_ext, swsm;

	if (!adapter->has_manage) {
		return;
	}

	if (adapter->hw.mac.type == e1000_82573) {
		swsm = E1000_READ_REG(&adapter->hw, E1000_SWSM);
		E1000_WRITE_REG(&adapter->hw, E1000_SWSM,
		    swsm & ~E1000_SWSM_DRV_LOAD);
		return;
	}
	/* else */
	ctrl_ext = E1000_READ_REG(&adapter->hw, E1000_CTRL_EXT);
	E1000_WRITE_REG(&adapter->hw, E1000_CTRL_EXT,
	    ctrl_ext & ~E1000_CTRL_EXT_DRV_LOAD);
}

static int
em_is_valid_ether_addr(u8 *addr)
{
	char zero_addr[6] = { 0, 0, 0, 0, 0, 0 };

	if ((addr[0] & 1) || (!bcmp(addr, zero_addr, ETHERADDRL))) {
		return (FALSE);
	}

	return (TRUE);
}

/*
 * Parse the interface capabilities with regard
 * to both system management and wake-on-lan for
 * later use.
 */
static void
em_get_wakeup(struct gem_dev *dp)
{
	struct em_dev	*adapter = dp->private;
	u16		eeprom_data = 0, device_id, apme_mask;

	adapter->has_manage = e1000_enable_mng_pass_thru(&adapter->hw);
	apme_mask = EM_EEPROM_APME;

	switch (adapter->hw.mac.type) {
	case e1000_82573:
	case e1000_82583:
		adapter->has_amt = TRUE;
		/* FALLTHRU */
	case e1000_82571:
	case e1000_82572:
	case e1000_80003es2lan:
		if (adapter->hw.bus.func == 1) {
			e1000_read_nvm(&adapter->hw,
			    NVM_INIT_CONTROL3_PORT_B, 1, &eeprom_data);
			break;
		} else {
			e1000_read_nvm(&adapter->hw,
			    NVM_INIT_CONTROL3_PORT_A, 1, &eeprom_data);
		}
		break;

	case e1000_ich8lan:
	case e1000_ich9lan:
	case e1000_ich10lan:
	case e1000_pchlan:
	case e1000_pch2lan:
		apme_mask = E1000_WUC_APME;
		adapter->has_amt = TRUE;
		eeprom_data = E1000_READ_REG(&adapter->hw, E1000_WUC);
		break;

	default:
		e1000_read_nvm(&adapter->hw,
		    NVM_INIT_CONTROL3_PORT_A, 1, &eeprom_data);
		break;
	}
	if (eeprom_data & apme_mask) {
		adapter->wol = (E1000_WUFC_MAG | E1000_WUFC_MC);
	}
	/*
         * We have the eeprom settings, now apply the special cases
         * where the eeprom may be wrong or the board won't support
         * wake on lan on a particular port
	 */
	device_id = adapter->hw.device_id;
        switch (device_id) {
	case E1000_DEV_ID_82571EB_FIBER:
		/* Wake events only supported on port A for dual fiber
		 * regardless of eeprom setting */
		if (E1000_READ_REG(&adapter->hw, E1000_STATUS) &
		    E1000_STATUS_FUNC_1) {
			adapter->wol = 0;
		}
		break;

	case E1000_DEV_ID_82571EB_QUAD_COPPER:
	case E1000_DEV_ID_82571EB_QUAD_FIBER:
	case E1000_DEV_ID_82571EB_QUAD_COPPER_LP:
                /* if quad port adapter, disable WoL on all but port A */
		if (global_quad_port_a != 0) {
			adapter->wol = 0;
		}
		/* Reset for multiple quad port adapters */
		if (++global_quad_port_a == 4) {
			global_quad_port_a = 0;
		}
                break;
	}
	return;
}

/*
 * Enable PCI Wake On Lan capability
 */
static void
em_enable_wakeup(struct gem_dev *dp)
{
	struct em_dev	*adapter = dp->private;
	u32		pmc, ctrl, ctrl_ext, rctl;
	u16     	status;
	ddi_acc_handle_t	conf_handle;

	if ((pmc = adapter->pme_offset) == 0) {
		return;
	}

	/* Advertise the wakeup capability */
	ctrl = E1000_READ_REG(&adapter->hw, E1000_CTRL);
	ctrl |= (E1000_CTRL_SWDPIN2 | E1000_CTRL_SWDPIN3);
	E1000_WRITE_REG(&adapter->hw, E1000_CTRL, ctrl);
	E1000_WRITE_REG(&adapter->hw, E1000_WUC, E1000_WUC_PME_EN);

	if ((adapter->hw.mac.type == e1000_ich8lan) ||
	    (adapter->hw.mac.type == e1000_pchlan) ||
	    (adapter->hw.mac.type == e1000_ich9lan) ||
	    (adapter->hw.mac.type == e1000_ich10lan)) {
D 5
		e1000_disable_gig_wol_ich8lan(&adapter->hw);
		e1000_hv_phy_powerdown_workaround_ich8lan(&adapter->hw);
E 5
I 5
		e1000_suspend_workarounds_ich8lan(&adapter->hw);
E 5
	}

	/* Keep the laser running on Fiber adapters */
	if (adapter->hw.phy.media_type == e1000_media_type_fiber ||
	    adapter->hw.phy.media_type == e1000_media_type_internal_serdes) {
		ctrl_ext = E1000_READ_REG(&adapter->hw, E1000_CTRL_EXT);
		ctrl_ext |= E1000_CTRL_EXT_SDP3_DATA;
		E1000_WRITE_REG(&adapter->hw, E1000_CTRL_EXT, ctrl_ext);
	}
#ifdef notyet
	/*
	 * Determine type of Wakeup: note that wol
	 * is set with all bits on by default.
	 */
	if ((ifp->if_capenable & IFCAP_WOL_MAGIC) == 0) {
		adapter->wol &= ~E1000_WUFC_MAG;
	}

	if ((ifp->if_capenable & IFCAP_WOL_MCAST) == 0) {
		adapter->wol &= ~E1000_WUFC_MC;
E 4
	} else {
D 4
		reg_tctl |= E1000_HDX_COLLISION_DISTANCE << E1000_COLD_SHIFT;
E 4
I 4
		rctl = E1000_READ_REG(&adapter->hw, E1000_RCTL);
		rctl |= E1000_RCTL_MPE;
		E1000_WRITE_REG(&adapter->hw, E1000_RCTL, rctl);
E 4
	}
D 4
	/* This write will effectively turn on the transmit unit */
	E1000_WRITE_REG(&lp->hw, TCTL, reg_tctl);
E 4
I 4
#endif
	if ((adapter->hw.mac.type == e1000_pchlan) ||
	    (adapter->hw.mac.type == e1000_pch2lan)) {
		if (em_enable_phy_wakeup(adapter)) {
			return;
		}
	} else {
		E1000_WRITE_REG(&adapter->hw, E1000_WUC, E1000_WUC_PME_EN);
		E1000_WRITE_REG(&adapter->hw, E1000_WUFC, adapter->wol);
	}
E 4

D 4
	/* Setup Transmit Descriptor Settings for this adapter */   
	lp->txd_cmd = E1000_TXD_CMD_IFCS | E1000_TXD_CMD_RS;
E 4
I 4
	if (adapter->hw.phy.type == e1000_phy_igp_3) {
		e1000_igp3_phy_powerdown_workaround_ich8lan(&adapter->hw);
	}
E 4

D 4
	if (lp->tx_int_delay > 0) {
		lp->txd_cmd |= E1000_TXD_CMD_IDE;
E 4
I 4
        /* Request PME */
        status = pci_config_get16(adapter->conf_ha, pmc + PCI_PMCSR);
	status &= ~(PCI_PMCSR_PME_STAT | PCI_PMCSR_PME_EN);
#if 0
	if (ifp->if_capenable & IFCAP_WOL) {
		status |= PCI_PMCSR_PME_STAT | PCI_PMCSR_PME_EN;
E 4
	}
I 4
#endif
        pci_config_put16(adapter->conf_ha, pmc + PCI_PMCSR, status);

	return;
E 4
}

I 4
/*
 * WOL in the newer chipset interfaces (pchlan)
 * require thing to be copied into the phy
 */
E 4
D 3
static void
E 3
I 3
static int
I 4
em_enable_phy_wakeup(struct em_dev *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 mreg, ret = 0;
	u16 preg;
	int i;

	/* copy MAC RARs to PHY RARs */
	e1000_copy_rx_addrs_to_phy_ich8lan(hw);

	/* copy MAC MTA to PHY MTA */
	for (i = 0; i < adapter->hw.mac.mta_reg_count; i++) {
		mreg = E1000_READ_REG_ARRAY(hw, E1000_MTA, i);
		e1000_write_phy_reg(hw, BM_MTA(i), (u16)(mreg & 0xFFFF));
		e1000_write_phy_reg(hw, BM_MTA(i) + 1,
		    (u16)((mreg >> 16) & 0xFFFF));
	}

	/* configure PHY Rx Control register */
	e1000_read_phy_reg(&adapter->hw, BM_RCTL, &preg);
	mreg = E1000_READ_REG(hw, E1000_RCTL);
	if (mreg & E1000_RCTL_UPE)
		preg |= BM_RCTL_UPE;
	if (mreg & E1000_RCTL_MPE)
		preg |= BM_RCTL_MPE;
	preg &= ~(BM_RCTL_MO_MASK);
	if (mreg & E1000_RCTL_MO_3)
		preg |= (((mreg & E1000_RCTL_MO_3) >> E1000_RCTL_MO_SHIFT)
				<< BM_RCTL_MO_SHIFT);
	if (mreg & E1000_RCTL_BAM)
		preg |= BM_RCTL_BAM;
	if (mreg & E1000_RCTL_PMCF)
		preg |= BM_RCTL_PMCF;
	mreg = E1000_READ_REG(hw, E1000_CTRL);
	if (mreg & E1000_CTRL_RFCE)
		preg |= BM_RCTL_RFCE;
	e1000_write_phy_reg(&adapter->hw, BM_RCTL, preg);

	/* enable PHY wakeup in MAC register */
	E1000_WRITE_REG(hw, E1000_WUC,
	    E1000_WUC_PHY_WAKE | E1000_WUC_PME_EN);
	E1000_WRITE_REG(hw, E1000_WUFC, adapter->wol);

	/* configure and enable PHY wakeup in PHY registers */
	e1000_write_phy_reg(&adapter->hw, BM_WUFC, adapter->wol);
	e1000_write_phy_reg(&adapter->hw, BM_WUC, E1000_WUC_PME_EN);

	/* activate PHY wakeup */
	ret = hw->phy.ops.acquire(hw);
	if (ret) {
		printf("Could not acquire PHY\n");
		return ret;
	}
	e1000_write_phy_reg_mdic(hw, IGP01E1000_PHY_PAGE_SELECT,
	                         (BM_WUC_ENABLE_PAGE << IGP_PAGE_SHIFT));
	ret = e1000_read_phy_reg_mdic(hw, BM_WUC_ENABLE_REG, &preg);
	if (ret) {
		printf("Could not read PHY page 769\n");
		goto out;
	}
	preg |= BM_WUC_ENABLE_BIT | BM_WUC_HOST_WU_BIT;
	ret = e1000_write_phy_reg_mdic(hw, BM_WUC_ENABLE_REG, preg);
	if (ret)
		printf("Could not set PHY Host Wakeup bit\n");
out:
	hw->phy.ops.release(hw);

	return ret;
}

static void
em_led_func(void *arg, int onoff)
{
	struct em_dev	*adapter = arg;
 
	EM_CORE_LOCK(adapter);
	if (onoff) {
		e1000_setup_led(&adapter->hw);
		e1000_led_on(&adapter->hw);
	} else {
		e1000_led_off(&adapter->hw);
		e1000_cleanup_led(&adapter->hw);
	}
	EM_CORE_UNLOCK(adapter);
}

I 5
/*
** Disable the L0S and L1 LINK states
*/
static void
em_disable_aspm(struct gem_dev *dp)
{
	struct em_dev	*adapter = dp->private;
	int		reg;
	uint16_t	link_cap,link_ctrl;

	switch (adapter->hw.mac.type) {
	case e1000_82573:
	case e1000_82574:
	case e1000_82583:
		break;
	default:
		return;
	}

	if (adapter->pcie_offset == 0) {
		return;
	}

	reg = adapter->pcie_offset + PCIR_EXPRESS_LINK_CAP;
	link_cap = pci_config_get16(adapter->conf_ha, reg);
	if ((link_cap & PCIM_LINK_CAP_ASPM) == 0) {
		return;
	}
	reg = adapter->pcie_offset + PCIR_EXPRESS_LINK_CTL;
	link_ctrl = pci_config_get16(adapter->conf_ha, reg);
	link_ctrl &= 0xFFFC; /* turn off bit 1 and 2 */
	pci_config_put16(adapter->conf_ha, reg, link_ctrl);
	return;
}
E 5
/**********************************************************************
 *
 *  Update the board statistics counters.
 *
 **********************************************************************/
static void
em_update_stats_counters(struct gem_dev *dp)
{
	struct em_dev	*adapter = dp->private;

	if(adapter->hw.phy.media_type == e1000_media_type_copper ||
	   (E1000_READ_REG(&adapter->hw, E1000_STATUS) & E1000_STATUS_LU)) {
		adapter->stats.symerrs += E1000_READ_REG(&adapter->hw, E1000_SYMERRS);
		adapter->stats.sec += E1000_READ_REG(&adapter->hw, E1000_SEC);
	}
	adapter->stats.crcerrs += E1000_READ_REG(&adapter->hw, E1000_CRCERRS);
	adapter->stats.mpc += E1000_READ_REG(&adapter->hw, E1000_MPC);
	adapter->stats.scc += E1000_READ_REG(&adapter->hw, E1000_SCC);
	adapter->stats.ecol += E1000_READ_REG(&adapter->hw, E1000_ECOL);

	adapter->stats.mcc += E1000_READ_REG(&adapter->hw, E1000_MCC);
	adapter->stats.latecol += E1000_READ_REG(&adapter->hw, E1000_LATECOL);
	adapter->stats.colc += E1000_READ_REG(&adapter->hw, E1000_COLC);
	adapter->stats.dc += E1000_READ_REG(&adapter->hw, E1000_DC);
	adapter->stats.rlec += E1000_READ_REG(&adapter->hw, E1000_RLEC);
	adapter->stats.xonrxc += E1000_READ_REG(&adapter->hw, E1000_XONRXC);
	adapter->stats.xontxc += E1000_READ_REG(&adapter->hw, E1000_XONTXC);
	/*
	** For watchdog management we need to know if we have been
	** paused during the last interval, so capture that here.
	*/
	adapter->stats.xoffrxc += E1000_READ_REG(&adapter->hw, E1000_XOFFRXC);
	adapter->stats.xofftxc += E1000_READ_REG(&adapter->hw, E1000_XOFFTXC);
	adapter->stats.fcruc += E1000_READ_REG(&adapter->hw, E1000_FCRUC);
	adapter->stats.prc64 += E1000_READ_REG(&adapter->hw, E1000_PRC64);
	adapter->stats.prc127 += E1000_READ_REG(&adapter->hw, E1000_PRC127);
	adapter->stats.prc255 += E1000_READ_REG(&adapter->hw, E1000_PRC255);
	adapter->stats.prc511 += E1000_READ_REG(&adapter->hw, E1000_PRC511);
	adapter->stats.prc1023 += E1000_READ_REG(&adapter->hw, E1000_PRC1023);
	adapter->stats.prc1522 += E1000_READ_REG(&adapter->hw, E1000_PRC1522);
	adapter->stats.gprc += E1000_READ_REG(&adapter->hw, E1000_GPRC);
	adapter->stats.bprc += E1000_READ_REG(&adapter->hw, E1000_BPRC);
	adapter->stats.mprc += E1000_READ_REG(&adapter->hw, E1000_MPRC);
	adapter->stats.gptc += E1000_READ_REG(&adapter->hw, E1000_GPTC);

	/* For the 64-bit byte counters the low dword must be read first. */
	/* Both registers clear on the read of the high dword */

	adapter->stats.gorc += E1000_READ_REG(&adapter->hw, E1000_GORCH);
	adapter->stats.gotc += E1000_READ_REG(&adapter->hw, E1000_GOTCH);

	adapter->stats.rnbc += E1000_READ_REG(&adapter->hw, E1000_RNBC);
	adapter->stats.ruc += E1000_READ_REG(&adapter->hw, E1000_RUC);
	adapter->stats.rfc += E1000_READ_REG(&adapter->hw, E1000_RFC);
	adapter->stats.roc += E1000_READ_REG(&adapter->hw, E1000_ROC);
	adapter->stats.rjc += E1000_READ_REG(&adapter->hw, E1000_RJC);

	adapter->stats.tor += E1000_READ_REG(&adapter->hw, E1000_TORH);
	adapter->stats.tot += E1000_READ_REG(&adapter->hw, E1000_TOTH);

	adapter->stats.tpr += E1000_READ_REG(&adapter->hw, E1000_TPR);
	adapter->stats.tpt += E1000_READ_REG(&adapter->hw, E1000_TPT);
	adapter->stats.ptc64 += E1000_READ_REG(&adapter->hw, E1000_PTC64);
	adapter->stats.ptc127 += E1000_READ_REG(&adapter->hw, E1000_PTC127);
	adapter->stats.ptc255 += E1000_READ_REG(&adapter->hw, E1000_PTC255);
	adapter->stats.ptc511 += E1000_READ_REG(&adapter->hw, E1000_PTC511);
	adapter->stats.ptc1023 += E1000_READ_REG(&adapter->hw, E1000_PTC1023);
	adapter->stats.ptc1522 += E1000_READ_REG(&adapter->hw, E1000_PTC1522);
	adapter->stats.mptc += E1000_READ_REG(&adapter->hw, E1000_MPTC);
	adapter->stats.bptc += E1000_READ_REG(&adapter->hw, E1000_BPTC);

	if (adapter->hw.mac.type >= e1000_82543) {
		adapter->stats.algnerrc += 
		E1000_READ_REG(&adapter->hw, E1000_ALGNERRC);
		adapter->stats.rxerrc += 
		E1000_READ_REG(&adapter->hw, E1000_RXERRC);
		adapter->stats.tncrs += 
		E1000_READ_REG(&adapter->hw, E1000_TNCRS);
		adapter->stats.cexterr += 
		E1000_READ_REG(&adapter->hw, E1000_CEXTERR);
		adapter->stats.tsctc += 
		E1000_READ_REG(&adapter->hw, E1000_TSCTC);
		adapter->stats.tsctfc += 
		E1000_READ_REG(&adapter->hw, E1000_TSCTFC);
	}
#if 0
	ifp = adapter->ifp;

	ifp->if_collisions = adapter->stats.colc;

	/* Rx Errors */
	ifp->if_ierrors = adapter->dropped_pkts + adapter->stats.rxerrc +
	    adapter->stats.crcerrs + adapter->stats.algnerrc +
	    adapter->stats.ruc + adapter->stats.roc +
	    adapter->stats.mpc + adapter->stats.cexterr;

	/* Tx Errors */
	ifp->if_oerrors = adapter->stats.ecol +
	    adapter->stats.latecol + adapter->watchdog_events;
#endif
}
/* ==================================================================== */
/*
 *  gem methods
 */
/* ==================================================================== */
static int
em_reset_chip(struct gem_dev *dp)
{
	uint32_t	err;
	struct em_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, CONS "%s: %s called", dp->name, __func__));
	ASSERT(lp->hw.back != NULL);
	ASSERT(lp->hw.hw_addr != NULL);

	em_disable_intr(dp);

	lp->nic_active = B_FALSE;
#ifdef notdef
	/* allow resetting phy */
	lp->hw.phy.reset_disable = B_FALSE;
#endif
	if (e1000_reset_hw(&lp->hw) != E1000_SUCCESS) {
		return (GEM_FAILURE);
	}

	/* When hardware is reset, fifo_head is also reset */
	lp->tx_fifo_head = 0;

	return (GEM_SUCCESS);
}

static int
E 4
E 3
em_init_chip(struct gem_dev *dp)
{
	uint32_t	val;
D 4
	struct em_dev	*lp = (struct em_dev *)dp->private;
E 4
I 4
	uint32_t	pba;
	uint32_t	rx_buffer_size;
	struct em_dev	*lp = dp->private;
	struct e1000_hw	*hw = &lp->hw;
E 4

D 3
	DPRINTF(1, (CE_CONT, CONS "%s: %s called", dp->name, __func__));
E 3
I 3
	DPRINTF(0, (CE_CONT, CONS "%s: %s called", dp->name, __func__));
E 3

I 3
D 4
	/* setup buffer allocation */
	E1000_WRITE_REG(&lp->hw, PBA, lp->pba);
E 4
I 4
	lp->nic_active = B_FALSE;
E 4

D 4
	/* Set up smart power down as default off on newer adapters */
	if (!em_smart_pwr_down &&
	    (lp->hw.mac_type == em_82571 ||
	     lp->hw.mac_type == em_82572)) {
E 4
I 4
	em_mii_config_param(dp);

	/*
	 * from em_init_locked ()
	 */

	/*
I 5
	 * from em_reset()
	 */
#ifdef CONFIG_NEW_EM
	/* Set up smart power down as default off on newer adapters. */
	if (!e1000_smart_pwr_down && (hw->mac.type == e1000_82571 ||
	    hw->mac.type == e1000_82572)) {
		uint16_t phy_tmp = 0;

		/* Speed up time to link by disabling smart power down. */
		e1000_read_phy_reg(hw,
		    IGP02E1000_PHY_POWER_MGMT, &phy_tmp);
		phy_tmp &= ~IGP02E1000_PM_SPD;
		e1000_write_phy_reg(hw,
		    IGP02E1000_PHY_POWER_MGMT, phy_tmp);
	}
#endif /* CONFIG_NEW_EM */

	/*
E 5
	 * Packet Buffer Allocation (PBA)
	 * Writing PBA sets the receive portion of the buffer
	 * the remainder is used for the transmit buffer.
	 *
	 * Devices before the 82547 had a Packet Buffer of 64K.
	 *   Default allocation: PBA=48K for Rx, leaving 16K for Tx.
	 * After the 82547 the buffer was reduced to 40K.
	 *   Default allocation: PBA=30K for Rx, leaving 10K for Tx.
	 *   Note: default does not leave enough room for Jumbo Frame >10k.
	 */
	switch (hw->mac.type) {
I 5

#ifdef CONFIG_LEM
E 5
	case e1000_82547:
	case e1000_82547_rev_2: /* 82547: Total Packet Buffer is 40K */
		if (lp->max_frame_size > 8192) {
			pba = E1000_PBA_22K; /* 22K for Rx, 18K for Tx */
		} else {
			pba = E1000_PBA_30K; /* 30K for Rx, 10K for Tx */
		}
		lp->tx_fifo_head = 0;
		lp->tx_head_addr = pba << E1000_TX_HEAD_ADDR_SHIFT;
		lp->tx_fifo_size =
		    (E1000_PBA_40K - pba) << E1000_PBA_BYTES_SHIFT;
		break;
I 5
#endif /* CONFIG_LEM */
E 5

#ifdef CONFIG_NEW_EM
	/* Total Packet Buffer on these is 48K */
	case e1000_82571:
	case e1000_82572:
	case e1000_80003es2lan:
D 5
			pba = E1000_PBA_32K; /* 32K for Rx, 16K for Tx */
E 5
I 5
		pba = E1000_PBA_32K; /* 32K for Rx, 16K for Tx */
E 5
		break;
	case e1000_82573: /* 82573: Total Packet Buffer is 32K */
D 5
			pba = E1000_PBA_12K; /* 12K for Rx, 20K for Tx */
E 5
I 5
		pba = E1000_PBA_12K; /* 12K for Rx, 20K for Tx */
E 5
		break;
	case e1000_82574:
	case e1000_82583:
D 5
			pba = E1000_PBA_20K; /* 20K for Rx, 20K for Tx */
E 5
I 5
		pba = E1000_PBA_20K; /* 20K for Rx, 20K for Tx */
E 5
		break;
	case e1000_ich8lan:
		pba = E1000_PBA_8K;
		break;
	case e1000_ich9lan:
	case e1000_ich10lan:
D 5
		pba = E1000_PBA_10K;
E 5
I 5
		/* Boost Receive side for jumbo frames */
		if (lp->max_frame_size > 4096)
			pba = E1000_PBA_14K;
		else
			pba = E1000_PBA_10K;
E 5
		break;
	case e1000_pchlan:
	case e1000_pch2lan:
I 5
	case e1000_pch_lpt:
E 5
		pba = E1000_PBA_26K;
		break;
#endif
	default:
		/* Devices before 82547 had a Packet Buffer of 64K.   */
		if (lp->max_frame_size > 8192) {
			pba = E1000_PBA_40K; /* 40K for Rx, 24K for Tx */
		} else {
			pba = E1000_PBA_48K; /* 48K for Rx, 16K for Tx */
		}
	}
D 5

E 5
	DPRINTF(0, (CE_CONT, CONS "%s: %s: pba=%dK", dp->name, __func__, pba));
	E1000_WRITE_REG(&lp->hw, E1000_PBA, pba);

	/*
D 5
	 * from em_reset()
	 */

	/* Set up smart power down as default off on newer adapters. */
	if (!e1000_smart_pwr_down && (hw->mac.type == e1000_82571 ||
	    hw->mac.type == e1000_82572)) {
E 4
		uint16_t phy_tmp = 0;
D 4
		/* speed up time to link by disabling smart power down */
		em_read_phy_reg(&lp->hw, IGP02E1000_PHY_POWER_MGMT,
			   &phy_tmp);
E 4
I 4

		/* Speed up time to link by disabling smart power down. */
		e1000_read_phy_reg(hw,
		    IGP02E1000_PHY_POWER_MGMT, &phy_tmp);
E 4
		phy_tmp &= ~IGP02E1000_PM_SPD;
D 4
		em_write_phy_reg(&lp->hw, IGP02E1000_PHY_POWER_MGMT,
			    phy_tmp);
E 4
I 4
		e1000_write_phy_reg(hw,
		    IGP02E1000_PHY_POWER_MGMT, phy_tmp);
E 4
	}

E 3
D 4
	if (em_init_hw(&lp->hw) != E1000_SUCCESS) {
		cmn_err(CE_WARN, "%s: $s: em_init_hw: failed",
			dp->name, __func__);
E 4
I 4
	/*
E 5
	 * These parameters control the automatic generation (Tx) and
	 * response (Rx) to Ethernet PAUSE frames.
	 * - High water mark should allow for at least two frames to be
	 *   received after sending an XOFF.
	 * - Low water mark works best when it is very near the high water mark.
	 *   This allows the receiver to restart by sending XON when it has
	 *   drained a bit. Here we use an arbitary value of 1500 which will
	 *   restart after one full frame is pulled from the buffer. There
	 *   could be several smaller frames in the buffer and if so they will
	 *   not trigger the XON until their total number reduces the buffer
	 *   by 1500.
	 * - The pause time is fairly large at 1000 x 512ns = 512 usec.
	 */
	rx_buffer_size = ((E1000_READ_REG(hw, E1000_PBA) & 0xffff) << 10);
D 5

E 5
	hw->fc.high_water = rx_buffer_size -
	    roundup2(lp->max_frame_size, 1024);
	hw->fc.low_water = hw->fc.high_water - 1500;

I 5
	if (lp->fc) /* locally set flow control value? */
		hw->fc.requested_mode = lp->fc;
	else
		hw->fc.requested_mode = e1000_fc_full;

E 5
	if (hw->mac.type == e1000_80003es2lan) {
		hw->fc.pause_time = 0xFFFF;
	} else {
		hw->fc.pause_time = E1000_FC_PAUSE_TIME;
E 4
	}
D 4
	DPRINTF(0, (CE_CONT, "%s: %s: rx_ring base:%x, tx ring base:%x",
		dp->name, __func__,
		dp->rx_ring, dp->tx_ring));
E 4
I 4
	hw->fc.send_xon = TRUE;
E 4

D 4
	em_initialize_receive_unit(dp);
E 4
I 4
D 5
#ifdef notdef
E 5
#ifdef E1000_DEV_ID_82574LA
	/* XXX - not implemented */
	/* Set Flow control, use the tunable location if sane */
	switch (dp->flow_control) {
	default:
	case FLOW_CONTROL_NONE:
		hw->fc.requested_mode = e1000_fc_none;
		break;

	case FLOW_CONTROL_SYMMETRIC:
		hw->fc.requested_mode = e1000_fc_full;
		break;

	case FLOW_CONTROL_TX_PAUSE:
		hw->fc.requested_mode = e1000_fc_tx_pause;
		break;

	case FLOW_CONTROL_RX_PAUSE:
		hw->fc.requested_mode = e1000_fc_rx_pause;
		break;
	}
#else
	hw->fc.type = e1000_fc_full;
#endif

D 5
#ifdef notyet	/* only for new em */
	/* Set Flow control, use the tunable location if sane */
	hw->fc.requested_mode = adapter->fc_setting;
#endif

	/* Workaround: no TX flow ctrl for PCH */
	if (hw->mac.type == e1000_pchlan) {
E 5
I 5
#ifdef CONFIG_NEW_EM
	/* Device specific overrides/settings */
	switch (hw->mac.type) {
	case e1000_pchlan:
		/* Workaround: no TX flow ctrl for PCH */
E 5
		hw->fc.requested_mode = e1000_fc_rx_pause;
D 5
	}
#endif /* notdef */

	/* Override - settings for PCH2LAN, ya its magic :) */
	if (hw->mac.type == e1000_pch2lan) {
E 5
I 5
		hw->fc.pause_time = 0xFFFF; /* override */
		if (dp->mtu > ETHERMTU) {
			hw->fc.high_water = 0x3500;
			hw->fc.low_water = 0x1500;
		} else {
			hw->fc.high_water = 0x5000;
			hw->fc.low_water = 0x3000;
		}
		hw->fc.refresh_time = 0x1000;
		break;
	case e1000_pch2lan:
	case e1000_pch_lpt:
E 5
		hw->fc.high_water = 0x5C20;
		hw->fc.low_water = 0x5048;
		hw->fc.pause_time = 0x0650;
		hw->fc.refresh_time = 0x0400;
		/* Jumbos need adjusted PBA */
D 5
		if (dp->mtu > ETHERMTU) {
E 5
I 5
		if (dp->mtu > ETHERMTU)
E 5
			E1000_WRITE_REG(hw, E1000_PBA, 12);
D 5
		} else {
E 5
I 5
		else
E 5
			E1000_WRITE_REG(hw, E1000_PBA, 26);
I 5
		break;
	case e1000_ich9lan:
	case e1000_ich10lan:
		if (dp->mtu > ETHERMTU) {
			hw->fc.high_water = 0x2800;
			hw->fc.low_water = hw->fc.high_water - 8;
			break;
E 5
		}
I 5
		/* else fall thru */
	default:
		if (hw->mac.type == e1000_80003es2lan)
			hw->fc.pause_time = 0xFFFF;
		break;
E 5
	}
I 5
#endif /* CONFIG_NEW_EM */
E 5

	/* Issue a global reset */
	e1000_reset_hw(hw);
	E1000_WRITE_REG(hw, E1000_WUC, 0);
I 5
#ifdef CONFIG_NEW_EM
	em_disable_aspm(dp);
#endif
E 5
#ifdef notdef
#ifdef CONFIG_HW_LINK_DETECTION
	/* XXX - what should we do ? */
#else
	dp->mii_state = MII_STATE_UNKNOWN;
#endif
#endif
I 5
	lp->hw.mac.get_link_status = 1;

E 5
	/* XXX - init_hw also restart autonegotiation */
	if (e1000_init_hw(hw) != E1000_SUCCESS) {
		cmn_err(CE_WARN, "!%s: %s: e1000_init_hw: failed",
		    dp->name, __func__);
	}
D 5
#if 0
E 5
I 5
#ifdef CONFIG_NEW_EM
E 5
	E1000_WRITE_REG(hw, E1000_VET, ETHERTYPE_VLAN);
I 5
#ifdef notdef
	/* XXX - don't call get_phy_info, it waits until the link become up */
E 5
	e1000_get_phy_info(hw);
I 5
#endif
	/* XXX - don't call check_for_link, link will be down now */
E 5
	e1000_check_for_link(hw);
#endif
D 5
	/* XXX - e1000_hardware_init: ends */

E 5
I 5
	/* XXX - em_reset: ends */
#if 0
	em_update_link_status(dp);
#endif
E 5
	/* Configure for OS presence */
	em_init_manageability(dp);

	DPRINTF(0, (CE_CONT, CONS "%s: %s: rx_ring base:%x, tx ring base:%x",
	    dp->name, __func__,
	    dp->rx_ring, dp->tx_ring));

E 4
	em_initialize_transmit_unit(dp);
I 5

	/* XXX - we setup multicast table later */

E 5
I 4
	em_initialize_receive_unit(dp);
E 4

I 4
#ifdef notyet	/* from legacy em */
	/* Use real VLAN Filter support? */
	if (ifp->if_capenable & IFCAP_VLAN_HWTAGGING) {
		if (ifp->if_capenable & IFCAP_VLAN_HWFILTER) {
			/* Use real VLAN Filter support */
			lem_setup_vlan_hw_support(adapter);
		} else {
			u32 ctrl;
			ctrl = E1000_READ_REG(&adapter->hw, E1000_CTRL);
			ctrl |= E1000_CTRL_VME;
			E1000_WRITE_REG(&adapter->hw, E1000_CTRL, ctrl);
		}
	}
#else
E 4
I 2
	em_enable_vlans(dp);
I 4
#endif
E 4

I 4
#ifdef never
	/* Don't lose promiscuous settings */
	lem_set_promisc(adapter);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

#endif
	e1000_clear_hw_cntrs_base_generic(hw);

#ifdef CONFIG_MSI
	/* MSI/X configuration for 82574 */
	if (hw->mac.type == e1000_82574) {
		int tmp;
		tmp = E1000_READ_REG(hw, E1000_CTRL_EXT);
		tmp |= E1000_CTRL_EXT_PBA_CLR;
		E1000_WRITE_REG(hw, E1000_CTRL_EXT, tmp);
		/*
		 * Set the IVAR - interrupt vector routing.
		 * Each nibble represents a vector, high bit
		 * is enable, other 3 bits are the MSIX table
		 * entry, we map RXQ0 to 0, TXQ0 to 1, and
		 * Link (other) to 2, hence the magic number.
		 */
		E1000_WRITE_REG(hw, E1000_IVAR, 0x800A0908);
	}
#endif

E 4
E 2
	lp->our_intr_mask = 0;
I 4

E 4
D 5
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
I 5
#if defined(CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
D 4
	lp->tx_cksum_ctx = TX_CTX_NONE;
E 4
I 4
	bzero(&lp->tx_ctx, sizeof (lp->tx_ctx));
E 4
#endif
I 2
	lp->tx_head = 0;
	lp->tx_tail = 0;
	lp->tx_tail_real = 0;
D 4
	lp->nic_active = B_FALSE;
E 4
I 3

	lp->tx_fifo_head = 0;
	lp->tx_fifo_full = B_FALSE;

	return (GEM_SUCCESS);
E 3
E 2
}

D 3
static void
E 3
I 3
static int
E 3
em_set_rx_filter(struct gem_dev *dp)
{
	int		i;
D 4
	uint32_t	ctrl;
	struct em_dev	*lp = (struct em_dev *)dp->private;
E 4
I 4
	uint32_t	reg_rctrl;
	struct em_dev	*lp = dp->private;
E 4

D 3
	DPRINTF(4, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 3
I 3
	DPRINTF(0, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 3

I 3
D 4
	ctrl = lp->rctl;
E 4
I 4
	reg_rctrl = lp->rctl;
E 4

E 3
	/* Set Receive filter control register */
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
D 3
		lp->rctl = 0;
E 3
I 3
D 4
		E1000_WRITE_REG(&lp->hw, RCTL, 0);
E 4
I 4
		E1000_WRITE_REG(&lp->hw, E1000_RCTL, 0);
E 4
		return (GEM_SUCCESS);
E 3
	}
D 3
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
		lp->rctl |= (E1000_RCTL_UPE | E1000_RCTL_MPE);
E 3
I 3

D 4
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
		ctrl |= (E1000_RCTL_UPE | E1000_RCTL_MPE);
E 4
I 4
	if (dp->rxmode & RXMODE_PROMISC) {
		reg_rctrl |= E1000_RCTL_UPE | E1000_RCTL_MPE;
	} else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 32) {
		reg_rctrl |= E1000_RCTL_MPE;
		reg_rctrl &= ~E1000_RCTL_UPE;
	} else {
		reg_rctrl &= ~(E1000_RCTL_UPE | E1000_RCTL_MPE);
E 4
E 3
	}
D 4
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 32) {
D 3
		lp->rctl |= E1000_RCTL_MPE;
		lp->rctl &= ~E1000_RCTL_UPE;
E 3
I 3
		ctrl |= E1000_RCTL_MPE;
		ctrl &= ~E1000_RCTL_UPE;
E 3
	}
	else {
D 3
		lp->rctl &= ~(E1000_RCTL_UPE | E1000_RCTL_MPE);
E 3
I 3
		ctrl &= ~(E1000_RCTL_UPE | E1000_RCTL_MPE);
E 3
	}
E 4

	/* Load Multicast hash table */
D 3
	if ((lp->rctl & E1000_RCTL_MPE) == 0 && dp->mc_count > 0) {
E 3
I 3
D 4
	if ((ctrl & E1000_RCTL_MPE) == 0 && dp->mc_count > 0) {
E 3
		if (lp->hw.mac_type == em_82542_rev2_0) {
			if (lp->hw.pci_cmd_word & CMD_MEM_WRT_INVALIDATE) { 
				em_pci_clear_mwi(&lp->hw);
E 4
I 4
	if ((reg_rctrl & E1000_RCTL_MPE) == 0) {
		uint8_t	*dest;

		if (lp->hw.mac.type == e1000_82542 &&
		    lp->hw.revision_id == E1000_REVISION_2) {
			if (lp->hw.bus.pci_cmd_word &
			    CMD_MEM_WRT_INVALIDATE) {
				e1000_pci_clear_mwi(&lp->hw);
E 4
			}
D 3
			lp->rctl |= E1000_RCTL_RST;
			E1000_WRITE_REG(&lp->hw, RCTL, lp->rctl);
E 3
I 3
D 4
			ctrl |= E1000_RCTL_RST;
			E1000_WRITE_REG(&lp->hw, RCTL, ctrl);
E 4
I 4
			reg_rctrl |= E1000_RCTL_RST;
			E1000_WRITE_REG(&lp->hw, E1000_RCTL, reg_rctrl);
E 4
E 3
			drv_usecwait(5000);
		}
D 4
		
		em_mc_addr_list_update(&lp->hw,
			(uint8_t *) dp->mc_list, dp->mc_count, 
			sizeof(struct mcast_addr) - ETHERADDRL, 1);
E 4

D 4
		if (lp->hw.mac_type == em_82542_rev2_0) {
D 3
			lp->rctl &= ~E1000_RCTL_RST;
			E1000_WRITE_REG(&lp->hw, RCTL, lp->rctl);
E 3
I 3
			ctrl &= ~E1000_RCTL_RST;
			E1000_WRITE_REG(&lp->hw, RCTL, ctrl);
E 4
I 4
		dest = lp->mta;
		for (i = 0; i < dp->mc_count; i++) {
			bcopy(dp->mc_list[i].addr.ether_addr_octet,
			    dest, ETHERADDRL);
			dest += ETHERADDRL;
		}
#ifdef E1000_DEV_ID_82574LA
		e1000_update_mc_addr_list(&lp->hw, lp->mta, dp->mc_count);
#else
		e1000_update_mc_addr_list(&lp->hw, lp->mta,
		    dp->mc_count, 1, lp->hw.mac.rar_entry_count);
#endif

		if (lp->hw.mac.type == e1000_82542 &&
		    lp->hw.revision_id == E1000_REVISION_2) {
			reg_rctrl &= ~E1000_RCTL_RST;
			E1000_WRITE_REG(&lp->hw, E1000_RCTL, reg_rctrl);
E 4
E 3
			drv_usecwait(5000);

D 4
			if (lp->hw.pci_cmd_word & CMD_MEM_WRT_INVALIDATE) {
				em_pci_set_mwi(&lp->hw);
E 4
I 4
			if (lp->hw.bus.pci_cmd_word & CMD_MEM_WRT_INVALIDATE) {
				e1000_pci_set_mwi(&lp->hw);
E 4
			}
		}
	}

	/* Load station address if it has been changed */
	if (bcmp(dp->cur_addr.ether_addr_octet,
D 4
			lp->hw.mac_addr, ETHERADDRL) != 0) {
E 4
I 4
	    lp->hw.mac.addr, ETHERADDRL) != 0) {
E 4
		bcopy(dp->cur_addr.ether_addr_octet,
D 4
				lp->hw.mac_addr, ETHERADDRL);
		em_rar_set(&lp->hw, lp->hw.mac_addr, 0);
E 4
I 4
		    lp->hw.mac.addr, ETHERADDRL);
		e1000_rar_set(&lp->hw, lp->hw.mac.addr, 0);
E 4
	}

	/* Load new rx filter mode */
D 3
	E1000_WRITE_REG(&lp->hw, RCTL, lp->rctl);
E 3
I 3
D 4
	E1000_WRITE_REG(&lp->hw, RCTL, ctrl);
E 4
I 4
	E1000_WRITE_REG(&lp->hw, E1000_RCTL, reg_rctrl);
E 4

	return (GEM_SUCCESS);
E 3
D 2

#ifdef notdef /* GEM_CONFIG_VLAN */
	ctrl = E1000_READ_REG(&lp->hw, CTRL) & ~E1000_CTRL_VME;
	/* enable vlan mode if we are not in promiscious mode */
	if ((lp->rctl & E1000_RCTL_UPE) == 0) {
		ctrl |= E1000_CTRL_VME;
	}
	E1000_WRITE_REG(&lp->hw, CTRL, ctrl);
#endif
E 2
}

D 3
static void
E 3
I 3
static int
E 3
em_start_chip(struct gem_dev *dp)
{
D 4
	struct em_dev	*lp = (struct em_dev *)dp->private;
E 4
I 4
	struct em_dev	*adapter = dp->private;
E 4

	DPRINTF(0, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));

I 3
D 4
	/* Initialize statistics */
	em_clear_hw_cntrs(&lp->hw);

E 3
	lp->our_intr_mask = IMS_ENABLE_MASK;
D 2

E 2
I 2
	lp->nic_active    = B_TRUE;
E 4
I 4
	adapter->our_intr_mask = IMS_ENABLE_MASK;
	adapter->nic_active = B_TRUE;
E 4
E 2
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
D 4
		E1000_WRITE_REG(&lp->hw, IMS, lp->our_intr_mask);
E 4
I 4
		em_enable_intr(dp);
E 4
	}

D 4
	/* Don't reset the phy next time init gets called */
	lp->hw.phy_reset_disable = B_TRUE;
E 4
I 4
	/* AMT based hardware can now take control from firmware */
	if (adapter->has_manage && adapter->has_amt) {
		em_get_hw_control(dp);
	}
E 4
I 3

I 4

E 4
	return (GEM_SUCCESS);
E 3
}

static int
D 4
em_stop_chip(struct gem_dev *dp)
E 4
I 4
em_stop_chip(struct gem_dev *dp)	/* done */
E 4
{
D 4
	struct em_dev	*lp = (struct em_dev *)dp->private;
E 4
I 4
	struct em_dev	*adapter = dp->private;
	struct e1000_hw	*hw = &adapter->hw;
E 4

I 3
	DPRINTF(0, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));

E 3
	/* disable interrupt */
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
D 3
		E1000_WRITE_REG(&lp->hw, IMC, (0xffffffff & ~E1000_IMC_RXSEQ));
E 3
I 3
		em_disable_intr(dp);
E 3
	}
D 4
	lp->our_intr_mask = 0;
E 4
I 4
	adapter->our_intr_mask = 0;
E 4

I 3
D 4
	lp->nic_active = B_FALSE;
E 3
	em_reset_hw(&lp->hw);
E 4
I 4
	adapter->nic_active = B_FALSE;
E 4

I 4
	e1000_reset_hw(hw);
	if (hw->mac.type >= e1000_82544) {
		E1000_WRITE_REG(hw, E1000_WUC, 0);
	}
#ifdef CONFIG_NEW_EM
	e1000_led_off(hw);
	e1000_cleanup_led(hw);
#endif

E 4
D 3
	DPRINTF(0, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 3
I 3
	DPRINTF(0, (CE_CONT, CONS "%s: %s: exited", dp->name, __func__));
E 3

	return (GEM_SUCCESS);
}

D 3
static void
E 3
I 3
D 4
static int
E 4
I 4
static int			/* done */
E 4
E 3
em_set_media(struct gem_dev *dp)
{
D 3
	uint32_t	val;
E 3
D 4
	struct em_dev	*lp = (struct em_dev *)dp->private;
E 4
I 4
	struct em_dev	*lp = dp->private;
	struct e1000_hw	*hw = &lp->hw;
E 4
	extern int gem_speed_value[];

D 3
	DPRINTF(2, (CE_CONT, CONS "%s: %s: %s duplex, %d Mbps",
E 3
I 3
	DPRINTF(0, (CE_CONT, CONS "%s: %s: %s duplex, %d Mbps",
E 3
D 4
		dp->name, __func__,
		dp->full_duplex ? "full" : "half",
		gem_speed_value[dp->speed]));
E 4
I 4
	    dp->name, __func__,
	    dp->full_duplex ? "full" : "half",
	    gem_speed_value[dp->speed]));
E 4

D 4
	em_check_for_link(&lp->hw);
E 4
I 4
	e1000_get_phy_info(hw);
E 4

D 3
#ifdef CONFIG_PCIE
E 3
D 4
#define	SPEED_MODE_BIT	(1<<21)	/* On PCI-E MACs only */
	/* Check if we may set SPEED_MODE bit on PCI-E */
	if ((dp->speed == GEM_SPD_1000) &&
	    ((lp->hw.mac_type == em_82571) ||
	     (lp->hw.mac_type == em_82572))) {
E 4
I 4
	switch (hw->phy.media_type) {
	case e1000_media_type_copper:
		/* ESB2 fix */
		e1000_cfg_on_link_up(hw);
	}

	/* Check if we must disable SPEED_MODE bit on PCI-E */
	if ((dp->speed != GEM_SPD_1000) &&
	    ((hw->mac.type == e1000_82571) ||
	    (hw->mac.type == e1000_82572))) {
E 4
		int tarc0;
D 4
		tarc0 = E1000_READ_REG(&lp->hw, TARC0);
		tarc0 |= SPEED_MODE_BIT;
		E1000_WRITE_REG(&lp->hw, TARC0, tarc0);
E 4
I 4

		tarc0 = E1000_READ_REG(&lp->hw, E1000_TARC(0));
		tarc0 &= ~SPEED_MODE_BIT;
		E1000_WRITE_REG(&lp->hw, E1000_TARC(0), tarc0);
E 4
	}
I 4
	lp->smartspeed = 0;
E 4
D 3
#endif /* CONFIG_PCIE */
E 3
I 3

	return (GEM_SUCCESS);
E 3
}

D 3
static void
E 3
I 3
static int
E 3
em_get_stats(struct gem_dev *dp)
{
D 4
	/* not implemented yet */
#ifdef notdef
	struct ifnet   *ifp;
E 4
I 4
	struct em_dev	*lp = dp->private;
	struct e1000_hw	*hw = &lp->hw;
E 4

D 4
	if(lp->hw.media_type == em_media_type_copper ||
	   (E1000_READ_REG(&lp->hw, STATUS) & E1000_STATUS_LU)) {
		lp->stats.symerrs += E1000_READ_REG(&lp->hw, SYMERRS);
		lp->stats.sec += E1000_READ_REG(&lp->hw, SEC);
E 4
I 4
	if (lp->hw.phy.media_type == e1000_media_type_copper ||
	    (E1000_READ_REG(&lp->hw, E1000_STATUS) & E1000_STATUS_LU)) {
		lp->stats.symerrs += E1000_READ_REG(&lp->hw, E1000_SYMERRS);
		lp->stats.sec += E1000_READ_REG(&lp->hw, E1000_SEC);
E 4
	}
D 4
	lp->stats.crcerrs += E1000_READ_REG(&lp->hw, CRCERRS);
	lp->stats.mpc += E1000_READ_REG(&lp->hw, MPC);
	lp->stats.scc += E1000_READ_REG(&lp->hw, SCC);
	lp->stats.ecol += E1000_READ_REG(&lp->hw, ECOL);
E 4
I 4
	lp->stats.crcerrs += E1000_READ_REG(&lp->hw, E1000_CRCERRS);
	lp->stats.mpc += E1000_READ_REG(&lp->hw, E1000_MPC);
	lp->stats.scc += E1000_READ_REG(&lp->hw, E1000_SCC);
	lp->stats.ecol += E1000_READ_REG(&lp->hw, E1000_ECOL);
E 4

D 4
	lp->stats.mcc += E1000_READ_REG(&lp->hw, MCC);
	lp->stats.latecol += E1000_READ_REG(&lp->hw, LATECOL);
	lp->stats.colc += E1000_READ_REG(&lp->hw, COLC);
	lp->stats.dc += E1000_READ_REG(&lp->hw, DC);
	lp->stats.rlec += E1000_READ_REG(&lp->hw, RLEC);
	lp->stats.xonrxc += E1000_READ_REG(&lp->hw, XONRXC);
	lp->stats.xontxc += E1000_READ_REG(&lp->hw, XONTXC);
	lp->stats.xoffrxc += E1000_READ_REG(&lp->hw, XOFFRXC);
	lp->stats.xofftxc += E1000_READ_REG(&lp->hw, XOFFTXC);
	lp->stats.fcruc += E1000_READ_REG(&lp->hw, FCRUC);
	lp->stats.prc64 += E1000_READ_REG(&lp->hw, PRC64);
	lp->stats.prc127 += E1000_READ_REG(&lp->hw, PRC127);
	lp->stats.prc255 += E1000_READ_REG(&lp->hw, PRC255);
	lp->stats.prc511 += E1000_READ_REG(&lp->hw, PRC511);
	lp->stats.prc1023 += E1000_READ_REG(&lp->hw, PRC1023);
	lp->stats.prc1522 += E1000_READ_REG(&lp->hw, PRC1522);
	lp->stats.gprc += E1000_READ_REG(&lp->hw, GPRC);
	lp->stats.bprc += E1000_READ_REG(&lp->hw, BPRC);
	lp->stats.mprc += E1000_READ_REG(&lp->hw, MPRC);
	lp->stats.gptc += E1000_READ_REG(&lp->hw, GPTC);
E 4
I 4
	lp->stats.mcc += E1000_READ_REG(&lp->hw, E1000_MCC);
	lp->stats.latecol += E1000_READ_REG(&lp->hw, E1000_LATECOL);
	lp->stats.colc += E1000_READ_REG(&lp->hw, E1000_COLC);
	lp->stats.dc += E1000_READ_REG(&lp->hw, E1000_DC);
	lp->stats.rlec += E1000_READ_REG(&lp->hw, E1000_RLEC);
	lp->stats.xonrxc += E1000_READ_REG(&lp->hw, E1000_XONRXC);
	lp->stats.xontxc += E1000_READ_REG(&lp->hw, E1000_XONTXC);
	lp->stats.xoffrxc += E1000_READ_REG(&lp->hw, E1000_XOFFRXC);
	lp->stats.xofftxc += E1000_READ_REG(&lp->hw, E1000_XOFFTXC);
	lp->stats.fcruc += E1000_READ_REG(&lp->hw, E1000_FCRUC);
	lp->stats.prc64 += E1000_READ_REG(&lp->hw, E1000_PRC64);
	lp->stats.prc127 += E1000_READ_REG(&lp->hw, E1000_PRC127);
	lp->stats.prc255 += E1000_READ_REG(&lp->hw, E1000_PRC255);
	lp->stats.prc511 += E1000_READ_REG(&lp->hw, E1000_PRC511);
	lp->stats.prc1023 += E1000_READ_REG(&lp->hw, E1000_PRC1023);
	lp->stats.prc1522 += E1000_READ_REG(&lp->hw, E1000_PRC1522);
	lp->stats.gprc += E1000_READ_REG(&lp->hw, E1000_GPRC);
	lp->stats.bprc += E1000_READ_REG(&lp->hw, E1000_BPRC);
	lp->stats.mprc += E1000_READ_REG(&lp->hw, E1000_MPRC);
	lp->stats.gptc += E1000_READ_REG(&lp->hw, E1000_GPTC);
E 4

	/* For the 64-bit byte counters the low dword must be read first. */
	/* Both registers clear on the read of the high dword */

D 4
	lp->stats.gorcl += E1000_READ_REG(&lp->hw, GORCL); 
	lp->stats.gorch += E1000_READ_REG(&lp->hw, GORCH);
	lp->stats.gotcl += E1000_READ_REG(&lp->hw, GOTCL);
	lp->stats.gotch += E1000_READ_REG(&lp->hw, GOTCH);
E 4
I 4
	lp->stats.gorc += E1000_READ_REG(&lp->hw, E1000_GORCL);
	lp->stats.hgorc += E1000_READ_REG(&lp->hw, E1000_GORCH);
	lp->stats.gotc += E1000_READ_REG(&lp->hw, E1000_GOTCL);
	lp->stats.hgotc += E1000_READ_REG(&lp->hw, E1000_GOTCH);
E 4

D 4
	lp->stats.rnbc += E1000_READ_REG(&lp->hw, RNBC);
	lp->stats.ruc += E1000_READ_REG(&lp->hw, RUC);
	lp->stats.rfc += E1000_READ_REG(&lp->hw, RFC);
	lp->stats.roc += E1000_READ_REG(&lp->hw, ROC);
	lp->stats.rjc += E1000_READ_REG(&lp->hw, RJC);
E 4
I 4
	lp->stats.rnbc += E1000_READ_REG(&lp->hw, E1000_RNBC);
	lp->stats.ruc += E1000_READ_REG(&lp->hw, E1000_RUC);
	lp->stats.rfc += E1000_READ_REG(&lp->hw, E1000_RFC);
	lp->stats.roc += E1000_READ_REG(&lp->hw, E1000_ROC);
	lp->stats.rjc += E1000_READ_REG(&lp->hw, E1000_RJC);
E 4

D 4
	lp->stats.torl += E1000_READ_REG(&lp->hw, TORL);
	lp->stats.torh += E1000_READ_REG(&lp->hw, TORH);
	lp->stats.totl += E1000_READ_REG(&lp->hw, TOTL);
	lp->stats.toth += E1000_READ_REG(&lp->hw, TOTH);
E 4
I 4
	lp->stats.tor += E1000_READ_REG(&lp->hw, E1000_TORH);
	lp->stats.tot += E1000_READ_REG(&lp->hw, E1000_TOTH);
E 4

D 4
	lp->stats.tpr += E1000_READ_REG(&lp->hw, TPR);
	lp->stats.tpt += E1000_READ_REG(&lp->hw, TPT);
	lp->stats.ptc64 += E1000_READ_REG(&lp->hw, PTC64);
	lp->stats.ptc127 += E1000_READ_REG(&lp->hw, PTC127);
	lp->stats.ptc255 += E1000_READ_REG(&lp->hw, PTC255);
	lp->stats.ptc511 += E1000_READ_REG(&lp->hw, PTC511);
	lp->stats.ptc1023 += E1000_READ_REG(&lp->hw, PTC1023);
	lp->stats.ptc1522 += E1000_READ_REG(&lp->hw, PTC1522);
	lp->stats.mptc += E1000_READ_REG(&lp->hw, MPTC);
	lp->stats.bptc += E1000_READ_REG(&lp->hw, BPTC);
E 4
I 4
	lp->stats.tpr += E1000_READ_REG(&lp->hw, E1000_TPR);
	lp->stats.tpt += E1000_READ_REG(&lp->hw, E1000_TPT);
	lp->stats.ptc64 += E1000_READ_REG(&lp->hw, E1000_PTC64);
	lp->stats.ptc127 += E1000_READ_REG(&lp->hw, E1000_PTC127);
	lp->stats.ptc255 += E1000_READ_REG(&lp->hw, E1000_PTC255);
	lp->stats.ptc511 += E1000_READ_REG(&lp->hw, E1000_PTC511);
	lp->stats.ptc1023 += E1000_READ_REG(&lp->hw, E1000_PTC1023);
	lp->stats.ptc1522 += E1000_READ_REG(&lp->hw, E1000_PTC1522);
	lp->stats.mptc += E1000_READ_REG(&lp->hw, E1000_MPTC);
	lp->stats.bptc += E1000_READ_REG(&lp->hw, E1000_BPTC);
E 4

I 5
	/* Interrupt Counts */

	lp->stats.iac += E1000_READ_REG(&lp->hw, E1000_IAC);
	lp->stats.icrxptc += E1000_READ_REG(&lp->hw, E1000_ICRXPTC);
	lp->stats.icrxatc += E1000_READ_REG(&lp->hw, E1000_ICRXATC);
	lp->stats.ictxptc += E1000_READ_REG(&lp->hw, E1000_ICTXPTC);
	lp->stats.ictxatc += E1000_READ_REG(&lp->hw, E1000_ICTXATC);
	lp->stats.ictxqec += E1000_READ_REG(&lp->hw, E1000_ICTXQEC);
	lp->stats.ictxqmtc += E1000_READ_REG(&lp->hw, E1000_ICTXQMTC);
	lp->stats.icrxdmtc += E1000_READ_REG(&lp->hw, E1000_ICRXDMTC);
	lp->stats.icrxoc += E1000_READ_REG(&lp->hw, E1000_ICRXOC);

E 5
D 4
	if (lp->hw.mac_type >= em_82543) {
		lp->stats.algnerrc +=
		E1000_READ_REG(&lp->hw, ALGNERRC);
		lp->stats.rxerrc += 
		E1000_READ_REG(&lp->hw, RXERRC);
		lp->stats.tncrs += 
		E1000_READ_REG(&lp->hw, TNCRS);
		lp->stats.cexterr += 
		E1000_READ_REG(&lp->hw, CEXTERR);
		lp->stats.tsctc += 
		E1000_READ_REG(&lp->hw, TSCTC);
		lp->stats.tsctfc += 
		E1000_READ_REG(&lp->hw, TSCTFC);
E 4
I 4
	if (lp->hw.mac.type >= e1000_82543) {
		lp->stats.algnerrc += E1000_READ_REG(&lp->hw, E1000_ALGNERRC);
		lp->stats.rxerrc += E1000_READ_REG(&lp->hw, E1000_RXERRC);
		lp->stats.tncrs += E1000_READ_REG(&lp->hw, E1000_TNCRS);
		lp->stats.cexterr += E1000_READ_REG(&lp->hw, E1000_CEXTERR);
		lp->stats.tsctc += E1000_READ_REG(&lp->hw, E1000_TSCTC);
		lp->stats.tsctfc += E1000_READ_REG(&lp->hw, E1000_TSCTFC);
E 4
	}
I 4
#ifdef notdef
E 4
	ifp = lp->ifp;

	ifp->if_collisions = lp->stats.colc;

	/* Rx Errors */
D 4
	
E 4
I 4

E 4
	ifp->if_ierrors =
D 4
	lp->dropped_pkts +
	lp->stats.rxerrc +
	lp->stats.crcerrs +
	lp->stats.algnerrc +
	lp->stats.ruc + lp->stats.roc +
	lp->stats.mpc + lp->stats.cexterr;
E 4
I 4
	    lp->dropped_pkts +
	    lp->stats.rxerrc +
	    lp->stats.crcerrs +
	    lp->stats.algnerrc +
	    lp->stats.ruc + lp->stats.roc +
	    lp->stats.mpc + lp->stats.cexterr;
E 4

	/* Tx Errors */
	ifp->if_oerrors = lp->stats.ecol + lp->stats.latecol;
#endif
I 3

	return (GEM_SUCCESS);
E 3
}

/*
 * tx and rx discriptor  manupiration
 */
#ifdef notdef
D 4
#define	TXD_OFFSET(m)	((int)((long) &(((struct em_tx_desc *) 0)->m)))
#define	RXD_OFFSET(m)	((int)((long) &(((struct em_rx_desc *) 0)->m)))
E 4
I 4
#define	TXD_OFFSET(m)	((int)((long)&(((struct e1000_tx_desc *)0)->m)))
#define	RXD_OFFSET(m)	((int)((long)&(((struct e1000_rx_desc *)0)->m)))
E 4

D 4
#define	TXD64(tdp, member)	((uint64_t *) (tdp))[TXD_OFFSET(member)/8]
#define	TXD32(tdp, member)	((uint32_t *) (tdp))[TXD_OFFSET(member)/4]
#define	TXD16(tdp, member)	((uint16_t *) (tdp))[TXD_OFFSET(member)/2]
#define	TXD8(tdp, member)	((uint8_t *) (tdp))[TXD_OFFSET(member)]
E 4
I 4
#define	TXD64(tdp, member)	((uint64_t *)(tdp))[TXD_OFFSET(member)/8]
#define	TXD32(tdp, member)	((uint32_t *)(tdp))[TXD_OFFSET(member)/4]
#define	TXD16(tdp, member)	((uint16_t *)(tdp))[TXD_OFFSET(member)/2]
#define	TXD8(tdp, member)	((uint8_t *)(tdp))[TXD_OFFSET(member)]
E 4

D 4
#define	RXD64(rdp, member)	((uint64_t *) (rdp))[RXD_OFFSET(member)/8]
#define	RXD32(rdp, member)	((uint32_t *) (rdp))[RXD_OFFSET(member)/4]
#define	RXD16(rdp, member)	((uint16_t *) (rdp))[RXD_OFFSET(member)/2]
#define	RXD8(rdp, member)	((uint8_t *) (rdp))[RXD_OFFSET(member)]
E 4
I 4
#define	RXD64(rdp, member)	((uint64_t *)(rdp))[RXD_OFFSET(member)/8]
#define	RXD32(rdp, member)	((uint32_t *)(rdp))[RXD_OFFSET(member)/4]
#define	RXD16(rdp, member)	((uint16_t *)(rdp))[RXD_OFFSET(member)/2]
#define	RXD8(rdp, member)	((uint8_t *)(rdp))[RXD_OFFSET(member)]
E 4
#else
#define	TXD64(tdp, member)	(tdp)->member
#define	TXD32(tdp, member)	(tdp)->member
#define	TXD16(tdp, member)	(tdp)->member
#define	TXD8(tdp, member)	(tdp)->member

#define	RXD64(rdp, member)	(rdp)->member
#define	RXD32(rdp, member)	(rdp)->member
#define	RXD16(rdp, member)	(rdp)->member
#define	RXD8(rdp, member)	(rdp)->member
#endif

I 4
#if 1
E 4
static int
em_tx_desc_write(struct gem_dev *dp, int slot,
D 4
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flags)
E 4
I 4
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
E 4
{
D 4
	uint			used;
	int			new_ctx;
E 4
I 4
	uint_t			used;
E 4
	uint32_t		txd_upper;
	uint32_t		txd_lower;
I 2
#ifdef CONFIG_VLAN
E 2
	uint16_t		vtag;
I 2
#endif
E 2
D 4
	struct em_tx_desc	*tdp;
E 4
I 4
	struct e1000_tx_desc	*tdp;
E 4
	ddi_dma_cookie_t	*dcp;
D 4
	struct em_dev		*lp = (struct em_dev *)dp->private;
E 4
I 4
	struct em_dev		*lp = dp->private;
E 4
	int			i;
I 2
	uint64_t		addr;
D 4
	uint64_t		len;
E 4
I 4
	uint32_t		len;
I 5
#if defined(CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
	uint32_t		hck_start;
	uint32_t		hck_stuff;
	uint32_t		mss = 0;
I 5
#endif
E 5
E 4
E 2

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 4
	CONS "%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %d",
		dp->name, ddi_get_lbolt(), __func__,
		dp->tx_active_tail, slot, frags, flags);
E 4
I 4
	    CONS "%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %lld",
	    dp->name, ddi_get_lbolt(), __func__,
	    dp->tx_active_tail, slot, frags, flags);
E 4

	for (i = 0; i < frags; i++) {
D 4
		cmn_err(CE_CONT, CONS "%d: addr: 0x%x, len: 0x%x",
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 4
I 4
		cmn_err(CE_CONT, CONS "%d: addr: 0x%llx, len: 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 4
	}
#endif
	/*
	 * write tx descriptor in reversed order.
	 */
	txd_upper = 0;
	txd_lower = 0;
D 2
	used = frags;
E 2
I 2
	used = 0;
E 2
D 5
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
I 5
#if defined(CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
D 4
	new_ctx = TX_CTX_NONE;
	if ((flags & (GEM_TXFLAG_TCP | GEM_TXFLAG_UDP)) != 0) {
		txd_upper = (E1000_TXD_POPTS_TXSM | E1000_TXD_POPTS_IXSM) << 8;
E 4
I 4
	if (flags & (GEM_TXFLAG_MSS | GEM_TXFLAG_TCP | GEM_TXFLAG_UDP)) {
		struct e1000_context_desc	*tcp;
		struct e1000_context_desc	new_ctx;
		uint32_t	hcksum_cmd;
#define	EHDLEN	sizeof (struct ether_header)

		txd_upper = E1000_TXD_POPTS_TXSM << 8;
		if (flags & GEM_TXFLAG_IPv4) {
			txd_upper |= E1000_TXD_POPTS_IXSM << 8;
		}
E 4
		txd_lower = (E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D);
D 4
		new_ctx   = (flags & GEM_TXFLAG_TCP) ? TX_CTX_TCP : TX_CTX_UDP;
	}
E 4

D 4
	if (new_ctx != lp->tx_cksum_ctx && new_ctx != TX_CTX_NONE) {
		struct em_context_desc *tcp;
		uint32_t		hcksum_cmd;
#define EHDLEN sizeof(struct ether_header)
E 4
I 4
		mss = (flags & GEM_TXFLAG_MSS) >> GEM_TXFLAG_MSS_SHIFT;
E 4

D 4
		tcp = &((struct em_context_desc *) dp->tx_ring)[slot];
		tcp->lower_setup.ip_fields.ipcss = EHDLEN;
		tcp->lower_setup.ip_fields.ipcso = 
					EHDLEN + offsetof(struct ip, ip_sum);
		tcp->lower_setup.ip_fields.ipcse = 
					LE16(EHDLEN + sizeof(struct ip) - 1);
		tcp->upper_setup.tcp_fields.tucss = EHDLEN + sizeof(struct ip);
E 4
I 4
		hck_start = (flags & GEM_TXFLAG_HCKSTART) >>
		    GEM_TXFLAG_HCKSTART_SHIFT;
		hck_stuff = (flags & GEM_TXFLAG_HCKSTUFF) >>
		    GEM_TXFLAG_HCKSTUFF_SHIFT;

		bzero(&new_ctx, sizeof (new_ctx));
		tcp = &new_ctx;

		/* IPv4 header */
		if (flags & GEM_TXFLAG_IPv4) {
			tcp->lower_setup.ip_fields.ipcss = EHDLEN;
			tcp->lower_setup.ip_fields.ipcso = 
			    EHDLEN + offsetof(struct ip, ip_sum);
			tcp->lower_setup.ip_fields.ipcse = LE_16(hck_start - 1);
			hcksum_cmd = E1000_TXD_CMD_IP;
		} else {
			/* others, i.e. IPv6 */
			tcp->lower_setup.ip_config = 0;
			hcksum_cmd = 0;
		}

		/* TCP or UDP */
		tcp->upper_setup.tcp_fields.tucss = hck_start;
E 4
		tcp->upper_setup.tcp_fields.tucse = 0;
I 4
		tcp->upper_setup.tcp_fields.tucso = hck_stuff;
E 4

D 4
		switch (new_ctx) {
		case TX_CTX_TCP:
			tcp->upper_setup.tcp_fields.tucso = 
					EHDLEN + sizeof(struct ip) + 
					offsetof(struct tcphdr, th_sum);
E 4
I 4
	 	if (flags & GEM_TXFLAG_TCP) {
E 4
			/*
			 * XXX - we must request IP checksum too, otherwize
			 * ip check sum field will be cleared.
			 */
D 4
			hcksum_cmd = (E1000_TXD_CMD_IP | E1000_TXD_CMD_TCP);
			break;
E 4
I 4
			hcksum_cmd |= E1000_TXD_CMD_TCP;
		}
E 4

D 4
		case TX_CTX_UDP:
			tcp->upper_setup.tcp_fields.tucso = 
					EHDLEN + sizeof(struct ip) + 
					offsetof(struct udphdr, uh_sum);
E 4
I 4
		tcp->tcp_seg_setup.data = 0;
		if (mss) {
			txd_lower |= E1000_TXD_CMD_TSE;

                        tcp->tcp_seg_setup.fields.hdr_len =
			    ((flags & GEM_TXFLAG_TCPHLEN)
			    >> GEM_TXFLAG_TCPHLEN_SHIFT) << 2;
                        tcp->tcp_seg_setup.fields.mss = LE_16(mss);
		}

		tcp->cmd_and_length =
		    LE_32(hcksum_cmd | E1000_TXD_CMD_DEXT | lp->txd_cmd);

		if (bcmp(tcp, &lp->tx_ctx, sizeof (*tcp)) != 0 || mss) {
			/* need to update context */
			tcp = &((struct e1000_context_desc *)dp->tx_ring)[slot];
			*tcp = new_ctx;
			lp->tx_ctx = new_ctx;
			
			/* we consumed an additional slot */
			used++;
		}
#undef EHDLEN
	}
D 5
#endif /* GEM_CONFIG_CKSUM_OFFLOAD  && defined(CONFIG_VLAN) */
E 5
I 5
#endif /* CONFIG_CKSUM_OFFLOAD  && defined(CONFIG_VLAN) */
E 5

	txd_lower |= lp->txd_cmd;

	for (dcp = dmacookie, i = 0; i < frags; dcp++, i++) {
		tdp = &((struct e1000_tx_desc *)dp->tx_ring)[
		    SLOT(slot + used, dp->gc.gc_tx_ring_size)];
		used++;

		addr = dcp->dmac_laddress;
		len = dcp->dmac_size;
		if (lp->pcix_82544 && len > 4) {
			switch (((addr & 0x7) + (len & 0xf)) & 0xf) {
			case 1: case 2: case 3: case 4:
			case 9: case 0xa: case 0xb: case 0xc:
				len -= 4;
				tdp->buffer_addr = LE_64(addr);
				tdp->lower.data = LE_32(txd_lower | len);
				tdp->upper.data = LE_32(txd_upper);

				addr += len;
				len = 4;

				tdp = &((struct e1000_tx_desc *)dp->tx_ring)[
				    SLOT(slot + used, dp->gc.gc_tx_ring_size)];
				used++;
			}
		}

		tdp->buffer_addr = LE_64(addr);
		tdp->lower.data = LE_32(txd_lower | len);
		tdp->upper.data = LE_32(txd_upper);
	}

	/* fix last descriptor */
#ifdef CONFIG_VLAN
	vtag = (flags & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT;
	if (vtag) {
		DPRINTF(2, (CE_CONT, CONS "%s: %s: vtag:%x",
		    dp->name, __func__, vtag));
		tdp->lower.data |= LE_32(E1000_TXD_CMD_VLE);
		tdp->upper.fields.special = LE_16(vtag);
	}
D 5

E 5
I 5
#if defined(CONFIG_CKSUM_OFFLOAD)
E 5
	if (mss) {
		tdp->lower.data |= LE_32(E1000_TXD_CMD_TSE);
	}
#endif
I 5
#endif
E 5
	tdp->lower.data |= LE_32(E1000_TXD_CMD_EOP | E1000_TXD_CMD_RS);

	return (used);
}
#else
/* from t8 */
static int
em_tx_desc_write(struct gem_dev *dp, int slot,
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
{
	uint_t			used;
	uint32_t		new_ctx;
	uint32_t		txd_upper;
	uint32_t		txd_lower;
#ifdef CONFIG_VLAN
	uint16_t		vtag;
#endif
	struct e1000_tx_desc	*tdp;
	ddi_dma_cookie_t	*dcp;
	struct em_dev		*lp = dp->private;
	int			i;
	uint64_t		addr;
	uint64_t		len;
	uint32_t		hck_start;
	uint32_t		hck_stuff;

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
	    CONS "%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %lld",
	    dp->name, ddi_get_lbolt(), __func__,
	    dp->tx_active_tail, slot, frags, flags);

	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, CONS "%d: addr: 0x%llx, len: 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
	}
#endif
	/*
	 * write tx descriptor in reversed order.
	 */
	txd_upper = 0;
	txd_lower = 0;
	used = 0;
D 5
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
I 5
#if defined(CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
	new_ctx = 0;
	if (flags & (GEM_TXFLAG_TCP | GEM_TXFLAG_UDP)) {
		txd_upper = E1000_TXD_POPTS_TXSM << 8;
		if (flags & GEM_TXFLAG_IPv4) {
			txd_upper |= E1000_TXD_POPTS_IXSM << 8;
		}
		txd_lower = (E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D);
		new_ctx = flags &
		    (GEM_TXFLAG_TCP | GEM_TXFLAG_UDP |
		    GEM_TXFLAG_IPv4 | GEM_TXFLAG_IPv6);
	}

	if (new_ctx != lp->tx_cksum_ctx && new_ctx != 0) {
		struct e1000_context_desc *tcp;
		uint32_t	hcksum_cmd;
#define	EHDLEN	sizeof (struct ether_header)

		hck_start =
		    (flags & GEM_TXFLAG_HCKSTART) >> GEM_TXFLAG_HCKSTART_SHIFT;
		hck_stuff =
		    (flags & GEM_TXFLAG_HCKSTUFF) >> GEM_TXFLAG_HCKSTUFF_SHIFT;

		tcp = &((struct e1000_context_desc *)dp->tx_ring)[slot];

		/* IPv4 header */
		if (new_ctx & GEM_TXFLAG_IPv4) {
			tcp->lower_setup.ip_fields.ipcss = EHDLEN;
			tcp->lower_setup.ip_fields.ipcso = 
			    EHDLEN + offsetof(struct ip, ip_sum);
			tcp->lower_setup.ip_fields.ipcse = LE_16(hck_start - 1);
E 4
			hcksum_cmd = E1000_TXD_CMD_IP;
D 4
			break;
E 4
I 4
		} else {
			/* others, i.e. IPv6 */
			tcp->lower_setup.ip_config = 0;
			hcksum_cmd = 0;
E 4
		}

I 4
		/* TCP or UDP */
		tcp->upper_setup.tcp_fields.tucss = hck_start;
		tcp->upper_setup.tcp_fields.tucse = 0;
		tcp->upper_setup.tcp_fields.tucso = hck_stuff;

	 	if (new_ctx & GEM_TXFLAG_TCP) {
			/*
			 * XXX - we must request IP checksum too, otherwize
			 * ip check sum field will be cleared.
			 */
			hcksum_cmd |= E1000_TXD_CMD_TCP;
		}

E 4
		tcp->tcp_seg_setup.data = 0;
		tcp->cmd_and_length =
D 4
			LE32(hcksum_cmd | E1000_TXD_CMD_DEXT | lp->txd_cmd);
E 4
I 4
		    LE_32(hcksum_cmd | E1000_TXD_CMD_DEXT | lp->txd_cmd);
E 4

		/* we consumed an additional slot */
D 2
		slot = SLOT(slot + 1, TX_RING_SIZE);
E 2
		used++;
#undef EHDLEN
	}
	lp->tx_cksum_ctx = new_ctx;
D 5
#endif /* GEM_CONFIG_CKSUM_OFFLOAD  && defined(CONFIG_VLAN) */
E 5
I 5
#endif /* CONFIG_CKSUM_OFFLOAD  && defined(CONFIG_VLAN) */
E 5

D 2
#if DEBUG_LEVEL > 3
	flags |= GEM_TXFLAG_INTR;
#endif
E 2
	txd_lower |= lp->txd_cmd;

D 2
	dcp = dmacookie;
	for (i = 0; i < frags - 1; i++) {
E 2
I 2
	for (dcp = dmacookie, i = 0; i < frags; dcp++, i++) {
E 2
D 4
		tdp = &((struct em_tx_desc *) dp->tx_ring)[
D 2
				SLOT(slot + i, TX_RING_SIZE)];
		tdp->buffer_addr = LE64(dcp->dmac_laddress);
		tdp->lower.data  = LE32(txd_lower | dcp->dmac_size);
E 2
I 2
				SLOT(slot + used, TX_RING_SIZE)];
E 4
I 4
		tdp = &((struct e1000_tx_desc *)dp->tx_ring)[
		    SLOT(slot + used, dp->gc.gc_tx_ring_size)];
E 4
		used++;

		addr = dcp->dmac_laddress;
D 4
		len  = dcp->dmac_size;
E 4
I 4
		len = dcp->dmac_size;
E 4
		if (lp->pcix_82544 && len > 4) {
			switch (((addr & 0x7) + (len & 0xf)) & 0xf) {
			case 1: case 2: case 3: case 4:
			case 9: case 0xa: case 0xb: case 0xc:
				len -= 4;
D 4
				tdp->buffer_addr = LE64(addr);
				tdp->lower.data  = LE32(txd_lower | len);
				tdp->upper.data  = LE32(txd_upper);
E 4
I 4
				tdp->buffer_addr = LE_64(addr);
				tdp->lower.data = LE_32(txd_lower | len);
				tdp->upper.data = LE_32(txd_upper);
E 4

				addr += len;
				len = 4;

D 4
				tdp = &((struct em_tx_desc *) dp->tx_ring)[
					SLOT(slot + used, TX_RING_SIZE)];
E 4
I 4
				tdp = &((struct e1000_tx_desc *)dp->tx_ring)[
				    SLOT(slot + used, dp->gc.gc_tx_ring_size)];
E 4
				used++;
			}
		}

D 4
		tdp->buffer_addr = LE64(addr);
		tdp->lower.data  = LE32(txd_lower | len);
E 2
		tdp->upper.data  = LE32(txd_upper);
E 4
I 4
		tdp->buffer_addr = LE_64(addr);
		tdp->lower.data = LE_32(txd_lower | len);
		tdp->upper.data = LE_32(txd_upper);
E 4
D 2
		dcp++;
E 2
	}

D 2
#ifdef GEM_CONFIG_VLAN
	if ((vtag = (flags & GEM_TXFLAG_VTAG)) != 0) {
		txd_lower |= E1000_TXD_CMD_VLE;
E 2
I 2
	/* fix last descriptor */
#ifdef CONFIG_VLAN
D 4
	if ((vtag = (flags & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT) != 0) {
		DPRINTF(2, (CE_CONT, "%s: %s: vtag:%x",
			dp->name, __func__, vtag));
		tdp->lower.data |= LE32(E1000_TXD_CMD_VLE);
		tdp->upper.fields.special = LE16(vtag);
E 4
I 4
	vtag = (flags & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT;
	if (vtag) {
		DPRINTF(2, (CE_CONT, CONS "%s: %s: vtag:%x",
		    dp->name, __func__, vtag));
		tdp->lower.data |= LE_32(E1000_TXD_CMD_VLE);
		tdp->upper.fields.special = LE_16(vtag);
E 4
E 2
	}
#endif
D 2
	/* for last descriptor */
	txd_lower |= E1000_TXD_CMD_EOP;
E 2
I 2
D 4
	tdp->lower.data |= LE32(E1000_TXD_CMD_EOP);
E 4
I 4
	tdp->lower.data |= LE_32(E1000_TXD_CMD_EOP | E1000_TXD_CMD_RS);
E 4
E 2

D 2
	tdp = &((struct em_tx_desc *) dp->tx_ring)[
			SLOT(slot + i, TX_RING_SIZE)];
	tdp->buffer_addr = LE64(dcp->dmac_laddress);
	tdp->lower.data  = LE32(txd_lower | dcp->dmac_size);
	tdp->upper.data  = LE32(txd_upper);
#ifdef GEM_CONFIG_VLAN
	tdp->upper.fields.special = LE16(vtag);
#endif
E 2
	return (used);
}
I 4
#endif
E 4

static void
em_tx_start(struct gem_dev *dp, int start_slot, int nslots)
{
D 2
	struct em_dev		*lp = (struct em_dev *)dp->private;
#ifdef notdef
	if () {
		end_slot = SLOT(start_slot + nslots, TX_RING_SIZE);
		slot = lp->tx_last_slot;
E 2
I 2
D 4
	struct em_dev	*lp = (struct em_dev *)dp->private;
E 4
I 4
	struct em_dev	*lp = dp->private;
E 4

	/* first of all, record the real descriptor tail position */
D 4
	lp->tx_tail_real = SLOT(start_slot + nslots, TX_RING_SIZE);
E 4
I 4
	lp->tx_tail_real = SLOT(start_slot + nslots, dp->gc.gc_tx_ring_size);
E 4

I 4
	if (
E 4
#ifndef TEST_82547
D 4
	if (lp->hw.mac_type == em_82547 && !dp->full_duplex)
E 4
I 4
	    lp->hw.mac.type == e1000_82547 &&
E 4
#endif
D 4
	{
E 4
I 4
	    !dp->full_duplex) {
E 4
		uint32_t	txd_lower;
		int		accepted;
		int		len;
		int		slot;
		int		i;
D 4
		struct em_tx_desc *tdp;
E 4
I 4
		struct e1000_tx_desc *tdp;
E 4

		if (lp->tx_fifo_full) {
			/* do nothing */
			return;
		}

E 2
		len = 0;
D 2
		i   = 0;
		while (slot !=  end_slot) {
E 2
I 2
		accepted = 0;
		for (i = 0; i < nslots; i++) {
D 4
			slot = SLOT(start_slot + i, TX_RING_SIZE);
E 2
			tdp = &((struct em_tx_desc *) dp->tx_ring)[slot];
D 2
			if (tdp->lower & TYP) {
				/* this is not real fragmet */
E 2
I 2
			txd_lower = LE32(tdp->lower.data);
E 4
I 4
			slot = SLOT(start_slot + i, dp->gc.gc_tx_ring_size);
			tdp = &((struct e1000_tx_desc *)dp->tx_ring)[slot];
			txd_lower = tdp->lower.data;
			txd_lower = LE_32(txd_lower);
E 4

			if ((txd_lower &
D 4
				(E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D))
					== E1000_TXD_CMD_DEXT) {
E 4
I 4
			    (E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D))
			    == E1000_TXD_CMD_DEXT) {
E 4
				/* this is not real fragment */
E 2
				continue;
			}
D 2
			len += LE32(txd_lower | dcp->dmac_size) & 0xffff;
			if (eop) {
				if (lp->tx_fifo_head + len > lp->tx_fifo_size) {
					/* no room in tx fifo */
					lp->tx_fifo_full = TRUE;
					break;
				}
				lp->tx_fifo_head += len;
				len = 0;
				last_slot = slot;
E 2
I 2

			/* accumulate fragment size */
			len += txd_lower & 0xffff;

			if ((txd_lower & E1000_TXD_CMD_EOP) == 0) {
				continue;
E 2
			}
D 2
			i++;
			slot = SLOT(slot + i, TX_RING_SIZE);
		}
		start_slot = lp->tx_last_slot;
		nslots = i;
	}
E 2

D 2
	if (nslots == 0) {
		/* fifo is full */
		if (lp->tx_fifo_full && lp->tx_fifo_head == lp->tx_fifo_tail) {
			em_reset_tx_fifo(dp);
			goto again;
E 2
I 2
			accepted = i + 1;

			/* we are at the last fragment in a packet */
D 4
			lp->tx_fifo_head += 
				ROUNDUP(len + EM_FIFO_HDR, EM_FIFO_HDR);
E 4
I 4
			lp->tx_fifo_head +=
			    ROUNDUP(len + EM_FIFO_HDR, EM_FIFO_HDR);
E 4
			len = 0;

			if (lp->tx_fifo_head > lp->tx_fifo_thresh) {
				/* this is the last packet we can accept */
				lp->tx_fifo_full = B_TRUE;
				DPRINTF(3, (CE_CONT,
D 4
					"%s: %s: tx fifo is full",
					dp->name, __func__));
E 4
I 4
				    CONS "%s: %s: tx fifo is full",
				    dp->name, __func__));
E 4
				break;
			}
E 2
		}
D 2
		return;
E 2
I 2
D 4
		DPRINTF(3, (CE_CONT, "%s: %s: nslots:%d, accepted:%d",
				dp->name, __func__, nslots, accepted));
E 4
I 4
		DPRINTF(3, (CE_CONT, CONS "%s: %s: nslots:%d, accepted:%d",
		    dp->name, __func__, nslots, accepted));
E 4
		/* fix valid slots */
		ASSERT(accepted > 0);
		nslots = accepted;
E 2
	}
D 2
#endif
E 2
I 2

E 2
	gem_tx_desc_dma_sync(dp, start_slot, nslots, DDI_DMA_SYNC_FORDEV);

	if (dp->mac_active) {
D 2
		E1000_WRITE_REG(&lp->hw,
			TDT, SLOT(start_slot + nslots, TX_RING_SIZE));
E 2
I 2
D 4
		lp->tx_tail = SLOT(start_slot + nslots, TX_RING_SIZE);
		E1000_WRITE_REG(&lp->hw, TDT, lp->tx_tail);
E 4
I 4
		lp->tx_tail = SLOT(start_slot + nslots, dp->gc.gc_tx_ring_size);
		E1000_WRITE_REG(&lp->hw, E1000_TDT(0), lp->tx_tail);
E 4
E 2
	}
}

static void
em_rx_desc_write(struct gem_dev *dp, int slot,
D 4
	    ddi_dma_cookie_t *dmacookie, int frags)
E 4
I 4
    ddi_dma_cookie_t *dmacookie, int frags)
E 4
{
D 4
	struct em_rx_desc	*rdp;
	struct em_dev		*lp = (struct em_dev *)dp->private;
E 4
I 4
	struct e1000_rx_desc	*rdp;
	struct em_dev		*lp = dp->private;
E 4
#if DEBUG_LEVEL > 2
	int			i;

	ASSERT(frags == 1);

D 4
	cmn_err(CE_CONT, CONS
		"%s: %s seqnum: %d, slot %d, frags: %d",
		dp->name, __func__, dp->rx_active_tail, slot, frags);
E 4
I 4
	cmn_err(CE_CONT,
	    CONS "%s: %s seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_active_tail, slot, frags);
E 4
	for (i = 0; i < frags; i++) {
D 4
		cmn_err(CE_CONT, CONS "  frag: %d addr: 0x%x, len: 0x%x",
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 4
I 4
		cmn_err(CE_CONT, CONS "  frag: %d addr: 0x%llx, len: 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 4
	}
#endif
D 4
	rdp = &((struct em_rx_desc *) dp->rx_ring)[slot];
E 4
I 4
	rdp = &((struct e1000_rx_desc *)dp->rx_ring)[slot];
E 4

D 4
	rdp->buffer_addr = LE64(dmacookie->dmac_laddress);
E 4
I 4
	rdp->buffer_addr = LE_64(dmacookie->dmac_laddress);
E 4
	rdp->status = 0;
}

static void
em_rx_start(struct gem_dev *dp, int start_slot, int nslots)
{
D 4
	struct em_dev	*lp = (struct em_dev *)dp->private;
E 4
I 4
	struct em_dev	*lp = dp->private;
E 4

	gem_rx_desc_dma_sync(dp, start_slot, nslots, DDI_DMA_SYNC_FORDEV);
	if (dp->mac_active) {
		E1000_WRITE_REG(&lp->hw,
D 4
			RDT, SLOT(start_slot + nslots, RX_RING_SIZE));
E 4
I 4
		    E1000_RDT(0),
		    SLOT(start_slot + nslots, dp->gc.gc_rx_ring_size));
E 4
	}
}

I 2
static int
em_82547_tx_fifo_reset(struct gem_dev *dp)
D 4
{	
E 4
I 4
{
E 4
	uint32_t	tdt;
	uint32_t	tdh;
	uint32_t	tdft;
	uint32_t	tdfh;
	uint32_t	tdfts;
	uint32_t	tdfhs;
	uint32_t	tdfpc;
	uint32_t	tctl;
D 4
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = dp->private;
E 4

D 4
	if ( ((tdt   = E1000_READ_REG(&lp->hw, TDT)) ==
	      (tdh   = E1000_READ_REG(&lp->hw, TDH))) &&
	     ((tdft  = E1000_READ_REG(&lp->hw, TDFT)) == 
	      (tdfh  = E1000_READ_REG(&lp->hw, TDFH))) &&
	     ((tdfts = E1000_READ_REG(&lp->hw, TDFTS)) ==
	      (tdfhs = E1000_READ_REG(&lp->hw, TDFHS))) &&
	     ((tdfpc = E1000_READ_REG(&lp->hw, TDFPC)) == 0)) {
E 4
I 4
	if (((tdt = E1000_READ_REG(&lp->hw, E1000_TDT(0))) ==
	    (tdh = E1000_READ_REG(&lp->hw, E1000_TDH(0)))) &&
	    ((tdft = E1000_READ_REG(&lp->hw, E1000_TDFT)) ==
	    (tdfh = E1000_READ_REG(&lp->hw, E1000_TDFH))) &&
	    ((tdfts = E1000_READ_REG(&lp->hw, E1000_TDFTS)) ==
	    (tdfhs = E1000_READ_REG(&lp->hw, E1000_TDFHS))) &&
	    ((tdfpc = E1000_READ_REG(&lp->hw, E1000_TDFPC)) == 0)) {
E 4

		/* Disable TX unit */
D 4
		tctl = E1000_READ_REG(&lp->hw, TCTL);
		E1000_WRITE_REG(&lp->hw, TCTL, tctl & ~E1000_TCTL_EN);
E 4
I 4
		tctl = E1000_READ_REG(&lp->hw, E1000_TCTL);
		E1000_WRITE_REG(&lp->hw, E1000_TCTL, tctl & ~E1000_TCTL_EN);
E 4

		/* Reset FIFO pointers */
D 4
		E1000_WRITE_REG(&lp->hw, TDFT,  lp->tx_head_addr);
		E1000_WRITE_REG(&lp->hw, TDFH,  lp->tx_head_addr);
		E1000_WRITE_REG(&lp->hw, TDFTS, lp->tx_head_addr);
		E1000_WRITE_REG(&lp->hw, TDFHS, lp->tx_head_addr);
E 4
I 4
		E1000_WRITE_REG(&lp->hw, E1000_TDFT,  lp->tx_head_addr);
		E1000_WRITE_REG(&lp->hw, E1000_TDFH,  lp->tx_head_addr);
		E1000_WRITE_REG(&lp->hw, E1000_TDFTS, lp->tx_head_addr);
		E1000_WRITE_REG(&lp->hw, E1000_TDFHS, lp->tx_head_addr);
E 4

		/* Re-enable TX unit */
D 4
		E1000_WRITE_REG(&lp->hw, TCTL, tctl);
E 4
I 4
		E1000_WRITE_REG(&lp->hw, E1000_TCTL, tctl);
E 4
		E1000_WRITE_FLUSH(&lp->hw);

		lp->tx_fifo_head = 0;
		lp->tx_fifo_reset_cnt++;
		lp->tx_fifo_full = B_FALSE;
D 4
		DPRINTF(3, (CE_CONT, "%s: %s: tx fifo was reset successfully",
			dp->name, __func__));
E 4
I 4
		DPRINTF(3, (CE_CONT,
		    CONS "%s: %s: tx fifo was reset successfully",
		    dp->name, __func__));
E 4
		return (GEM_SUCCESS);
D 4
	}
	else {
		DPRINTF(3, (CE_CONT, "%s: %s: failed to reset tx fifo: "
			"tdt:%x, tdh:%x, "
			"tdft:%x, tdfh:%x, "
			"tdfts:%x, tdfhs:%x, "
			"tdfpc:%x",
			dp->name, __func__,
			tdt, tdh,
			tdft, tdfh,
			tdfts, tdfhs,
			tdfpc));
E 4
I 4
	} else {
		DPRINTF(3, (CE_CONT, CONS "%s: %s: failed to reset tx fifo: "
		    "tdt:%x, tdh:%x, "
		    "tdft:%x, tdfh:%x, "
		    "tdfts:%x, tdfhs:%x, "
		    "tdfpc:%x",
		    dp->name, __func__,
		    tdt, tdh,
		    tdft, tdfh,
		    tdfts, tdfhs,
		    tdfpc));
E 4
		return (GEM_FAILURE);
	}
}

static void
em_txfifo_restart(struct gem_dev *dp)
{
	int		rest;
D 4
	struct em_dev	*lp = (struct em_dev *) dp->private;
	
E 4
I 4
	struct em_dev	*lp = dp->private;

E 4
	if (em_82547_tx_fifo_reset(dp) == GEM_SUCCESS) {
		ASSERT(!lp->tx_fifo_full);

		/* we also reload descriptors */
		if ((rest = lp->tx_tail_real - lp->tx_tail) < 0) {
D 4
			rest += TX_RING_SIZE;
E 4
I 4
			rest += dp->gc.gc_tx_ring_size;
E 4
		}
		if (rest > 0) {
			em_tx_start(dp, lp->tx_head, rest);
		}
		lp->txfifo_watcher_id = 0;
D 4
	}
	else {
E 4
I 4
	} else {
E 4
		/*
		 * We cannot load the tx descriptors for the time
		 * being, because tx fifo isn't empty now.
		 * Wait while tx fifo is draining.
		 */
		lp->txfifo_watcher_id =
D 4
			timeout(em_txfifo_watcher, (void *)dp, 1);
E 4
I 4
		    timeout(em_txfifo_watcher, (void *)dp, 1);
E 4
	}
}

static void
em_txfifo_watcher(void *arg)
{
D 4
	struct gem_dev	*dp = (struct gem_dev *) arg;
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct gem_dev	*dp = arg;
	struct em_dev	*lp = dp->private;
E 4

	mutex_enter(&dp->intrlock);
	mutex_enter(&dp->xmitlock);
	if (!lp->tx_fifo_full) {
		cmn_err(CE_WARN, "!%s: %s: tx fifo isn't full",
D 4
			dp->name, __func__);
E 4
I 4
		    dp->name, __func__);
E 4
		goto x;
	}

	em_txfifo_restart(dp);

x:
	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);
}

I 4
#ifdef GEM_CONFIG_TX_HEAD_PTR
static uint_t
em_tx_desc_head(struct gem_dev *dp)
{
	struct em_dev	*lp = dp->private;

	if (lp->nic_active) {
		lp->tx_head = E1000_READ_REG(&lp->hw, E1000_TDH(0));
	}
	return (lp->tx_head);
}
#else
E 4
#define	INSIDE(slot, head, tail)	\
	(((head) <= (tail)) ?	\
		((head) <= (slot) && (slot) < (tail)) :	\
D 4
		((slot) < (tail)  || (head) <= (slot)))
E 4
I 4
		((slot) < (tail) || (head) <= (slot)))
E 4
E 2
static uint_t
em_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	uint8_t			status;
	int			i;
I 2
	int			last_slot;
E 2
	int			cols;
D 4
	struct em_tx_desc	*tdp;
D 2
#ifdef DEBUG_LEVEL
E 2
	struct em_dev		*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct e1000_tx_desc	*tdp;
	struct em_dev		*lp = dp->private;
E 4
D 2
	clock_t			delay;
#endif
E 2
I 2

E 2
D 4
	tdp = &((struct em_tx_desc *) dp->tx_ring)[
			SLOT(slot + ndesc - 1, TX_RING_SIZE)];
E 4
I 4
	tdp = &((struct e1000_tx_desc *)dp->tx_ring)[
	    SLOT(slot + ndesc - 1, dp->gc.gc_tx_ring_size)];
E 4

	status = tdp->upper.fields.status;

	DPRINTF(1, (CE_CONT,
D 4
		CONS "%s: time:%d %s: slot:%d, status:0x%x",
		dp->name, ddi_get_lbolt(), __func__,
		slot, status));
E 4
I 4
	    CONS "%s: time:%d %s: slot:%d, status:0x%x",
	    dp->name, ddi_get_lbolt(), __func__,
	    slot, status));
E 4
D 2

E 2
I 2
#ifdef CONFIG_USE_TXDWB
E 2
	if ((status & E1000_TXD_STAT_DD) == 0) {
		return (0);
	}
I 2
D 4
	lp->tx_head = SLOT(slot + ndesc, TX_RING_SIZE);
E 4
I 4
	lp->tx_head = SLOT(slot + ndesc, dp->gc.gc_tx_ring_size);
E 4
#else
	if (lp->nic_active) {
D 4
		lp->tx_head = E1000_READ_REG(&lp->hw, TDH);
E 4
I 4
		lp->tx_head = E1000_READ_REG(&lp->hw, E1000_TDH(0));
E 4
	}
D 4
	last_slot = SLOT(slot + ndesc - 1, TX_RING_SIZE);
E 4
I 4
	last_slot = SLOT(slot + ndesc - 1, dp->gc.gc_tx_ring_size);
E 4
	if (INSIDE(last_slot, lp->tx_head, lp->tx_tail)) {
		return (0);
	}
#endif
	if (lp->tx_fifo_full && lp->tx_head == lp->tx_tail) {
		em_txfifo_restart(dp);
	}
E 2

	return (GEM_TX_DONE);
}
I 4
#endif /* GEM_CONFIG_TX_HEAD_PTR */
E 4

static uint64_t
em_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	uint64_t		len;
	uint64_t		flags;
	uint8_t			status;
D 4
	struct em_rx_desc	*rdp;
	struct em_dev		*lp = (struct em_dev *)dp->private;
E 4
I 4
	struct e1000_rx_desc	*rdp;
	struct em_dev		*lp = dp->private;
E 4

D 4
	rdp = &((struct em_rx_desc *) dp->rx_ring)[slot];
E 4
I 4
	rdp = &((struct e1000_rx_desc *)dp->rx_ring)[slot];
E 4

D 4
	status = rdp->status;
E 4
I 4
	status = LE_8(rdp->status);
E 4

	DPRINTF(2, (CE_CONT,
D 4
		CONS "%s: time:%d %s: slot:%d, status:0x%x",
		dp->name, ddi_get_lbolt(), __func__,
		slot, status));
E 4
I 4
	    CONS "%s: time:%d %s: slot:%d, status:0x%x",
	    dp->name, ddi_get_lbolt(), __func__,
	    slot, status));
E 4

	if ((status & E1000_RXD_STAT_DD) == 0) {
		return (0);
	}
D 5

E 5
I 5
#ifdef CONFIG_NO_RXCRC
	len = LE_16(rdp->length);
#else
E 5
D 4
	DPRINTF(2, (CE_CONT,
		CONS "%s: time:%d %s: slot:%d, status:0x%x, errors:0x%x",
		dp->name, ddi_get_lbolt(), __func__,
		slot, status, rdp->errors));
E 4
I 4
	len = LE_16(rdp->length) - ETHERFCSL;
E 4
D 5

E 5
I 5
#endif
E 5
D 4
	len = LE16(rdp->length) - ETHERFCSL;
E 4
I 4
	DPRINTF(1, (CE_CONT,
	    CONS "%s: time:%d %s: slot:%d, status:0x%x, errors:0x%x, len:%d",
	    dp->name, ddi_get_lbolt(), __func__,
	    slot, status, rdp->errors, len));

E 4
	flags = GEM_RX_DONE;

#ifdef CONFIG_VLAN
D 4
	if ((status & E1000_RXD_STAT_VP) != 0) {
		flags |= ((uint64_t)LE16(rdp->special)) << GEM_RX_VTAG_SHIFT;
E 4
I 4
	if (status & E1000_RXD_STAT_VP) {
		flags |= ((uint64_t)LE_16(rdp->special)) << GEM_RX_VTAG_SHIFT;
E 4
	}
#endif
D 5
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
I 5
#if defined(CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
	/* XXX - we have full hw checksum function for rx */
D 4
	if ((lp->hw.mac_type >= em_82543) &&
E 4
I 4
	if ((lp->hw.mac.type >= e1000_82543) &&
E 4
	    (status & E1000_RXD_STAT_IXSM) == 0) {

D 4
		if ((status & E1000_RXD_STAT_IPCS) != 0 &&
			 (rdp->errors & E1000_RXD_ERR_IPE) == 0) {
E 4
I 4
		if ((status & E1000_RXD_STAT_IPCS) &&
		    (rdp->errors & E1000_RXD_ERR_IPE) == 0) {
E 4
			flags |= GEM_RX_CKSUM_IPv4;
		}

D 4
		if ((status & E1000_RXD_STAT_TCPCS) != 0 &&
E 4
I 4
		if ((status & E1000_RXD_STAT_TCPCS) &&
E 4
		    (rdp->errors & E1000_RXD_ERR_TCPE) == 0) {
			/* this includes both of tcp and udp */
			flags |= (GEM_RX_CKSUM_TCP | GEM_RX_CKSUM_UDP);
		}
	}
#endif
	return (flags | (len & GEM_RX_LEN));
}

static void
em_tx_desc_init(struct gem_dev *dp, int slot)
{
D 4
	bzero(&((struct em_tx_desc *) dp->tx_ring)[slot],
			sizeof(struct em_tx_desc));
E 4
I 4
	bzero(&((struct e1000_tx_desc *)dp->tx_ring)[slot],
	    sizeof (struct e1000_tx_desc));
E 4
}

static void
em_rx_desc_init(struct gem_dev *dp, int slot)
{
D 4
	bzero(&((struct em_rx_desc *) dp->rx_ring)[slot],
			sizeof(struct em_rx_desc));
E 4
I 4
	bzero(&((struct e1000_rx_desc *)dp->rx_ring)[slot],
	    sizeof (struct e1000_rx_desc));
E 4
}

/*
 * Device depend interrupt handler
 */
D 4
static u_int
E 4
I 4
static uint_t
E 4
em_interrupt(struct gem_dev *dp)
{
D 4
	uint32_t	icr;
E 4
I 4
	uint32_t	reg_icr;
E 4
	uint_t		flags = 0;
D 4
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = dp->private;
E 4

D 4
	icr = E1000_READ_REG(&lp->hw, ICR);
E 4
I 4
	reg_icr = E1000_READ_REG(&lp->hw, E1000_ICR);
E 4

D 4
	DPRINTF(2, (CE_CONT,"!%s: time:%d %s: icr:%x",
		dp->name, ddi_get_lbolt(), __func__, icr));
E 4
I 4
	DPRINTF(4, (CE_CONT, CONS "%s: time:%d %s: icr:%x",
	    dp->name, ddi_get_lbolt(), __func__, reg_icr));
E 4
D 3
#ifdef CONFIG_PCIE
	if (lp->hw.mac_type >= em_82571 && (icr & E1000_ICR_INT_ASSERTED) == 0) {
E 3
I 3

D 4
	if (lp->hw.mac_type >= em_82571 &&
	   (icr & E1000_ICR_INT_ASSERTED) == 0) {
E 4
I 4
	if (reg_icr == 0 || (lp->hw.mac.type >= e1000_82571 &&
	    (reg_icr & E1000_ICR_INT_ASSERTED) == 0) ||
	/*
	 * XXX: some laptops trigger several spurious interrupts
	 * on em(4) when in the resume cycle. The ICR register
	 * reports all-ones value in this case. Processing such
	 * interrupts would lead to a freeze. I don't know why.
	 */
	    reg_icr == 0xffffffffU) {
E 4
E 3
		return (DDI_INTR_UNCLAIMED);
D 3
	} else
#endif
	if ((icr & lp->our_intr_mask) == 0) {
E 3
I 3
D 4
	}
	else if ((icr & lp->our_intr_mask) == 0) {
E 4
I 4
	} else if ((reg_icr & lp->our_intr_mask) == 0) {
E 4
E 3
		/* not for us */
		return (DDI_INTR_UNCLAIMED);
	}

D 4
	DPRINTF(2, (CE_CONT,"!%s: time:%d %s: icr:%x",
		dp->name, ddi_get_lbolt(), __func__, icr));
E 4
I 4
	DPRINTF(1, (CE_CONT, CONS "%s: time:%d %s: icr:%x",
	    dp->name, ddi_get_lbolt(), __func__, reg_icr));
E 4

	if (!dp->mac_active) {
		return (DDI_INTR_CLAIMED);
	}

D 4
	if ((icr & (E1000_ICR_RXSEQ | E1000_ICR_RXDMT0 |
				E1000_ICR_RXO | E1000_ICR_RXT0)) != 0) {
E 4
I 4
	reg_icr &= lp->our_intr_mask;

	if (reg_icr & (E1000_ICR_RXT0 | E1000_ICR_RXDMT0)) {
E 4
D 3
		gem_receive(dp);
E 3
I 3
		(void) gem_receive(dp);
E 3
	}

D 4
	if ((icr & (E1000_ICR_TXDW | E1000_ICR_TXQE)) != 0) {
E 4
I 4
	if (reg_icr & (E1000_ICR_TXDW | E1000_ICR_TXQE)) {
E 4
		if (gem_tx_done(dp)) {
			flags |= INTR_RESTART_TX;
		}
	}

D 4
	if ((icr & (E1000_ICR_RXSEQ | E1000_ICR_LSC)) != 0) {
		DPRINTF(0, (CE_NOTE, "!%s: %s: link status changed",
			dp->name, __func__));
E 4
I 4
	if (reg_icr & (E1000_ICR_RXSEQ | E1000_ICR_LSC)) {
		DPRINTF(0, (CE_NOTE, CONS "%s: %s: link status changed, icr:%x",
		    dp->name, __func__, reg_icr));
I 5
		lp->hw.mac.get_link_status = 1;
E 5
#ifdef GEM3
		gem_mii_link_check(dp);
#else
E 4
		if (gem_mii_link_check(dp)) {
			flags |= INTR_RESTART_TX;
		}
I 4
#endif
E 4
	}

D 4
	if ((icr & E1000_ICR_RXO) != 0) {
E 4
I 4
	if (reg_icr & E1000_ICR_RXO) {
E 4
		cmn_err(CE_NOTE, "!%s: RX overrun", dp->name);
	}

	return (DDI_INTR_CLAIMED | flags);
}

/* ======================================================== */
/*
 * HW depend MII routine
 */
/* ======================================================== */
static void
em_mii_sync(struct gem_dev *dp)
{
	/* nothing to do */
}

I 4

static boolean_t
D 5
em_link_status(struct e1000_hw *hw)
E 5
I 5
em_update_link_status(struct gem_dev *dp)
E 5
{
I 5
	struct em_dev	*lp = dp->private;
	struct e1000_hw	*hw = &lp->hw;
E 5
	u32 link_check = B_FALSE;

	/* Get the cached link value or read phy for real */
D 5
	hw->mac.get_link_status = TRUE;
E 5
I 5
#ifdef notdef
	hw->mac.get_link_status = 1;
#endif
E 5
	switch (hw->phy.media_type) {
	case e1000_media_type_copper:
		if (hw->mac.get_link_status) {
			/* Do the work to read phy */
			e1000_check_for_link(hw);
			link_check = !hw->mac.get_link_status;
I 5
#ifdef notdef
			/*
			 * XXX - The lines below were moved to set_media
			 * to adapt gem framework.
			 */
E 5
			if (link_check) {
				/* ESB2 fix */
				e1000_cfg_on_link_up(hw);
			}
I 5
#endif
E 5
		} else {
			link_check = B_TRUE;
		}
		break;

	case e1000_media_type_fiber:
		e1000_check_for_link(hw);
		link_check =
		    (E1000_READ_REG(hw, E1000_STATUS) & E1000_STATUS_LU) != 0;
		break;

	case e1000_media_type_internal_serdes:
		e1000_check_for_link(hw);
		link_check = (hw->mac.serdes_has_link) != 0;
		break;

	default:
	case e1000_media_type_unknown:
		break;
	}

I 5
#ifdef notdef
	/*
	 * XXX - The lines below were moved to set_media to adapt
	 * gem framework.
	 */

	/* Now check for a transition */
	if (link_check && (dp->mii_state != MII_STATE_LINKUP)) {

		e1000_get_speed_and_duplex(hw, &adapter->link_speed,
		    &adapter->link_duplex);

		/* Check if we must disable SPEED_MODE bit on PCI-E */
		if ((dp->speed != GEM_SPD_1000) &&
		    ((hw->mac.type == e1000_82571) ||
		    (hw->mac.type == e1000_82572))) {
			int tarc0;
			tarc0 = E1000_READ_REG(hw, E1000_TARC(0));
			tarc0 &= ~SPEED_MODE_BIT;
			E1000_WRITE_REG(hw, E1000_TARC(0), tarc0);
		}
	}
#endif
E 5
	return (link_check);
}

E 4
static uint16_t
em_mii_read(struct gem_dev *dp, uint32_t reg)
{
	uint16_t	val;
D 4
	struct em_dev	*lp = (struct em_dev *)dp->private;
E 4
I 4
	struct em_dev	*lp = dp->private;
	struct e1000_hw	*hw = &lp->hw;
E 4

D 4
	if (em_read_phy_reg(&lp->hw, reg, &val) != E1000_SUCCESS) {
		val = 0xffff;
E 4
I 4
D 5
	if (e1000_read_phy_reg(hw, reg, &val) != E1000_SUCCESS) {
		val = 0;
E 4
	}
I 4

	if (reg == MII_STATUS) {
		/* fix link status */
		if (em_link_status(hw)) {
			val |= MII_STATUS_LINKUP;
E 5
I 5
	if (reg == MII_STATUS && hw->mac.get_link_status == 0) {
		/* use cached link status */
		val = dp->mii_status;
		if (em_update_link_status(dp)) {
			val |= MII_STATUS_LINKUP | MII_STATUS_ANDONE;
E 5
		} else {
D 5
			val &= ~MII_STATUS_LINKUP;
E 5
I 5
			val &= ~(MII_STATUS_LINKUP | MII_STATUS_ANDONE);
E 5
		}
I 5

	} else if (e1000_read_phy_reg(hw, reg, &val) != E1000_SUCCESS) {
		val = 0;
E 5
	}

E 4
	return (val);
}

static void
em_mii_write(struct gem_dev *dp, uint32_t reg, uint16_t val)
{
D 4
	struct em_dev	*lp = (struct em_dev *)dp->private;
E 4
I 4
#ifdef notdef
	struct em_dev	*lp = dp->private;
	struct e1000_hw	*hw = &lp->hw;
E 4

D 4
	if (em_write_phy_reg(&lp->hw, reg, val) != E1000_SUCCESS) {
		cmn_err(CE_WARN, "%s: %s: failed to write to PHY",
			dp->name, __func__);
E 4
I 4
	if (reg == MII_CONTROL && (val & MII_CONTROL_RESET)) {
		/* allow resetting phy and restarting autonegotiation */
		hw->phy.reset_disable = B_FALSE;
E 4
	}
I 4
#endif
	/* don't write to phy */
E 4
}

static int
I 4
em_mii_probe(struct gem_dev *dp)
{
	uint16_t	status;
	struct em_dev	*lp = dp->private;

	/*
	 * We need not scan phy here, because e1000_init_phy_params(),
	 * which has been called by e1000_setup_init_funcs(), is
	 * responsible for identifying the phy.
	 */

	/* fake gem */
	dp->mii_phy_addr = 1;

I 5
	/* force to read real phy status */
	lp->hw.mac.get_link_status = 1;

E 5
	status = gem_mii_read(dp, MII_STATUS);

	dp->mii_status = status;
	dp->mii_status_ro = ~status;
	dp->mii_phy_id  = (gem_mii_read(dp, MII_PHYIDH) << 16) |
	    gem_mii_read(dp, MII_PHYIDL);

	if (dp->mii_phy_addr < 0) {
		cmn_err(CE_CONT, "!%s: using internal/non-MII PHY(0x%08x)",
		    dp->name, dp->mii_phy_id);
	} else {
		cmn_err(CE_CONT, "!%s: MII PHY (0x%08x) found at %d",
		    dp->name, dp->mii_phy_id, dp->mii_phy_addr);
	}

	cmn_err(CE_CONT,
	    "!%s: PHY control:%b, status:%b, advert:%b, lpar:%b, exp:%b",
	    dp->name,
	    gem_mii_read(dp, MII_CONTROL), MII_CONTROL_BITS,
	    status, MII_STATUS_BITS,
	    gem_mii_read(dp, MII_AN_ADVERT), MII_ABILITY_BITS,
	    gem_mii_read(dp, MII_AN_LPABLE), MII_ABILITY_BITS,
	    gem_mii_read(dp, MII_AN_EXPANSION), MII_AN_EXP_BITS);

	dp->mii_xstatus = 0;
	if (status & MII_STATUS_XSTATUS) {
		dp->mii_xstatus = gem_mii_read(dp, MII_XSTATUS);

		cmn_err(CE_CONT, "!%s: xstatus:%b",
		    dp->name, dp->mii_xstatus, MII_XSTATUS_BITS);

		dp->mii_xstatus &= ~MII_XSTATUS_1000BASET;
	}
	dp->mii_xstatus_ro = ~dp->mii_xstatus;

	return (GEM_SUCCESS);
}

static int
E 4
em_mii_init(struct gem_dev *dp)
{
D 4
	int	ret;
E 4
I 4
	struct em_dev	*lp = dp->private;
	struct e1000_hw	*hw = &lp->hw;
E 4

D 4
	ret = gem_mii_init_default(dp);
	if (ret != GEM_SUCCESS) {
D 3
		return ret;
E 3
I 3
		return (ret);
E 4
I 4
	/* setup defaults for link parameters */

	hw->mac.autoneg = B_TRUE;
	hw->phy.autoneg_wait_to_complete = B_FALSE;
	hw->phy.autoneg_advertised = AUTONEG_ADV_DEFAULT;

	/* Copper options */
	if (hw->phy.media_type == e1000_media_type_copper) {
		hw->phy.mdix = AUTO_ALL_MODES;
		hw->phy.disable_polarity_correction = B_FALSE;
		hw->phy.ms_type = e1000_ms_hw_default;
E 4
E 3
	}

D 4
	return (ret);
E 4
I 4
	return (GEM_SUCCESS);
E 4
}

I 4
static void
em_mii_config_param(struct gem_dev *dp)
{
	struct em_dev	*lp = dp->private;
	struct e1000_hw	*hw = &lp->hw;
	uint16_t	mii_stat;
	uint16_t	val;

	static uint16_t fc_cap_encode[4] = {
		/* none */		e1000_fc_none,
		/* symmetric */		e1000_fc_full,
		/* tx */		e1000_fc_tx_pause,
		/* rx-symmetric */	e1000_fc_rx_pause,
	};

	DPRINTF(0, (CE_CONT, "!%s: %s: called, nic_state:%d",
	    dp->name, __func__, dp->nic_state));

	/*
	 * Configure bits in advertisement register
	 */
	mii_stat = dp->mii_status;

	DPRINTF(1, (CE_CONT, "!%s: %s: MII_STATUS reg:%b",
	    dp->name, __func__, mii_stat, MII_STATUS_BITS));

	if ((mii_stat & MII_STATUS_ABILITY_TECH) == 0) {
		/* it's funny */
		cmn_err(CE_WARN, "!%s: wrong ability bits: mii_status:%b",
		    dp->name, mii_stat, MII_STATUS_BITS);
		return;
	}

	hw->mac.autoneg = dp->anadv_autoneg;

	val = 0;
	if (dp->anadv_100fdx) {
		val |= ADVERTISE_100_FULL;
	}
	if (dp->anadv_100hdx) {
		val |= ADVERTISE_100_HALF;
	}
	if (dp->anadv_10fdx) {
		val |= ADVERTISE_10_FULL;
	}
	if (dp->anadv_10hdx) {
		val |= ADVERTISE_10_HALF;
	}

	if (mii_stat & MII_STATUS_XSTATUS) {
		/*
		 * 1000Base-T GMII support
		 */
		if (!dp->anadv_autoneg) {
			/* enable manual configuration */
			switch (dp->anadv_1000t_ms) {
			default:
			case 0:	/* auto */
			case 1:	/* slave */
				hw->phy.ms_type = e1000_ms_force_slave;
				break;

			case 2:	/* master */
				hw->phy.ms_type = e1000_ms_force_master;
				break;
			}
		} else {
			if (dp->anadv_1000fdx) {
				val |= ADVERTISE_1000_FULL;
			}
			switch (dp->anadv_1000t_ms) {
			case 0: /* auto: do nothing */
			default:
				hw->phy.ms_type = e1000_ms_auto;
				break;

			case 1: /* slave */
				hw->phy.ms_type = e1000_ms_force_slave;
				break;

			case 2: /* master */
				hw->phy.ms_type = e1000_ms_force_master;
				break;
			}
		}
	}
	hw->phy.autoneg_advertised = val;

	DPRINTF(0, (CE_CONT,
	    "!%s: %s: setting autoneg:%d, advertised:%x, ms_type:%d",
	    dp->name, __func__,
	    hw->mac.autoneg, hw->phy.autoneg_advertised, hw->phy.ms_type));

	/* set flow control capability */
	hw->fc.requested_mode =
	    fc_cap_encode[dp->anadv_asmpause * 2 + dp->anadv_pause];

	/* Workaround: no TX flow ctrl for PCH */
	if (hw->mac.type == e1000_pchlan) {
		switch (hw->fc.requested_mode) {
		case e1000_fc_full:
			hw->fc.requested_mode = e1000_fc_rx_pause;
			break;

		case e1000_fc_tx_pause:
			hw->fc.requested_mode = e1000_fc_none;
			break;
		}
	}

	DPRINTF(0, (CE_CONT,
	    "!%s: %s: setting fc_requested_mode:%d, pause:%d, asmpause:%d",
	    dp->name, __func__,  hw->fc.requested_mode,
	    dp->anadv_pause, dp->anadv_asmpause));
I 5

	lp->hw.fc.current_mode = lp->hw.fc.requested_mode;
	e1000_force_mac_fc(&lp->hw);
E 5
}

static int
em_mii_config(struct gem_dev *dp)
{
	struct em_dev	*lp = dp->private;
	struct e1000_hw	*hw = &lp->hw;

	if (dp->nic_state < NIC_STATE_INITIALIZED) {
		return (GEM_FAILURE);
	}

	em_mii_config_param(dp);

	/* set parameters to PHY */
I 5
#ifdef CONFIG_SEPARETE_PHY
E 5
	(* lp->setup_link)(hw);
I 5
#else
	e1000_setup_link(hw);
#endif
E 5

#ifdef notdef
	/* avoid to restart auto-negotiation on autonegotiation timeout */
	hw->phy.reset_disable = B_TRUE;
#endif
	return (GEM_SUCCESS);
}

E 4
/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
I 4

E 4
D 5
static int
E 5
I 5
static void
E 5
D 4
em_attach_chip(struct gem_dev *dp)	
E 4
I 4
em_fixup_params(struct gem_dev *dp)
E 4
{
D 4
	uint32_t	rctl;
	uint32_t	pba;
E 4
I 4
	struct nfo_dev	*lp = dp->private;
D 5
	int	ret = GEM_SUCCESS;
E 5

	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d",
	    dp->name, __func__, ddi_get_lbolt()));

	/* fix rx buffer size according with the HW spec.  */
	if (dp->rx_buf_len <= 2048) {
		dp->rx_buf_len = 2048;
	} else if (dp->rx_buf_len <= 4096) {
		dp->rx_buf_len = 4096;
	} else if (dp->gc.gc_max_mtu != 9234 - sizeof (struct ether_header)
	    && dp->rx_buf_len <= 8192) {
		dp->rx_buf_len = 8192;
	} else if (dp->gc.gc_max_mtu == 9234 - sizeof (struct ether_header)
	    && dp->rx_buf_len <= 9234) {
		dp->rx_buf_len = 9234;
	} else if (dp->rx_buf_len <= 16384) {
		dp->rx_buf_len = 16384;
D 5
	} else {
		cmn_err(CE_WARN,
		    CONS "%s: %s: rx buffer size is too big (%d), using 16384",
		    dp->name, __func__, dp->rx_buf_len);
		dp->rx_buf_len = 16384;
		ret = GEM_FAILURE;
E 5
	}
D 5

	return (ret);
E 5
}

static int
em_attach_chip(struct gem_dev *dp)
{
E 4
	uint32_t	val;
	uint16_t	rx_buffer_size;
D 4
	struct em_dev	*lp = (struct em_dev *) dp->private;
E 4
I 4
	struct em_dev	*lp = dp->private;
	struct e1000_hw	*hw = &lp->hw;
E 4

	DPRINTF(0, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));

D 2

E 2
D 4
	/* 
	 * Set the max frame size assuming standard ethernet 
	 * sized frames 
	 */   
	lp->hw.max_frame_size = 
			dp->mtu + sizeof(struct ether_header) + ETHERFCSL;
E 4
I 4
	em_get_wakeup(dp);
E 4

D 4
	lp->hw.min_frame_size = 
			MINIMUM_ETHERNET_PACKET_SIZE + ETHERFCSL;

D 2

E 2
	/* Packet Buffer Allocation (PBA)
	 * Writing PBA sets the receive portion of the buffer
	 * the remainder is used for the transmit buffer.
	 *
	 * Devices before the 82547 had a Packet Buffer of 64K.
	 *   Default allocation: PBA=48K for Rx, leaving 16K for Tx.
	 * After the 82547 the buffer was reduced to 40K.
	 *   Default allocation: PBA=30K for Rx, leaving 10K for Tx.
	 *   Note: default does not leave enough room for Jumbo Frame >10k.
	 */
	switch (lp->hw.mac_type) {
	case em_82547: 
	case em_82547_rev_2: /* 82547: Total Packet Buffer is 40K */
	    if (lp->hw.max_frame_size > 8192)
	            pba = E1000_PBA_22K; /* 22K for Rx, 18K for Tx */
	    else
	            pba = E1000_PBA_30K; /* 30K for Rx, 10K for Tx */
	    lp->tx_fifo_head = 0;
	    lp->tx_head_addr = pba << /* EM_TX_HEAD_ADDR_SHIFT */7;
D 2
	    lp->tx_fifo_size =
E 2
I 2
	    lp->tx_fifo_thresh =
E 2
			(E1000_PBA_40K - pba) << /* EM_PBA_BYTES_SHIFT */0xA;
	    break;
	case em_80003es2lan: /* 80003es2lan: Total Packet Buffer is 48K */
	case em_82571: /* 82571: Total Packet Buffer is 48K */
	case em_82572: /* 82572: Total Packet Buffer is 48K */
	    pba = E1000_PBA_32K; /* 32K for Rx, 16K for Tx */
	    break;
	case em_82573: /* 82573: Total Packet Buffer is 32K */
	    /* Jumbo frames not supported */
	    pba = E1000_PBA_12K; /* 12K for Rx, 20K for Tx */
	    break;
	case em_ich8lan:
	    pba = E1000_PBA_8K;
	    break;
	default:
	    /* Devices before 82547 had a Packet Buffer of 64K.   */
	    if(lp->hw.max_frame_size > 8192)
	        pba = E1000_PBA_40K; /* 40K for Rx, 24K for Tx */
	    else
	        pba = E1000_PBA_48K; /* 48K for Rx, 16K for Tx */
I 2
#ifdef TEST_82547
	    lp->tx_fifo_head = 0;
	    lp->tx_head_addr = pba << /* EM_TX_HEAD_ADDR_SHIFT */7;
	    lp->tx_fifo_thresh = 64*1024 - (pba << /* EM_PBA_BYTES_SHIFT */0xA);
#endif
E 4
I 4
	if (lp->has_manage && !lp->has_amt) {
		em_get_hw_control(dp);
E 4
E 2
	}
D 5

E 5
I 5
#ifdef notdef	/* moved to mii_init() */
E 5
I 2
D 4
	lp->tx_fifo_thresh -= dp->mtu - sizeof(struct ether_header) - 4 - 32;
E 4
I 4
	/* setup defaults for link parameters */
E 4

E 2
D 4
	DPRINTF(0, (CE_CONT, "!%s: %s: pba=%dK", dp->name, __func__, pba));
D 3
	E1000_WRITE_REG(&lp->hw, PBA, pba);
	
E 3
I 3
#if 0
	E1000_WRITE_REG(&lp->hw, PBA, lp->pba = pba);
#else
	lp->pba = pba;
#endif	
E 3
	/* Set up some sysctls for the tunable interrupt delays */
E 4
I 4
	hw->mac.autoneg = B_TRUE;
	hw->phy.autoneg_wait_to_complete = B_FALSE;
	hw->phy.autoneg_advertised = AUTONEG_ADV_DEFAULT;
E 4

D 4
	/* Parameters (to be read from user) */   
	lp->hw.autoneg = !dp->mii_fixedmode;
	lp->hw.wait_autoneg_complete = 0;	/* no wait */
E 4
I 4
	/* Copper options */
	if (hw->phy.media_type == e1000_media_type_copper) {
		hw->phy.mdix = AUTO_ALL_MODES;
		hw->phy.disable_polarity_correction = B_FALSE;
		hw->phy.ms_type = e1000_ms_hw_default;
	}
E 4
D 5

E 5
I 5
#endif
E 5
D 3
	/* contruct from gem capabilities */
E 3
I 3
D 4
	/* contruct AN advertisement bits from gem capabilities */
E 3
	if (dp->anadv_1000hdx) {
D 2
		cmn_err(CE_CONT, "%s: 1Gbps half duplex is not supported",
E 2
I 2
		cmn_err(CE_CONT, "!%s: 1Gbps half duplex is not supported",
E 2
			dp->name);
		dp->anadv_1000hdx = 0;
		dp->anadv_1000fdx = 1;
E 4
I 4
	/* XXX - continuing e1000_attach */

	/* TODO: new em has only 2048, 4096 and 9K */
	/* fix rx buffer size according with the HW spec.  */
D 5
	if (em_fixup_params(dp) != GEM_SUCCESS) {
		return (GEM_FAILURE);
E 5
I 5
	if (dp->rx_buf_len > 16384) {
		cmn_err(CE_WARN,
		    CONS "%s: %s: rx buffer size is too big (%d), using 16384",
		    dp->name, __func__, dp->rx_buf_len);
		dp->rx_buf_len = 16384;
E 5
E 4
	}
I 5
	em_fixup_params(dp);
E 5
D 4
	val = 0;
	val |= dp->anadv_10hdx ? ADVERTISE_10_HALF : 0;
	val |= dp->anadv_10fdx ? ADVERTISE_10_FULL : 0;
	val |= dp->anadv_100hdx ? ADVERTISE_100_HALF : 0;
	val |= dp->anadv_100fdx ? ADVERTISE_100_FULL : 0;
	val |= dp->anadv_1000hdx ? ADVERTISE_1000_HALF : 0;
	val |= dp->anadv_1000fdx ? ADVERTISE_1000_FULL : 0;
	lp->hw.autoneg_advertised = val;
E 4

D 4
	lp->hw.tbi_compatibility_en  = B_TRUE;
E 4
I 4
	e1000_init_script_state_82541(&lp->hw, B_TRUE);
	e1000_set_tbi_compatibility_82543(&lp->hw, B_TRUE);
E 4

D 4
#ifdef old
	/* 
	 * These parameters control the automatic generation(Tx) and
	 * response(Rx) to Ethernet PAUSE frames.
	 */
	lp->hw.fc_high_water = FC_DEFAULT_HI_THRESH;
	lp->hw.fc_low_water  = FC_DEFAULT_LO_THRESH;
	lp->hw.fc_pause_time = FC_DEFAULT_TX_TIMER;
#else
E 4
I 4
	/* Copper options */
	if (hw->phy.media_type == e1000_media_type_copper) {
		hw->phy.mdix = AUTO_ALL_MODES;
		hw->phy.disable_polarity_correction = B_FALSE;
		hw->phy.ms_type = E1000_MASTER_SLAVE;
	}

E 4
	/*
D 4
	 * These parameters control the automatic generation (Tx) and
	 * response(Rx) to Ethernet PAUSE frames.
	 * - High water mark should allow for at least two frames to be
	 *   received after sending an XOFF.
	 * - Low water mark works best when it is very near the high water mark.
	 *   This allows the receiver to restart by sending XON when it has
	 *   drained a bit.  Here we use an arbitary value of 1500 which will
	 *   restart after one full frame is pulled from the buffer.  There
	 *   could be several smaller frames in the buffer and if so they will
	 *    not trigger the XON until their
	 *   total number reduces the buffer by 1500.
	 * - The pause time is fairly large at 1000 x 512ns = 512 usec.
E 4
I 4
	 * Set the max frame size assuming standard ethernet
	 * sized frames
E 4
	 */
I 5
#ifdef CONFIG_NO_RXCRC
	lp->max_frame_size = dp->mtu + sizeof (struct ether_header);
	lp->min_frame_size = ETHERMIN;
#else
E 5
D 4
	rx_buffer_size = ((E1000_READ_REG(&lp->hw, PBA) & 0xffff) << 10);
E 4
I 4
	lp->max_frame_size = dp->mtu + sizeof (struct ether_header) + ETHERFCSL;
	lp->min_frame_size = ETHERMIN + ETHERFCSL;
I 5
#endif
E 5
	lp->tx_fifo_thresh = dp->mtu - sizeof (struct ether_header) - 4 - 32;
I 5
#ifdef CONFIG_NEW_EM
	lp->hw.mac.max_frame_size = lp->max_frame_size;
#endif
E 5
E 4

D 4
	lp->hw.fc_high_water =
			rx_buffer_size - ROUNDUP(lp->hw.max_frame_size, 1024);
	lp->hw.fc_low_water  = lp->hw.fc_high_water - 1500;
	if (lp->hw.mac_type == em_80003es2lan) {
		lp->hw.fc_pause_time = 0xFFFF;
	} else {
		lp->hw.fc_pause_time = 0x1000;
	}
#endif
	lp->hw.fc_send_xon   = B_TRUE;
I 3
#ifdef E1000_FC_FULL
	lp->hw.fc = E1000_FC_FULL;
#else
E 3
	lp->hw.fc = em_fc_full;
D 3

E 3
I 3
#endif
E 3
	lp->hw.phy_init_script = 1;
	lp->hw.phy_reset_disable = B_FALSE;

D 3
#ifndef EM_MASTER_SLAVE
	lp->hw.master_slave = em_ms_hw_default;
#else
E 3
I 3
#ifdef EM_MASTER_SLAVE
E 3
	lp->hw.master_slave = EM_MASTER_SLAVE;
I 3
#else
	lp->hw.master_slave = em_ms_hw_default;
E 3
#endif

D 3
#if 0
E 3
	/* 
D 3
	 * Set the max frame size assuming standard ethernet 
	 * sized frames 
	 */   
	lp->hw.max_frame_size = 
			dp->mtu + sizeof(struct ether_header) + ETHERFCSL;

	lp->hw.min_frame_size = 
			MINIMUM_ETHERNET_PACKET_SIZE + ETHERFCSL;
#endif
	/* 
E 3
	 * This controls when hardware reports transmit completion 
	 * status. 
E 4
I 4
	/*
	 * This controls when hardware reports transmit completion
	 * status.
E 4
	 */
D 4
	lp->hw.report_tx_early = 1;
E 4
I 4
	hw->mac.report_tx_early = 1;
E 4

D 4
	em_init_eeprom_params(&lp->hw);

E 4
I 4
	/*
	 * EEPROM sections
	 */
E 4
	/* Make sure we have a good EEPROM before we read from it */
D 4
	if (em_validate_eeprom_checksum(&lp->hw) != E1000_SUCCESS) {
E 4
I 4
	if (e1000_validate_nvm_checksum(hw) < 0) {
		/*
		 * Some PCI-E parts fail the first check due to
		 * the link being in sleep state, call it again,
		 * if it fails a second time its a real issue.
		 */
		if (e1000_validate_nvm_checksum(hw) < 0) {
			cmn_err(CE_WARN,
			    CONS "%s: %s: The EEPROM Checksum Is Not Valid",
			    dp->name, __func__);
			return (GEM_FAILURE);
		}
	}

	/* Copy the permanent MAC address out of the EEPROM */
	if (e1000_read_mac_addr(hw) < 0) {
E 4
		cmn_err(CE_WARN,
D 2
			"%s: %s:The EEPROM Checksum Is Not Valid",
E 2
I 2
D 4
			"!%s: %s:The EEPROM Checksum Is Not Valid",
E 2
		       dp->name, __func__);
E 4
I 4
		    CONS "%s: %s: EEPROM read error while reading mac addr",
		    dp->name, __func__);
E 4
#ifndef DEBUG
		return (GEM_FAILURE);
#endif
	}

D 4
	if (em_read_part_num(&lp->hw, &lp->part_num) != E1000_SUCCESS) {
		cmn_err(CE_WARN,
D 2
			"%s: %s: EEPROM read error while reading part number",
E 2
I 2
			"!%s: %s: EEPROM read error while reading part number",
E 2
		       dp->name, __func__);
E 4
I 4
	if (!em_is_valid_ether_addr(hw->mac.perm_addr)) {
		cmn_err(CE_WARN, CONS "%s: %s:Invalid mac address",
		    dp->name, __func__);
E 4
#ifndef DEBUG
		return (GEM_FAILURE);
#endif
	}

D 4
	if (em_read_mac_addr(&lp->hw) != E1000_SUCCESS) {
		cmn_err(CE_WARN,
D 2
			"%s: %s: EEPROM read error while reading mac addr",
E 2
I 2
			"!%s: %s: EEPROM read error while reading mac addr",
E 2
		       dp->name, __func__);
#ifndef DEBUG
		return (GEM_FAILURE);
E 4
I 4
	bcopy(hw->mac.perm_addr, dp->dev_addr.ether_addr_octet, ETHERADDRL);
#ifdef notdef
	bzero(hw->mac.addr, ETHERADDRL);
#else
	bcopy(hw->mac.perm_addr, hw->mac.addr, ETHERADDRL);
E 4
#endif
I 4
	/* Indicate SOL/IDER usage */
	if (e1000_check_reset_block(&lp->hw)) {
		cmn_err(CE_NOTE,
		    CONS
		    "%s: %s: PHY reset is blocked due to SOL/IDER session.",
		    dp->name, __func__);
E 4
	}

D 4
	if ((lp->hw.perm_mac_addr[0] & 1) != 0 ||
	     bcmp(lp->hw.perm_mac_addr,
			"\000\000\000\000\000\000", ETHERADDRL) == 0) {
D 2
		cmn_err(CE_WARN, "%s: %s:Invalid mac address",
E 2
I 2
		cmn_err(CE_WARN, "!%s: %s:Invalid mac address",
E 2
			dp->name, __func__);
#ifndef DEBUG
		return (GEM_FAILURE);
E 4
I 4
D 5
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
I 5
#if defined(CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 5
	if (hw->mac.type >= e1000_82543) {
		dp->misc_flag |= GEM_CKSUM_PARTIAL;
		dp->misc_flag |= GEM_CKSUM_HEADER_IPv4;
	}
E 4
#endif
I 4
#ifdef CONFIG_VLAN
	dp->misc_flag |= GEM_VLAN_HARD;
#endif
	cmn_err(CE_CONT, CONS "%s: firmware version: %s",
	    dp->name, FIRMWARE_VERSION);

	return (GEM_SUCCESS);
}

/* ======================================================== */
/*
 *  Determine hardware revision.
 */
/* ======================================================== */
static int
em_identify_hardware(dev_info_t *dip, struct em_dev *lp)	/* ok */
{
	const int	unit = ddi_get_instance(dip);
	const char	*drv_name = ddi_driver_name(dip);

	/* Make sure our PCI config space has the necessary stuff set */
	lp->hw.bus.pci_cmd_word = pci_config_get16(lp->conf_ha, PCI_CONF_COMM);

	if (!((lp->hw.bus.pci_cmd_word & PCI_COMM_ME) &&
	    (lp->hw.bus.pci_cmd_word & PCI_COMM_MAE))) {
		cmn_err(CE_CONT, CONS "%s%d: %s: "
		    "Memory Access and/or Bus Master bits were not set!",
		    drv_name, unit, __func__);
		lp->hw.bus.pci_cmd_word |= (PCI_COMM_ME | PCI_COMM_MAE);
		pci_config_put16(lp->conf_ha,
		    PCI_CONF_COMM, lp->hw.bus.pci_cmd_word);
E 4
	}

D 4
	bcopy(lp->hw.perm_mac_addr, dp->dev_addr.ether_addr_octet, ETHERADDRL);
E 4
I 4
	/* Save off the information about this board */
	lp->hw.vendor_id = pci_config_get16(lp->conf_ha, PCI_CONF_VENID);
	lp->hw.device_id = pci_config_get16(lp->conf_ha, PCI_CONF_DEVID);
	lp->hw.revision_id = pci_config_get8(lp->conf_ha, PCI_CONF_REVID);
	lp->hw.subsystem_vendor_id =
	    pci_config_get16(lp->conf_ha, PCI_CONF_SUBVENID);
	lp->hw.subsystem_device_id =
	    pci_config_get16(lp->conf_ha, PCI_CONF_SUBSYSID);
E 4

I 3
D 4
#ifdef notdef
	/* XXX - moved into em_start_chip() */
E 3
	/* Initialize statistics */
	em_clear_hw_cntrs(&lp->hw);
E 4
I 4
	/* Do Shared Code Init and Setup */
	if (e1000_set_mac_type(&lp->hw)) {
		cmn_err(CE_WARN, CONS "%s%d: %s: Setup init failure",
		    drv_name, unit, __func__);
		return (DDI_FAILURE);
	}
E 4
D 3
#ifdef notdef
E 3
I 3

D 4
	/* XXX - moved into em_set_media() */
E 3
	lp->hw.get_link_status = 1;
	em_check_for_link(&lp->hw);
E 4
I 4
	DPRINTF(0, (CE_CONT, "!%s%d: %s: type:%d",
	    drv_name, unit, __func__, lp->hw.mac.type));
E 4
D 3
#endif
I 2
	/* XXX - moved into emattach() */
E 3
I 3

D 4
	/* XXX - moved into em_reset_chip() */
E 3
E 2
	/* Identify 82544 on PCIX */
	em_get_bus_info(&lp->hw);	
I 2
D 3
#ifdef notdef
E 2
	lp->pcix_82544 = (lp->hw.bus_type == em_bus_type_pcix &&
			       lp->hw.mac_type == em_82544);
D 2

E 2
I 2
	if (lp->pcix_82544) {
		dp->gc.gc_tx_max_frags = 2*MAXTXFRAGS;
		dp->gc.gc_tx_max_descs_per_pkt = dp->gc.gc_tx_max_frags + 1;
		dp->gc.gc_tx_desc_write_oo = B_FALSE;
	}
E 3
#endif
E 4
I 4
	return (DDI_SUCCESS);
}
E 4
I 3

E 3
E 2
D 4
	/* Setup costant values in the Receive Control Register */
	rctl  = E1000_RCTL_EN | E1000_RCTL_BAM | E1000_RCTL_LBM_NO |
		E1000_RCTL_RDMTS_HALF |
		(lp->hw.mc_filter_type << E1000_RCTL_MO_SHIFT);
E 4
I 4
static void
e1000_free_pci_resources(struct em_dev *lp)
{
	lp->hw.hw_addr = 0;
E 4

D 4
	if (lp->hw.tbi_compatibility_on == B_TRUE) {
		rctl |= E1000_RCTL_SBP;
E 4
I 4
	if (lp->io_ha) {
		ddi_regs_map_free(&lp->io_ha);
		lp->io_ha = 0;
E 4
	}

D 4
	/* fix rx buffer size according with the HW spec. */
	if (dp->rx_buf_len <= 2048) {
		rctl |= E1000_RCTL_SZ_2048;
		if (dp->mtu > ETHERMTU) {
			rctl |= E1000_RCTL_LPE;
		}
		dp->rx_buf_len = 2048;
E 4
I 4
	if (lp->flash_ha) {
		ddi_regs_map_free(&lp->flash_ha);
		lp->flash_ha = 0;
E 4
	}
D 4
	else if (dp->rx_buf_len <= 4096) {
		rctl |= E1000_RCTL_SZ_4096 | E1000_RCTL_BSEX | E1000_RCTL_LPE;
		dp->rx_buf_len = 4096;
E 4
I 4
}

static int
em_allocate_pci_resources(dev_info_t *dip, struct em_dev *lp)
{
	const int	unit = ddi_get_instance(dip);
	const char	*drv_name = ddi_driver_name(dip);
	int		err = 0;

	lp->reg_ha = 0;
	lp->io_ha = 0;
	lp->flash_ha = 0;
	lp->hw.hw_addr = 0;

	/* the first base address is for mapping control registers */
	if (gem_pci_regs_map_setup(dip,
	    PCI_CONF_BASE0, PCI_REG_REG_M,
	    &em_dev_attr,
	    (void *)&lp->hw.hw_addr, &lp->reg_ha) != DDI_SUCCESS) {
		cmn_err(CE_WARN, CONS "%s%d: %s: ddi_regs_map_setup failed",
		    drv_name, unit, __func__);
		lp->hw.hw_addr = 0;
		err = ENXIO;
		goto x;
E 4
	}
D 4
	else if (dp->rx_buf_len <= 8192) {
		rctl |= E1000_RCTL_SZ_8192 | E1000_RCTL_BSEX | E1000_RCTL_LPE;
		dp->rx_buf_len = 8192;
	}
	else if (dp->rx_buf_len <= 16384) {
		rctl |= E1000_RCTL_SZ_16384 | E1000_RCTL_BSEX | E1000_RCTL_LPE;
		dp->rx_buf_len = 16384;
	}
	else {
		cmn_err(CE_WARN,
			"%s: %s: rx buffer size is too big (%d), using 16384",
			dp->name, __func__, dp->rx_buf_len);
		return (GEM_FAILURE);
	}
	lp->rctl = rctl;
E 4

D 4
	lp->tx_int_delay = em_tx_int_delay_dflt;
	lp->rx_int_delay = em_rx_int_delay_dflt;
	lp->tx_abs_int_delay = em_tx_abs_int_delay_dflt;
	lp->rx_abs_int_delay = em_rx_abs_int_delay_dflt;
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
	if (lp->hw.mac_type >= em_82543) {
		dp->misc_flag |= GEM_CKSUM_PARTIAL;
		dp->misc_flag |= GEM_CKSUM_HEADER_IPv4;
E 4
I 4
	if (lp->hw.mac.type > e1000_82543) {
		/* Figure our where our IO BAR is ? */
		if (gem_pci_regs_map_setup(dip,
		    PCI_ADDR_IO, PCI_ADDR_MASK,
		    &em_dev_attr,
		    (void *)&lp->io_base, &lp->io_ha) != DDI_SUCCESS) {
			cmn_err(CE_WARN,
			    CONS "%s%d: %s: Unable to locate IO BAR",
			    drv_name, unit, __func__);
			lp->io_ha = 0;
			err = ENXIO;
			goto x;
		}
E 4
	}
D 4
#endif
#ifdef CONFIG_VLAN
	dp->misc_flag |= GEM_VLAN_HARD;
#endif
I 2
	cmn_err(CE_CONT, "!%s: firmware version: %s",
			dp->name, FIRMWARE_VERSION);
E 4

E 2
D 4
	return (GEM_SUCCESS);
E 4
I 4
	lp->hw.back = lp;

	return (0);

x:
	e1000_free_pci_resources(lp);

	return (err);
E 4
}

I 4

E 4
static int
emattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
D 4
	int                     unit;
E 4
I 4
	int			unit;
E 4
	const char		*drv_name;
	int			i;
	ddi_acc_handle_t	conf_handle;
D 4
	uint16_t		vid;
	uint16_t		did;
	uint16_t		svid;
	uint16_t		ssid;
E 4
	uint16_t		pci_cmd;
D 4
	uint8_t			rev;
E 4
#ifdef DEBUG_LEVEL
	uint32_t		iline;
	uint8_t			latim;
#endif
I 3
D 4
	boolean_t		is_pcie;
E 4
I 4
	int			pcie;
E 4
E 3
	struct gem_dev		*dp;
	struct em_dev		*lp;
	void			*base;
	ddi_acc_handle_t	regs_ha;
	struct gem_conf		*gcp;
I 4
	int			num_tx_desc;
	int			num_rx_desc;
	struct e1000_hw		*hw;
E 4

D 4
	unit     = ddi_get_instance(dip);
E 4
I 4
	unit = ddi_get_instance(dip);
E 4
	drv_name = ddi_driver_name(dip);

	DPRINTF(3, (CE_CONT, CONS "%s%d: %s: called (%s)",
D 4
		drv_name, unit, __func__, ident));
E 4
I 4
	    drv_name, unit, __func__, ident));
E 4

	/*
	 * Common codes after power-up
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 4
		cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
			drv_name, unit);
E 4
I 4
		cmn_err(CE_WARN, CONS "%s%d: ddi_regs_map_setup failed",
		    drv_name, unit);
E 4
D 3
		return DDI_FAILURE;
E 3
I 3
		return (DDI_FAILURE);
E 3
	}

D 4
	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	rev  = pci_config_get16(conf_handle, PCI_CONF_REVID);
	svid  = pci_config_get16(conf_handle, PCI_CONF_SUBVENID);
	ssid  = pci_config_get16(conf_handle, PCI_CONF_SUBSYSID);
E 4
#ifdef DEBUG_LEVEL
D 4
	iline =	pci_config_get32(conf_handle, PCI_CONF_ILINE),
E 4
I 4
	iline =	pci_config_get32(conf_handle, PCI_CONF_ILINE);
E 4
	latim = pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER);
#endif

D 4
	pci_cmd = pci_config_get16(conf_handle, PCI_CONF_COMM);
	pci_cmd |= PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME;
	pci_config_put16(conf_handle, PCI_CONF_COMM, pci_cmd);
	pci_cmd = pci_config_get16(conf_handle, PCI_CONF_COMM);
E 4
I 4
	pci_config_put16(conf_handle, PCI_CONF_COMM,
	    PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
	    pci_config_get16(conf_handle, PCI_CONF_COMM));
E 4

	/* ensure D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);
D 2
#if 0
	pci_config_teardown(&conf_handle);
#endif
E 2
I 2

I 3
D 4
	is_pcie = gem_is_pcie(dip, conf_handle);
E 4

E 3
E 2
	switch (cmd) {
	case DDI_RESUME:
I 5
#ifdef CONFIG_NEW_EM
		dp = GEM_GET_DEV(dip);
		lp = (struct em_dev *)dp->private;
		if (lp->hw.mac.type == e1000_pch2lan)
			e1000_resume_workarounds_pchlan(&lp->hw);
#endif
E 5
		if (gem_resume(dip) == DDI_SUCCESS) {
I 4
			pci_config_teardown(&conf_handle);
E 4
D 2
			return DDI_SUCCESS;
E 2
I 2
			return (DDI_SUCCESS);
E 2
		}
		goto err;

	case DDI_ATTACH:

		DPRINTF(0, (CE_CONT,
D 4
			CONS "%s%d: ilr 0x%08x, latency_timer:0x%02x",
			drv_name, unit, iline, latim));
		/*
		 * Map in the device registers.
		 */
D 3

		if (gem_pci_regs_map_setup(dip,
			PCI_ADDR_MEM32, PCI_REG_ADDR_M,
			&em_dev_attr, (caddr_t *)&base, &regs_ha) !=
								DDI_SUCCESS) {
E 3
I 3
		/* the first address is for registers */
		if (ddi_regs_map_setup(dip, 1, (void *)&base, 0, 0,
				&em_dev_attr, &regs_ha) != DDI_SUCCESS) {
E 3
			cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
				drv_name, unit);
			goto err;
		}
E 4
I 4
		    CONS "%s%d: ilr 0x%08x, latency_timer:0x%02x",
		    drv_name, unit, iline, latim));
E 4

		/*
D 2
		 * construct gem configration
E 2
I 2
		 * Setup device specific information
E 2
		 */
I 2
D 4
		lp = (struct em_dev *)
			kmem_zalloc(sizeof(struct em_dev), KM_SLEEP);
E 4
I 4
		lp = kmem_zalloc(sizeof (struct em_dev), KM_SLEEP);
		hw = &lp->hw;
E 4

		lp->conf_ha = conf_handle;
I 4
		lp->pcie_offset =
		    gem_search_pci_cap(dip, conf_handle, PCI_CAP_ID_PCI_E);
		lp->pme_offset =
		    gem_search_pci_cap(dip, conf_handle, PCI_CAP_ID_PM);
E 4

D 4
		/* fill required hw info (em_identify_hardware) */
		lp->hw.pci_cmd_word		= pci_cmd;
		lp->hw.vendor_id		= vid;
		lp->hw.device_id		= did;
		lp->hw.revision_id		= rev;
		lp->hw.subsystem_vendor_id 	= svid;
		lp->hw.subsystem_id		= ssid;

		/* Identify the MAC */
		if (em_set_mac_type(&lp->hw) != E1000_SUCCESS) {
			cmn_err(CE_WARN, "%s%d: unknown mac type: "
			"vid:%04x, did:%04x, svid:%04x, ssid:%04x, rev:%02x",
				drv_name, unit,
				vid, did, svid, ssid, rev);
E 4
I 4
		if (em_identify_hardware(dip, lp) != DDI_SUCCESS) {
			cmn_err(CE_WARN,
			    CONS "%s%d: unknown mac type: "
			    "vid:%04x, did:%04x, svid:%04x,"
			    " ssid:%04x, rev:%02x",
			    drv_name, unit,
			    hw->vendor_id,
			    hw->device_id,
			    hw->subsystem_vendor_id,
			    hw->subsystem_device_id,
			    hw->revision_id);
E 4
			goto err_freelp;
		}

D 4
		switch (lp->hw.mac_type) {
		case em_82541:
		case em_82541_rev_2:
		case em_82547:
		case em_82547_rev_2:
			lp->hw.phy_init_script = B_TRUE;
			break;
E 4
I 4
		/*
		 * Map in the device registers.
		 */
		if (em_allocate_pci_resources(dip, lp) != DDI_SUCCESS) {
			goto err_freelp;
E 4
		}

D 4
		if (lp->hw.mac_type > em_82543) {
			/*
			 * Make an additional map for accessing registers
			 * through io space.
			 */
E 4
I 4
		/*
		 * For ICH8 and family we need to
		 * map the flash memory, and this
		 * must happen after the MAC is
		 * identified
		 */
		if ((hw->mac.type == e1000_ich8lan) ||
		    (hw->mac.type == e1000_ich9lan) ||
		    (hw->mac.type == e1000_ich10lan) ||
		    (hw->mac.type == e1000_pchlan) ||
D 5
		    (hw->mac.type == e1000_pch2lan)) {
E 5
I 5
		    (hw->mac.type == e1000_pch2lan) ||
		    (hw->mac.type == e1000_pch_lpt)) {
E 5
E 4
			if (gem_pci_regs_map_setup(dip,
D 4
					PCI_ADDR_IO, PCI_REG_ADDR_M,
					&em_dev_attr, (caddr_t *)&lp->io_base,
					&lp->io_ha) != DDI_SUCCESS) {
D 3
				cmn_err(CE_WARN,
					"!%s%d: %s: gem_regs_map_setup failed",
E 3
I 3
				cmn_err(CE_NOTE,
					"!%s%d: %s: no registers in IO space ",
E 3
					drv_name, unit, __func__);
I 3
				lp->io_ha = 0;
			}
		}

		/* For ICH8 we need to find the flash memory. */
		if (lp->hw.mac_type == em_ich8lan) {
			if (gem_pci_regs_map_setup(dip,
					0x14, PCI_REG_REG_M,
					&em_dev_attr,
					(caddr_t *) &lp->flash_base,
					&lp->flash_ha) != DDI_SUCCESS) {
				cmn_err(CE_WARN,
					"%s%d: failed to map flash regisgers",
					drv_name, unit);
E 4
I 4
			    E1000_FLASH, PCI_REG_REG_M,
			    &em_dev_attr,
			    (caddr_t *)&hw->flash_address,
			    &lp->flash_ha) != DDI_SUCCESS) {
				cmn_err(CE_WARN, CONS
				    "%s%d: %s: failed to map flash regisgers",
				    drv_name, unit, __func__);
E 4
				lp->flash_ha = 0;
E 3
D 4
				goto err_free_iorange;
E 4
I 4
				goto err_free_maps;
E 4
			}
		}

I 4
		/* Do Shared Code initialization */
		if (e1000_setup_init_funcs(hw, B_TRUE) != E1000_SUCCESS) {
			cmn_err(CE_WARN,
			    CONS "%s%d: %s: Setup of Shared code failed",
			    drv_name, unit, __func__);
			goto err_free_maps;
		}
I 5

#ifdef CONFIG_SEPARETE_PHY
E 5
E 4
		/*
D 4
		 * Now device registers are fully mapped, let's identify
		 * 82544 on PCIX.
E 4
I 4
		 * Workaround to separate mac and phy operation
E 4
		 */
D 4
#ifdef notdef
E 4
I 4
D 5
#if 0
		lp->setup_link = e1000_null_ops_generic;
#endif
E 5
		lp->setup_link = hw->mac.ops.setup_link;
		hw->mac.ops.setup_link = e1000_null_ops_generic;
I 5
#endif
E 5

		e1000_get_bus_info(hw);

		/* Set up some sysctls for the tunable interrupt delays */
		lp->rx_int_delay = em_rx_int_delay_dflt;
		lp->tx_int_delay = em_tx_int_delay_dflt;
		if (hw->mac.type >= e1000_82540) {
			lp->rx_abs_int_delay = em_rx_abs_int_delay_dflt;
			lp->tx_abs_int_delay = em_tx_abs_int_delay_dflt;
		}

E 4
		/*
D 4
		 * XXX - we cannot call em_get_bus_info because lp->back
		 * hasn't been set.
E 4
I 4
		 * Validate number of transmit and receive descriptors. It
		 * must not exceed hardware maximum, and must be multiple
		 * of E1000_DBA_ALIGN.
E 4
		 */
D 4
		em_get_bus_info(&lp->hw);	
		lp->pcix_82544 = (lp->hw.bus_type == em_bus_type_pcix &&
				       lp->hw.mac_type == em_82544);
#else
		lp->pcix_82544 = B_FALSE;
		if (lp->hw.mac_type == em_82544) {
			uint32_t	status;
			status = ddi_get32(regs_ha,
				(uint32_t *)((caddr_t)base + E1000_STATUS));
			lp->pcix_82544 = (status & E1000_STATUS_PCIX_MODE) != 0;
E 4
I 4
		if (((em_txd * sizeof (struct e1000_tx_desc)) %
		    E1000_DBA_ALIGN) != 0||
		    (hw->mac.type >= e1000_82544 && em_txd > EM_MAX_TXD) ||
		    (hw->mac.type < e1000_82544 &&
		    em_txd > EM_MAX_TXD_82543) ||
		    (em_txd < EM_MIN_TXD)) {
			cmn_err(CE_CONT,
			    CONS "Using %d TX descriptors instead of %d!",
			    EM_DEFAULT_TXD, em_txd);
			num_tx_desc = EM_DEFAULT_TXD;
		} else {
			num_tx_desc = em_txd;
E 4
		}
D 4
#endif
E 4
I 4

		if (((em_rxd * sizeof (struct e1000_rx_desc)) %
		    E1000_DBA_ALIGN) != 0 ||
		    (hw->mac.type >= e1000_82544
		    && em_rxd > EM_MAX_RXD) ||
		    (hw->mac.type < e1000_82544
		    && em_rxd > EM_MAX_RXD_82543) ||
		    (em_rxd < EM_MIN_RXD)) {
			cmn_err(CE_CONT,
			    CONS "Using %d RX descriptors instead of %d!",
			    EM_DEFAULT_RXD, em_rxd);
			num_rx_desc = EM_DEFAULT_RXD;
		} else {
			num_rx_desc = em_rxd;
		}
		DPRINTF(0, (CE_CONT,
		    CONS "%s%d: num_tx_desc:%d, num_rx_desc:%d",
		    drv_name, unit, num_tx_desc, num_rx_desc));

		/* Identify 82544 on PCIX */
		if (hw->bus.type == e1000_bus_type_pcix &&
		    hw->mac.type == e1000_82544) {
			lp->pcix_82544 = B_TRUE;
		} else {
			lp->pcix_82544 = B_FALSE;
		}
E 4
#ifdef TEST_82544
		lp->pcix_82544 = B_TRUE;
#endif

D 4
		DPRINTF(0, (CE_CONT, CONS "%s%d: rev:0x%02x",
			drv_name, unit, rev));

E 4
		/*
		 * Construct gem configration
		 */
E 2
D 4
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 4
I 4
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 4

		/* name */
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);

		/* consistency on tx and rx */
D 4
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
E 4
I 4
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
E 4
		gcp->gc_tx_max_frags = MAXTXFRAGS;
I 2
		if (lp->pcix_82544) {
			gcp->gc_tx_max_frags *= 2;
		}
E 2
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags + 1;
		gcp->gc_tx_desc_unit_shift = 4;	/* 16 byte */
D 4
		gcp->gc_tx_buf_size   = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit  = gcp->gc_tx_buf_size - 1;
		gcp->gc_tx_ring_size  = TX_RING_SIZE;
E 4
I 4
		gcp->gc_tx_buf_size = num_tx_desc;
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size - 1;
		gcp->gc_tx_ring_size = num_tx_desc;
E 4
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;
D 4
		gcp->gc_tx_auto_pad   = B_TRUE;
E 4
I 4
		gcp->gc_tx_auto_pad = B_TRUE;
E 4
		gcp->gc_tx_copy_thresh = em_tx_copy_thresh;
D 2
#ifdef CONFIG_OO
		gcp->gc_tx_desc_write_oo = B_TRUE;
#else
E 2
D 4
		gcp->gc_tx_desc_write_oo = B_FALSE;
I 2
#ifdef CONFIG_OO
		if (!lp->pcix_82544) {
			gcp->gc_tx_desc_write_oo = B_TRUE;
		}
E 2
#endif
		gcp->gc_rx_buf_align = sizeof(uint64_t) - 1;
E 4
I 4

		gcp->gc_rx_buf_align = sizeof (uint64_t) - 1;
E 4
		gcp->gc_rx_max_frags = 1;
		gcp->gc_rx_desc_unit_shift = 4;
D 4
		gcp->gc_rx_ring_size = RX_RING_SIZE;
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 4
I 4
		gcp->gc_rx_ring_size = num_rx_desc;
		gcp->gc_rx_buf_max = num_rx_desc - 1;
E 4
		gcp->gc_rx_copy_thresh = em_rx_copy_thresh;

D 4
		gcp->gc_io_area_size   = 0;
E 4
I 4
		gcp->gc_io_area_size = 0;
E 4

		/* map attributes */
D 4
		STRUCT_COPY(gcp->gc_dev_attr, em_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, em_buf_attr);
		STRUCT_COPY(gcp->gc_desc_attr, em_buf_attr);
E 4
I 4
		gcp->gc_dev_attr = em_dev_attr;
		gcp->gc_buf_attr = em_buf_attr;
		gcp->gc_desc_attr = em_buf_attr;
E 4

		/* dma attributes */
D 4
		STRUCT_COPY(gcp->gc_dma_attr_desc, em_dma_attr_desc);
E 4
I 4
		gcp->gc_dma_attr_desc = em_dma_attr_desc;
E 4

D 4
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, em_dma_attr_buf);
		gcp->gc_dma_attr_txbuf.dma_attr_align = gcp->gc_tx_buf_align+1;
E 4
I 4
		gcp->gc_dma_attr_txbuf = em_dma_attr_buf;
		gcp->gc_dma_attr_txbuf.dma_attr_align =
		    gcp->gc_tx_buf_align + 1;
E 4
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;

D 4
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, em_dma_attr_buf);
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;
E 4
I 4
		gcp->gc_dma_attr_rxbuf = em_dma_attr_buf;
		gcp->gc_dma_attr_rxbuf.dma_attr_align =
		    gcp->gc_rx_buf_align + 1;
E 4
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;

		/* time out parameters */
D 4
		gcp->gc_tx_timeout = 5*ONESEC;
E 4
I 4
		gcp->gc_tx_timeout = 3*ONESEC;
E 4
		gcp->gc_tx_timeout_interval = ONESEC;

		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = ONESEC;
D 4
		gcp->gc_mii_an_watch_interval   = ONESEC/5;
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
E 4
I 4
		gcp->gc_mii_an_watch_interval = ONESEC/5;
		gcp->gc_mii_reset_timeout = ONESEC;	/* 1 sec */
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT*2;	/* 10 sec */
E 4
		gcp->gc_mii_an_wait = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;

		/* setting for general PHY */
		gcp->gc_mii_addr_min =  1;
		gcp->gc_mii_an_delay =  0;
D 4
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
E 4
I 4
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_NONE;

		/* enable phy reset within the first reset */
E 4
		gcp->gc_mii_dont_reset = B_FALSE;
I 4
		gcp->gc_mii_stop_mac_on_linkdown = B_TRUE;
#ifdef CONFIG_HW_LINK_DETECTION
E 4
		gcp->gc_mii_hw_link_detection = B_TRUE;
I 4
#else
		gcp->gc_mii_hw_link_detection = B_FALSE;
#endif
I 5
#ifdef notdef
E 5
		/* allow resetting phy */
		lp->hw.phy.reset_disable = B_FALSE;
E 4
D 5

E 5
I 5
#endif
E 5
D 4

E 4
		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &em_attach_chip;
I 4
#ifdef GEM_CONFIG_JUMBO_FRAME
D 5
		gcp->gc_fixup_params = (void *)&em_fixup_params;
E 5
I 5
		gcp->gc_fixup_params = &em_fixup_params;
E 5
#endif
E 4
		gcp->gc_reset_chip = &em_reset_chip;
D 4
		gcp->gc_init_chip  = &em_init_chip;
E 4
I 4
		gcp->gc_init_chip = &em_init_chip;
E 4
		gcp->gc_start_chip = &em_start_chip;
D 4
		gcp->gc_stop_chip  = &em_stop_chip;
E 4
I 4
		gcp->gc_stop_chip = &em_stop_chip;
E 4
		gcp->gc_multicast_hash = NULL;
		gcp->gc_set_rx_filter = &em_set_rx_filter;
		gcp->gc_set_media = &em_set_media;
		gcp->gc_get_stats = &em_get_stats;
		gcp->gc_interrupt = &em_interrupt;

		/* descriptor operation */
		gcp->gc_tx_desc_write = &em_tx_desc_write;
		gcp->gc_rx_desc_write = &em_rx_desc_write;
		gcp->gc_tx_start = &em_tx_start;
		gcp->gc_rx_start = &em_rx_start;
D 4

		gcp->gc_tx_desc_stat  = &em_tx_desc_stat;
		gcp->gc_rx_desc_stat  = &em_rx_desc_stat;
		gcp->gc_tx_desc_init  = &em_tx_desc_init;
		gcp->gc_rx_desc_init  = &em_rx_desc_init;
E 4
I 4
#ifdef GEM_CONFIG_TX_HEAD_PTR
		gcp->gc_tx_desc_head = &em_tx_desc_head;
		gcp->gc_tx_desc_stat = NULL;
#else
		gcp->gc_tx_desc_stat = &em_tx_desc_stat;
#endif
		gcp->gc_rx_desc_stat = &em_rx_desc_stat;
		gcp->gc_tx_desc_init = &em_tx_desc_init;
		gcp->gc_rx_desc_init = &em_rx_desc_init;
E 4
		gcp->gc_tx_desc_clean = &em_tx_desc_init;
		gcp->gc_rx_desc_clean = &em_rx_desc_init;

		/* mii operations */
D 4
		gcp->gc_mii_init     = &em_mii_init;
		gcp->gc_mii_config   = &gem_mii_config_default;
		gcp->gc_mii_sync     = &em_mii_sync;
		gcp->gc_mii_read     = &em_mii_read;
		gcp->gc_mii_write    = &em_mii_write;
E 4
I 4
		gcp->gc_mii_probe = &em_mii_probe;
		gcp->gc_mii_init = &em_mii_init;
		gcp->gc_mii_config = &em_mii_config;
		gcp->gc_mii_sync = &em_mii_sync;
		gcp->gc_mii_read = &em_mii_read;
		gcp->gc_mii_write = &em_mii_write;
E 4
D 3
		gcp->gc_flow_control = FLOW_CONTROL_SYMMETRIC;
E 3
I 3
		gcp->gc_flow_control = FLOW_CONTROL_RX_PAUSE;
E 3

D 2
		lp = (struct em_dev *)
			kmem_zalloc(sizeof(struct em_dev), KM_SLEEP);

		lp->conf_ha = conf_handle;

		/* fill required hw info (em_identify_hardware) */
		lp->hw.pci_cmd_word		= pci_cmd;
		lp->hw.vendor_id		= vid;
		lp->hw.device_id		= did;
		lp->hw.revision_id		= rev;
		lp->hw.subsystem_vendor_id 	= svid;
		lp->hw.subsystem_id		= ssid;

		/* Identify the MAC */
		if (em_set_mac_type(&lp->hw) != E1000_SUCCESS) {
			cmn_err(CE_WARN, "%s%d: unknown mac type: "
			"vid:%04x, did:%04x, svid:%04x, ssid:%04x, rev:%02x",
				drv_name, unit,
				vid, did, svid, ssid, rev);
			goto err_freelp;
		}

		switch (lp->hw.mac_type) {
		case em_82541:
		case em_82541_rev_2:
		case em_82547:
		case em_82547_rev_2:
			lp->hw.phy_init_script = B_TRUE;
			break;
		}
		if (lp->hw.mac_type > em_82543) {
			if (gem_pci_regs_map_setup(dip,
				PCI_ADDR_IO, PCI_REG_ADDR_M,
				&em_dev_attr, (caddr_t *)&lp->io_base,
				&lp->io_ha) != DDI_SUCCESS) {
				cmn_err(CE_WARN,
					"%s%d: %s: gem_regs_map_setup failed",
					drv_name, unit, __func__);
				goto err_free_iorange;
			}
		}

		DPRINTF(0, (CE_CONT, CONS "%s%d: rev:0x%02x",
			drv_name, unit, rev));

		ddi_set_driver_private(dip, NULL);

E 2
D 4
		dp = gem_do_attach(dip, gcp, base, &regs_ha,
			lp, sizeof(*lp));
		kmem_free(gcp, sizeof(*gcp));
E 4
I 4
		/* offload and jumbo frame */
		gcp->gc_max_lso = 64 * 1024 - 1;
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);
E 4

I 4
		switch (hw->mac.type) {
		case e1000_82571:
		case e1000_82572:
		case e1000_ich9lan:
		case e1000_ich10lan:
		case e1000_pch2lan:
I 5
		case e1000_pch_lpt:
E 5
		case e1000_82574:
I 5
		case e1000_82583:
E 5
		case e1000_80003es2lan: /* 9K Jumbo Frame size */
			gcp->gc_max_mtu = 9234 - sizeof (struct ether_header);
			break;

		case e1000_pchlan:
			gcp->gc_max_mtu = 4096 - sizeof (struct ether_header);
			break;

			/* Adapters that do not support jumbo frames */
D 5
		case e1000_82583:
E 5
		case e1000_ich8lan:
			gcp->gc_max_mtu = ETHERMTU;
			break;
		default:
			gcp->gc_max_mtu = 0x3f00 - sizeof (struct ether_header);
		}

		dp = gem_do_attach(dip, 0,
		    gcp, hw->hw_addr, &lp->reg_ha, lp, sizeof (*lp));
		kmem_free(gcp, sizeof (*gcp));

E 4
		if (dp != NULL) {
D 3
			return DDI_SUCCESS;
E 3
I 3
			return (DDI_SUCCESS);
E 3
		}

I 3
D 4
		if (lp->flash_ha != 0) {
			ddi_regs_map_free(&lp->flash_ha);
		}
E 4
I 4
err_free_maps:
		e1000_free_pci_resources(lp);
E 4

E 3
D 4
err_free_iorange:
D 3
		ddi_regs_map_free(&lp->io_ha);
E 3
I 3
		if (lp->io_ha != 0) {
			ddi_regs_map_free(&lp->io_ha);
		}
E 4
E 3
err_freelp:
D 4
		kmem_free(lp, sizeof(struct em_dev));
E 4
I 4
		kmem_free(lp, sizeof (struct em_dev));
E 4
err:
		pci_config_teardown(&conf_handle);
D 3
		return DDI_FAILURE;
E 3
I 3
		return (DDI_FAILURE);
E 3
	}
	pci_config_teardown(&conf_handle);
D 3
	return DDI_FAILURE;
E 3
I 3
	return (DDI_FAILURE);
E 3
}

static int
emdetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
D 3
	gld_mac_info_t		*macinfo;
E 3
	struct gem_dev		*dp;
	struct em_dev		*lp;
	timeout_id_t		old_id;
I 4
	int			ret;
E 4

D 3
        macinfo = (gld_mac_info_t *) ddi_get_driver_private(dip);
	dp = (struct gem_dev *) macinfo->gldm_private;
E 3
I 3
	dp = GEM_GET_DEV(dip);
E 3
D 4
	lp = (struct em_dev *) dp->private;
E 4
I 4
	lp = (struct em_dev *)dp->private;
E 4

	switch (cmd) {
	case DDI_DETACH:
D 4
		if (dp->link_watcher_id != 0) {
E 4
I 4
		em_release_manageability(dp);
		em_release_hw_control(dp);

		if (dp->link_watcher_id) {
E 4
			do {
				untimeout(old_id = dp->link_watcher_id);
			} while (old_id != dp->link_watcher_id);
			dp->link_watcher_id = 0;
		}

D 3
		ddi_regs_map_free(&lp->io_ha);
E 3
I 3
D 4
		if (lp->flash_ha != 0) {
E 4
I 4
		if (lp->flash_ha) {
E 4
			ddi_regs_map_free(&lp->flash_ha);
		}

D 4
		if (lp->io_ha != 0) {
E 4
I 4
		if (lp->io_ha) {
E 4
			ddi_regs_map_free(&lp->io_ha);
		}

E 3
		pci_config_teardown(&lp->conf_ha);

D 3
		return gem_do_detach(dip);
E 3
I 3
		return (gem_do_detach(dip));
E 3

	case DDI_SUSPEND:
D 3
		return  gem_suspend(dip);
E 3
I 3
D 4
		return  (gem_suspend(dip));
E 4
I 4
		ret = gem_suspend(dip);
		if (ret == DDI_SUCCESS) {
			em_release_manageability(dp);
			em_release_hw_control(dp);
D 5
#ifdef notyet
			em_enable_wakeup(dev);
E 5
I 5
#ifdef CONFIG_NEW_EM
			em_enable_wakeup(dp);
E 5
#endif
		}
E 4
E 3
	}
D 3
	return DDI_FAILURE;
E 3
I 3
	return (DDI_FAILURE);
E 3
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
I 4
#ifdef GEM_CONFIG_GLDv3
GEM_STREAM_OPS(em_ops, emattach, emdetach);
#else
E 4
static	struct module_info emminfo = {
	0,			/* mi_idnum */
	"em",			/* mi_idname */
	0,			/* mi_minpsz */
D 3
	ETHERMTU,		/* mi_maxpsz */
	TX_BUF_SIZE*ETHERMAX,	/* mi_hiwat */
E 3
I 3
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 3
	1,			/* mi_lowat */
};

static	struct qinit emrinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&emminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit emwinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&emminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	em_info = {
	&emrinit,	/* st_rdinit */
	&emwinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_em_ops = {
	nulldev,	/* cb_open */
	nulldev,	/* cb_close */
	nodev,		/* cb_strategy */
	nodev,		/* cb_print */
	nodev,		/* cb_dump */
	nodev,		/* cb_read */
	nodev,		/* cb_write */
	nodev,		/* cb_ioctl */
	nodev,		/* cb_devmap */
	nodev,		/* cb_mmap */
	nodev,		/* cb_segmap */
	nochpoll,	/* cb_chpoll */
	ddi_prop_op,	/* cb_prop_op */
	&em_info,	/* cb_stream */
	D_MP,		/* cb_flag */
};

static	struct dev_ops em_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	emattach,	/* devo_attach */
	emdetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_em_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
D 4
	gem_power	/* devo_power */
E 4
I 4
	gem_power,	/* devo_power */
#if DEVO_REV >= 4
	gem_quiesce,	/* devo_quiesce */
#endif
E 4
};
D 4

E 4
I 4
#endif /* GEM_CONFIG_GLDv3 */
E 4
static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&em_ops,	/* driver ops */
};

static struct modlinkage modlinkage = {
	MODREV_1, &modldrv, NULL
};

/* ======================================================== */
/*
 * Loadable module support
 */
/* ======================================================== */
int
_init(void)
{
	int 	status;

D 4
	DPRINTF(2, (CE_CONT, "!em: _init: called"));
E 4
I 4
	DPRINTF(2, (CE_CONT, CONS "em: _init: called"));
E 4

D 4
	gem_mod_init(&em_ops, "em");
E 4
I 4
	status = gem_mod_init(&em_ops, "em");
	if (status != DDI_SUCCESS) {
		return (status);
	}
E 4
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&em_ops);
	}
	return (status);
}

/*
 * _fini : done
 */
int
_fini(void)
{
	int	status;

D 4
	DPRINTF(2, (CE_CONT, "!em: _fini: called"));
E 4
I 4
	DPRINTF(2, (CE_CONT, CONS "em: _fini: called"));
E 4
	status = mod_remove(&modlinkage);
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&em_ops);
	}
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
