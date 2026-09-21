#include "Carta.h"
#include <iostream>
using namespace std;

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