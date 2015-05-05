# Makefile
# Compilatie objecten (*.o) gaan naar ./obj/, binaries gaan naar ./bin/, library headers (*.hpp) gaan naar ./include/ en libraries (*.so) gaan naar ./lib/



SRC_PATH=$(wildcard ./will_it_fly/*.cpp)
SRC_WIF=$(notdir $(SRC_PATH))
OBJ_WIF=$(SRC_WIF:.cpp=.o)
OBJ_PATH=$(addprefix ./build/obj/wif/, $(OBJ_WIF))

PATH:=/home/uauser/Software/root-v5.34.25/builddir/bin:$(PATH)

INCLUDE_CORE={add_sheet_c.hpp}
INCLUDE_ALGO=
INCLUDE_VIZ=

CC=g++ -std=c++11
CC_FLAGS=-Wall

INCLUDE=-I./build/include
LIBDIR=-L./build/lib
LIBS=-lwif_core -lwif_algo -lwif_viz
EXECUTABLE=./build/bin/wif

all : demos exec
	echo "Building all"

doxygen :
	mkdir -p ./build	
	mkdir -p ./build/doc
	doxygen
	ln -sLf ./html/index.html ./build/doc/index.html

demos : wifcore wifalgo wifviz
	cd ./demos; $(MAKE) demo

exec: wif
	echo "Building binary"
	echo $(SRC_PATH)
	$(CC) $(CC_FLAGS) -o $(EXECUTABLE) $(OBJ_PATH) $(INCLUDE) $(LIBDIR) $(LIBS)

wif : wifcore wifalgo wifviz
	mkdir -p ./build/obj/wif
	$(MAKE) -C ./will_it_fly willitfly

wifcore :
	mkdir -p ./build/obj
	mkdir -p ./build/obj/wif_core
	mkdir -p ./build/include
	mkdir -p ./build/include/wif_core
	mkdir -p ./build/bin
	mkdir -p ./build/lib
	cat ./wif_core/install_headers.txt | xargs -I % cp -u ./wif_core/% ./build/include/wif_core
	$(MAKE) -C ./wif_core core

wifalgo : wif_core
	mkdir -p ./build/obj/wif_algo
	mkdir -p ./build/include/wif_algo
	cat ./wif_algo/install_headers.txt | xargs -I % cp -u ./wif_algo/% ./build/include/wif_algo
	$(MAKE) -C ./wif_algo algo

wifviz : wif_core
	mkdir -p ./build/obj/wif_viz
	mkdir -p ./build/include/wif_viz
	cat ./wif_viz/install_headers.txt | xargs -I % cp -u ./wif_viz/% ./build/include/wif_viz
	$(MAKE) -C ./wif_viz viz

clean :
	echo "Cleaning build directory"
	rm -rf ./build
