# Makefile wif_algo

SRC_ALGO=wif_algo.cpp
OBJ_ALGO=$(SRC_ALGO:.cpp=.o)

CC=g++ -std=c++11
CC_FLAGS=-Wall
INCLUDE=-I./will-it-fly/build/include

all : wif_algo


wif_algo : $(OBJ_ALGO)
	echo "Building wif-algo"

%.o : %.cpp
	mkdir -p ../will-it-fly/build/obj
	mkdir -p ../will-it-fly/build/bin
	mkdir -p ../will-it-fly/build/include
	mkdir -p ../will-it-fly/build/lib
	rsync -az --include '*.hpp' --exclude '*' ./ ../will-it-fly/build/include/wif-algo
	$(CC) -c $(CC_FLAGS) $(INCLUDE) -o ../will-it-fly/build/obj/$@ $<
	$(CC) -shared -o ../will-it-fly/build/lib/lib$(@:.o=.so) ../will-it-fly/build/obj/$@
