#include "complex.h"
#include <stdio.h>

int main(void) {
    Complex c1 = {1.9, 3.0};
    Complex c2 = {-2.2, 5.1};
    Complex c = prod(c1, c2);
    printf("Posso vedere i dettagli interni di c1\nc1.Re = %f\nc1.Im = %f",
           c1.Re, c1.Im);
    return 0;
}