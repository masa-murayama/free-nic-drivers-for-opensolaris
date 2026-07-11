/*********************************************************************
 *
 *  This routine maps the mbufs to tx descriptors.
 *
 *  return 0 on success, positive on failure
 **********************************************************************/

static int
em_tx_desc_write(struct adapter *adapter, struct mbuf *m_head)
{ 
        u_int32_t		txd_upper;
        u_int32_t		txd_lower;
        int			txd_used;
	int			i;
	int			curslot;
	uint64_t		addr;
        struct em_tx_desc	*tdp;

	txd_upper = txd_lower = 0;
	if (ifp->if_hwassist > 0) {
		em_transmit_checksum_setup(adapter,  m_head,
			   &txd_upper, &txd_lower);
	}

	for (txd_used = i = 0; i < frags; i++) {
		curslot = SLOT(slot + txd_used, TX_RING_SIZE);
		tdp = &((struct em_tx_desc *)dp->tx_ring)[curslot];

		addr = dcp->dmac_address;
		len  = dcp->dmac_size;

		/*
		 * If adapter is 82544 and on PCIX bus, check the address
		 * and Length combination andsplit the data accordingly.
		 */
        	if (lp->pcix_82544 &&
		    (fixed_len = em_tx_82544_wa(addr, len)) > 0) {

			/* the workaround is required */
			tdp->buffer_addr = addr;
           	   	tdp->lower.data = lp->txd_cmd
					| txd_lower 
					| ((u_int16_t) fixed_len);

			tdp->upper.data = txd_upper;	

			/* advance current slot */
                	txd_used++;
			curslot = SLOT(slot + txd_used, TX_RING_SIZE);
			addr += fixed_len;
			len  -= fixed_len;
        	}

		tdp->buffer_addr = addr;
		tdp->lower.data = lp->txd_cmd
				| txd_lower
				| len;

		tdp->upper.data = txd_upper;
		txd_used++;
	}

#if __FreeBSD_version < 500000
        if (mtag != NULL) {
                /* Set the vlan id */
                tdp->upper.fields.special = VLAN_TAG_VALUE(mtag);
                /* Tell hardware to add tag */
                tdp->lower.data |= E1000_TXD_CMD_VLE;
        }
#endif

	/* 
	 * Last Descriptor of Packet needs End Of Packet (EOP)
	 */
	tdp->lower.data |= E1000_TXD_CMD_EOP;

	/* 
	 * Advance the Transmit Descriptor Tail (Tdt), this tells the E1000
	 * that this frame is available to transmit.
	 */
	if (adapter->hw.mac_type == em_82547 && !dp->full_duplex) {
		em_82547_move_tail(adapter);
	}
	else {
		E1000_WRITE_REG(&adapter->hw, TDT,
				SLOT(slot + txd_used, TX_RING_SIZE));
		if (lp->hw.mac_type == em_82547) {
			em_82547_update_fifo_head(lp, m_head->m_pkthdr.len);
		}
	}

	return (txd_used);
}


/*********************************************************************
 *
 * 82547 workaround to avoid controller hang in half-duplex environment.
 * The workaround is to avoid queuing a large packet that would span   
 * the internal Tx FIFO ring boundary. We need to reset the FIFO pointers
 * in this case. We do that only when FIFO is queiced.
 *
 **********************************************************************/
static void
em_82547_move_tail(void *arg)
{
	int s;
	struct adapter *adapter = arg;
	uint16_t hw_tdt;
	uint16_t sw_tdt;
	struct em_tx_desc *tx_desc;
	uint16_t length = 0;
	boolean_t eop = 0;

	s = splimp();
	hw_tdt = E1000_READ_REG(&adapter->hw, TDT);
	sw_tdt = adapter->next_avail_tx_desc;
	
	while (hw_tdt != sw_tdt) {
		tx_desc = &adapter->tx_desc_base[hw_tdt];
		length += tx_desc->lower.flags.length;
		eop = tx_desc->lower.data & E1000_TXD_CMD_EOP;
		if(++hw_tdt == adapter->num_tx_desc)
			hw_tdt = 0;

		if(eop) {
			if (em_82547_fifo_workaround(adapter, length)) {
				/*
				 * we cannot apply the workaround now
				 * wait for a while.
				 */
				adapter->tx_fifo_wrk_cnt++;
				adapter->tx_fifo_timer_handle = 
					timeout(em_82547_move_tail,
						adapter, 1);
				splx(s);
				return;
			}
			else {
				E1000_WRITE_REG(&adapter->hw, TDT, hw_tdt);
				em_82547_update_fifo_head(adapter, length);
				length = 0;
			}
		}
	}	
	splx(s);
	return;
}

static int
em_82547_fifo_workaround(struct gem_dev *dp, int len)
{	
	int		fifo_space;
	int		fifo_pkt_len;
	struct em_dev	*lp = (struct em_dev *)dp->private;

	if (!dp->full_duplex) {
		/* the workaround is not required */
		return (0);
	}

	fifo_pkt_len = EM_ROUNDUP(len + EM_FIFO_HDR, EM_FIFO_HDR);
	fifo_space = adapter->tx_fifo_size - adapter->tx_fifo_head;

	if (fifo_pkt_len >= (EM_82547_PKT_THRESH + fifo_space)) {
		if (em_82547_tx_fifo_reset(adapter) == 0) {
			return(1);
		}
	}

	return(0);
}

static void
em_82547_update_fifo_head(struct gem_dev *dp, int len)
{
	int		fifo_pkt_len;
	struct em_dev	*lp = (struct em_dev *)dp->private;
	
	fifo_pkt_len = EM_ROUNDUP(len + EM_FIFO_HDR, EM_FIFO_HDR);

	/* tx_fifo_head is always 16 byte aligned */
	adapter->tx_fifo_head += fifo_pkt_len;
	if (adapter->tx_fifo_head >= adapter->tx_fifo_size) {
		adapter->tx_fifo_head -= adapter->tx_fifo_size;
	}

	return;
}


static int
em_82547_tx_fifo_reset(struct gem_dev *dp)
{	
	struct em_dev	*lp = (struct em_dev *)dp->private;
	uint32_t	tctl;

	if ( (E1000_READ_REG(&adapter->hw, TDT) ==
	      E1000_READ_REG(&adapter->hw, TDH)) &&
	     (E1000_READ_REG(&adapter->hw, TDFT) == 
	      E1000_READ_REG(&adapter->hw, TDFH)) &&
	     (E1000_READ_REG(&adapter->hw, TDFTS) ==
	      E1000_READ_REG(&adapter->hw, TDFHS)) &&
	     (E1000_READ_REG(&adapter->hw, TDFPC) == 0)) {

		/* Disable TX unit */
		tctl = E1000_READ_REG(&adapter->hw, TCTL);
		E1000_WRITE_REG(&adapter->hw, TCTL, tctl & ~E1000_TCTL_EN);

		/* Reset FIFO pointers */
		E1000_WRITE_REG(&adapter->hw, TDFT,  adapter->tx_head_addr);
		E1000_WRITE_REG(&adapter->hw, TDFH,  adapter->tx_head_addr);
		E1000_WRITE_REG(&adapter->hw, TDFTS, adapter->tx_head_addr);
		E1000_WRITE_REG(&adapter->hw, TDFHS, adapter->tx_head_addr);

		/* Re-enable TX unit */
		E1000_WRITE_REG(&adapter->hw, TCTL, tctl);
		E1000_WRITE_FLUSH(&adapter->hw);

		adapter->tx_fifo_head = 0;
		adapter->tx_fifo_reset_cnt++;

		return(TRUE);
	}
	else {
		return(FALSE);
	}
}
