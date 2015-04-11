# Makefile wif_algo

SRC_ALGO=wif_algo.cpp
OBJ_ALGO=$(SRC_ALGO:.cpp=.o)

CC=g++ -std=c++11
CC_FLAGS=-Wall
INCLUDE=-I../wif_core

algo : $(OBJ_ALGO)
	echo "Building wif-algo"

%.o : %.cpp
	$(CC) -c -fpic $(CC_FLAGS) $(INCLUDE) -o ../build/obj/wif_algo/$@ $<
	$(CC) -shared -o ../build/lib/libwif_algo.so ../build/obj/wif_algo/$@
