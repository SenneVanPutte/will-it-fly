# Makefile
# Compilatie objecten (*.o) gaan naar ./obj/, binaries gaan naar ./bin/, library headers (*.hpp) gaan naar ./include/ en libraries (*.so) gaan naar ./lib/

SRC_WIF=main.cpp
OBJ_WIF=$(SRC_WIF:.cpp=.o)

CC=g++ -std=c++11
CC_FLAGS=-Wall
INCLUDE=-I./build/include
LIBDIR=-L./build/lib
LIBS=-lwif_core -lwif_algo -lwif_viz
EXECUTABLE=./build/bin/wif

all : wif demos
	echo "Building all"

demos :
	echo "Building demos"

wif : wifcore wifalgo wifviz
	cd ./will_it_fly; make willitfly
	$(CC) $(CC_FLAGS) $(INCLUDE) $(LIBDIR) -o $(EXECUTABLE) ./build/obj/wif/$(OBJ_WIF) $(LIBS)

wifcore : 
	mkdir -p ./build/obj/wif_core
	mkdir -p ./build/obj/wif_algo
	mkdir -p ./build/obj/wif_viz
	mkdir -p ./build/obj/wif
	mkdir -p ./build/include/wif_core
	mkdir -p ./build/include/wif_algo
	mkdir -p ./build/include/wif_viz
	mkdir -p ./build/bin
	mkdir -p ./build/lib
	rsync -az --include '*.hpp' --exclude '*' ./wif_core/ ./build/include/wif_core
	rsync -az --include '*.hpp' --exclude '*' ./wif_algo/ ./build/include/wif_algo
	rsync -az --include '*.hpp' --exclude '*' ./wif_viz/ ./build/include/wif_viz
	cd ./wif_core; make core

wifalgo : wif_core 
	cd ./wif_algo; make algo

wifviz : wif_core 
	cd ./wif_viz; make viz

clean :
	echo "Cleaning build directory"
	rm -rf ./build
