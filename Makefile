# Makefile
# Compilatie objecten (*.o) gaan naar ./obj/, binaries gaan naar ./bin/, library headers (*.hpp) gaan naar ./include/ en libraries (*.so) gaan naar ./lib/

SRC_CORE=./wif-core/wif_core.cpp

SRC_ALGO=./wif-algo/wif_algo.cpp

SRC_VIZ=./wif-algo/wif_viz.cpp

CC=g++

all : wif demos
	echo "Building all"

demos :
	echo "Building demos"

wif : wif_core wif_algo wif_viz
	echo "Building will-it-fly"

wif_core : obj_core lib_core
	echo "Building wif-core"

	mkdir -p ./will-it-fly/Build/obj
	mkdir -p ./will-it-fly/Build/bin
	mkdir -p ./will-it-fly/Build/include
	mkdir -p ./will-it-fly/Build/lib

	rsync -az --include '*.hpp' --exclude '*' ./wif-core/ ./will-it-fly/Build/include
	

wif_algo : wif_core
	echo "Building wif-algo"

	rsync -az --include '*.hpp' --exclude '*' ./wif-algo/ ./will-it-fly/Build/include

wif_viz : wif_core
	echo "Building wif-viz"

	rsync -az --include '*.hpp' --exclude '*' ./wif-viz/ ./will-it-fly/Build/include

obj_core : 



clean :
	echo "Cleaning build directory"
	rm -rf ./will-it-fly/Build
