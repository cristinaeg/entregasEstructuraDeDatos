#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Carta {
private:
    int numero;
    string color;

public:
    Carta(int num, const string& col) {
        numero = num;
        color = col;
    }

    int getNumero() const { return numero; }
    string getColor() const { return color; }

    void mostrar() const {
        cout << color << " " << numero << endl;
    }
};

int main() {
    string colores[4] = {"Azul", "Rojo", "Amarillo", "Verde"};
    vector<Carta> mazo;
    mazo.reserve(40);

    for (const string& color : colores) {
        for (int n = 0; n <= 9; n++) {
            mazo.emplace_back(n, color);
        }
    }

    cout << "Total: " << mazo.size() << " cartas" << endl;

    for (const Carta& carta : mazo) {
        carta.mostrar();
    }

    return 0;
}