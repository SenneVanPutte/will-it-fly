# Makefile will-it-fly

SRC_WIF=$(wildcard *.cpp)
OBJ_WIF=$(SRC_WIF:.cpp=.o)
OBJ_PATH=$(addprefix ../build/obj/wif/,  $(OBJ_WIF))

CC=g++ 
CC_FLAGS=-g -std=c++11 -Wall

INCLUDE=-I../build/include -I/usr/include/gsl
LIBDIR=-L../build/lib -L/usr/lib/ -L/usr/lib/gsl
LIBS=-lwif_core -lwif_algo -lwif_viz -lgsl -lgslcblas -lm

willitfly : $(OBJ_PATH)
	echo "Building will-it-fly"
	$(CC) -o ../build/bin/wif $(OBJ_PATH) $(LIBDIR) $(LIBS)

../build/obj/wif/%.o : %.cpp
	$(CC) -c $(CC_FLAGS) -o $@ $< $(INCLUDE)
