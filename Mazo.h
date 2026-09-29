#ifndef MAZO_H
#define MAZO_H

#include "Carta.h"

class Mazo {
private:
    Carta cartas[40];   // arreglo fijo con las 40 cartas
    int totalCartas;
    int tope;           // indice de la siguiente carta a repartir

public:
    Mazo();

    void barajar();
    Carta tomarCarta();
};

#endif

