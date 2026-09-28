#ifndef MESA_H
#define MESA_H

#include <string>
#include "Carta.h"
#include "Jugador.h"

class Mesa {
private:
    Carta** cartasEnMesa;
    Jugador* jugadoresEnMesa[10];
    int cantidadSobreMesa;

public:
    Mesa(int numJugadores);
    ~Mesa();

    void recibirCarta(Jugador* j, Carta* c);

    Jugador* compararCartas(std::string color, bool condicion);

    void limpiarMesa();
};

#endif
