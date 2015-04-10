# Makefile wif_viz

SRC_VIZ=wif_viz.cpp
OBJ_VIZ=$(SRC_VIZ:.cpp=.o)

CC=g++ -std=c++11
CC_FLAGS=-Wall
INCLUDE=-I./will-it-fly/build/include

all : wif_viz


wif_viz : $(OBJ_VIZ)
	echo "Building wif-viz"

%.o : %.cpp
	mkdir -p ../will-it-fly/build/obj
	mkdir -p ../will-it-fly/build/bin
	mkdir -p ../will-it-fly/build/include
	mkdir -p ../will-it-fly/build/lib
	rsync -az --include '*.hpp' --exclude '*' ./ ../will-it-fly/build/include/wif-viz
	$(CC) -c $(CC_FLAGS) $(INCLUDE) -o ../will-it-fly/build/obj/$@ $<
	$(CC) -shared -o ../will-it-fly/build/lib/lib$(@:.o=.so) ../will-it-fly/build/obj/$@
