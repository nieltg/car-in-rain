#!/bin/sh

lib_path="$(pwd)/build/vendor"

export LD_LIBRARY_PATH="${lib_path}:$LD_LIBRARY_PATH"
export PATH="${lib_path}:$PATH"

build/app-prefix/src/app-build/src/main
