#include <iostream>
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

    if (opcion == 1) {
        int numJugadores;
        cout << "\nIngrese la cantidad de jugadores participantes (4 a 10): ";
        cin >> numJugadores;

        while (numJugadores < 4 || numJugadores > 10) {
            cout << "Numero invalido. Debe haber entre 4 y 10 jugadores: ";
            cin >> numJugadores;
        }

        juego = Partida(numJugadores);
        juego.registrarJugadores();
        juego.sortearOrdenInicio(); // Tira el dado para saber quién empieza
        juego.iniciar();            // Reparte las 4 cartas fijas
    } else {
        if (!juego.cargarPartida("partida.dat")) {
            cout << "No se pudo cargar la partida. Iniciando nueva partida con 4 jugadores..." << endl;
            juego = Partida(4);
            juego.registrarJugadores();
            juego.sortearOrdenInicio();
            juego.iniciar();
        }
    }

    // Exactamente 4 rondas de juego (una por cada carta en mano)
    for (int r = 1; r <= 4; r++) {
        cout << "\n==========================================" << endl;
        cout << "               RONDA " << r << " DE 4" << endl;
        cout << "==========================================" << endl;

        juego.jugarRonda();
        juego.guardarPartida("partida.dat");
    }

    // Anuncio del ganador definitivo
    Jugador campeon = juego.ganadorFinal();
    cout << "\n==========================================" << endl;
    cout << "¡FIN DE LA PARTIDA TRAS 4 RONDAS!" << endl;
    cout << "El GANADOR DEFINITIVO es el JUGADOR " << campeon.getId() 
         << " con " << campeon.getCartasGanadas() << " cartas acumuladas." << endl;
    cout << "==========================================" << endl;

    return 0;
}