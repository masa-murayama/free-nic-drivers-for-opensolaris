	/*
	 * configure GLD 
	 */
	macinfo->gldm_devinfo	   = dp->dip;
	macinfo->gldm_private	   = (caddr_t)dp;
	macinfo->gldm_cookie       = dp->iblock_cookie;
	macinfo->gldm_reset        = &gem_gld_reset;
	macinfo->gldm_start        = &gem_gld_start;
	macinfo->gldm_stop         = &gem_gld_stop;
	macinfo->gldm_set_mac_addr = &gem_gld_set_mac_address;
	macinfo->gldm_send         = &gem_gld_send;
#ifdef GEM_CONFIG_VLAN
	if ((dp->misc_flag & GEM_VLAN) != 0) {
		macinfo->gldm_send_tagged = &gem_gld_send_tagged;
	}
#endif
	macinfo->gldm_set_promiscuous = &gem_gld_set_promiscuous;
	macinfo->gldm_get_stats    = &gem_gld_get_stats;
	macinfo->gldm_ioctl        = NULL; 
	macinfo->gldm_set_multicast= &gem_gld_set_multicast;
	macinfo->gldm_intr         = &gem_gld_intr;
	macinfo->gldm_mctl         = NULL;
#ifdef GEM_COMPAT
	macinfo->gldm_ident   = (char *)ddi_driver_name(dip);
#else
	macinfo->gldm_ident   = ident;
#endif
	macinfo->gldm_type    = DL_ETHER;
	macinfo->gldm_minpkt  = 0;
	macinfo->gldm_maxpkt  = dp->mtu;
	macinfo->gldm_addrlen = ETHERADDRL;
	macinfo->gldm_saplen  = -2;
	macinfo->gldm_ppa     = unit;

#ifdef SOLARIS10
	macinfo->gldm_capabilities = GLD_CAP_LINKSTATE;
#  ifdef GEM_CONFIG_CKSUM_OFFLOAD
	if ((dp->misc_flag & (GEM_CKSUM_IPv4 | GEM_CKSUM_TCP | GEM_CKSUM_UDP))
			 == (GEM_CKSUM_IPv4 | GEM_CKSUM_TCP | GEM_CKSUM_UDP)) {
		macinfo->gldm_capabilities |= 
			(GLD_CAP_CKSUM_IPHDR | GLD_CAP_CKSUM_FULL_V4);
	}
#  endif
#endif
