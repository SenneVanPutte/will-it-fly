# Makefile wif_viz

SRC_VIZ=wif_viz.cpp
OBJ_VIZ=$(SRC_VIZ:.cpp=.o)
OBJ_PATH=$(addprefix ../build/obj/wif_viz/, $(OBJ_VIZ))

CC=g++ -std=c++11
CC_FLAGS=-Wall
INCLUDE=-I../build/include/wif_core

viz : $(OBJ_VIZ)
	echo "Building wif-viz"
	$(CC) -shared -o ../build/lib/libwif_viz.so $(OBJ_PATH)

%.o : %.cpp
	$(CC) -c -fpic $(CC_FLAGS) $(INCLUDE) -o ../build/obj/wif_viz/$@ $<

