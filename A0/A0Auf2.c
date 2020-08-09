#include <stdio.h>
#include <math.h>


const double G = 6.67384E-11; /* Gravitationskonstante */
double mErde = 5.972E24; /* Masse Erde */
double distanz;
/* Berechnet Kraft zwischen zwei Objekten */
double force(double mass1, double mass2, double distance) {
    double d2 = pow(distance, 2);
    return G * mass1 * mass2 / d2;
}

int main(void) {
    distanz = 3.844E8; /* Distanz Erde zu Mond */
    double f = force(mErde, 7.349E22, distanz); /* Kraft Erde zu Mond */
    printf("Kraft Erde zu Mond: %e\n", f);
    return 0;
}
