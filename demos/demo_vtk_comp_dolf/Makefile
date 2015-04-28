# Makefile

SRC_DEMO=$(wildcard *.cpp)
OBJ_DEMO=$(SRC_DEMO:.cpp=.o)
OBJ_PATH=$(addprefix ../../build/obj/demos/$(DEMO_NAME)/, $(OBJ_DEMO))

CC=g++ -std=c++11
CC_FLAGS=-Wall
INCLUDE=-I../../build/include -I/usr/include/vtk-5.8/
LIBDIR=-L../../build/lib
LIBS=-lvtkCommon -lvtkFiltering -lvtkGraphics -lvtkRendering -lvtkIO -lvtkHybrid

demo : $(OBJ_DEMO)
	echo "Building ${DEMO_NAME}"
	$(CC) $(CC_FLAGS) -o ../../build/bin/wif_$(DEMO_NAME) $(OBJ_PATH) $(INCLUDE) $(LIBDIR) $(LIBS)

%.o : %.cpp
	$(CC) -c $(CC_FLAGS) $(INCLUDE) -o ../../build/obj/demos/$(DEMO_NAME)/$@ $<
