# Makefile

SRC_DEMO=$(wildcard *.cpp)
OBJ_DEMO=$(SRC_DEMO:.cpp=.o)
OBJ_PATH=$(addprefix ../../build/obj/demos/$(DEMO_NAME)/, $(OBJ_DEMO))

CC=g++
CC_FLAGS=-std=c++11 -g -Wall
INCLUDE=-I../../build/include
LIBDIR=-L../../build/lib
LIBS=-lwif_core -lwif_algo -lwif_viz

demo : ../../build/bin/wif_$(DEMO_NAME)

../../build/bin/wif_$(DEMO_NAME): $(OBJ_PATH)
	echo "Building ${DEMO_NAME}"
	$(CC) $(CC_FLAGS) -o ../../build/bin/wif_$(DEMO_NAME) $(OBJ_PATH) $(INCLUDE) $(LIBDIR) $(LIBS)

../../build/obj/demos/$(DEMO_NAME)/%.o : %.cpp
	$(CC) -c $(CC_FLAGS) $(INCLUDE) -o $@ $<
