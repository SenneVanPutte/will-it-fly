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

class visualization_c
{
public:
	visualization_c(std::shared_ptr<flow_c> flow, const vector_2d_c & min, const vector_2d_c & max);

	virtual ~visualization_c();

	/**
	 * Redelijk voor de hand liggend, de minima van het plot-bereik zitten in min,
	 * de maxima in max.
	 */
	void set_range(const vector_2d_c & min, const vector_2d_c & max);

	/**
	 * Standaard zijn de bins == (0, 0)
	 * Als de bins == (0, 0), moet niks getekend worden van dat veld.
	 * Als de bins != (0, 0), worden de bins gevonden door round(abs(x)), round(abs(y))
	 * Ge rond de absolute waarden van de vector af.
	 */
	void set_psi_bins(const vector_2d_c & bins);
	void set_phi_bins(const vector_2d_c & bins);
	void set_velocity_bins(const vector_2d_c & bins);

	/**
	 * Tekent de velden/airfoil/extra stroomlijnen/stagnatiepunten.
	 *
	 * Pas in deze method worden de grids opgevuld met punten.
	 *
	 * Als de filename == "", print naar het scherm, anders naar het
	 * bestand dat gegeven is door filename.c_str()
	 */
	virtual void draw(const std::string & filename = "") = 0;

	//

private:
	std::shared_ptr<flow_c> flow;
	vector_2d_c min;
	vector_2d_c max;

	vector_2d_c psi_bins;
	vector_2d_c phi_bins;
	vector_2d_c velocity_bins;
};


// In een visualisation_vtk_c.hpp

class visualisation_vtk_c : public visualisation_c
{
public:
	visualisation_vtk_c();

	//
	virtual ~visualisation_vtk_c();

	virtual void draw(const std::string & filename = "");

private:
	// Smart pointers gebruiken in plaats van gewoon sterretjes.

	void add_lines_to_renderer(vtkRenderer * renderer, const std::vector<line_2d_c> & lines);

	void add_points_to_renderer(vtkRenderer * renderer, const std::vector<vector_2d_c> & points);

	//

	void add_psi_field(vtkRenderer * renderer);

	void add_phi_field(vtkRenderer * renderer);

	void add_velocity_field(vtkRenderer * renderer);
};


// In een visualisation_root_c.hpp

class visualisation_root_c : public visualisation_c
{
public:
	//

	virtual void draw(const std::string & filename = "");

private:
	//
};

```