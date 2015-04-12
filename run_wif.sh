#!/bin/bash
# runt de executable ./build/bin/wif

LIB_PATH=${LD_LIBRARY_PATH}

export LD_LIBRARY_PATH=./build/lib:${LD_LIBRARY_PATH}
./build/bin/wif
unset LD_LIBRARY_PATH
export LD_LIBRARY_PATH=${LIB_PATH}
