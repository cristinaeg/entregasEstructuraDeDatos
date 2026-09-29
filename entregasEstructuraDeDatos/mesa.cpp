#include "Mesa.h"

Mesa::Mesa() {
    cantidadSobreMesa = 0;[cite: 7]
}

void Mesa::limpiarMesa() {
    cantidadSobreMesa = 0;   // Reiniciar la mesa
}

void Mesa::recibirCarta(Jugador j, Carta c) {
    if (cantidadSobreMesa < 10) {
        jugadoresEnMesa[cantidadSobreMesa] = j;   // Guarda el jugador
        cartasEnMesa[cantidadSobreMesa] = c;      // Guarda la carta
        cantidadSobreMesa++;[cite: 7]
    }
}


Jugador Mesa::compararCartas(string colorBuscado, int condicion) {   
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

