# Makefile wif_viz

SRC_VIZ=$(wildcard *.cpp)
OBJ_VIZ=$(SRC_VIZ:.cpp=.o)
OBJ_PATH=$(addprefix ../build/obj/wif_viz/, $(OBJ_VIZ))

CC=g++ -std=c++11
CC_FLAGS=-Wall

INCLUDE=-I../build/include/

#Vul VTK_LIBS aan met de vtk libraries die je gebruikt. bv. -lvtkCommon.
VTK_LIBDIR=-L/usr/lib/
VTK_LIBS=
VTK_INCLUDE=-I/usr/include/vtk-5.8/
ROOT_LIBS=$(shell root-config --libs)
ROOT_INCLUDE=$(shell root-config --cflags)

viz: ../build/lib/libwif_viz.so

../build/lib/libwif_viz.so : $(OBJ_PATH)
	echo "Building wif-viz"
	$(CC) -shared -o ../build/lib/libwif_viz.so $(OBJ_PATH)

../build/obj/wif_viz/%.o : %.cpp
	$(CC) -c -fPIC $(CC_FLAGS) -o $@ $< $(INCLUDE) $(VTK_INCLUDE) $(ROOT_INCLUDE) $(VTK_LIBDIR) $(ROOT_LIBS) $(VTK_LIBS)

