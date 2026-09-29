#include "Mazo.h"
#include <random>
#include <utility>

Mazo::Mazo() {
    totalCartas = 40;
    tope = 0;
    cartas = new Carta*[totalCartas];

    int k = 0;
    for (int color = 0; color < 4; color++) {
        for (int num = 0; num < 10; num++) {
            cartas[k++] = new Carta(color, num);
        }
    }
}

Mazo::~Mazo() {
    for (int i = 0; i < totalCartas; i++) {
        delete cartas[i];
    }
    delete[] cartas;
}

void Mazo::barajar() {
    static std::mt19937 gen(std::random_device{}());

    for (int i = totalCartas - 1; i > 0; i--) {
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(gen);
        std::swap(cartas[i], cartas[j]);
    }
    tope = 0;
}
