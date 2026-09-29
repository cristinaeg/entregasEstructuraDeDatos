#include "Partida.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

Partida::Partida() {
    cantidadJugadores = 2;
    turnoActual = 0;
    rondaActual = 1;
}

Partida::Partida(int numJugadores) {    
    cantidadJugadores = numJugadores;
    turnoActual = 0;
    rondaActual = 1;

    for (int i = 0; i < cantidadJugadores; i++) {
        jugadores[i] = Jugador(i + 1);   // para el ID de los jugadores xd
    }
}
void Partida::registrarJugadores() {
    cout << "\n--- REGISTRO DE JUGADORES ---" << endl;
    for (int i = 0; i < cantidadJugadores; i++) {
        cout << "Jugador " << (i + 1) << " registrado con ID: " << jugadores[i].getId() << endl;
    }
}
void Partida::sortearOrdenInicio() {
    srand(time(NULL));
    cout << "\n--- SORTEO DE TURNO INICIAL (LANZAMIENTO DE DADO) ---" << endl;

    int mayorDado = -1;
    int liderInicial = 0;

    for (int i = 0; i < cantidadJugadores; i++) {
        int dado = (rand() % 6) + 1;
        cout << "Jugador " << jugadores[i].getId() << " tiro el dado y saco: " << dado << endl;

        if (dado > mayorDado) {
            mayorDado = dado;
            liderInicial = i;
        }
    }

    turnoActual = liderInicial;
    cout << "\n>>> ¡El Jugador " << jugadores[turnoActual].getId() 
         << " saco el dado mas alto (" << mayorDado << ") y comenzara liderando! <<<" << endl;
}
void Partida::iniciar() {               
    mazo.barajar();             
        
    // 4 cartas a cada bobolon
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < cantidadJugadores; j++) {
            Carta c = mazo.tomarCarta();               
            jugadores[j].agregarCartaMano(c);         
        }
    }
}

void Partida::jugarRonda() {            
    mesa.limpiarMesa();        
        
    int cartaSeleccionada;
    string colorObjetivo;
    int condicion;

    //Aqui empieza la persona de turno a analizar que cartas y dar al condision de como es
    cout << "\n------------------------------------------" << endl;
    cout << "TURNO LIDER - Jugador " << jugadores[turnoActual].getId() << endl;
    jugadores[turnoActual].mostrarMano();
    cout << "Elige el indice de la carta a jugar (0 a " << (jugadores[turnoActual].getCantMano() - 1) << "): ";
    cin >> cartaSeleccionada;

    Carta cLider = jugadores[turnoActual].jugarCarta(cartaSeleccionada);  
    mesa.recibirCarta(jugadores[turnoActual], cLider);                     

    cout << "Ingresa el color objetivo a evaluar (Rojo, Azul, Verde, Amarillo): ";
    cin >> colorObjetivo;
    cout << "Ingresa condicion (1: Numero mas BAJO, 2: Numero mas ALTO): ";
    cin >> condicion;

    for (int i = 0; i < cantidadJugadores; i++) {
        int idx = (turnoActual + i) % cantidadJugadores;
        
        if (idx != turnoActual) {
            cout << "\nJugador " << jugadores[idx].getId() << endl;
            jugadores[idx].mostrarMano();
            cout << "Elige el indice de la carta a jugar: ";
            cin >> cartaSeleccionada;
            
            Carta c = jugadores[idx].jugarCarta(cartaSeleccionada);         
            mesa.recibirCarta(jugadores[idx], c);                            
        }
    }

    Jugador ganador = mesa.compararCartas(colorObjetivo, condicion);       
    cout << "\n>>> ¡El ganador de la ronda es el Jugador " << ganador.getId() << "! <<<" << endl;

    for (int i = 0; i < cantidadJugadores; i++) {
        if (jugadores[i].getId() == ganador.getId()) {
            jugadores[i].sumarGanadas(cantidadJugadores);                  
            turnoActual = i;
        }
    }

    rondaActual++;
}
Jugador Partida::ganadorFinal() {
    int maxPuntos = -1;
    int indiceGanador = 0;

    for (int i = 0; i < cantidadJugadores; i++) {
        if (jugadores[i].getCartasGanadas() > maxPuntos) {
            maxPuntos = jugadores[i].getCartasGanadas();
            indiceGanador = i;
        }
    }
    return jugadores[indiceGanador];
}
// -------------------------------------------------------------------
// ESCRIBIR Y LEER ARCHIVO
// -------------------------------------------------------------------

bool Partida::guardarPartida(string ruta) {                                         
    ofstream archivo(ruta.c_str(), ios::binary);                           
    if (!archivo) return false;

    DatosPartida datos;
    datos.cantidadJugadores = cantidadJugadores;
    datos.turnoActual = turnoActual;
    datos.rondaActual = rondaActual;

    for (int i = 0; i < cantidadJugadores; i++) {
        datos.puntosJugadores[i] = jugadores[i].getCartasGanadas();
    }

    archivo.write((char*)&datos, sizeof(DatosPartida));                    
    archivo.close();                                                       
    return true;
}

bool Partida::cargarPartida(string ruta) {                                          
    ifstream lectura(ruta.c_str(), ios::binary);                           
    if (!lectura) return false;

    DatosPartida datos;

    if (lectura.read((char*)&datos, sizeof(DatosPartida))) {               
        cantidadJugadores = datos.cantidadJugadores;
        turnoActual = datos.turnoActual;
        rondaActual = datos.rondaActual;

        for (int i = 0; i < cantidadJugadores; i++) {
            jugadores[i] = Jugador(i + 1);
            jugadores[i].sumarGanadas(datos.puntosJugadores[i]);
        }
        lectura.close();                                                  
        return true;
    }

    lectura.close();                                                     
    return false;
}
