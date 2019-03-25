#define NPLANETS 8
typedef struct {
	char name[10];
	double radius;
	double density;
	double orbital_radius;
	} Planet;

int input_planet (Planet *);
