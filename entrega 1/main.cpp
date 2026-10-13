#include <iostream>
#include <cstdio>
#include "Partida.h"

using namespace std;

int main() {
    int opcion = 0;
    cout << "========================================" << endl;
    cout << "         MINI JUEGO DE CARTAS           " << endl;
    cout << "========================================" << endl;
    cout << "1. Iniciar nueva partida" << endl;
    cout << "2. Cargar partida anterior" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    Partida juego;

    if (opcion == 2 && juego.cargarPartida("partida.dat")) {
        cout << "\nPartida cargada. Se continua desde la ronda "
             << juego.getRondaActual() << "." << endl;
    } else {
        if (opcion == 2) {
            cout << "No hay partida guardada. Se inicia una nueva." << endl;
        }

        int numJugadores;
        cout << "\nIngrese la cantidad de jugadores participantes (4 a 10): ";
        cin >> numJugadores;

        while (numJugadores < 4 || numJugadores > 10) {
            cout << "Numero invalido. Debe haber entre 4 y 10 jugadores: ";
            cin >> numJugadores;
        }

        juego = Partida(numJugadores);
        juego.registrarJugadores();
        juego.sortearOrdenInicio(); // Tira el dado para saber quien empieza
        juego.iniciar();            // Reparte las 4 cartas fijas
    }

    while (juego.getRondaActual() <= 4) {
        cout << "\n==========================================" << endl;
        cout << "               RONDA " << juego.getRondaActual() << " DE 4" << endl;
        cout << "==========================================" << endl;

        juego.jugarRonda();
        juego.guardarPartida("partida.dat");   // se guarda al terminar cada ronda

        if (juego.getRondaActual() <= 4) {
            int seguir;
            cout << "\nPartida guardada. 1: Seguir jugando  2: Salir (continuar despues): ";
            cin >> seguir;
            if (seguir == 2) {
                cout << "Hasta luego. Elige 'Cargar partida anterior' para continuar." << endl;
                return 0;
            }
        }
    }

    Jugador campeon = juego.ganadorFinal();
    cout << "\n==========================================" << endl;
    cout << "¡FIN DE LA PARTIDA TRAS 4 RONDAS!" << endl;
    cout << "El GANADOR DEFINITIVO es el JUGADOR " << campeon.getId() 
         << " con " << campeon.getCartasGanadas() << " cartas acumuladas." << endl;
    cout << "==========================================" << endl;

    remove("partida.dat");

    return 0;
}
