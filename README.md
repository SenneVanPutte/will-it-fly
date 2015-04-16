# will-it-fly

Zie git-hulp/README.md voor informatie over Git en GitHub.


We gebruiken makefiles voor de compilatie, maar een CodeBlocks project die gebruik maakt van deze makefile zit ook in dit project, omdat een IDE nu eenmaal handig is.

Individuele opdrachten zitten teams/.


De .gitignore is geschreven om object files (*.o) en shared objects (*.so) globaal te negeren. Ook de mappen bin/, obj/, include/ en lib/ zijn genegeerd.

Voorbeeld bestanden van de afgesproken code-style zitten in style/.


Om een executable uit te voeren moet eerst het script set_env.sh worden uitgevoerd. Dit past de environmental variable LD_LIBRARY_PATH aan, zodat de executable de libraries 

terugvindt. Nadat alles is uitgevoerd kan je het script unset_env.sh uitvoeren om LD_LIBRARY_PATH terug naar zijn origineel te brengen

Praktisch gezien komt dit neer op bijvoorbeeld:
	
	source set_env.sh
	./build/bin/wif
	./build/bin/wif_demo_test
	source unset_env.sh

vergeet vooral het source commando niet, anders werkt het nog steeds niet.
