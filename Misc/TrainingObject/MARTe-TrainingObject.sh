#!/bin/sh

if [ -z "$1" ]; then
	echo "Please specify the location of the configuration file"
	exit
else
	echo "Going to start MARTe with the configuration specified in: " $1
fi

CODE_DIRECTORY=../..
LD_LIBRARY_PATH=.:$CODE_DIRECTORY/BaseLib2/linux
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/MARTe/MARTeSupportLib/linux
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./linux

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH
echo $LD_LIBRARY_PATH

$CODE_DIRECTORY/MARTe/linux/MARTe.ex $1

#cgdb --args $CODE_DIRECTORY/MARTe/linux/MARTe.ex $1

