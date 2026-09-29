#include "Mazo.h"
#include <cstdlib>

Mazo::Mazo() {
    totalCartas = 40;
    tope = 0;

    string colores[4] = {"Azul", "Rojo", "Amarillo", "Verde"};

    int k = 0;
    for (int c = 0; c < 4; c++) {
        for (int num = 0; num < 10; num++) {
            cartas[k] = Carta(num, colores[c]);
            k++;
        }
    }
}

void Mazo::barajar() {
    for (int i = totalCartas - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }
    tope = 0;
}

Carta Mazo::tomarCarta() {
    if (tope >= totalCartas) {
        return Carta();
    }
    Carta c = cartas[tope];
    tope++;
    return c;
}
