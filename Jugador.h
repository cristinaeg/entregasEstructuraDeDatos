#ifndef JUGADOR_H
#define JUGADOR_H

#include "Carta.h"

class Jugador {
private:
    static const int MAX_MANO = 4;

    int id;
    Carta mano[MAX_MANO];
    int cantMano;
    int cartasGanadas;

public:
    Jugador();
    Jugador(int id_);

    bool agregarCartaMano(Carta c);
    Carta jugarCarta(int index);
    void sumarGanadas(int cant);

    int getId();
    int getCantMano();
    int getCartasGanadas();
    bool tieneCartas();
    void mostrarMano();
};

#endif