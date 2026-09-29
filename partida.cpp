#include "Partida.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>

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
    while (cartaSeleccionada < 0 || cartaSeleccionada >= jugadores[turnoActual].getCantMano()) {
        cout << "Indice invalido, intenta de nuevo: ";
        cin >> cartaSeleccionada;
    }

    Carta cLider = jugadores[turnoActual].jugarCarta(cartaSeleccionada);  
    mesa.recibirCarta(jugadores[turnoActual], cLider);                     

    // El color se pide con un numero para evitar errores de escritura (rojo vs Rojo)
    int opcionColor;
    cout << "Color objetivo (1: Azul, 2: Rojo, 3: Amarillo, 4: Verde): ";
    cin >> opcionColor;
    while (opcionColor < 1 || opcionColor > 4) {
        cout << "Opcion invalida, intenta de nuevo: ";
        cin >> opcionColor;
    }
    if (opcionColor == 1) colorObjetivo = "Azul";
    if (opcionColor == 2) colorObjetivo = "Rojo";
    if (opcionColor == 3) colorObjetivo = "Amarillo";
    if (opcionColor == 4) colorObjetivo = "Verde";

    cout << "Ingresa condicion (1: Numero mas BAJO, 2: Numero mas ALTO): ";
    cin >> condicion;
    while (condicion != 1 && condicion != 2) {
        cout << "Condicion invalida, escribe 1 o 2: ";
        cin >> condicion;
    }

    for (int i = 0; i < cantidadJugadores; i++) {
        int idx = (turnoActual + i) % cantidadJugadores;
        
        if (idx != turnoActual) {
            cout << "\nJugador " << jugadores[idx].getId() << endl;
            jugadores[idx].mostrarMano();
            cout << "Elige el indice de la carta a jugar: ";
            cin >> cartaSeleccionada;
            while (cartaSeleccionada < 0 || cartaSeleccionada >= jugadores[idx].getCantMano()) {
                cout << "Indice invalido, intenta de nuevo: ";
                cin >> cartaSeleccionada;
            }
            
            Carta c = jugadores[idx].jugarCarta(cartaSeleccionada);         
            mesa.recibirCarta(jugadores[idx], c);                            
        }
    }

    Jugador ganador = mesa.compararCartas(colorObjetivo, condicion);       
    cout << "\nSe voltean las cartas... (color: " << colorObjetivo
         << ", " << (condicion == 1 ? "mas BAJO" : "mas ALTO") << ")" << endl;
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
int Partida::getRondaActual() {
    return rondaActual;
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
        datos.cantMano[i] = jugadores[i].getCantMano();

        // Guardar cada carta que el jugador todavia tiene en la mano
        for (int k = 0; k < datos.cantMano[i]; k++) {
            Carta c = jugadores[i].getCartaMano(k);
            datos.numeroCarta[i][k] = c.getNumero();
            strcpy(datos.colorCarta[i][k], c.getColor().c_str());
        }
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

            // Devolverle a cada jugador las cartas que tenia en la mano
            for (int k = 0; k < datos.cantMano[i]; k++) {
                Carta c(datos.numeroCarta[i][k], string(datos.colorCarta[i][k]));
                jugadores[i].agregarCartaMano(c);
            }
        }
        lectura.close();                                                  
        return true;
    }

    lectura.close();                                                     
    return false;
}
