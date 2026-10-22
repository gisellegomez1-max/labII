#include "enrutador.h"
#include <iostream>

Enrutador::Enrutador() : nombre("") {}

Enrutador::Enrutador(const string& nombre) : nombre(nombre) {
    // Un enrutador siempre está a costo 0 de sí mismo
    tablaCostos[nombre] = 0;
}

string Enrutador::getNombre() const {
    return nombre;
}

const map<string, int>& Enrutador::getVecinos() const {
    return vecinos;
}

const map<string, int>& Enrutador::getTablaCostos() const {
    return tablaCostos;
}

void Enrutador::agregarVecino(const string& vecino, int costo) {
    vecinos[vecino] = costo;        // si ya existía, actualiza el costo
    tablaCostos[vecino] = costo;    // tabla inicial: solo destinos directos
}

void Enrutador::eliminarVecino(const string& vecino) {
    vecinos.erase(vecino);
    tablaCostos.erase(vecino);
}

void Enrutador::actualizarCosto(const string& destino, int costo) {
    tablaCostos[destino] = costo;
}

int Enrutador::getCosto(const string& destino) const {
    map<string, int>::const_iterator it = tablaCostos.find(destino);
    if (it == tablaCostos.end()) {
        return -1;                  // destino desconocido
    }
    return it->second;
}

void Enrutador::mostrarTabla() const {
    cout << "Tabla de " << nombre << ":" << endl;
    for (map<string, int>::const_iterator it = tablaCostos.begin();
         it != tablaCostos.end(); ++it) {
        cout << "  -> " << it->first << " : " << it->second << endl;
    }
}

void Enrutador::reiniciarTabla() {
    tablaCostos.clear();
    tablaCostos[nombre] = 0;
    for (map<string, int>::const_iterator it = vecinos.begin();
         it != vecinos.end(); ++it) {
        tablaCostos[it->first] = it->second;
    }
}