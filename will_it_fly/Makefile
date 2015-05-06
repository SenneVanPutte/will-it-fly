# Makefile will-it-fly

SRC_WIF=$(wildcard *.cpp)
OBJ_WIF=$(SRC_WIF:.cpp=.o)
OBJ_PATH=$(addprefix ../build/obj/wif/,  $(OBJ_WIF))

CC=g++ -std=c++11
CC_FLAGS=-Wall

INCLUDE=-I../build/include
LIBDIR=-L../build/lib
LIBS=-lwif_core -lwif_algo -lwif_viz

willitfly : $(OBJ_PATH)
	echo "Building will-it-fly"

../build/obj/wif/%.o : %.cpp
	$(CC) -c $(CC_FLAGS) -o $@ $< $(INCLUDE) $(LIBDIR) $(LIBS)
