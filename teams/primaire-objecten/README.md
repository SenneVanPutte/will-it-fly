# Team primaire objecten

Teamleden: Jeroen Roefs, Jelle Segers, Thorvald Dox

Jullie zijn verantwoordelijk voor het onderhoud en de ontwikkeling van de shared library wif-core, waarin primaire objecten en hulpklassen worden gedefinieerd.

## Opdracht 1

Eerste opdracht voor jullie: het op orde stellen van het compilatiesysteem dat gebruikt zal worden. Dit moet direct gebeuren in de top level van deze repository, en dus niet in deze directory. Een skeletstructuur van de Makefile is al beschikbaar, evenals een CodeBlocks project die hiermee kan werken.

Voor alle libraries verwacht ik een source en header file waarin enkel de namespace staat, met natuurlijk de include guards in de header files. Voor wif-core verwacht ik dus een wif-core.cpp, wif-core.hpp met namespace wif_core. Natuurlijk moet de header file geinclude worden door de source file. Implementeer eenvoudige functies in de libraries, zoals uint32_t get_version() die altijd 1 returnen. Deze moeten compileren naar shared libraries (dus bijvoorbeeld wif-core.so).

Voor alle duidelijkheid, ik verwacht dus de volgende drie functies:

```
uint32_t wif_core::get_version()
uint32_t wif_algo::get_version()
uint32_t wif_viz::get_version()
```

Zorg ook dat wif-algo en wif-viz beiden afhankelijk zijn van wif-core, en daarmee gelinkt zijn. Om dit te checken moet wif_core::get_version() opgeroepen worden vanuit wif_algo::get_version() en wif_viz::get_version(). Het resultaat van die calls moet niet gereturnt worden, het moet enkel kunnen compileren zonder waarschuwingen.

Voor wif verwacht ik een main.cpp file die alle get_versions oproept van de shared libraries. Deze moet gelinkt worden met de bovenstaande drie libraries, en moet ook de respectievelijke header files includen. Compilatie moet lukken, en ik verwacht de outputs van de drie get_versions naar std::cout.

Respecteer de conventies in style/ en zorg dat alle output van de makefiles op de juiste plaats komt (dus header files van de libraries in include/, libraries zelf in lib/ en de binary van wif in bin/). Schrijf ook een clean target in de makefile die de outputs van de makefile opruimt.

## Opdracht 2

Twee zeer belangrijke classen moeten gedefinieerd worden: vector_2d_c en line_2d_c, die respectievelijk een cartesische vector en een lijnstuk in twee dimensies voorstellen.

Twee public members voor vector_2d_c : x en y, beiden moeten doubles zijn.
Twee public members voor line_2d_c : begin en end, beiden moeten vector_2d_c's zijn.

Voor vector_2d_c moeten de basis operatoren geimplementeerd worden:

```
vector_2d_c (+ en -) vector_2d_c
vector_2d_c (* en /) double
double * vector_2d_c
```

Ook de volgende functie moet geimplementeerd worden:

```
double get_length() const
```

Zinnige andere functies mogen ook gedefinieerd worden, zeker als ze vaak nuttig zullen zijn!

Voor line_2d_c moeten de volgende functies geimplementeerd worden:

```
double get_length() const
vector_2d_c get_center_point() const
double get_angle() const // Hoek met de x-as
bool get_intersection(const line_2d_c & other, vector_2d_c & intersection) const // Returnt true als er een intersectie is, en zal deze opslaan in intersection.
```

## Opdracht 3

Een airfoil_c klasse moet geimplementeerd worden, welke een vector van vector_2d_c opslaat als punten die een airfoil bepalen.

Er moet zowel gelezen kunnen worden van een .dat bestand, als kopie gemaakt worden van een vector van vector_2d_c's.

De volgende projectiefunctie moet aanwezig zijn:

airfoil_c get_circle_projection(uint32_t n, const vector_2d_c & projection_center) const

Verdere info volgt.

## Opdracht 4

Source sheets, vortex sheets en uniforme flows moeten geimplementeerd worden, plus er moet een manier gevonden worden om ze samen te stellen.

Verdere info volgt.