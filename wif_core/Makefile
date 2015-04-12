# Makefile wif_core

SRC_CORE=wif_core.cpp
OBJ_CORE=$(SRC_CORE:.cpp=.o)
OBJ_PATH=$(addprefix ../build/obj/wif_core/,  $(OBJ_CORE))

CC=g++ -std=c++11
CC_FLAGS=-Wall

core : $(OBJ_CORE)
	echo "Building wif-core"
	$(CC) -shared -o ../build/lib/libwif_core.so $(OBJ_PATH)

%.o : %.cpp
	$(CC) -c -fPIC $(CC_FLAGS) -o ../build/obj/wif_core/$@  $<


	
