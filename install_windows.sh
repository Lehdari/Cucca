#!/bin/bash

BASEDIR=$(dirname $0)

BUILD_PREFIX=${BASEDIR}/build

DEST_PREFIX=/c/minGW/i686-5.1.0-posix-dwarf-rt_v4-rev0/mingw32/i686-w64-mingw32

DEST_LIB_DYNAMIC=/c/Windows/SysWOW64
LIB_DYNAMIC_POSTFIX=dll

SRC_INCLUDE=${BASEDIR}/include
DEST_INCLUDE=${DEST_PREFIX}/include/Cucca


#install libraries
cp ${BUILD_PREFIX}/bin/*.${LIB_DYNAMIC_POSTFIX} ${DEST_LIB_DYNAMIC}/

#install headers
mkdir ${DEST_INCLUDE}
cp -r ${SRC_INCLUDE}/* ${DEST_INCLUDE}/