#! /bin/csh -f
#
# IP1000A GbE mac driver
#
# Tested PCI cards
#
set DEVLIST = ""
set DEVLIST = ($DEVLIST '"pci13f0,1023"')	# IC plus ip1000a
#
# Untested PCI cards
#
set DEVLIST = ($DEVLIST '"pci1186,4020"')	# D-Link DL-2000

#echo $DEVLIST

set DEVLIST2 = ( )
foreach i ($DEVLIST)
	set pcidev = `grep $i /etc/driver_aliases`
#	echo $pcidev
	if ("$pcidev" == "") then
		set DEVLIST2 = ( $DEVLIST2 "$i" )
	endif
end

#echo $DEVLIST2

if ("$DEVLIST2" == "") then
	echo nothing to do.
	exit 1
endif

set existing = `grep "^icpt " /etc/driver_aliases`
if ("$existing" == "") then
	/usr/sbin/add_drv -n -v -m '* 0600 root sys' -i "$DEVLIST2" icpt
else
	/usr/sbin/update_drv -a -v -m '* 0600 root sys' -i "$DEVLIST2" icpt
endif
sync
