#!/bin/bash

# author: qiutao
# date: 2015/2/1
# version: 1.1

# update history
# 2015/4/20 change mount path the desktop

# mac os mount external medias with ntfs format on READ ONLY by default
# this program will eject the ntfs medias and remount them on READ & WRITE

# variables
MAIN_PATH="/Users/qtao/Desktop"
DISK1=ENTERTAINMENT
DISK2="STUDY&WORK"
TRGFILE="remounted.trg"

# test whether the external medias have been mounted
if [ -d /Volumes/${DISK1} ]; then
	disk_id1=`diskutil info /Volumes/${DISK1} | grep Node | awk '{print $3}'`
	echo "/Volumes/${DISK1} has been found...Node-> ${disk_id1}"
else
	echo "we have not found /Volumes/${DISK1}, program will exit for safty..."
	echo "exited"
	exit -1
fi

if [ -d /Volumes/${DISK2} ]; then
	disk_id2=`diskutil info /Volumes/${DISK2} | grep Node | awk '{print $3}'`
	echo "/Volumes/${DISK2} has been found...Node-> ${disk_id2}"
else
	echo "we have not found /Volumes/${DISK2}, program will exit for safty..."
	echo "exited"
	exit -1
fi

echo "now, eject external media firstly..."

# eject external media

step1=`hdiutil eject /Volumes/${DISK1}`
ret=$?

echo $step1

if [ $ret -ne 0 ]; then
	echo "error on ejecting, please check your external media!"
	echo "exited"
	exit -2
fi

# DISK2 need not be rejected because it is same disk with DISK1 in my condition

# build path for external media remount

if [ ! -d ${MAIN_PATH} ]; then
	mkdir ${MAIN_PATH}
fi


if [ ! -d "${MAIN_PATH}/${DISK2}" ]; then
	mkdir "${MAIN_PATH}/${DISK2}"
fi

# remount

step2=`sudo mount_ntfs -o rw,nobrowse ${disk_id2} "${MAIN_PATH}/${DISK2}"`

ret=$?
if [ $ret -ne 0 ]; then
	echo "error on remounting, please check your external media!"
	echo "exited"
	exit -3
fi

echo "${disk_id2} has been remounted! path: ${MAIN_PATH}/${DISK2}"

if [ ! -d "${MAIN_PATH}/${DISK1}" ]; then
	mkdir "${MAIN_PATH}/${DISK1}"
fi

step3=`sudo mount_ntfs -o rw,nobrowse ${disk_id1} "${MAIN_PATH}/${DISK1}"`

ret=$?
if [ $ret -ne 0 ]; then
	echo "error on remounting, please check your external media!"
	echo "exited"
	exit -3
fi

echo "${disk_id1} has been remounted! path: ${MAIN_PATH}/${DISK1}"

if [ ! -f "${MAIN_PATH}/${TRGFILE}" ]; then
	touch "${MAIN_PATH}/${TRGFILE}"
	echo "WARNNING: DON'T TRY TO DELETE THIS FILE!!" >> "${MAIN_PATH}/${TRGFILE}"
fi

echo "done[$?]"

exit 0
