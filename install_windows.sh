#!/bin/bash

BASEDIR=$(dirname $0)

BUILD_PREFIX=${BASEDIR}/build
LIB_DYNAMIC_POSTFIX=dll
LIB_STATIC_POSTFIX=dll.a

SRC_INCLUDE=${BASEDIR}/include

DEST_LIB_DYNAMIC=/c/Windows/System32

DEST_PREFIX=/c/minGW/x86_64-5.3.0-posix-seh-rt_v4-rev0/mingw64
DEST_INCLUDE=${DEST_PREFIX}/include
DEST_LIB_STATIC=${DEST_PREFIX}/lib


#install libraries
cp -u ${BUILD_PREFIX}/bin/*.${LIB_DYNAMIC_POSTFIX} ${DEST_LIB_DYNAMIC}/
cp -u ${BUILD_PREFIX}/lib/*.${LIB_STATIC_POSTFIX} ${DEST_LIB_STATIC}/

#install headers
if [ ! -d "${DEST_INCLUDE}" ]; then
	mkdir ${DEST_INCLUDE}
fi
cp -ru ${SRC_INCLUDE}/*  ${DEST_INCLUDE}/