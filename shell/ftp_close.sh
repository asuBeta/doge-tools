#!/bin/bash

`sudo -s launchctl unload -w /System/Library/LaunchDaemons/ftp.plist`

ret=$?

if [ ${ret} -ne 0 ]; then
	echo "abnormal!"
	exit -1
fi

echo "ftp server closed!"

echo "to reopen ftp, run ~/shell/ftp_open.sh"
