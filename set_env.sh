#! /bin/bash

export LIB_PATH=${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=./build/lib:${LD_LIBRARY_PATH}
echo ${LD_LIBRARY_PATH}

