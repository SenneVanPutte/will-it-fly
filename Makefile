# Makefile
# Compilatie objecten (*.o) gaan naar ./obj/, binaries gaan naar ./bin/, library headers (*.hpp) gaan naar ./include/ en libraries (*.so) gaan naar ./lib/

SRC_PATH=$(wildcard ./will_it_fly/*.cpp)
SRC_WIF=$(notdir $(SRC_PATH))
OBJ_WIF=$(SRC_WIF:.cpp=.o)
OBJ_PATH=$(addprefix ./build/obj/wif/, $(OBJ_WIF))

CC=g++ -std=c++11
CC_FLAGS=-Wall
INCLUDE=-I./build/include
LIBDIR=-L./build/lib
LIBS=-lwif_core -lwif_algo -lwif_viz
EXECUTABLE=./build/bin/wif

all : exec demos
	echo "Building all"

demos :
	echo "Building demos"

exec: wif
	echo "Building binary"
	echo $(SRC_PATH)
	$(CC) $(CC_FLAGS) $(LIBDIR) -o $(EXECUTABLE) $(OBJ_PATH) $(INCLUDE) $(LIBDIR) $(LIBS)

wif : wifcore wifalgo wifviz
	mkdir -p ./build/obj/wif
	cd ./will_it_fly; make willitfly

wifcore : 
	mkdir -p ./build/obj/wif_core
	mkdir -p ./build/include/wif_core
	mkdir -p ./build/bin
	mkdir -p ./build/lib
	rsync -az --include '*.hpp' --exclude '*' ./wif_core/ ./build/include/wif_core
	cd ./wif_core; make core

wifalgo : wif_core
	mkdir -p ./build/obj/wif_algo
	mkdir -p ./build/include/wif_algo
	rsync -az --include '*.hpp' --exclude '*' ./wif_algo/ ./build/include/wif_algo
	cd ./wif_algo; make algo

wifviz : wif_core
	mkdir -p ./build/obj/wif_viz
	mkdir -p ./build/include/wif_viz
	rsync -az --include '*.hpp' --exclude '*' ./wif_viz/ ./build/include/wif_viz
	cd ./wif_viz; make viz

clean :
	echo "Cleaning build directory"
	rm -rf ./build
