# Makefile wif_core

SRC_CORE=wif_core.cpp
OBJ_CORE=$(SRC_CORE:.cpp=.o)

CC=g++ -std=c++11
CC_FLAGS=-Wall

core : $(OBJ_CORE)
	echo "Building wif-core"

%.o : %.cpp
	$(CC) -c -fpic $(CC_FLAGS) -o ../build/obj/wif_core/$@  $<
	$(CC) -shared -o ../build/lib/libwif_core.so ../build/obj/wif_core/$@

	
