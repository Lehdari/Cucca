#!/bin/bash

BASEDIR=$(dirname $0)

BUILD_PREFIX=${BASEDIR}/build
LIB_DYNAMIC_POSTFIX=dll
LIB_STATIC_POSTFIX=dll.a

SRC_INCLUDE=${BASEDIR}/include

DEST_LIB_DYNAMIC=/c/Windows/SysWOW64

DEST_PREFIX=/c/minGW/i686-5.1.0-posix-dwarf-rt_v4-rev0/mingw32/i686-w64-mingw32
DEST_INCLUDE=${DEST_PREFIX}/include/Cucca
DEST_LIB_STATIC=${DEST_PREFIX}/lib


#install libraries
cp -u ${BUILD_PREFIX}/bin/*.${LIB_DYNAMIC_POSTFIX} ${DEST_LIB_DYNAMIC}/
cp -u ${BUILD_PREFIX}/lib/*.${LIB_STATIC_POSTFIX} ${DEST_LIB_STATIC}/

#install headers
if [ ! -d "${DEST_INCLUDE}" ]; then
	mkdir ${DEST_INCLUDE}
fi
cp -ru ${SRC_INCLUDE}/* ${DEST_INCLUDE}/