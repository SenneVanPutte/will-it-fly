# Team primaire objecten

Teamleden: Jeroen Roefs, Jelle Segers, Thorvald Dox

Jullie zijn verantwoordelijk voor het onderhoud en de ontwikkeling van de shared library wif-core, waarin primaire objecten en hulpklassen worden gedefinieerd.

## Opdracht 1

Gegeven aan: Jeroen.

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

Respecteer de conventies in style/ en zorg dat alle output van de makefiles op de juiste plaats komt (dus header files van de libraries in include/, libraries zelf in lib/ en de binary van wif in bin/, allemaal in een build directory). Schrijf ook een clean target in de makefile die de outputs van de makefile opruimt.

Dus de volgende directory structuur wordt verwacht na het runnen van de makefile:

```
will-it-fly/build/bin
will-it-fly/build/lib
will-it-fly/build/obj
will-it-fly/build/include
```

De build directory wordt automatisch genegeerd door Git, dus niet eens proberen de bestanden erin te stagen!

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

Verdere info volgt.

De punten zijn in wijzerzin gedefinieerd, zodat de normalen naar buiten wijzen.

```
class airfoil_c
{
public:
	/**
	 * Lege constructor: zonder points
	 */
	airfoil_c();

	/**
	 * Leest de file in filename, laat points leeg als er iets misloopt. Moet beiden .dat formaten kunnen lezen.
	 */
	airfoil_c(const std::string & filename);

	airfoil_c(std::vector<vector_2d_c> & points);

	airfoil_c get_circle_projection(uint32_t n, const vector_2d_c & projection_center) const;

	/**
	 * Is het laatste punt hetzelfde als de eerste, dan is de curve gesloten. De epsilon dient voor
	 * floating point weirdness met afrondingen tegen te gaan.
	 */
	bool is_closed(double epsilon = 0.0001) const;

	/**
	 * Zit er ten minste 1 punt in de vector (handig als tijdens het lezen iets misloopt).
	 */
	bool is_valid() const;

	/**
	 * Maakt van alle koppels ([i], [i+1]) lijnstukken, met i = 0 tot i < (points.size() + 1).
	 */
	std::vector<line_2d_c> get_lines() const;

private:
	std::vector<vector_2d_c> points;
};
```

## Opdracht 4

Source sheets, vortex sheets en uniforme flows moeten geimplementeerd worden, plus er moet een manier gevonden worden om ze samen te stellen.

De volgende klassen moeten geimplementeerd worden:

```
// Alle afgeleide klassen moeten de virtuele methods implementeren.
class flow_c
{
public:
	virtual double get_phi(const vector_2d_c & position) const = 0;

	virtual double get_psi(const vector_2d_c & position) const = 0;

	virtual vector_2d_c get_velocity(const vector_2d_c & position) const = 0;
};

// Maakt een lineare combinatie van alle elementaire flow objecten.
class flow_accumulate_c : public flow_c
{
public:
	/**
	 * Lege constructor, een "lege flow", dus zonder elementen.
	 */
	flow_accumulate_c();

	/**
	 * Kopieert de flow pointers.
	 */
	flow_accumulate_c(const std::vector<std::shared_ptr<flow_c>> & flows);

	/**
	 * Constructor met slechts 1 flow.
	 */
	flow_accumulate_c(std::shared_ptr<flow_c> flow);

	/**
	 * Adds a new flow to the internal array.
	 */
	void add_flow(std::shared_ptr<flow_c> flow);

private:
	std::vector<std::shared_ptr<flow_c>> flows;
};

class source_sheet_c : public flow_c
{
public:
	/**
	 * Lege constructor: maakt een source sheet aan van (-1, 0) tot (1, 0) met sigma = 1.0
	 */
	source_sheet_c();

	source_sheet_c(const line_2d_t & line, double sigma);

private:
	line_2d_c line;
	double sigma;
};

class vortex_sheet_c : public flow_c
{
public:
	/**
	 * Lege constructor: maakt een vortex sheet aan van (-1, 0) tot (1, 0) met lambda = 1.0
	 */
	vortex_sheet_c();

	vortex_sheet_c(const line_2d_t & line, double lambda);

private:
	line_2d_c line;
	double lambda;
};

class uniform_flow_c : public flow_c
{
public:
	/**
	 * Lege constructor: uniform flow met angle = 0, en u_infinity = 1
	 */
	uniform_flow_c();

	uniform_flow_c(double angle, double u_infinity);

private:
	vector_2d_c flow_vec;
};

// Sinks zijn sources met een negatieve sterkte.
class source_sink_c : public flow_c
{
public:
	/**
	 * Lege constructor: source sink op (0, 0) met sterkte q = 1
	 */
	source_sink_c();

	source_sink_c(const vector_2d_c & location, double q);

private:
	vector_2d_c location;
	double q;
};
```


