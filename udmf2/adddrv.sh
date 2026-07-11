#! /bin/csh -f
#
# davicom dm9601 driver
set DEVLIST = ( )

#
# Tested USB devices
#
set DEVLIST = ( $DEVLIST '"usb7aa,9601"' )	# Corega CG-FEUSBTXCG
set DEVLIST = ( $DEVLIST '"usbfe6,8101"' )	# Onechip SR9600
set DEVLIST = ( $DEVLIST '"usbfe6,9700"' )	# Onechip SR9700

#
# Untested USB devices
#
set DEVLIST = ( $DEVLIST '"usba46,6688"' )	# ZT6688 USB NIC
set DEVLIST = ( $DEVLIST '"usba46,268"' )	# ShanTou ST268 USB NIC
set DEVLIST = ( $DEVLIST '"usba46,9601"' )	# Davicom USB-100

#echo $DEVLIST

set DEVLIST2 = ( )
foreach i ($DEVLIST)
	set pcidev = `grep $i /etc/driver_aliases`
	echo $pcidev
	if ("$pcidev" == "") then
		set DEVLIST2 = ( $DEVLIST2 "$i" )
	endif
end

#echo $DEVLIST2
if ("$DEVLIST2" == "") then
	echo nothing to do.
	exit 1
endif

set existing = `grep "udmf " /etc/driver_aliases`
#echo $existing

if ("$existing" == "") then
	/usr/sbin/add_drv -n -v -m '* 0600 root sys' -i "$DEVLIST2" udmf
else 
	/usr/sbin/update_drv -a -v -m '* 0600 root sys' -i "$DEVLIST2" udmf
endif
sync
