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
    int puntosJugadores[10];
    int cantMano[10];
    int numeroCarta[10][4];
    char colorCarta[10][4][10];
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
    void registrarJugadores();
    void sortearOrdenInicio();
    void iniciar();
    void jugarRonda();
    Jugador ganadorFinal();
    int getRondaActual();
    bool guardarPartida(string ruta);
    bool cargarPartida(string ruta);
};

#endif
