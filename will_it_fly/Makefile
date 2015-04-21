# Makefile will-it-fly

SRC_WIF=$(wildcard *.cpp)
OBJ_WIF=$(SRC_WIF:.cpp=.o)

CC=g++ -std=c++11
CC_FLAGS=-Wall

INCLUDE=-I../build/include
LIBDIR=-L../build/lib
LIBS=-lwif_core -lwif_algo -lwif_viz

willitfly : $(OBJ_WIF)
	echo "Building will-it-fly"

%.o : %.cpp
	$(CC) -c $(CC_FLAGS) -o ../build/obj/wif/$@ $< $(INCLUDE) $(LIBDIR) $(LIBS)
