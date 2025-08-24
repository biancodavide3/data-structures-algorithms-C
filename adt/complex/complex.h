#ifndef COMPLEX_H
#define COMPLEX_H

// quasi adt
// dichiaro il tipo nell'header nelle funzioni
// e lo implemento nel file .c senza usare memoria dinamica

// si puo' realizzare un quasi adt in modo che si possa usare
// una sola istanza di quell'adt dichiarando semplicemente i suoi
// componenti nel .c come variabili globali usando static

// typedef struct complex* COMPLEX

typedef struct complex {
   float Re;
   float Im;
} Complex;

Complex prod(Complex c1, Complex c2);
#endif