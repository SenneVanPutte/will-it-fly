# Makefile will-it-fly

CC=g++ -std=c++11
CC_FLAGS=-Wall
INCLUDE=-I./will-it-fly/build/include/wif-core I./will-it-fly/build/include/wif-algo I./will-it-fly/build/include/wif-viz
LIBDIR=-L./will-it-fly/build/lib
LIBS=-lwif_core -lwif_algo -lwif_viz
EXECUTABLE=not-yet

wif:
	echo "Building will-it-fly"
	$(CC) $(CC_FLAGS) $(INCLUDE) $(LIBDIR) $(LIBS) -o $(EXECUTABLE)  main.cpp
