#include "Partida.h"
#include <iostream>
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
    cout << "\nJugador " << jugadores[turnoActual].getId() << ", elige carta (0-3): ";
    cin >> cartaSeleccionada;

    Carta cLider = jugadores[turnoActual].jugarCarta(cartaSeleccionada);  
    mesa.recibirCarta(jugadores[turnoActual], cLider);                     

    cout << "Ingresa el color objetivo: ";
    cin >> colorObjetivo;
    cout << "Condicion (1: Mas bajo, 2: Mas alto): ";
    cin >> condicion;

    //El resto de gentes tira las cartas
    for (int i = 0; i < cantidadJugadores; i++) {
        if (i != turnoActual) {
            cout << "Jugador " << jugadores[i].getId() << ", elige carta a tirar: ";
            cin >> cartaSeleccionada;
            Carta c = jugadores[i].jugarCarta(cartaSeleccionada);         
            mesa.recibirCarta(jugadores[i], c);                            
        }
    }

    //Esto dice que en es el ganador de la RONDA NO EL DEFINITVO
    Jugador ganador = mesa.compararCartas(colorObjetivo, condicion);       
    cout << "¡El ganador de la ronda es el Jugador " << ganador.getId() << "!\n";

    //esto busca que jugar se gano esas carticas para no andar abudineando
    for (int i = 0; i < cantidadJugadores; i++) {
        if (jugadores[i].getId() == ganador.getId()) {
            jugadores[i].sumarGanadas(cantidadJugadores);                  
        }
    }

    rondaActual++;
}

// -------------------------------------------------------------------
// ESCRIBIR Y LEER ARCHIVO
// -------------------------------------------------------------------

bool Partida::guardarPartida(string ruta) {                                         
    ofstream archivo(ruta.c_str(), ios::binary);                           

    if (!archivo) {
        cout << "Error al crear/abrir el archivo para guardar." << endl;    
        return false;
    }

    // llenar los datos
    DatosPartida datos;
    datos.cantidadJugadores = cantidadJugadores;
    datos.turnoActual = turnoActual;
    datos.rondaActual = rondaActual;

    for (int i = 0; i < cantidadJugadores; i++) {
        datos.puntosJugadores[i] = jugadores[i].getCartasGanadas();
    }

    // Guardar datos en bloque
    archivo.write((char*)&datos, sizeof(DatosPartida));                    

    archivo.close();                                                       
    return true;
}

bool Partida::cargarPartida(string ruta) {                                          
    ifstream lectura(ruta.c_str(), ios::binary);                           

    if (!lectura) {
        cout << "Error al abrir el archivo cargado." << endl;              
        return false;
    }

    DatosPartida datos;

    // leer archivo
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
