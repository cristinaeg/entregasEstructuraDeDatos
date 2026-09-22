#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Carta.cpp"

using namespace std;

class Mazo {
private:
    Carta* cartas;
    int totalCartas;
    int tope;

public:
    Mazo() {
        totalCartas = 40;
        tope = 0;

        cartas = new Carta[40];

        string colores[4] = {
            "rojo",
            "azul",
            "verde",
            "amarillo"
        };

        int posicion = 0;

        for (int i = 0; i < 4; i++) {
            for (int numero = 1; numero <= 10; numero++) {
                cartas[posicion] = Carta(colores[i], numero);
                posicion++;
            }
        }

        srand(time(NULL));
    }

    void barajar() {
        for (int i = totalCartas - 1; i > 0; i--) {
            int j = rand() % (i + 1);

            Carta auxiliar = cartas[i];
            cartas[i] = cartas[j];
            cartas[j] = auxiliar;
        }

        tope = 0;
    }

    Carta tomarCarta() {
        if (tope >= totalCartas) {
            return Carta("ninguno", -1);
        }

        Carta carta = cartas[tope];
        tope++;

        return carta;
    }
};
