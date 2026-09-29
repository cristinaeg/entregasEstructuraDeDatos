#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include "Mazo.h"
#include "Mesa.h"
#include "Jugador.h"

using namespace std;

struct DatosPartida {
    int cantidadJugadores;    
    int turnoActual;          
    int rondaActual;
    int puntosJugadores[10];  // Cartas acumuladas
};

class Partida {
private:
    Mazo mazo;                
    Mesa mesa;                
    Jugador jugadores[10];    // Maximo 10 jugadores papu
    int cantidadJugadores;    
    int turnoActual;         
    int rondaActual;

public:
    Partida();
    Partida(int numJugadores);
    void iniciar();
    void jugarRonda();
    bool guardarPartida(string ruta);
    bool cargarPartida(string ruta);
};

#endif
