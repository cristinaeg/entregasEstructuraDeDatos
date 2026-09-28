#ifndef MAZO_H
#define MAZO_H

#include "Carta.h"

class Mazo {
private:
    Carta** cartas;
    int totalCartas;
    int tope;

public:
    Mazo();
    ~Mazo();

    void barajar();
};

#endif
