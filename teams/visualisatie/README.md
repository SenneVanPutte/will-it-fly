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

## Opdracht 2

Verdere info volgt.