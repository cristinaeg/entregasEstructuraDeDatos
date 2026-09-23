#include "Jugador.h"
#include <iostream>
using namespace std;

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


Jugador::Jugador() {
    id = -1;
    cantMano = 0;
    cartasGanadas = 0;
}

Jugador::Jugador(int id_) {
    id = id_;
    cantMano = 0;
    cartasGanadas = 0;
}

bool Jugador::agregarCartaMano(Carta c) {
    if (cantMano >= MAX_MANO) {
        return false;
    }
    mano[cantMano] = c;
    cantMano++;
    return true;
}

Carta Jugador::jugarCarta(int index) {
    if (index < 0 || index >= cantMano) {
        return Carta();
    }

    Carta elegida = mano[index];

    for (int i = index; i < cantMano - 1; i++) {
        mano[i] = mano[i + 1];
    }

    cantMano--;
    return elegida;
}

void Jugador::sumarGanadas(int cant) {
    cartasGanadas += cant;
}

int Jugador::getId() {
    return id;
}

int Jugador::getCantMano() {
    return cantMano;
}

int Jugador::getCartasGanadas() {
    return cartasGanadas;
}

bool Jugador::tieneCartas() {
    return cantMano > 0;
}

void Jugador::mostrarMano() {
    cout << "Jugador " << id << " (" << cantMano << " cartas):" << endl;
    for (int i = 0; i < cantMano; i++) {
        cout << "  [" << i << "] ";
        mano[i].mostrar();
    }
}
