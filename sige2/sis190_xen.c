  1 /*
  2    sis190.c: Silicon Integrated Systems SiS190 ethernet driver
  3 
  4    Copyright (c) 2003 K.M. Liu <kmliu@sis.com>
  5    Copyright (c) 2003, 2004 Jeff Garzik <jgarzik@pobox.com>
  6    Copyright (c) 2003, 2004, 2005 Francois Romieu <romieu@fr.zoreil.com>
  7 
  8    Based on r8169.c, tg3.c, 8139cp.c, skge.c, epic100.c and SiS 190/191
  9    genuine driver.
 10 
 11    This software may be used and distributed according to the terms of
 12    the GNU General Public License (GPL), incorporated herein by reference.
 13    Drivers based on or derived from this code fall under the GPL and must
 14    retain the authorship, copyright and license notice.  This file is not
 15    a complete program and may only be used when the entire operating
 16    system is licensed under the GPL.
 17 
 18    See the file COPYING in this distribution for more information.
 19 
 20  */
 21 
 22 #include <linux/module.h>
 23 #include <linux/moduleparam.h>
 24 #include <linux/netdevice.h>
 25 #include <linux/rtnetlink.h>
 26 #include <linux/etherdevice.h>
 27 #include <linux/ethtool.h>
 28 #include <linux/pci.h>
 29 #include <linux/mii.h>
 30 #include <linux/delay.h>
 31 #include <linux/crc32.h>
 32 #include <linux/dma-mapping.h>
 33 #include <asm/irq.h>
 34 
 35 #define net_drv(p, arg...)      if (netif_msg_drv(p)) \
 36                                         printk(arg)
 37 #define net_probe(p, arg...)    if (netif_msg_probe(p)) \
 38                                         printk(arg)
 39 #define net_link(p, arg...)     if (netif_msg_link(p)) \
 40                                         printk(arg)
 41 #define net_intr(p, arg...)     if (netif_msg_intr(p)) \
 42                                         printk(arg)
 43 #define net_tx_err(p, arg...)   if (netif_msg_tx_err(p)) \
 44                                         printk(arg)
 45 
 46 #define PHY_MAX_ADDR            32
 47 #define PHY_ID_ANY              0x1f
 48 #define MII_REG_ANY             0x1f
 49 
 50 #ifdef CONFIG_SIS190_NAPI
 51 #define NAPI_SUFFIX     "-NAPI"
 52 #else
 53 #define NAPI_SUFFIX     ""
 54 #endif
 55 
 56 #define DRV_VERSION             "1.2" NAPI_SUFFIX
 57 #define DRV_NAME                "sis190"
 58 #define SIS190_DRIVER_NAME      DRV_NAME " Gigabit Ethernet driver " DRV_VERSION
 59 #define PFX DRV_NAME ": "
 60 
 61 #ifdef CONFIG_SIS190_NAPI
 62 #define sis190_rx_skb                   netif_receive_skb
 63 #define sis190_rx_quota(count, quota)   min(count, quota)
 64 #else
 65 #define sis190_rx_skb                   netif_rx
 66 #define sis190_rx_quota(count, quota)   count
 67 #endif
 68 
 69 #define MAC_ADDR_LEN            6
 70 
 71 #define NUM_TX_DESC             64      /* [8..1024] */
 72 #define NUM_RX_DESC             64      /* [8..8192] */
 73 #define TX_RING_BYTES           (NUM_TX_DESC * sizeof(struct TxDesc))
 74 #define RX_RING_BYTES           (NUM_RX_DESC * sizeof(struct RxDesc))
 75 #define RX_BUF_SIZE             1536
 76 #define RX_BUF_MASK             0xfff8
 77 
 78 #define SIS190_REGS_SIZE        0x80
 79 #define SIS190_TX_TIMEOUT       (6*HZ)
 80 #define SIS190_PHY_TIMEOUT      (10*HZ)
 81 #define SIS190_MSG_DEFAULT      (NETIF_MSG_DRV | NETIF_MSG_PROBE | \
 82                                  NETIF_MSG_LINK | NETIF_MSG_IFUP | \
 83                                  NETIF_MSG_IFDOWN)
 84 
 85 /* Enhanced PHY access register bit definitions */
 86 #define EhnMIIread              0x0000
 87 #define EhnMIIwrite             0x0020
 88 #define EhnMIIdataShift         16
 89 #define EhnMIIpmdShift          6       /* 7016 only */
 90 #define EhnMIIregShift          11
 91 #define EhnMIIreq               0x0010
 92 #define EhnMIInotDone           0x0010
 93 
 94 /* Write/read MMIO register */
 95 #define SIS_W8(reg, val)        writeb ((val), ioaddr + (reg))
 96 #define SIS_W16(reg, val)       writew ((val), ioaddr + (reg))
 97 #define SIS_W32(reg, val)       writel ((val), ioaddr + (reg))
 98 #define SIS_R8(reg)             readb (ioaddr + (reg))
 99 #define SIS_R16(reg)            readw (ioaddr + (reg))
100 #define SIS_R32(reg)            readl (ioaddr + (reg))
101 
102 #define SIS_PCI_COMMIT()        SIS_R32(IntrControl)
103 
104 enum sis190_registers {
105         TxControl               = 0x00,
106         TxDescStartAddr         = 0x04,
107         rsv0                    = 0x08, // reserved
108         TxSts                   = 0x0c, // unused (Control/Status)
109         RxControl               = 0x10,
110         RxDescStartAddr         = 0x14,
111         rsv1                    = 0x18, // reserved
112         RxSts                   = 0x1c, // unused
113         IntrStatus              = 0x20,
114         IntrMask                = 0x24,
115         IntrControl             = 0x28,
116         IntrTimer               = 0x2c, // unused (Interupt Timer)
117         PMControl               = 0x30, // unused (Power Mgmt Control/Status)
118         rsv2                    = 0x34, // reserved
119         ROMControl              = 0x38,
120         ROMInterface            = 0x3c,
121         StationControl          = 0x40,
122         GMIIControl             = 0x44,
123         GIoCR                   = 0x48, // unused (GMAC IO Compensation)
124         GIoCtrl                 = 0x4c, // unused (GMAC IO Control)
125         TxMacControl            = 0x50,
126         TxLimit                 = 0x54, // unused (Tx MAC Timer/TryLimit)
127         RGDelay                 = 0x58, // unused (RGMII Tx Internal Delay)
128         rsv3                    = 0x5c, // reserved
129         RxMacControl            = 0x60,
130         RxMacAddr               = 0x62,
131         RxHashTable             = 0x68,
132         // Undocumented         = 0x6c,
133         RxWolCtrl               = 0x70,
134         RxWolData               = 0x74, // unused (Rx WOL Data Access)
135         RxMPSControl            = 0x78, // unused (Rx MPS Control)
136         rsv4                    = 0x7c, // reserved
137 };
138 
139 enum sis190_register_content {
140         /* IntrStatus */
141         SoftInt                 = 0x40000000,   // unused
142         Timeup                  = 0x20000000,   // unused
143         PauseFrame              = 0x00080000,   // unused
144         MagicPacket             = 0x00040000,   // unused
145         WakeupFrame             = 0x00020000,   // unused
146         LinkChange              = 0x00010000,
147         RxQEmpty                = 0x00000080,
148         RxQInt                  = 0x00000040,
149         TxQ1Empty               = 0x00000020,   // unused
150         TxQ1Int                 = 0x00000010,
151         TxQ0Empty               = 0x00000008,   // unused
152         TxQ0Int                 = 0x00000004,
153         RxHalt                  = 0x00000002,
154         TxHalt                  = 0x00000001,
155 
156         /* {Rx/Tx}CmdBits */
157         CmdReset                = 0x10,
158         CmdRxEnb                = 0x08,         // unused
159         CmdTxEnb                = 0x01,
160         RxBufEmpty              = 0x01,         // unused
161 
162         /* Cfg9346Bits */
163         Cfg9346_Lock            = 0x00,         // unused
164         Cfg9346_Unlock          = 0xc0,         // unused
165 
166         /* RxMacControl */
167         AcceptErr               = 0x20,         // unused
168         AcceptRunt              = 0x10,         // unused
169         AcceptBroadcast         = 0x0800,
170         AcceptMulticast         = 0x0400,
171         AcceptMyPhys            = 0x0200,
172         AcceptAllPhys           = 0x0100,
173 
174         /* RxConfigBits */
175         RxCfgFIFOShift          = 13,
176         RxCfgDMAShift           = 8,            // 0x1a in RxControl ?
177 
178         /* TxConfigBits */
179         TxInterFrameGapShift    = 24,
180         TxDMAShift              = 8, /* DMA burst value (0-7) is shift this many bits */
181 
182         LinkStatus              = 0x02,         // unused
183         FullDup                 = 0x01,         // unused
184 
185         /* TBICSRBit */
186         TBILinkOK               = 0x02000000,   // unused
187 };
188 
189 struct TxDesc {
190         __le32 PSize;
191         __le32 status;
192         __le32 addr;
193         __le32 size;
194 };
195 
196 struct RxDesc {
197         __le32 PSize;
198         __le32 status;
199         __le32 addr;
200         __le32 size;
201 };
202 
203 enum _DescStatusBit {
204         /* _Desc.status */
205         OWNbit          = 0x80000000, // RXOWN/TXOWN
206         INTbit          = 0x40000000, // RXINT/TXINT
207         CRCbit          = 0x00020000, // CRCOFF/CRCEN
208         PADbit          = 0x00010000, // PREADD/PADEN
209         /* _Desc.size */
210         RingEnd         = 0x80000000,
211         /* TxDesc.status */
212         LSEN            = 0x08000000, // TSO ? -- FR
213         IPCS            = 0x04000000,
214         TCPCS           = 0x02000000,
215         UDPCS           = 0x01000000,
216         BSTEN           = 0x00800000,
217         EXTEN           = 0x00400000,
218         DEFEN           = 0x00200000,
219         BKFEN           = 0x00100000,
220         CRSEN           = 0x00080000,
221         COLEN           = 0x00040000,
222         THOL3           = 0x30000000,
223         THOL2           = 0x20000000,
224         THOL1           = 0x10000000,
225         THOL0           = 0x00000000,
226         /* RxDesc.status */
227         IPON            = 0x20000000,
228         TCPON           = 0x10000000,
229         UDPON           = 0x08000000,
230         Wakup           = 0x00400000,
231         Magic           = 0x00200000,
232         Pause           = 0x00100000,
233         DEFbit          = 0x00200000,
234         BCAST           = 0x000c0000,
235         MCAST           = 0x00080000,
236         UCAST           = 0x00040000,
237         /* RxDesc.PSize */
238         TAGON           = 0x80000000,
239         RxDescCountMask = 0x7f000000, // multi-desc pkt when > 1 ? -- FR
240         ABORT           = 0x00800000,
241         SHORT           = 0x00400000,
242         LIMIT           = 0x00200000,
243         MIIER           = 0x00100000,
244         OVRUN           = 0x00080000,
245         NIBON           = 0x00040000,
246         COLON           = 0x00020000,
247         CRCOK           = 0x00010000,
248         RxSizeMask      = 0x0000ffff
249         /*
250          * The asic could apparently do vlan, TSO, jumbo (sis191 only) and
251          * provide two (unused with Linux) Tx queues. No publically
252          * available documentation alas.
253          */
254 };
255 
256 enum sis190_eeprom_access_register_bits {
257         EECS    = 0x00000001,   // unused
258         EECLK   = 0x00000002,   // unused
259         EEDO    = 0x00000008,   // unused
260         EEDI    = 0x00000004,   // unused
261         EEREQ   = 0x00000080,
262         EEROP   = 0x00000200,
263         EEWOP   = 0x00000100    // unused
264 };
265 
266 /* EEPROM Addresses */
267 enum sis190_eeprom_address {
268         EEPROMSignature = 0x00,
269         EEPROMCLK       = 0x01, // unused
270         EEPROMInfo      = 0x02,
271         EEPROMMACAddr   = 0x03
272 };
273 
274 enum sis190_feature {
275         F_HAS_RGMII     = 1,
276         F_PHY_88E1111   = 2,
277         F_PHY_BCM5461   = 4
278 };
279 
280 struct sis190_private {
281         void __iomem *mmio_addr;
282         struct pci_dev *pci_dev;
283         struct net_device_stats stats;
284         spinlock_t lock;
285         u32 rx_buf_sz;
286         u32 cur_rx;
287         u32 cur_tx;
288         u32 dirty_rx;
289         u32 dirty_tx;
290         dma_addr_t rx_dma;
291         dma_addr_t tx_dma;
292         struct RxDesc *RxDescRing;
293         struct TxDesc *TxDescRing;
294         struct sk_buff *Rx_skbuff[NUM_RX_DESC];
295         struct sk_buff *Tx_skbuff[NUM_TX_DESC];
296         struct work_struct phy_task;
297         struct timer_list timer;
298         u32 msg_enable;
299         struct mii_if_info mii_if;
300         struct list_head first_phy;
301         u32 features;
302 };
303 
304 struct sis190_phy {
305         struct list_head list;
306         int phy_id;
307         u16 id[2];
308         u16 status;
309         u8  type;
310 };
311 
312 enum sis190_phy_type {
313         UNKNOWN = 0x00,
314         HOME    = 0x01,
315         LAN     = 0x02,
316         MIX     = 0x03
317 };
318 
319 static struct mii_chip_info {
320         const char *name;
321         u16 id[2];
322         unsigned int type;
323         u32 feature;
324 } mii_chip_table[] = {
325         { "Broadcom PHY BCM5461", { 0x0020, 0x60c0 }, LAN, F_PHY_BCM5461 },
326         { "Agere PHY ET1101B",    { 0x0282, 0xf010 }, LAN, 0 },
327         { "Marvell PHY 88E1111",  { 0x0141, 0x0cc0 }, LAN, F_PHY_88E1111 },
328         { "Realtek PHY RTL8201",  { 0x0000, 0x8200 }, LAN, 0 },
329         { NULL, }
330 };
331 
332 static const struct {
333         const char *name;
334 } sis_chip_info[] = {
335         { "SiS 190 PCI Fast Ethernet adapter" },
336         { "SiS 191 PCI Gigabit Ethernet adapter" },
337 };
338 
339 static struct pci_device_id sis190_pci_tbl[] __devinitdata = {
340         { PCI_DEVICE(PCI_VENDOR_ID_SI, 0x0190), 0, 0, 0 },
341         { PCI_DEVICE(PCI_VENDOR_ID_SI, 0x0191), 0, 0, 1 },
342         { 0, },
343 };
344 
345 MODULE_DEVICE_TABLE(pci, sis190_pci_tbl);
346 
347 static int rx_copybreak = 200;
348 
349 static struct {
350         u32 msg_enable;
351 } debug = { -1 };
352 
353 MODULE_DESCRIPTION("SiS sis190 Gigabit Ethernet driver");
354 module_param(rx_copybreak, int, 0);
355 MODULE_PARM_DESC(rx_copybreak, "Copy breakpoint for copy-only-tiny-frames");
356 module_param_named(debug, debug.msg_enable, int, 0);
357 MODULE_PARM_DESC(debug, "Debug verbosity level (0=none, ..., 16=all)");
358 MODULE_AUTHOR("K.M. Liu <kmliu@sis.com>, Ueimor <romieu@fr.zoreil.com>");
359 MODULE_VERSION(DRV_VERSION);
360 MODULE_LICENSE("GPL");
361 
362 static const u32 sis190_intr_mask =
363         RxQEmpty | RxQInt | TxQ1Int | TxQ0Int | RxHalt | TxHalt | LinkChange;
364 
365 /*
366  * Maximum number of multicast addresses to filter (vs. Rx-all-multicast).
367  * The chips use a 64 element hash table based on the Ethernet CRC.
368  */
369 static int multicast_filter_limit = 32;
370 
371 static void __mdio_cmd(void __iomem *ioaddr, u32 ctl)
372 {
373         unsigned int i;
374 
375         SIS_W32(GMIIControl, ctl);
376 
377         msleep(1);
378 
379         for (i = 0; i < 100; i++) {
380                 if (!(SIS_R32(GMIIControl) & EhnMIInotDone))
381                         break;
382                 msleep(1);
383         }
384 
385         if (i > 999)
386                 printk(KERN_ERR PFX "PHY command failed !\n");
387 }
388 
389 static void mdio_write(void __iomem *ioaddr, int phy_id, int reg, int val)
390 {
391         __mdio_cmd(ioaddr, EhnMIIreq | EhnMIIwrite |
392                 (((u32) reg) << EhnMIIregShift) | (phy_id << EhnMIIpmdShift) |
393                 (((u32) val) << EhnMIIdataShift));
394 }
395 
396 static int mdio_read(void __iomem *ioaddr, int phy_id, int reg)
397 {
398         __mdio_cmd(ioaddr, EhnMIIreq | EhnMIIread |
399                 (((u32) reg) << EhnMIIregShift) | (phy_id << EhnMIIpmdShift));
400 
401         return (u16) (SIS_R32(GMIIControl) >> EhnMIIdataShift);
402 }
403 
404 static void __mdio_write(struct net_device *dev, int phy_id, int reg, int val)
405 {
406         struct sis190_private *tp = netdev_priv(dev);
407 
408         mdio_write(tp->mmio_addr, phy_id, reg, val);
409 }
410 
411 static int __mdio_read(struct net_device *dev, int phy_id, int reg)
412 {
413         struct sis190_private *tp = netdev_priv(dev);
414 
415         return mdio_read(tp->mmio_addr, phy_id, reg);
416 }
417 
418 static u16 mdio_read_latched(void __iomem *ioaddr, int phy_id, int reg)
419 {
420         mdio_read(ioaddr, phy_id, reg);
421         return mdio_read(ioaddr, phy_id, reg);
422 }
423 
424 static u16 __devinit sis190_read_eeprom(void __iomem *ioaddr, u32 reg)
425 {
426         u16 data = 0xffff;
427         unsigned int i;
428 
429         if (!(SIS_R32(ROMControl) & 0x0002))
430                 return 0;
431 
432         SIS_W32(ROMInterface, EEREQ | EEROP | (reg << 10));
433 
434         for (i = 0; i < 200; i++) {
435                 if (!(SIS_R32(ROMInterface) & EEREQ)) {
436                         data = (SIS_R32(ROMInterface) & 0xffff0000) >> 16;
437                         break;
438                 }
439                 msleep(1);
440         }
441 
442         return data;
443 }
444 
445 static void sis190_irq_mask_and_ack(void __iomem *ioaddr)
446 {
447         SIS_W32(IntrMask, 0x00);
448         SIS_W32(IntrStatus, 0xffffffff);
449         SIS_PCI_COMMIT();
450 }
451 
452 static void sis190_asic_down(void __iomem *ioaddr)
453 {
454         /* Stop the chip's Tx and Rx DMA processes. */
455 
456         SIS_W32(TxControl, 0x1a00);
457         SIS_W32(RxControl, 0x1a00);
458 
459         sis190_irq_mask_and_ack(ioaddr);
460 }
461 
462 static void sis190_mark_as_last_descriptor(struct RxDesc *desc)
463 {
464         desc->size |= cpu_to_le32(RingEnd);
465 }
466 
467 static inline void sis190_give_to_asic(struct RxDesc *desc, u32 rx_buf_sz)
468 {
469         u32 eor = le32_to_cpu(desc->size) & RingEnd;
470 
471         desc->PSize = 0x0;
472         desc->size = cpu_to_le32((rx_buf_sz & RX_BUF_MASK) | eor);
473         wmb();
474         desc->status = cpu_to_le32(OWNbit | INTbit);
475 }
476 
477 static inline void sis190_map_to_asic(struct RxDesc *desc, dma_addr_t mapping,
478                                       u32 rx_buf_sz)
479 {
480         desc->addr = cpu_to_le32(mapping);
481         sis190_give_to_asic(desc, rx_buf_sz);
482 }
483 
484 static inline void sis190_make_unusable_by_asic(struct RxDesc *desc)
485 {
486         desc->PSize = 0x0;
487         desc->addr = 0xdeadbeef;
488         desc->size &= cpu_to_le32(RingEnd);
489         wmb();
490         desc->status = 0x0;
491 }
492 
493 static int sis190_alloc_rx_skb(struct pci_dev *pdev, struct sk_buff **sk_buff,
494                                struct RxDesc *desc, u32 rx_buf_sz)
495 {
496         struct sk_buff *skb;
497         dma_addr_t mapping;
498         int ret = 0;
499 
500         skb = dev_alloc_skb(rx_buf_sz);
501         if (!skb)
502                 goto err_out;
503 
504         *sk_buff = skb;
505 
506         mapping = pci_map_single(pdev, skb->data, rx_buf_sz,
507                                  PCI_DMA_FROMDEVICE);
508 
509         sis190_map_to_asic(desc, mapping, rx_buf_sz);
510 out:
511         return ret;
512 
513 err_out:
514         ret = -ENOMEM;
515         sis190_make_unusable_by_asic(desc);
516         goto out;
517 }
518 
519 static u32 sis190_rx_fill(struct sis190_private *tp, struct net_device *dev,
520                           u32 start, u32 end)
521 {
522         u32 cur;
523 
524         for (cur = start; cur < end; cur++) {
525                 int ret, i = cur % NUM_RX_DESC;
526 
527                 if (tp->Rx_skbuff[i])
528                         continue;
529 
530                 ret = sis190_alloc_rx_skb(tp->pci_dev, tp->Rx_skbuff + i,
531                                           tp->RxDescRing + i, tp->rx_buf_sz);
532                 if (ret < 0)
533                         break;
534         }
535         return cur - start;
536 }
537 
538 static inline int sis190_try_rx_copy(struct sk_buff **sk_buff, int pkt_size,
539                                      struct RxDesc *desc, int rx_buf_sz)
540 {
541         int ret = -1;
542 
543         if (pkt_size < rx_copybreak) {
544                 struct sk_buff *skb;
545 
546                 skb = dev_alloc_skb(pkt_size + NET_IP_ALIGN);
547                 if (skb) {
548                         skb_reserve(skb, NET_IP_ALIGN);
549                         eth_copy_and_sum(skb, sk_buff[0]->data, pkt_size, 0);
550                         *sk_buff = skb;
551                         sis190_give_to_asic(desc, rx_buf_sz);
552                         ret = 0;
553                 }
554         }
555         return ret;
556 }
557 
558 static inline int sis190_rx_pkt_err(u32 status, struct net_device_stats *stats)
559 {
560 #define ErrMask (OVRUN | SHORT | LIMIT | MIIER | NIBON | COLON | ABORT)
561 
562         if ((status & CRCOK) && !(status & ErrMask))
563                 return 0;
564 
565         if (!(status & CRCOK))
566                 stats->rx_crc_errors++;
567         else if (status & OVRUN)
568                 stats->rx_over_errors++;
569         else if (status & (SHORT | LIMIT))
570                 stats->rx_length_errors++;
571         else if (status & (MIIER | NIBON | COLON))
572                 stats->rx_frame_errors++;
573 
574         stats->rx_errors++;
575         return -1;
576 }
577 
578 static int sis190_rx_interrupt(struct net_device *dev,
579                                struct sis190_private *tp, void __iomem *ioaddr)
580 {
581         struct net_device_stats *stats = &tp->stats;
582         u32 rx_left, cur_rx = tp->cur_rx;
583         u32 delta, count;
584 
585         rx_left = NUM_RX_DESC + tp->dirty_rx - cur_rx;
586         rx_left = sis190_rx_quota(rx_left, (u32) dev->quota);
587 
588         for (; rx_left > 0; rx_left--, cur_rx++) {
589                 unsigned int entry = cur_rx % NUM_RX_DESC;
590                 struct RxDesc *desc = tp->RxDescRing + entry;
591                 u32 status;
592 
593                 if (desc->status & OWNbit)
594                         break;
595 
596                 status = le32_to_cpu(desc->PSize);
597 
598                 // net_intr(tp, KERN_INFO "%s: Rx PSize = %08x.\n", dev->name,
599                 //       status);
600 
601                 if (sis190_rx_pkt_err(status, stats) < 0)
602                         sis190_give_to_asic(desc, tp->rx_buf_sz);
603                 else {
604                         struct sk_buff *skb = tp->Rx_skbuff[entry];
605                         int pkt_size = (status & RxSizeMask) - 4;
606                         void (*pci_action)(struct pci_dev *, dma_addr_t,
607                                 size_t, int) = pci_dma_sync_single_for_device;
608 
609                         if (unlikely(pkt_size > tp->rx_buf_sz)) {
610                                 net_intr(tp, KERN_INFO
611                                          "%s: (frag) status = %08x.\n",
612                                          dev->name, status);
613                                 stats->rx_dropped++;
614                                 stats->rx_length_errors++;
615                                 sis190_give_to_asic(desc, tp->rx_buf_sz);
616                                 continue;
617                         }
618 
619                         pci_dma_sync_single_for_cpu(tp->pci_dev,
620                                 le32_to_cpu(desc->addr), tp->rx_buf_sz,
621                                 PCI_DMA_FROMDEVICE);
622 
623                         if (sis190_try_rx_copy(&skb, pkt_size, desc,
624                                                tp->rx_buf_sz)) {
625                                 pci_action = pci_unmap_single;
626                                 tp->Rx_skbuff[entry] = NULL;
627                                 sis190_make_unusable_by_asic(desc);
628                         }
629 
630                         pci_action(tp->pci_dev, le32_to_cpu(desc->addr),
631                                    tp->rx_buf_sz, PCI_DMA_FROMDEVICE);
632 
633                         skb->dev = dev;
634                         skb_put(skb, pkt_size);
635                         skb->protocol = eth_type_trans(skb, dev);
636 
637                         sis190_rx_skb(skb);
638 
639                         dev->last_rx = jiffies;
640                         stats->rx_packets++;
641                         stats->rx_bytes += pkt_size;
642                         if ((status & BCAST) == MCAST)
643                                 stats->multicast++;
644                 }
645         }
646         count = cur_rx - tp->cur_rx;
647         tp->cur_rx = cur_rx;
648 
649         delta = sis190_rx_fill(tp, dev, tp->dirty_rx, tp->cur_rx);
650         if (!delta && count && netif_msg_intr(tp))
651                 printk(KERN_INFO "%s: no Rx buffer allocated.\n", dev->name);
652         tp->dirty_rx += delta;
653 
654         if (((tp->dirty_rx + NUM_RX_DESC) == tp->cur_rx) && netif_msg_intr(tp))
655                 printk(KERN_EMERG "%s: Rx buffers exhausted.\n", dev->name);
656 
657         return count;
658 }
659 
660 static void sis190_unmap_tx_skb(struct pci_dev *pdev, struct sk_buff *skb,
661                                 struct TxDesc *desc)
662 {
663         unsigned int len;
664 
665         len = skb->len < ETH_ZLEN ? ETH_ZLEN : skb->len;
666 
667         pci_unmap_single(pdev, le32_to_cpu(desc->addr), len, PCI_DMA_TODEVICE);
668 
669         memset(desc, 0x00, sizeof(*desc));
670 }
671 
672 static void sis190_tx_interrupt(struct net_device *dev,
673                                 struct sis190_private *tp, void __iomem *ioaddr)
674 {
675         u32 pending, dirty_tx = tp->dirty_tx;
676         /*
677          * It would not be needed if queueing was allowed to be enabled
678          * again too early (hint: think preempt and unclocked smp systems).
679          */
680         unsigned int queue_stopped;
681 
682         smp_rmb();
683         pending = tp->cur_tx - dirty_tx;
684         queue_stopped = (pending == NUM_TX_DESC);
685 
686         for (; pending; pending--, dirty_tx++) {
687                 unsigned int entry = dirty_tx % NUM_TX_DESC;
688                 struct TxDesc *txd = tp->TxDescRing + entry;
689                 struct sk_buff *skb;
690 
691                 if (le32_to_cpu(txd->status) & OWNbit)
692                         break;
693 
694                 skb = tp->Tx_skbuff[entry];
695 
696                 tp->stats.tx_packets++;
697                 tp->stats.tx_bytes += skb->len;
698 
699                 sis190_unmap_tx_skb(tp->pci_dev, skb, txd);
700                 tp->Tx_skbuff[entry] = NULL;
701                 dev_kfree_skb_irq(skb);
702         }
703 
704         if (tp->dirty_tx != dirty_tx) {
705                 tp->dirty_tx = dirty_tx;
706                 smp_wmb();
707                 if (queue_stopped)
708                         netif_wake_queue(dev);
709         }
710 }
711 
712 /*
713  * The interrupt handler does all of the Rx thread work and cleans up after
714  * the Tx thread.
715  */
716 static irqreturn_t sis190_interrupt(int irq, void *__dev, struct pt_regs *regs)
717 {
718         struct net_device *dev = __dev;
719         struct sis190_private *tp = netdev_priv(dev);
720         void __iomem *ioaddr = tp->mmio_addr;
721         unsigned int handled = 0;
722         u32 status;
723 
724         status = SIS_R32(IntrStatus);
725 
726         if ((status == 0xffffffff) || !status)
727                 goto out;
728 
729         handled = 1;
730 
731         if (unlikely(!netif_running(dev))) {
732                 sis190_asic_down(ioaddr);
733                 goto out;
734         }
735 
736         SIS_W32(IntrStatus, status);
737 
738         // net_intr(tp, KERN_INFO "%s: status = %08x.\n", dev->name, status);
739 
740         if (status & LinkChange) {
741                 net_intr(tp, KERN_INFO "%s: link change.\n", dev->name);
742                 schedule_work(&tp->phy_task);
743         }
744 
745         if (status & RxQInt)
746                 sis190_rx_interrupt(dev, tp, ioaddr);
747 
748         if (status & TxQ0Int)
749                 sis190_tx_interrupt(dev, tp, ioaddr);
750 out:
751         return IRQ_RETVAL(handled);
752 }
753 
754 #ifdef CONFIG_NET_POLL_CONTROLLER
755 static void sis190_netpoll(struct net_device *dev)
756 {
757         struct sis190_private *tp = netdev_priv(dev);
758         struct pci_dev *pdev = tp->pci_dev;
759 
760         disable_irq(pdev->irq);
761         sis190_interrupt(pdev->irq, dev, NULL);
762         enable_irq(pdev->irq);
763 }
764 #endif
765 
766 static void sis190_free_rx_skb(struct sis190_private *tp,
767                                struct sk_buff **sk_buff, struct RxDesc *desc)
768 {
769         struct pci_dev *pdev = tp->pci_dev;
770 
771         pci_unmap_single(pdev, le32_to_cpu(desc->addr), tp->rx_buf_sz,
772                          PCI_DMA_FROMDEVICE);
773         dev_kfree_skb(*sk_buff);
774         *sk_buff = NULL;
775         sis190_make_unusable_by_asic(desc);
776 }
777 
778 static void sis190_rx_clear(struct sis190_private *tp)
779 {
780         unsigned int i;
781 
782         for (i = 0; i < NUM_RX_DESC; i++) {
783                 if (!tp->Rx_skbuff[i])
784                         continue;
785                 sis190_free_rx_skb(tp, tp->Rx_skbuff + i, tp->RxDescRing + i);
786         }
787 }
788 
789 static void sis190_init_ring_indexes(struct sis190_private *tp)
790 {
791         tp->dirty_tx = tp->dirty_rx = tp->cur_tx = tp->cur_rx = 0;
792 }
793 
794 static int sis190_init_ring(struct net_device *dev)
795 {
796         struct sis190_private *tp = netdev_priv(dev);
797 
798         sis190_init_ring_indexes(tp);
799 
800         memset(tp->Tx_skbuff, 0x0, NUM_TX_DESC * sizeof(struct sk_buff *));
801         memset(tp->Rx_skbuff, 0x0, NUM_RX_DESC * sizeof(struct sk_buff *));
802 
803         if (sis190_rx_fill(tp, dev, 0, NUM_RX_DESC) != NUM_RX_DESC)
804                 goto err_rx_clear;
805 
806         sis190_mark_as_last_descriptor(tp->RxDescRing + NUM_RX_DESC - 1);
807 
808         return 0;
809 
810 err_rx_clear:
811         sis190_rx_clear(tp);
812         return -ENOMEM;
813 }
814 
815 static void sis190_set_rx_mode(struct net_device *dev)
816 {
817         struct sis190_private *tp = netdev_priv(dev);
818         void __iomem *ioaddr = tp->mmio_addr;
819         unsigned long flags;
820         u32 mc_filter[2];       /* Multicast hash filter */
821         u16 rx_mode;
822 
823         if (dev->flags & IFF_PROMISC) {
824                 /* Unconditionally log net taps. */
825                 net_drv(tp, KERN_NOTICE "%s: Promiscuous mode enabled.\n",
826                         dev->name);
827                 rx_mode =
828                         AcceptBroadcast | AcceptMulticast | AcceptMyPhys |
829                         AcceptAllPhys;
830                 mc_filter[1] = mc_filter[0] = 0xffffffff;
831         } else if ((dev->mc_count > multicast_filter_limit) ||
832                    (dev->flags & IFF_ALLMULTI)) {
833                 /* Too many to filter perfectly -- accept all multicasts. */
834                 rx_mode = AcceptBroadcast | AcceptMulticast | AcceptMyPhys;
835                 mc_filter[1] = mc_filter[0] = 0xffffffff;
836         } else {
837                 struct dev_mc_list *mclist;
838                 unsigned int i;
839 
840                 rx_mode = AcceptBroadcast | AcceptMyPhys;
841                 mc_filter[1] = mc_filter[0] = 0;
842                 for (i = 0, mclist = dev->mc_list; mclist && i < dev->mc_count;
843                      i++, mclist = mclist->next) {
844                         int bit_nr =
845                                 ether_crc(ETH_ALEN, mclist->dmi_addr) & 0x3f;
846                         mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
847                         rx_mode |= AcceptMulticast;
848                 }
849         }
850 
851         spin_lock_irqsave(&tp->lock, flags);
852 
853         SIS_W16(RxMacControl, rx_mode | 0x2);
854         SIS_W32(RxHashTable, mc_filter[0]);
855         SIS_W32(RxHashTable + 4, mc_filter[1]);
856 
857         spin_unlock_irqrestore(&tp->lock, flags);
858 }
859 
860 static void sis190_soft_reset(void __iomem *ioaddr)
861 {
862         SIS_W32(IntrControl, 0x8000);
863         SIS_PCI_COMMIT();
864         msleep(1);
865         SIS_W32(IntrControl, 0x0);
866         sis190_asic_down(ioaddr);
867         msleep(1);
868 }
869 
870 static void sis190_hw_start(struct net_device *dev)
871 {
872         struct sis190_private *tp = netdev_priv(dev);
873         void __iomem *ioaddr = tp->mmio_addr;
874 
875         sis190_soft_reset(ioaddr);
876 
877         SIS_W32(TxDescStartAddr, tp->tx_dma);
878         SIS_W32(RxDescStartAddr, tp->rx_dma);
879 
880         SIS_W32(IntrStatus, 0xffffffff);
881         SIS_W32(IntrMask, 0x0);
882         SIS_W32(GMIIControl, 0x0);
883         SIS_W32(TxMacControl, 0x60);
884         SIS_W16(RxMacControl, 0x02);
885         SIS_W32(RxHashTable, 0x0);
886         SIS_W32(0x6c, 0x0);
887         SIS_W32(RxWolCtrl, 0x0);
888         SIS_W32(RxWolData, 0x0);
889 
890         SIS_PCI_COMMIT();
891 
892         sis190_set_rx_mode(dev);
893 
894         /* Enable all known interrupts by setting the interrupt mask. */
895         SIS_W32(IntrMask, sis190_intr_mask);
896 
897         SIS_W32(TxControl, 0x1a00 | CmdTxEnb);
898         SIS_W32(RxControl, 0x1a1d);
899 
900         netif_start_queue(dev);
901 }
902 
903 static void sis190_phy_task(void * data)
904 {
905         struct net_device *dev = data;
906         struct sis190_private *tp = netdev_priv(dev);
907         void __iomem *ioaddr = tp->mmio_addr;
908         int phy_id = tp->mii_if.phy_id;
909         u16 val;
910 
911         rtnl_lock();
912 
913         val = mdio_read(ioaddr, phy_id, MII_BMCR);
914         if (val & BMCR_RESET) {
915                 // FIXME: needlessly high ?  -- FR 02/07/2005
916                 mod_timer(&tp->timer, jiffies + HZ/10);
917         } else if (!(mdio_read_latched(ioaddr, phy_id, MII_BMSR) &
918                      BMSR_ANEGCOMPLETE)) {
919                 net_link(tp, KERN_WARNING "%s: PHY reset until link up.\n",
920                          dev->name);
921                 netif_carrier_off(dev);
922                 mdio_write(ioaddr, phy_id, MII_BMCR, val | BMCR_RESET);
923                 mod_timer(&tp->timer, jiffies + SIS190_PHY_TIMEOUT);
924         } else {
925                 /* Rejoice ! */
926                 struct {
927                         int val;
928                         u32 ctl;
929                         const char *msg;
930                 } reg31[] = {
931                         { LPA_1000XFULL | LPA_SLCT, 0x07000c00 | 0x00001000,
932                                 "1000 Mbps Full Duplex" },
933                         { LPA_1000XHALF | LPA_SLCT, 0x07000c00,
934                                 "1000 Mbps Half Duplex" },
935                         { LPA_100FULL, 0x04000800 | 0x00001000,
936                                 "100 Mbps Full Duplex" },
937                         { LPA_100HALF, 0x04000800,
938                                 "100 Mbps Half Duplex" },
939                         { LPA_10FULL, 0x04000400 | 0x00001000,
940                                 "10 Mbps Full Duplex" },
941                         { LPA_10HALF, 0x04000400,
942                                 "10 Mbps Half Duplex" },
943                         { 0, 0x04000400, "unknown" }
944                 }, *p;
945                 u16 adv;
946 
947                 val = mdio_read(ioaddr, phy_id, 0x1f);
948                 net_link(tp, KERN_INFO "%s: mii ext = %04x.\n", dev->name, val);
949 
950                 val = mdio_read(ioaddr, phy_id, MII_LPA);
951                 adv = mdio_read(ioaddr, phy_id, MII_ADVERTISE);
952                 net_link(tp, KERN_INFO "%s: mii lpa = %04x adv = %04x.\n",
953                          dev->name, val, adv);
954 
955                 val &= adv;
956 
957                 for (p = reg31; p->val; p++) {
958                         if ((val & p->val) == p->val)
959                                 break;
960                 }
961 
962                 p->ctl |= SIS_R32(StationControl) & ~0x0f001c00;
963 
964                 if ((tp->features & F_HAS_RGMII) &&
965                     (tp->features & F_PHY_BCM5461)) {
966                         // Set Tx Delay in RGMII mode.
967                         mdio_write(ioaddr, phy_id, 0x18, 0xf1c7);
968                         udelay(200);
969                         mdio_write(ioaddr, phy_id, 0x1c, 0x8c00);
970                         p->ctl |= 0x03000000;
971                 }
972 
973                 SIS_W32(StationControl, p->ctl);
974 
975                 if (tp->features & F_HAS_RGMII) {
976                         SIS_W32(RGDelay, 0x0441);
977                         SIS_W32(RGDelay, 0x0440);
978                 }
979 
980                 net_link(tp, KERN_INFO "%s: link on %s mode.\n", dev->name,
981                          p->msg);
982                 netif_carrier_on(dev);
983         }
984 
985         rtnl_unlock();
986 }
987 
988 static void sis190_phy_timer(unsigned long __opaque)
989 {
990         struct net_device *dev = (struct net_device *)__opaque;
991         struct sis190_private *tp = netdev_priv(dev);
992 
993         if (likely(netif_running(dev)))
994                 schedule_work(&tp->phy_task);
995 }
996 
997 static inline void sis190_delete_timer(struct net_device *dev)
998 {
999         struct sis190_private *tp = netdev_priv(dev);
1000 
1001         del_timer_sync(&tp->timer);
1002 }
1003 
1004 static inline void sis190_request_timer(struct net_device *dev)
1005 {
1006         struct sis190_private *tp = netdev_priv(dev);
1007         struct timer_list *timer = &tp->timer;
1008 
1009         init_timer(timer);
1010         timer->expires = jiffies + SIS190_PHY_TIMEOUT;
1011         timer->data = (unsigned long)dev;
1012         timer->function = sis190_phy_timer;
1013         add_timer(timer);
1014 }
1015 
1016 static void sis190_set_rxbufsize(struct sis190_private *tp,
1017                                  struct net_device *dev)
1018 {
1019         unsigned int mtu = dev->mtu;
1020 
1021         tp->rx_buf_sz = (mtu > RX_BUF_SIZE) ? mtu + ETH_HLEN + 8 : RX_BUF_SIZE;
1022         /* RxDesc->size has a licence to kill the lower bits */
1023         if (tp->rx_buf_sz & 0x07) {
1024                 tp->rx_buf_sz += 8;
1025                 tp->rx_buf_sz &= RX_BUF_MASK;
1026         }
1027 }
1028 
1029 static int sis190_open(struct net_device *dev)
1030 {
1031         struct sis190_private *tp = netdev_priv(dev);
1032         struct pci_dev *pdev = tp->pci_dev;
1033         int rc = -ENOMEM;
1034 
1035         sis190_set_rxbufsize(tp, dev);
1036 
1037         /*
1038          * Rx and Tx descriptors need 256 bytes alignment.
1039          * pci_alloc_consistent() guarantees a stronger alignment.
1040          */
1041         tp->TxDescRing = pci_alloc_consistent(pdev, TX_RING_BYTES, &tp->tx_dma);
1042         if (!tp->TxDescRing)
1043                 goto out;
1044 
1045         tp->RxDescRing = pci_alloc_consistent(pdev, RX_RING_BYTES, &tp->rx_dma);
1046         if (!tp->RxDescRing)
1047                 goto err_free_tx_0;
1048 
1049         rc = sis190_init_ring(dev);
1050         if (rc < 0)
1051                 goto err_free_rx_1;
1052 
1053         INIT_WORK(&tp->phy_task, sis190_phy_task, dev);
1054 
1055         sis190_request_timer(dev);
1056 
1057         rc = request_irq(dev->irq, sis190_interrupt, SA_SHIRQ, dev->name, dev);
1058         if (rc < 0)
1059                 goto err_release_timer_2;
1060 
1061         sis190_hw_start(dev);
1062 out:
1063         return rc;
1064 
1065 err_release_timer_2:
1066         sis190_delete_timer(dev);
1067         sis190_rx_clear(tp);
1068 err_free_rx_1:
1069         pci_free_consistent(tp->pci_dev, RX_RING_BYTES, tp->RxDescRing,
1070                 tp->rx_dma);
1071 err_free_tx_0:
1072         pci_free_consistent(tp->pci_dev, TX_RING_BYTES, tp->TxDescRing,
1073                 tp->tx_dma);
1074         goto out;
1075 }
1076 
1077 static void sis190_tx_clear(struct sis190_private *tp)
1078 {
1079         unsigned int i;
1080 
1081         for (i = 0; i < NUM_TX_DESC; i++) {
1082                 struct sk_buff *skb = tp->Tx_skbuff[i];
1083 
1084                 if (!skb)
1085                         continue;
1086 
1087                 sis190_unmap_tx_skb(tp->pci_dev, skb, tp->TxDescRing + i);
1088                 tp->Tx_skbuff[i] = NULL;
1089                 dev_kfree_skb(skb);
1090 
1091                 tp->stats.tx_dropped++;
1092         }
1093         tp->cur_tx = tp->dirty_tx = 0;
1094 }
1095 
1096 static void sis190_down(struct net_device *dev)
1097 {
1098         struct sis190_private *tp = netdev_priv(dev);
1099         void __iomem *ioaddr = tp->mmio_addr;
1100         unsigned int poll_locked = 0;
1101 
1102         sis190_delete_timer(dev);
1103 
1104         netif_stop_queue(dev);
1105 
1106         flush_scheduled_work();
1107 
1108         do {
1109                 spin_lock_irq(&tp->lock);
1110 
1111                 sis190_asic_down(ioaddr);
1112 
1113                 spin_unlock_irq(&tp->lock);
1114 
1115                 synchronize_irq(dev->irq);
1116 
1117                 if (!poll_locked) {
1118                         netif_poll_disable(dev);
1119                         poll_locked++;
1120                 }
1121 
1122                 synchronize_sched();
1123 
1124         } while (SIS_R32(IntrMask));
1125 
1126         sis190_tx_clear(tp);
1127         sis190_rx_clear(tp);
1128 }
1129 
1130 static int sis190_close(struct net_device *dev)
1131 {
1132         struct sis190_private *tp = netdev_priv(dev);
1133         struct pci_dev *pdev = tp->pci_dev;
1134 
1135         sis190_down(dev);
1136 
1137         free_irq(dev->irq, dev);
1138 
1139         netif_poll_enable(dev);
1140 
1141         pci_free_consistent(pdev, TX_RING_BYTES, tp->TxDescRing, tp->tx_dma);
1142         pci_free_consistent(pdev, RX_RING_BYTES, tp->RxDescRing, tp->rx_dma);
1143 
1144         tp->TxDescRing = NULL;
1145         tp->RxDescRing = NULL;
1146 
1147         return 0;
1148 }
1149 
1150 static int sis190_start_xmit(struct sk_buff *skb, struct net_device *dev)
1151 {
1152         struct sis190_private *tp = netdev_priv(dev);
1153         void __iomem *ioaddr = tp->mmio_addr;
1154         u32 len, entry, dirty_tx;
1155         struct TxDesc *desc;
1156         dma_addr_t mapping;
1157 
1158         if (unlikely(skb->len < ETH_ZLEN)) {
1159                 skb = skb_padto(skb, ETH_ZLEN);
1160                 if (!skb) {
1161                         tp->stats.tx_dropped++;
1162                         goto out;
1163                 }
1164                 len = ETH_ZLEN;
1165         } else {
1166                 len = skb->len;
1167         }
1168 
1169         entry = tp->cur_tx % NUM_TX_DESC;
1170         desc = tp->TxDescRing + entry;
1171 
1172         if (unlikely(le32_to_cpu(desc->status) & OWNbit)) {
1173                 netif_stop_queue(dev);
1174                 net_tx_err(tp, KERN_ERR PFX
1175                            "%s: BUG! Tx Ring full when queue awake!\n",
1176                            dev->name);
1177                 return NETDEV_TX_BUSY;
1178         }
1179 
1180         mapping = pci_map_single(tp->pci_dev, skb->data, len, PCI_DMA_TODEVICE);
1181 
1182         tp->Tx_skbuff[entry] = skb;
1183 
1184         desc->PSize = cpu_to_le32(len);
1185         desc->addr = cpu_to_le32(mapping);
1186 
1187         desc->size = cpu_to_le32(len);
1188         if (entry == (NUM_TX_DESC - 1))
1189                 desc->size |= cpu_to_le32(RingEnd);
1190 
1191         wmb();
1192 
1193         desc->status = cpu_to_le32(OWNbit | INTbit | DEFbit | CRCbit | PADbit);
1194 
1195         tp->cur_tx++;
1196 
1197         smp_wmb();
1198 
1199         SIS_W32(TxControl, 0x1a00 | CmdReset | CmdTxEnb);
1200 
1201         dev->trans_start = jiffies;
1202 
1203         dirty_tx = tp->dirty_tx;
1204         if ((tp->cur_tx - NUM_TX_DESC) == dirty_tx) {
1205                 netif_stop_queue(dev);
1206                 smp_rmb();
1207                 if (dirty_tx != tp->dirty_tx)
1208                         netif_wake_queue(dev);
1209         }
1210 out:
1211         return NETDEV_TX_OK;
1212 }
1213 
1214 static struct net_device_stats *sis190_get_stats(struct net_device *dev)
1215 {
1216         struct sis190_private *tp = netdev_priv(dev);
1217 
1218         return &tp->stats;
1219 }
1220 
1221 static void sis190_free_phy(struct list_head *first_phy)
1222 {
1223         struct sis190_phy *cur, *next;
1224 
1225         list_for_each_entry_safe(cur, next, first_phy, list) {
1226                 kfree(cur);
1227         }
1228 }
1229 
1230 /**
1231  *      sis190_default_phy - Select default PHY for sis190 mac.
1232  *      @dev: the net device to probe for
1233  *
1234  *      Select first detected PHY with link as default.
1235  *      If no one is link on, select PHY whose types is HOME as default.
1236  *      If HOME doesn't exist, select LAN.
1237  */
1238 static u16 sis190_default_phy(struct net_device *dev)
1239 {
1240         struct sis190_phy *phy, *phy_home, *phy_default, *phy_lan;
1241         struct sis190_private *tp = netdev_priv(dev);
1242         struct mii_if_info *mii_if = &tp->mii_if;
1243         void __iomem *ioaddr = tp->mmio_addr;
1244         u16 status;
1245 
1246         phy_home = phy_default = phy_lan = NULL;
1247 
1248         list_for_each_entry(phy, &tp->first_phy, list) {
1249                 status = mdio_read_latched(ioaddr, phy->phy_id, MII_BMSR);
1250 
1251                 // Link ON & Not select default PHY & not ghost PHY.
1252                 if ((status & BMSR_LSTATUS) &&
1253                     !phy_default &&
1254                     (phy->type != UNKNOWN)) {
1255                         phy_default = phy;
1256                 } else {
1257                         status = mdio_read(ioaddr, phy->phy_id, MII_BMCR);
1258                         mdio_write(ioaddr, phy->phy_id, MII_BMCR,
1259                                    status | BMCR_ANENABLE | BMCR_ISOLATE);
1260                         if (phy->type == HOME)
1261                                 phy_home = phy;
1262                         else if (phy->type == LAN)
1263                                 phy_lan = phy;
1264                 }
1265         }
1266 
1267         if (!phy_default) {
1268                 if (phy_home)
1269                         phy_default = phy_home;
1270                 else if (phy_lan)
1271                         phy_default = phy_lan;
1272                 else
1273                         phy_default = list_entry(&tp->first_phy,
1274                                                  struct sis190_phy, list);
1275         }
1276 
1277         if (mii_if->phy_id != phy_default->phy_id) {
1278                 mii_if->phy_id = phy_default->phy_id;
1279                 net_probe(tp, KERN_INFO
1280                        "%s: Using transceiver at address %d as default.\n",
1281                        pci_name(tp->pci_dev), mii_if->phy_id);
1282         }
1283 
1284         status = mdio_read(ioaddr, mii_if->phy_id, MII_BMCR);
1285         status &= (~BMCR_ISOLATE);
1286 
1287         mdio_write(ioaddr, mii_if->phy_id, MII_BMCR, status);
1288         status = mdio_read_latched(ioaddr, mii_if->phy_id, MII_BMSR);
1289 
1290         return status;
1291 }
1292 
1293 static void sis190_init_phy(struct net_device *dev, struct sis190_private *tp,
1294                             struct sis190_phy *phy, unsigned int phy_id,
1295                             u16 mii_status)
1296 {
1297         void __iomem *ioaddr = tp->mmio_addr;
1298         struct mii_chip_info *p;
1299 
1300         INIT_LIST_HEAD(&phy->list);
1301         phy->status = mii_status;
1302         phy->phy_id = phy_id;
1303 
1304         phy->id[0] = mdio_read(ioaddr, phy_id, MII_PHYSID1);
1305         phy->id[1] = mdio_read(ioaddr, phy_id, MII_PHYSID2);
1306 
1307         for (p = mii_chip_table; p->type; p++) {
1308                 if ((p->id[0] == phy->id[0]) &&
1309                     (p->id[1] == (phy->id[1] & 0xfff0))) {
1310                         break;
1311                 }
1312         }
1313 
1314         if (p->id[1]) {
1315                 phy->type = (p->type == MIX) ?
1316                         ((mii_status & (BMSR_100FULL | BMSR_100HALF)) ?
1317                                 LAN : HOME) : p->type;
1318                 tp->features |= p->feature;
1319         } else
1320                 phy->type = UNKNOWN;
1321 
1322         net_probe(tp, KERN_INFO "%s: %s transceiver at address %d.\n",
1323                   pci_name(tp->pci_dev),
1324                   (phy->type == UNKNOWN) ? "Unknown PHY" : p->name, phy_id);
1325 }
1326 
1327 static void sis190_mii_probe_88e1111_fixup(struct sis190_private *tp)
1328 {
1329         if (tp->features & F_PHY_88E1111) {
1330                 void __iomem *ioaddr = tp->mmio_addr;
1331                 int phy_id = tp->mii_if.phy_id;
1332                 u16 reg[2][2] = {
1333                         { 0x808b, 0x0ce1 },
1334                         { 0x808f, 0x0c60 }
1335                 }, *p;
1336 
1337                 p = (tp->features & F_HAS_RGMII) ? reg[0] : reg[1];
1338 
1339                 mdio_write(ioaddr, phy_id, 0x1b, p[0]);
1340                 udelay(200);
1341                 mdio_write(ioaddr, phy_id, 0x14, p[1]);
1342                 udelay(200);
1343         }
1344 }
1345 
1346 /**
1347  *      sis190_mii_probe - Probe MII PHY for sis190
1348  *      @dev: the net device to probe for
1349  *
1350  *      Search for total of 32 possible mii phy addresses.
1351  *      Identify and set current phy if found one,
1352  *      return error if it failed to found.
1353  */
1354 static int __devinit sis190_mii_probe(struct net_device *dev)
1355 {
1356         struct sis190_private *tp = netdev_priv(dev);
1357         struct mii_if_info *mii_if = &tp->mii_if;
1358         void __iomem *ioaddr = tp->mmio_addr;
1359         int phy_id;
1360         int rc = 0;
1361 
1362         INIT_LIST_HEAD(&tp->first_phy);
1363 
1364         for (phy_id = 0; phy_id < PHY_MAX_ADDR; phy_id++) {
1365                 struct sis190_phy *phy;
1366                 u16 status;
1367 
1368                 status = mdio_read_latched(ioaddr, phy_id, MII_BMSR);
1369 
1370                 // Try next mii if the current one is not accessible.
1371                 if (status == 0xffff || status == 0x0000)
1372                         continue;
1373 
1374                 phy = kmalloc(sizeof(*phy), GFP_KERNEL);
1375                 if (!phy) {
1376                         sis190_free_phy(&tp->first_phy);
1377                         rc = -ENOMEM;
1378                         goto out;
1379                 }
1380 
1381                 sis190_init_phy(dev, tp, phy, phy_id, status);
1382 
1383                 list_add(&tp->first_phy, &phy->list);
1384         }
1385 
1386         if (list_empty(&tp->first_phy)) {
1387                 net_probe(tp, KERN_INFO "%s: No MII transceivers found!\n",
1388                           pci_name(tp->pci_dev));
1389                 rc = -EIO;
1390                 goto out;
1391         }
1392 
1393         /* Select default PHY for mac */
1394         sis190_default_phy(dev);
1395 
1396         sis190_mii_probe_88e1111_fixup(tp);
1397 
1398         mii_if->dev = dev;
1399         mii_if->mdio_read = __mdio_read;
1400         mii_if->mdio_write = __mdio_write;
1401         mii_if->phy_id_mask = PHY_ID_ANY;
1402         mii_if->reg_num_mask = MII_REG_ANY;
1403 out:
1404         return rc;
1405 }
1406 
1407 static void __devexit sis190_mii_remove(struct net_device *dev)
1408 {
1409         struct sis190_private *tp = netdev_priv(dev);
1410 
1411         sis190_free_phy(&tp->first_phy);
1412 }
1413 
1414 static void sis190_release_board(struct pci_dev *pdev)
1415 {
1416         struct net_device *dev = pci_get_drvdata(pdev);
1417         struct sis190_private *tp = netdev_priv(dev);
1418 
1419         iounmap(tp->mmio_addr);
1420         pci_release_regions(pdev);
1421         pci_disable_device(pdev);
1422         free_netdev(dev);
1423 }
1424 
1425 static struct net_device * __devinit sis190_init_board(struct pci_dev *pdev)
1426 {
1427         struct sis190_private *tp;
1428         struct net_device *dev;
1429         void __iomem *ioaddr;
1430         int rc;
1431 
1432         dev = alloc_etherdev(sizeof(*tp));
1433         if (!dev) {
1434                 net_drv(&debug, KERN_ERR PFX "unable to alloc new ethernet\n");
1435                 rc = -ENOMEM;
1436                 goto err_out_0;
1437         }
1438 
1439         SET_MODULE_OWNER(dev);
1440         SET_NETDEV_DEV(dev, &pdev->dev);
1441 
1442         tp = netdev_priv(dev);
1443         tp->msg_enable = netif_msg_init(debug.msg_enable, SIS190_MSG_DEFAULT);
1444 
1445         rc = pci_enable_device(pdev);
1446         if (rc < 0) {
1447                 net_probe(tp, KERN_ERR "%s: enable failure\n", pci_name(pdev));
1448                 goto err_free_dev_1;
1449         }
1450 
1451         rc = -ENODEV;
1452 
1453         if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) {
1454                 net_probe(tp, KERN_ERR "%s: region #0 is no MMIO resource.\n",
1455                           pci_name(pdev));
1456                 goto err_pci_disable_2;
1457         }
1458         if (pci_resource_len(pdev, 0) < SIS190_REGS_SIZE) {
1459                 net_probe(tp, KERN_ERR "%s: invalid PCI region size(s).\n",
1460                           pci_name(pdev));
1461                 goto err_pci_disable_2;
1462         }
1463 
1464         rc = pci_request_regions(pdev, DRV_NAME);
1465         if (rc < 0) {
1466                 net_probe(tp, KERN_ERR PFX "%s: could not request regions.\n",
1467                           pci_name(pdev));
1468                 goto err_pci_disable_2;
1469         }
1470 
1471         rc = pci_set_dma_mask(pdev, DMA_32BIT_MASK);
1472         if (rc < 0) {
1473                 net_probe(tp, KERN_ERR "%s: DMA configuration failed.\n",
1474                           pci_name(pdev));
1475                 goto err_free_res_3;
1476         }
1477 
1478         pci_set_master(pdev);
1479 
1480         ioaddr = ioremap(pci_resource_start(pdev, 0), SIS190_REGS_SIZE);
1481         if (!ioaddr) {
1482                 net_probe(tp, KERN_ERR "%s: cannot remap MMIO, aborting\n",
1483                           pci_name(pdev));
1484                 rc = -EIO;
1485                 goto err_free_res_3;
1486         }
1487 
1488         tp->pci_dev = pdev;
1489         tp->mmio_addr = ioaddr;
1490 
1491         sis190_irq_mask_and_ack(ioaddr);
1492 
1493         sis190_soft_reset(ioaddr);
1494 out:
1495         return dev;
1496 
1497 err_free_res_3:
1498         pci_release_regions(pdev);
1499 err_pci_disable_2:
1500         pci_disable_device(pdev);
1501 err_free_dev_1:
1502         free_netdev(dev);
1503 err_out_0:
1504         dev = ERR_PTR(rc);
1505         goto out;
1506 }
1507 
1508 static void sis190_tx_timeout(struct net_device *dev)
1509 {
1510         struct sis190_private *tp = netdev_priv(dev);
1511         void __iomem *ioaddr = tp->mmio_addr;
1512         u8 tmp8;
1513 
1514         /* Disable Tx, if not already */
1515         tmp8 = SIS_R8(TxControl);
1516         if (tmp8 & CmdTxEnb)
1517                 SIS_W8(TxControl, tmp8 & ~CmdTxEnb);
1518 
1519 
1520         net_tx_err(tp, KERN_INFO "%s: Transmit timeout, status %08x %08x.\n",
1521                    dev->name, SIS_R32(TxControl), SIS_R32(TxSts));
1522 
1523         /* Disable interrupts by clearing the interrupt mask. */
1524         SIS_W32(IntrMask, 0x0000);
1525 
1526         /* Stop a shared interrupt from scavenging while we are. */
1527         spin_lock_irq(&tp->lock);
1528         sis190_tx_clear(tp);
1529         spin_unlock_irq(&tp->lock);
1530 
1531         /* ...and finally, reset everything. */
1532         sis190_hw_start(dev);
1533 
1534         netif_wake_queue(dev);
1535 }
1536 
1537 static void sis190_set_rgmii(struct sis190_private *tp, u8 reg)
1538 {
1539         tp->features |= (reg & 0x80) ? F_HAS_RGMII : 0;
1540 }
1541 
1542 static int __devinit sis190_get_mac_addr_from_eeprom(struct pci_dev *pdev,
1543                                                      struct net_device *dev)
1544 {
1545         struct sis190_private *tp = netdev_priv(dev);
1546         void __iomem *ioaddr = tp->mmio_addr;
1547         u16 sig;
1548         int i;
1549 
1550         net_probe(tp, KERN_INFO "%s: Read MAC address from EEPROM\n",
1551                   pci_name(pdev));
1552 
1553         /* Check to see if there is a sane EEPROM */
1554         sig = (u16) sis190_read_eeprom(ioaddr, EEPROMSignature);
1555 
1556         if ((sig == 0xffff) || (sig == 0x0000)) {
1557                 net_probe(tp, KERN_INFO "%s: Error EEPROM read %x.\n",
1558                           pci_name(pdev), sig);
1559                 return -EIO;
1560         }
1561 
1562         /* Get MAC address from EEPROM */
1563         for (i = 0; i < MAC_ADDR_LEN / 2; i++) {
1564                 __le16 w = sis190_read_eeprom(ioaddr, EEPROMMACAddr + i);
1565 
1566                 ((u16 *)dev->dev_addr)[0] = le16_to_cpu(w);
1567         }
1568 
1569         sis190_set_rgmii(tp, sis190_read_eeprom(ioaddr, EEPROMInfo));
1570 
1571         return 0;
1572 }
1573 
1574 /**
1575  *      sis190_get_mac_addr_from_apc - Get MAC address for SiS965 model
1576  *      @pdev: PCI device
1577  *      @dev:  network device to get address for
1578  *
1579  *      SiS965 model, use APC CMOS RAM to store MAC address.
1580  *      APC CMOS RAM is accessed through ISA bridge.
1581  *      MAC address is read into @net_dev->dev_addr.
1582  */
1583 static int __devinit sis190_get_mac_addr_from_apc(struct pci_dev *pdev,
1584                                                   struct net_device *dev)
1585 {
1586         struct sis190_private *tp = netdev_priv(dev);
1587         struct pci_dev *isa_bridge;
1588         u8 reg, tmp8;
1589         int i;
1590 
1591         net_probe(tp, KERN_INFO "%s: Read MAC address from APC.\n",
1592                   pci_name(pdev));
1593 
1594         isa_bridge = pci_get_device(PCI_VENDOR_ID_SI, 0x0965, NULL);
1595         if (!isa_bridge) {
1596                 net_probe(tp, KERN_INFO "%s: Can not find ISA bridge.\n",
1597                           pci_name(pdev));
1598                 return -EIO;
1599         }
1600 
1601         /* Enable port 78h & 79h to access APC Registers. */
1602         pci_read_config_byte(isa_bridge, 0x48, &tmp8);
1603         reg = (tmp8 & ~0x02);
1604         pci_write_config_byte(isa_bridge, 0x48, reg);
1605         udelay(50);
1606         pci_read_config_byte(isa_bridge, 0x48, &reg);
1607 
1608         for (i = 0; i < MAC_ADDR_LEN; i++) {
1609                 outb(0x9 + i, 0x78);
1610                 dev->dev_addr[i] = inb(0x79);
1611         }
1612 
1613         outb(0x12, 0x78);
1614         reg = inb(0x79);
1615 
1616         sis190_set_rgmii(tp, reg);
1617 
1618         /* Restore the value to ISA Bridge */
1619         pci_write_config_byte(isa_bridge, 0x48, tmp8);
1620         pci_dev_put(isa_bridge);
1621 
1622         return 0;
1623 }
1624 
1625 /**
1626  *      sis190_init_rxfilter - Initialize the Rx filter
1627  *      @dev: network device to initialize
1628  *
1629  *      Set receive filter address to our MAC address
1630  *      and enable packet filtering.
1631  */
1632 static inline void sis190_init_rxfilter(struct net_device *dev)
1633 {
1634         struct sis190_private *tp = netdev_priv(dev);
1635         void __iomem *ioaddr = tp->mmio_addr;
1636         u16 ctl;
1637         int i;
1638 
1639         ctl = SIS_R16(RxMacControl);
1640         /*
1641          * Disable packet filtering before setting filter.
1642          * Note: SiS's driver writes 32 bits but RxMacControl is 16 bits
1643          * only and followed by RxMacAddr (6 bytes). Strange. -- FR
1644          */
1645         SIS_W16(RxMacControl, ctl & ~0x0f00);
1646 
1647         for (i = 0; i < MAC_ADDR_LEN; i++)
1648                 SIS_W8(RxMacAddr + i, dev->dev_addr[i]);
1649 
1650         SIS_W16(RxMacControl, ctl);
1651         SIS_PCI_COMMIT();
1652 }
1653 
1654 static int sis190_get_mac_addr(struct pci_dev *pdev, struct net_device *dev)
1655 {
1656         u8 from;
1657 
1658         pci_read_config_byte(pdev, 0x73, &from);
1659 
1660         return (from & 0x00000001) ?
1661                 sis190_get_mac_addr_from_apc(pdev, dev) :
1662                 sis190_get_mac_addr_from_eeprom(pdev, dev);
1663 }
1664 
1665 static void sis190_set_speed_auto(struct net_device *dev)
1666 {
1667         struct sis190_private *tp = netdev_priv(dev);
1668         void __iomem *ioaddr = tp->mmio_addr;
1669         int phy_id = tp->mii_if.phy_id;
1670         int val;
1671 
1672         net_link(tp, KERN_INFO "%s: Enabling Auto-negotiation.\n", dev->name);
1673 
1674         val = mdio_read(ioaddr, phy_id, MII_ADVERTISE);
1675 
1676         // Enable 10/100 Full/Half Mode, leave MII_ADVERTISE bit4:0
1677         // unchanged.
1678         mdio_write(ioaddr, phy_id, MII_ADVERTISE, (val & ADVERTISE_SLCT) |
1679                    ADVERTISE_100FULL | ADVERTISE_10FULL |
1680                    ADVERTISE_100HALF | ADVERTISE_10HALF);
1681 
1682         // Enable 1000 Full Mode.
1683         mdio_write(ioaddr, phy_id, MII_CTRL1000, ADVERTISE_1000FULL);
1684 
1685         // Enable auto-negotiation and restart auto-negotiation.
1686         mdio_write(ioaddr, phy_id, MII_BMCR,
1687                    BMCR_ANENABLE | BMCR_ANRESTART | BMCR_RESET);
1688 }
1689 
1690 static int sis190_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
1691 {
1692         struct sis190_private *tp = netdev_priv(dev);
1693 
1694         return mii_ethtool_gset(&tp->mii_if, cmd);
1695 }
1696 
1697 static int sis190_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
1698 {
1699         struct sis190_private *tp = netdev_priv(dev);
1700 
1701         return mii_ethtool_sset(&tp->mii_if, cmd);
1702 }
1703 
1704 static void sis190_get_drvinfo(struct net_device *dev,
1705                                struct ethtool_drvinfo *info)
1706 {
1707         struct sis190_private *tp = netdev_priv(dev);
1708 
1709         strcpy(info->driver, DRV_NAME);
1710         strcpy(info->version, DRV_VERSION);
1711         strcpy(info->bus_info, pci_name(tp->pci_dev));
1712 }
1713 
1714 static int sis190_get_regs_len(struct net_device *dev)
1715 {
1716         return SIS190_REGS_SIZE;
1717 }
1718 
1719 static void sis190_get_regs(struct net_device *dev, struct ethtool_regs *regs,
1720                             void *p)
1721 {
1722         struct sis190_private *tp = netdev_priv(dev);
1723         unsigned long flags;
1724 
1725         if (regs->len > SIS190_REGS_SIZE)
1726                 regs->len = SIS190_REGS_SIZE;
1727 
1728         spin_lock_irqsave(&tp->lock, flags);
1729         memcpy_fromio(p, tp->mmio_addr, regs->len);
1730         spin_unlock_irqrestore(&tp->lock, flags);
1731 }
1732 
1733 static int sis190_nway_reset(struct net_device *dev)
1734 {
1735         struct sis190_private *tp = netdev_priv(dev);
1736 
1737         return mii_nway_restart(&tp->mii_if);
1738 }
1739 
1740 static u32 sis190_get_msglevel(struct net_device *dev)
1741 {
1742         struct sis190_private *tp = netdev_priv(dev);
1743 
1744         return tp->msg_enable;
1745 }
1746 
1747 static void sis190_set_msglevel(struct net_device *dev, u32 value)
1748 {
1749         struct sis190_private *tp = netdev_priv(dev);
1750 
1751         tp->msg_enable = value;
1752 }
1753 
1754 static struct ethtool_ops sis190_ethtool_ops = {
1755         .get_settings   = sis190_get_settings,
1756         .set_settings   = sis190_set_settings,
1757         .get_drvinfo    = sis190_get_drvinfo,
1758         .get_regs_len   = sis190_get_regs_len,
1759         .get_regs       = sis190_get_regs,
1760         .get_link       = ethtool_op_get_link,
1761         .get_msglevel   = sis190_get_msglevel,
1762         .set_msglevel   = sis190_set_msglevel,
1763         .nway_reset     = sis190_nway_reset,
1764 };
1765 
1766 static int sis190_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
1767 {
1768         struct sis190_private *tp = netdev_priv(dev);
1769 
1770         return !netif_running(dev) ? -EINVAL :
1771                 generic_mii_ioctl(&tp->mii_if, if_mii(ifr), cmd, NULL);
1772 }
1773 
1774 static int __devinit sis190_init_one(struct pci_dev *pdev,
1775                                      const struct pci_device_id *ent)
1776 {
1777         static int printed_version = 0;
1778         struct sis190_private *tp;
1779         struct net_device *dev;
1780         void __iomem *ioaddr;
1781         int rc;
1782 
1783         if (!printed_version) {
1784                 net_drv(&debug, KERN_INFO SIS190_DRIVER_NAME " loaded.\n");
1785                 printed_version = 1;
1786         }
1787 
1788         dev = sis190_init_board(pdev);
1789         if (IS_ERR(dev)) {
1790                 rc = PTR_ERR(dev);
1791                 goto out;
1792         }
1793 
1794         pci_set_drvdata(pdev, dev);
1795 
1796         tp = netdev_priv(dev);
1797         ioaddr = tp->mmio_addr;
1798 
1799         rc = sis190_get_mac_addr(pdev, dev);
1800         if (rc < 0)
1801                 goto err_release_board;
1802 
1803         sis190_init_rxfilter(dev);
1804 
1805         INIT_WORK(&tp->phy_task, sis190_phy_task, dev);
1806 
1807         dev->open = sis190_open;
1808         dev->stop = sis190_close;
1809         dev->do_ioctl = sis190_ioctl;
1810         dev->get_stats = sis190_get_stats;
1811         dev->tx_timeout = sis190_tx_timeout;
1812         dev->watchdog_timeo = SIS190_TX_TIMEOUT;
1813         dev->hard_start_xmit = sis190_start_xmit;
1814 #ifdef CONFIG_NET_POLL_CONTROLLER
1815         dev->poll_controller = sis190_netpoll;
1816 #endif
1817         dev->set_multicast_list = sis190_set_rx_mode;
1818         SET_ETHTOOL_OPS(dev, &sis190_ethtool_ops);
1819         dev->irq = pdev->irq;
1820         dev->base_addr = (unsigned long) 0xdead;
1821 
1822         spin_lock_init(&tp->lock);
1823 
1824         rc = sis190_mii_probe(dev);
1825         if (rc < 0)
1826                 goto err_release_board;
1827 
1828         rc = register_netdev(dev);
1829         if (rc < 0)
1830                 goto err_remove_mii;
1831 
1832         net_probe(tp, KERN_INFO "%s: %s at %p (IRQ: %d), "
1833                "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x\n",
1834                pci_name(pdev), sis_chip_info[ent->driver_data].name,
1835                ioaddr, dev->irq,
1836                dev->dev_addr[0], dev->dev_addr[1],
1837                dev->dev_addr[2], dev->dev_addr[3],
1838                dev->dev_addr[4], dev->dev_addr[5]);
1839 
1840         net_probe(tp, KERN_INFO "%s: %s mode.\n", dev->name,
1841                   (tp->features & F_HAS_RGMII) ? "RGMII" : "GMII");
1842 
1843         netif_carrier_off(dev);
1844 
1845         sis190_set_speed_auto(dev);
1846 out:
1847         return rc;
1848 
1849 err_remove_mii:
1850         sis190_mii_remove(dev);
1851 err_release_board:
1852         sis190_release_board(pdev);
1853         goto out;
1854 }
1855 
1856 static void __devexit sis190_remove_one(struct pci_dev *pdev)
1857 {
1858         struct net_device *dev = pci_get_drvdata(pdev);
1859 
1860         sis190_mii_remove(dev);
1861         unregister_netdev(dev);
1862         sis190_release_board(pdev);
1863         pci_set_drvdata(pdev, NULL);
1864 }
1865 
1866 static struct pci_driver sis190_pci_driver = {
1867         .name           = DRV_NAME,
1868         .id_table       = sis190_pci_tbl,
1869         .probe          = sis190_init_one,
1870         .remove         = __devexit_p(sis190_remove_one),
1871 };
1872 
1873 static int __init sis190_init_module(void)
1874 {
1875         return pci_module_init(&sis190_pci_driver);
1876 }
1877 
1878 static void __exit sis190_cleanup_module(void)
1879 {
1880         pci_unregister_driver(&sis190_pci_driver);
1881 }
1882 
1883 module_init(sis190_init_module);
1884 module_exit(sis190_cleanup_module);
