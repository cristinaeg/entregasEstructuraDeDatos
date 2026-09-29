#include "Mesa.h"

Mesa::Mesa() {
    cantidadSobreMesa = 0;
}

void Mesa::limpiarMesa() {
    cantidadSobreMesa = 0;   // Reiniciar la mesa
}

void Mesa::recibirCarta(Jugador j, Carta c) {
    if (cantidadSobreMesa < 10) {
        jugadoresEnMesa[cantidadSobreMesa] = j;   // Guarda el jugador
        cartasEnMesa[cantidadSobreMesa] = c;      // Guarda la carta
        cantidadSobreMesa++;
    }
}

Jugador Mesa::compararCartas(string colorBuscado, int condicion) {
    int indiceGanador = -1;
    int numeroReferencia = 0;

    for (int i = 0; i < cantidadSobreMesa; i++) {
        // Solo cuentan las cartas del color declarado
        if (cartasEnMesa[i].getColor() == colorBuscado) {
            int numActual = cartasEnMesa[i].getNumero();

            if (indiceGanador == -1) {
                // Primera carta del color: es la referencia inicial
                numeroReferencia = numActual;
                indiceGanador = i;
            }
            // C1: Buscar el # MAS BAJO
            else if (condicion == 1 && numActual < numeroReferencia) {
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

    // Si nadie jugo el color declarado, gana el lider (la primera carta)
    if (indiceGanador == -1) {
        indiceGanador = 0;
    }

    return jugadoresEnMesa[indiceGanador];   // Retorna al jugador ganador
}
