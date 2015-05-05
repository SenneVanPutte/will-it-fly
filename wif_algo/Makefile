# Makefile wif_algo

SRC_ALGO=$(wildcard *.cpp)
OBJ_ALGO=$(SRC_ALGO:.cpp=.o)
OBJ_PATH=$(addprefix ../build/obj/wif_algo/,  $(OBJ_ALGO))

CC=g++ -std=c++11
CC_FLAGS=-Wall

INCLUDE=-I../build/include/

#Vul GSL_LIBS aan met de GSL libraries die je gebruikt. bv. -lgsl.
GSL_LIBDIR=-L/usr/lib
GSL_LIBS=-lgsl -lgslcblas -lm
GSL_INCLUDE=-I/usr/include/gsl
ROOT_LIBS=$(`shell root-config --libs`)
ROOT_INCLUDE=$(`shell root-config --cflags`)

algo: ../build/lib/libwif_algo.so 

../build/lib/libwif_algo.so : $(OBJ_PATH)
	echo "Building wif-algo"
	$(CC) -shared -o ../build/lib/libwif_algo.so $(OBJ_PATH)

../build/obj/wif_algo/%.o : %.cpp
	$(CC) -c -fPIC $(CC_FLAGS) -o $@ $< $(INCLUDE) $(GSL_INCLUDE) $(GSL_LIBDIR) $(GSL_LIBS) $(ROOT_INCLUDE) $(ROOT_LIBDIR) $(ROOT_LIBS)

