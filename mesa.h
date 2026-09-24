#ifndef MESA_H
#define MESA_H

#include <string>
#include "Jugador.h"
#include "Carta.h"

using namespace std;

class Mesa {
private:
    Carta cartasEnMesa[10];      // cartas jugadas en la ronda[cite: 7]
    Jugador jugadoresEnMesa[10];  // El jugador que esta jugando[cite: 7]
    int cantidadSobreMesa;       // Cuantas cartas hay en la mesa[cite: 7]

public:
    Mesa();
    void limpiarMesa();
    void recibirCarta(Jugador j, Carta c);
    Jugador compararCartas(string colorBuscado, int condicion);
};

#endif
