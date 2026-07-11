#! /bin/csh -f
#
# SMSC LAN7500 driver
set DEVLIST = ""
set DEVLIST = ($DEVLIST '"usb424,7500"')	# SMSC lan7500 generic
set DEVLIST = ($DEVLIST '"usb424,7505"')	# SMSC lan7505 generic

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

set existing = `grep "usge " /etc/driver_aliases`
#echo $existing

if ("$existing" == "") then
	/usr/sbin/add_drv -n -v -m '* 0600 root sys' -i "$DEVLIST2" usge
else 
	/usr/sbin/update_drv -a -v -m '* 0600 root sys' -i "$DEVLIST2" usge
endif
sync
