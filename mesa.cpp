
#include <iostream>
#include <string>
#include "Jugador.cpp"
#include "Carta.cpp"

using namespace std;

class Mesa {
private:
    Carta cartasEnMesa[10];      // cartas jugadas en la ronda
    Jugador jugadoresEnMesa[10];  // El jugador que esta jugando
    int cantidadSobreMesa;       // Cuantas cartas hay en la mesa

public:
    Mesa() {
        cantidadSobreMesa = 0;
    }

    void limpiarMesa() {
        cantidadSobreMesa = 0;   // Reiniciar la mesa
    }

    void recibirCarta(Jugador j, Carta c) {
        if (cantidadSobreMesa < 10) {
            jugadoresEnMesa[cantidadSobreMesa] = j;   // Guarda el jugador
            cartasEnMesa[cantidadSobreMesa] = c;      // Guarda la carta
            cantidadSobreMesa++;
        }
    }

    // Devuelve el jugador ganador de la ronda segun la condicion
    // condicion: 1 para el # mas bajo, 2 para el # mas alto
    Jugador compararCartas(string colorBuscado, int condicion) {   
        int indiceGanador = 0;
        int numeroReferencia = cartasEnMesa[0].getNumero();

        for (int i = 1; i < cantidadSobreMesa; i++) {
            // Verificar color
            if (cartasEnMesa[i].getColor() == colorBuscado) {
                int numActual = cartasEnMesa[i].getNumero();

                // C1: Buscar el # MAS BAJO
                if (condicion == 1 && numActual < numeroReferencia) {
                    numeroReferencia = numActual;
                    indiceGanador = i;
                }
                // C2: Buscar el # MAS ALTO
                else if (condicion == 2 && numActual > numeroReferencia) {
                    numeroReferencia = numActual;
                    indiceGanador = i;
                }
            }
        }

        return jugadoresEnMesa[indiceGanador];   // Retorna al jugador ganador
    }
};