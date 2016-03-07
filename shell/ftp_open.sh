#!/bin/bash

# obtain host IP adress, inet excluding local host and ipv6
host_ip="`/sbin/ifconfig -a|grep inet|grep -v 127.0.0.1|grep -v inet6|awk '{print $2}'|tr -d 'addr:'`"

`sudo -s launchctl load -w /System/Library/LaunchDaemons/ftp.plist`

ret=$?

if [ ${ret} -ne 0 ]; then
	echo "abnormal![${ret}]"
	exit -1
fi

echo "ftp server established successfully! you can connect it at ${host_ip}"

echo "to close ftp, run ~/shell/ftp_close.sh"

