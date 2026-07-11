typedef	unsigned char		u_int8_t;
typedef	unsigned short int	u_int16_t;
typedef	unsigned int		u_int32_t;
typedef	unsigned long long	u_int64_t;
typedef	int	bool;

typedef	dev_t	device_t;

/*
 * Some basic Ethernet constants.
 */
#define	ETHER_ADDR_LEN		6	/* length of an Ethernet address */
#define	ETHER_TYPE_LEN		2	/* length of the Ethernet type field */
#define	ETHER_CRC_LEN		4	/* length of the Ethernet CRC */
#define	ETHER_HDR_LEN		(ETHER_ADDR_LEN*2+ETHER_TYPE_LEN)
#define	ETHER_MIN_LEN		64	/* minimum frame len, including CRC */
#define	ETHER_MAX_LEN		1518	/* maximum frame len, including CRC */
#define	ETHER_MAX_LEN_JUMBO	9018	/* max jumbo frame len, including CRC */

#define	ETHER_VLAN_ENCAP_LEN	4	/* len of 802.1Q VLAN encapsulation */
/*
 * Mbuf adjust factor to force 32-bit alignment of IP header.
 * Drivers should do m_adj(m, ETHER_ALIGN) when setting up a
 * receive so the upper layers get the IP header properly aligned
 * past the 14-byte Ethernet header.
 */
#define	ETHER_ALIGN		2	/* driver adjust for IP hdr alignment */

#undef FS
#define	device_printf(...)	while(0)

#define	true	B_TRUE
#define	false	B_FALSE

#define	__P(x)		x
#define	SYSCTL_HANDLER_ARGS
#define	TUNABLE_INT(x, y)

#define MJUM9BYTES      (9 * 1024)      /* jumbo cluster 9k */
#define MJUM16BYTES     (16 * 1024)     /* jumbo cluster 16k */

typedef	int	bus_size_t;

#if 0
/*
 * 802.1q Virtual LAN header.
 */
struct ether_vlan_header {
	uint8_t evl_dhost[ETHER_ADDR_LEN];
	uint8_t evl_shost[ETHER_ADDR_LEN];
	uint16_t evl_encap_proto;
	uint16_t evl_tag;
	uint16_t evl_proto;
} __packed;
_Static_assert(sizeof(struct ether_vlan_header) == ETHER_HDR_LEN + ETHER_VLAN_ENCAP_LEN,
    "size of struct ether_vlan_header is wrong");

#define	EVL_VLID_MASK		0x0FFF
#define	EVL_PRI_MASK		0xE000
#define	EVL_VLANOFTAG(tag)	((tag) & EVL_VLID_MASK)
#define	EVL_PRIOFTAG(tag)	(((tag) >> 13) & 7)
#define	EVL_CFIOFTAG(tag)	(((tag) >> 12) & 1)
#define	EVL_MAKETAG(vlid, pri, cfi)					\
	((((((pri) & 7) << 1) | ((cfi) & 1)) << 12) | ((vlid) & EVL_VLID_MASK))
#endif

#define	CSR_WRITE_1(s, r, v)	OUTB((s)->dp, (r), (v))
#define	CSR_WRITE_2(s, r, v)	OUTW((s)->dp, (r), (v))
#define	CSR_WRITE_4(s, r, v)	OUTL((s)->dp, (r), (v))

#define	CSR_READ_1(s, r)	INB((s)->dp, (r))
#define	CSR_READ_2(s, r)	INW((s)->dp, (r))
#define	CSR_READ_4(s, r)	INL((s)->dp, (r))

#define	pci_get_vendor(sc)	pci_config_get16((sc)->conf_ha, PCI_CONF_VENID)
#define	pci_get_device(sc)	pci_config_get16((sc)->conf_ha, PCI_CONF_DEVID)
#define	pci_get_subvendor(sc)	pci_config_get16((sc)->conf_ha, PCI_CONF_SUBVENID)
#define	pci_get_subdevice(sc)	pci_config_get16((sc)->conf_ha, PCI_CONF_SUBSYSID)
#define	pci_get_revid(sc)	pci_config_get8((sc)->conf_ha, PCI_CONF_REVID)

#define	RE_PCIE(sc)	((sc)->re_if_flags & RL_FLAG_PCIE)
