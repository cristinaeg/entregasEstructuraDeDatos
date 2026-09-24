#include "Mesa.h"

Mesa::Mesa(int numJugadores) {
    if (numJugadores > 10) numJugadores = 10;
    if (numJugadores < 1)  numJugadores = 1;

    cartasEnMesa = new Carta*[numJugadores];
    for (int i = 0; i < numJugadores; i++) {
        cartasEnMesa[i] = nullptr;
    }
    for (int i = 0; i < 10; i++) {
        jugadoresEnMesa[i] = nullptr;
    }
    cantidadSobreMesa = 0;
}

Mesa::~Mesa() {
    delete[] cartasEnMesa;
}

void Mesa::recibirCarta(Jugador* j, Carta* c) {
    if (cantidadSobreMesa >= 10) return;

    cartasEnMesa[cantidadSobreMesa] = c;
    jugadoresEnMesa[cantidadSobreMesa] = j;
    cantidadSobreMesa++;
}

Jugador* Mesa::compararCartas(std::string color, bool condicion) {
    int mejor = -1; 

    for (int i = 0; i < cantidadSobreMesa; i++) {
        if (cartasEnMesa[i]->getColor() != color) continue;

        if (mejor == -1) {
            mejor = i;
        } else {
            int actual = cartasEnMesa[i]->getNumero();
            int best   = cartasEnMesa[mejor]->getNumero();
            if ((condicion && actual > best) || (!condicion && actual < best)) {
                mejor = i;
            }
        }
    }

    if (mejor == -1) return nullptr;
    return jugadoresEnMesa[mejor];
}

void Mesa::limpiarMesa() {
    for (int i = 0; i < cantidadSobreMesa; i++) {
        cartasEnMesa[i] = nullptr;
        jugadoresEnMesa[i] = nullptr;
    }
    cantidadSobreMesa = 0;
}
