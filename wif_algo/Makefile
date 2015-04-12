# Makefile wif_algo

SRC_ALGO=wif_algo.cpp
OBJ_ALGO=$(SRC_ALGO:.cpp=.o)
OBJ_PATH=$(addprefix ../build/obj/wif_algo/,  $(OBJ_ALGO))

CC=g++ -std=c++11
CC_FLAGS=-Wall
INCLUDE=-I../build/include/wif_core

algo : $(OBJ_ALGO)
	echo "Building wif-algo"
	$(CC) -shared -o ../build/lib/libwif_algo.so $(OBJ_PATH)

%.o : %.cpp
	$(CC) -c -fPIC $(CC_FLAGS) $(INCLUDE) -o ../build/obj/wif_algo/$@ $<

