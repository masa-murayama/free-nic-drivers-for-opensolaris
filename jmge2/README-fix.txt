***************************************************************************
CAUTION: There is NO WARRANTY for this software.
As this software is loaded into the kernel, it might cause the kernel to
panic or hang.

                                                Masayuki Murayama
                                                KHF04453@nifty.ne.jp
***************************************************************************


1. Introduction

This is the VIA Rhine family NIC driver for Solaris.  It is distributed under
GNU Lesser GPL license.

2. Specification of the driver

File name of the driver: /kernel/drv/rh

Special file name:
	/dev/rhN (where N is an unit number, typcally 0 for first card)
        For example
                % ifconfig rh0

Tested OS version
 Solaris8 00/10 x86, Solaris9 12/02 x86

Tested chips and cards
  VT6102(Rhine II rev 43) -- Planex communications Inc.(Japan) FNW-9702-T3
  VT6102(Rhine II rev 47)
  DL10030(Rhine I rev 6) --  Corega Inc.(Japan) FEtherII PCI TX
  VT6105(Rhine III rev 85) -- Corega Inc.(Japan) FEther PCI-TXA

VT86C100A(Rhine I) is not tested, but is likely to work. This driver is
ready for VT6105M (Rhine-III management adaptor) but not tested.

3. Set up Operating Environment

(1) Install your PCI card and boot Solaris.

(2) Copy source and binary files.
        # gunzip -cd rh-x.x.x.tar.gz | tar xf -

(3) Add hostname for the NIC card into the /etc/hosts file

(4) Making binaries (only for sparc platform)
Rh driver is ready for 64bit and 32bit sparc solaris8 10/00 or
later, but not tested. If you want to test it, you need to make
sparc binaries using Forte C compiler or gcc 3.x.x. Do the following
operations before testing and installation:

(for sparc 64bit kernel with Forte)
        % cd /.../rh-x.x.x
	% rm Makefile
	% ln -s Makefile.sparcv9_suncc Makefile
	% rm obj
	% ln -s sparcv9 obj
	% /usr/ccs/bin/make

(for sparc 32bit kernel with Forte)
        % cd /.../rh-x.x.x
	% rm Makefile
	% ln -s Makefile.sparc_suncc Makefile
	% rm obj
	% ln -s sparc obj
	% /usr/ccs/bin/make

(for sparc 64bit kernel with gcc3)
        % cd /.../rh-x.x.x
	% rm Makefile
	% ln -s Makefile.sparcv9_gcc Makefile
	% rm obj
	% ln -s sparcv9 obj
	% /usr/ccs/bin/make

(for sparc 32bit kernel with gcc)
        % cd /.../rh-x.x.x
	% rm Makefile
	% ln -s Makefile.sparc_gcc Makefile
	% rm obj
	% ln -s sparc obj
	% /usr/ccs/bin/make



4. Testing

        # cd /.../rh-x.x.x
        # /usr/ccs/bin/make install
        # ./adddrv.sh
	# rm /kernel/drv/rh (for Solaris7, do not remove rh )
        # modload obj/rh
        # devfsadm -i rh ( for solaris7, use drvconfig and reboot with -r option )
        # ifconfig rhN plumb ( where N is unit number, typcally 0 for first card)
        # ifconfig -a        ( you will see an entry for rh0, ensure ethernet address is correct)
        # ifconfig rhN HOSTNAME
        # ifconfig rhN      ( ensure IP address is correct)
        # ifconfig rhN up   ( and then you can test with ping, telnet, ftp ...)

5. Installation
    After you ensure that the rh driver is fully functional, install it.

(1) install the rh driver into kernel directory
        # cd /.../rh-x.x.x
        # /usr/ccs/bin/make install

       If you did not test rh driver yet, execute following commands:
            # ./adddrv.sh
            # devfsadm -i rh ( for Solaris7 use drvconfig and reboot with -r option )

(2) Configure the network interface. Create and/or modify the following files:
        /etc/hostname.rhN

(3) Reboot the system.
        # init 6


6. Troubleshooting

Q. Following message is printed in the /var/adm/messages file
    NOTE: rhN: link up but auto-negotiation failed.

A. This massage appears for Rhine I chips when the link partner does not
   have auto negotiation capability.
   Please disable auto negotiation capability for your NIC card by specifying
   the correct media mode in /kernel/drv/rh.conf with following syntax:

   rhN-duplex=["full"|"half"] rhN-speed=[100|10]; # where N is a unit number

  For example
	rh0-duplex="full" rh0-speed=100;   # full-duplex 100Mbps for rh0
	rh0-duplex="half" rh0-speed=10;    # half-duplex 10Mbps for rh0

Q. The driver cannot be unloaded because the device is busy, and the following
   message appears in /var/adm/messages file:
    NOTICE: rhN: rh_detach: buffer is busy

A. Wait for a little while until some modules in the kernel release receive
   buffers which were allocated by the rh driver.

Q. The system does not boot after the driver is installed.
A. Uninstall the NIC card and reboot solaris. Then, unregister the driver:
     # rem_drv rh

   Or boot solaris with -a option and use /etc/system.norh instead of
   default [etc/system]. This inhibits loading the driver.

   /etc/system.norh is automatically generated when executing 'make install'
   or 'make test'

Q. Solaris boots, but the network interface does not work.
A. Is the network interface running?

   Execute 'ifconfig -a'.  If you see an entry for rhN, the driver is loaded
   and working correctly.
   Please check the confguration of the network interface.


   Is an ethernet cable connected properly?

   Please check if the network interface is receiving packets.
	% snoop -P -d rhN

If Solaris panics while testing, please send me the following information:
  (1) /var/adm/messages

  (2) Output of prtconf -pv

  (3) Output of prtconf -vD

  (4) Output of adb
  Solaris core dump consists of unix.N and vmcore.N which are created in
   /var/crash/YOUR-HOST-NAME/ .

  Execute 'adb -k unix.N vmcore.N' and type the following subcommands:
   $c   (stack trace back will be printed)
   $<msgbuf   (last messages are printed)
   ^D         (To quit adb, type control-D)
