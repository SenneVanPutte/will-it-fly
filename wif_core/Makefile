# Makefile wif_core

SRC_CORE=$(wildcard *.cpp)
OBJ_CORE=$(SRC_CORE:.cpp=.o)
OBJ_PATH=$(addprefix ../build/obj/wif_core/,  $(OBJ_CORE))

CC=g++ -std=c++11
CC_FLAGS=-Wall

core : ../build/lib/libwif_core.so

../build/lib/libwif_core.so : $(OBJ_PATH)
	echo "Building wif-core"
	$(CC) -shared -o ../build/lib/libwif_core.so $(OBJ_PATH)

../build/obj/wif_core/%.o : %.cpp
	$(CC) -c -fPIC $(CC_FLAGS) -o $@  $<


	
