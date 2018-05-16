#!/bin/sh

mkdir -p build
cd build

cmake .. "$@"

[ -z "${MAKE}" ] && MAKE="make"
"${MAKE}"
