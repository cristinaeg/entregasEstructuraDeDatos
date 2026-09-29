#ifndef MESA_H
#define MESA_H

#include <string>
#include "Jugador.h"
#include "Carta.h"

using namespace std;

class Mesa {
private:
    Carta cartasEnMesa[10];      // cartas jugadas en la ronda
    Jugador jugadoresEnMesa[10];  // El jugador que esta jugando
    int cantidadSobreMesa;       // Cuantas cartas hay en la mesa

public:
    Mesa();
    void limpiarMesa();
    void recibirCarta(Jugador j, Carta c);
    Jugador compararCartas(string colorBuscado, int condicion);
};

#endif
