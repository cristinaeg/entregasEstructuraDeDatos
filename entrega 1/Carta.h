#ifndef CARTA_H
#define CARTA_H

#include <string>
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

#endif