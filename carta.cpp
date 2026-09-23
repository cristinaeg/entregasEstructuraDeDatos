#include "Carta.h"
#include <iostream>
using namespace std;

class Carta {
private:
    int numero;
    string color;

public:
    Carta();                      // carta vacia
    Carta(int num, string col);   // carta con datos

    int getNumero();
    string getColor();
    bool esValida();
    void mostrar();
};

Carta::Carta() {
    numero = -1;
    color = "NINGUNA";
}

Carta::Carta(int num, string col) {
    numero = num;
    color = col;
}

int Carta::getNumero() {
    return numero;
}

string Carta::getColor() {
    return color;
}

bool Carta::esValida() {
    return numero >= 0 && numero <= 9;
}

void Carta::mostrar() {
    cout << color << " " << numero << endl;
}
