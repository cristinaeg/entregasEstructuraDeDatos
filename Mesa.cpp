#pragma once

#include <iostream>
#include <string>
#include <climits>
#include "Carta.cpp"
#include "Jugador.cpp"

using namespace std;

class Mesa {
private:
    Carta* cartasEnMesa;
    Jugador* jugadoresEnMesa;
    int capacidadRonda;
    int cantidadSobreMesa;

public:
    Mesa() {
        capacidadRonda = 10;
        cantidadSobreMesa = 0;

        cartasEnMesa = new Carta[10];
        jugadoresEnMesa = new Jugador[10];
    }

    void recibirCarta(Jugador j, Carta c) {
        if (cantidadSobreMesa >= capacidadRonda) {
            cout << "La mesa ya esta llena." << endl;
            return;
        }

        jugadoresEnMesa[cantidadSobreMesa] = j;
        cartasEnMesa[cantidadSobreMesa] = c;

        cantidadSobreMesa++;
    }

    Jugador compararCartas(string color, bool condicion) {
        if (cantidadSobreMesa == 0) {
            return Jugador(-1);
        }

        int mejorNumero;
        int posicionGanador = -1;

        if (condicion) {
            // TRUE = buscar la carta mas alta
            mejorNumero = INT_MIN;
        }
        else {
            // FALSE = buscar la carta mas baja
            mejorNumero = INT_MAX;
        }

        for (int i = 0; i < cantidadSobreMesa; i++) {

            if (cartasEnMesa[i].getColor() == color) {

                int numeroActual = cartasEnMesa[i].getNumero();

                if (condicion) {
                    // Mayor
                    if (numeroActual > mejorNumero) {
                        mejorNumero = numeroActual;
                        posicionGanador = i;
                    }
                }
                else {
                    // Menor
                    if (numeroActual < mejorNumero) {
                        mejorNumero = numeroActual;
                        posicionGanador = i;
                    }
                }
            }
        }

        if (posicionGanador == -1) {
            cout << "No hay cartas del color " << color << " sobre la mesa." << endl;
            return Jugador(-1);
        }

        return jugadoresEnMesa[posicionGanador];
    }

    void limpiarMesa() {
        cantidadSobreMesa = 0;
    }
};
