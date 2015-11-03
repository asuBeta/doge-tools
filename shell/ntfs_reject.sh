#!/bin/bash

# author: qiutao
# date: 2015/2/1
# version: 1.0

# history
# 2015/4/20 change mount folder to desktop

# reject medias mounted by /Users/qtao/ntfs_remount.sh

# variables
MAIN_PATH="/Users/qtao/Desktop"
DISK1=ENT
DISK2=STU
TRGFILE="remounted.trg"

# test whether the external medias have been mounted

if [ ! -f "${MAIN_PATH}/${TRGFILE}" ]; then
	echo "external medias seem have not been mounted by /Users/qtao/ntfs_remount.sh"
	echo "program will not run"
	exit -1
fi

if [ -d "${MAIN_PATH}/${DISK2}" ]; then
	echo "${MAIN_PATH}/${DISK2} has been found..."
else
	echo "we have not found ${MAIN_PATH}/${DISK2}, program will exit for safty..."
	echo "exited"
	exit -1
fi

if [ -d "${MAIN_PATH}/${DISK1}" ]; then
	echo "${MAIN_PATH}/${DISK1} has been found..."
else
	echo "we have not found ${MAIN_PATH}/${DISK1}, program will exit for safty..."
	echo "exited"
	exit -1
fi

echo "now, eject external media..."

# eject external media

step1=`sudo hdiutil eject "${MAIN_PATH}/${DISK2}" `
echo $step1

ret=$?
if [ $ret -ne 0 ]; then
	echo "error on ejecting, please check your external media!"
	echo "exited"
	exit -2
fi

# remove mount folder
step2=`sudo rm -d "${MAIN_PATH}/${DISK1}" `
step3=`sudo rm -d "${MAIN_PATH}/${DISK2}" `
step4=`sudo rm -f "${MAIN_PATH}/${TRGFILE}" `

echo "done[$?]"

exit 0
