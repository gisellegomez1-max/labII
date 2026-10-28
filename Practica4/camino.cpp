#include "camino.h"
#include <iostream>

Camino::Camino() : costo(-1) {}

Camino::Camino(const list<string>& nodos, int costo)
    : nodos(nodos), costo(costo) {}

const list<string>& Camino::getNodos() const {
    return nodos;
}

int Camino::getCosto() const {
    return costo;
}

bool Camino::esValido() const {
    return !nodos.empty();
}

void Camino::mostrar() const {
    cout << "Camino: ";
    for (list<string>::const_iterator n = nodos.begin(); n != nodos.end(); ++n) {
        if (n != nodos.begin()) cout << " -> ";
        cout << *n;
    }
    cout << "\nCosto: " << costo << endl;
}