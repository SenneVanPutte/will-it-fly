# Makefile
# Compilatie objecten (*.o) gaan naar ./obj/, binaries gaan naar ./bin/, library headers (*.hpp) gaan naar ./include/ en libraries (*.so) gaan naar ./lib/

all : wif demos
	echo "Building all"

demos : 
	echo "Building demos"

wif : wif_core wif_algo wif_viz
	echo "Building will-it-fly"

wif_core : 
	echo "Building wif-core"

wif_algo : wif_core
	echo "Building wif-algo"

wif_viz : wif_core
	echo "Building wif-viz"