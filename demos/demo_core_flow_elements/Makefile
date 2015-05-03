# Makefile

SRC_DEMO=$(wildcard *.cpp)
OBJ_DEMO=$(SRC_DEMO:.cpp=.o)
OBJ_PATH=$(addprefix ../../build/obj/demos/$(DEMO_NAME)/, $(OBJ_DEMO))

CC=g++ -std=c++11
CC_FLAGS=-Wall
INCLUDE=-I../../build/include
LIBDIR=-L../../build/lib
LIBS=-lwif_core -lwif_algo -lwif_viz

demo : $(OBJ_DEMO)
	echo "Building $(DEMO_NAME)"
	$(CC) $(CC_FLAGS) -o ../../build/bin/wif_$(DEMO_NAME) $(OBJ_PATH) $(INCLUDE) $(LIBDIR) $(LIBS)

%.o : %.cpp
	$(CC) -c $(CC_FLAGS) $(INCLUDE) -o ../../build/obj/demos/$(DEMO_NAME)/$@ $<# Makefile

SRC_DEMO=$(wildcard *.cpp)
OBJ_DEMO=$(SRC_DEMO:.cpp=.o)
OBJ_PATH=$(addprefix ../../build/obj/demos/$(DEMO_NAME)/, $(OBJ_DEMO))

CC=g++ -std=c++11
CC_FLAGS=-Wall
INCLUDE=-I../../build/include -pthread -m64 -I/home/uauser/Software/root-v5.34.25/builddir/include
LIBDIR=-L../../build/lib -L/home/uauser/Software/root-v5.34.25/builddir/lib
LIBS=-lwif_core -lwif_algo -lwif_viz -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic

demo : $(OBJ_DEMO)
	echo "Building $(DEMO_NAME)"
	$(CC) $(CC_FLAGS) -o ../../build/bin/wif_$(DEMO_NAME) $(OBJ_PATH) $(INCLUDE) $(LIBDIR) $(LIBS)

%.o : %.cpp
	$(CC) -c $(CC_FLAGS) $(INCLUDE) -o ../../build/obj/demos/$(DEMO_NAME)/$@ $<
