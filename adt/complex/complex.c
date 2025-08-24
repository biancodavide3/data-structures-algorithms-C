#include "complex.h"

// typedef struct complex {
//    float Re;
//    float Im;
// } Complex;

Complex prod(Complex c1, Complex c2) {
    Complex c;
    c.Re = c1.Re * c2.Re - c1.Im * c1.Im;
    c.Im = c1.Re * c2.Im + c2.Re * c1.Im;
    return c;
}