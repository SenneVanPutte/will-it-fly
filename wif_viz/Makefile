# Makefile wif_viz

SRC_VIZ=wif_viz.cpp
OBJ_VIZ=$(SRC_VIZ:.cpp=.o)

CC=g++ -std=c++11
CC_FLAGS=-Wall
INCLUDE=-I../wif_core

viz : $(OBJ_VIZ)
	echo "Building wif-viz"

%.o : %.cpp
	$(CC) -c -fpic $(CC_FLAGS) $(INCLUDE) -o ../build/obj/wif_viz/$@ $<
	$(CC) -shared -o ../build/lib/libwif_viz.so ../build/obj/wif_viz/$@
