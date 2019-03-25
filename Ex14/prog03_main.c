#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prog03.h"

int main () {
    int i;
	Planet planets[NPLANETS];
	
	if (input_planet(planets) != 0) {
        fprintf(stderr,"Error has occurred!\n");
        exit(-1);
    }

	for (i = 0; i < NPLANETS; i++) {
		printf("Name: %s\n",planets[i].name);
		printf(" Radius: %.0f [km]\n", planets[i].radius);
		printf(" Density: %.2f [g/cc]\n", planets[i].density);
		printf(" Orbital Radius: %.3e [km]\n", planets[i].orbital_radius);
	}
	return 0;
}

#ifdef TEST0
int input_planet (Planet *planet) {
    int i;
	for (i = 0; i < NPLANETS; i++) {
        strcpy(planet[i].name, "Hoge");
        planet[i].radius = 1000;
        planet[i].density = 1.00;
        planet[i].orbital_radius = 100000000;
    }
    return 0;
}
#elif TEST1
int input_planet (Planet *planet) {
    return -1;
}
#endif
