# Team visualisatie

Teamleden: Dolf Huybrechts, Kristof Dockx, Merel Van Gorp, Senne van Putte

Jullie zijn verantwoordelijk voor het onderhoud en de ontwikkeling van de shared library wif-viz, waarmee scalaire en vectorvelden geplot kunnen worden, met allerhande varia (zoals scheidende stroomlijnen enzo).

## Opdracht 1

Gegeven dat de meeste van jullie waarschijnlijk met ROOT hebben gewerkt voor de laatste opdracht, gaan we eerst proberen VTK aan de praat te krijgen.

Ik wil uiteindelijk een geunificeerde interface hebben voor zowel ROOT als VTK, zodat bij het maken van de plotjes gemakkelijk gewisseld kan worden tussen beiden. Hiervoor moeten we dus weten hoe de workflow in VTK eruit ziet ten opzichte van de workflow in ROOT.

In deze directory verwacht ik dus in elke teamlid zijn map dat de volgende twee programma's aanwezig zijn:
+ Een programma dat met VTK het scalair veld f(x, y) = sqrt(x^2 + y^2) plot binnen x:[-1, 1] en y:[-1, 1]. Ik verwacht geen isocontours, maar het zou wel leuk zijn als 1 persoon dit zou proberen.
+ Een programma dat met VTK het vectorveld f(x, y) = x * e_x + y * e_y plot binnen x:[-1, 1] en y:[-1, 1], met de vector genormalizeerd (dus lengte == 1.0).

Dit mogen zeer eenvoudige programma's zijn zonder al-te-veel functionaliteit, het is gewoon belangrijk dat we de workflow van VTK onder de knie krijgen, en kunnen compileren zonder al te veel hoofdpijn.

PS: Jullie mogen perfect samenwerken en elkaar helpen, het wiel moet niet 4 keer heruitgevonden worden. Ik wil gewoon dat iedereen al eens een VTK programma vanaf nul heeft gecompileerd.

## Opdracht 1.5

Nu dat jullie werkende vtk demo's hebben, moeten jullie ervoor zorgen dat het werkt met de rest van het compilatiesysteem dat we hebben.

Iedereen mag zijn eigen vtk demo in een beschrijvende directory steken in de demos/ directory:

```
demos/demo_vtk_comp_merel
demos/demo_vtk_comp_senne
demos/demo_vtk_comp_kristof
demos/demo_vtk_comp_dolf
```

Denk eraan om te kopieren vanuit

## Opdracht 2

Nog niet kijken hieronder. Deze schematische voorstelling is nog niet volledig.

```

class visualization_element_c
{
public:
	visualization_element_c();

	visualization_element_c(const std::string & name, bool add_to_legend);

	virtual void draw(void * misc) = 0;

private:
	std::string name;
	bool add_to_legend;
};

class visualization_points_c : public visualization_element_c
{
public:
	//
};

class visualization_curve_c : public visualization_element_c
{
public:
	//
};

class visualization_c
{
public:
	visualization_c();

	void set_flow(std::shared_ptr<flow_c> flow);

	/**
	 * Zet de naam van de output van de draw_* methods, als 
	void set_output(const std::string & filename);

	virtual void draw_psi() = 0;

	virtual void draw_phi() = 0;

	virtual void draw_velocity() = 0;

private:
	std::shared_ptr<flow_c> flow;
};
```