#include "red.h"
#include <iostream>

Red::Red() {}

bool Red::existeEnrutador(const string& nombre) const {
    return enrutadores.find(nombre) != enrutadores.end();
}

bool Red::agregarEnrutador(const string& nombre) {
    if (nombre.empty() || existeEnrutador(nombre)) {
        return false;                       // vacío o repetido
    }
    enrutadores[nombre] = Enrutador(nombre);
    actualizarTablas();
    return true;
}

bool Red::eliminarEnrutador(const string& nombre) {
    if (!existeEnrutador(nombre)) {
        return false;
    }
    enrutadores.erase(nombre);

    // Los demás ya no pueden tenerlo como vecino
    for (map<string, Enrutador>::iterator it = enrutadores.begin();
         it != enrutadores.end(); ++it) {
        it->second.eliminarVecino(nombre);
    }
    actualizarTablas();
    return true;
}

bool Red::agregarEnlace(const string& a, const string& b, int costo) {
    if (a == b || costo <= 0 || !existeEnrutador(a) || !existeEnrutador(b)) {
        return false;
    }
    // El enlace es bidireccional: ambos enrutadores lo registran
    enrutadores[a].agregarVecino(b, costo);
    enrutadores[b].agregarVecino(a, costo);
    actualizarTablas();
    return true;
}

bool Red::eliminarEnlace(const string& a, const string& b) {
    if (!existeEnrutador(a) || !existeEnrutador(b)) {
        return false;
    }
    enrutadores[a].eliminarVecino(b);
    enrutadores[b].eliminarVecino(a);
    actualizarTablas();
    return true;
}

void Red::actualizarTablas() {
    // Versión parcial: cada tabla se reconstruye con los destinos directos.
    // En la 2da entrega aquí se calcula el camino más corto (Dijkstra)
    // y se llama a actualizarCosto() de cada enrutador.
    for (map<string, Enrutador>::iterator it = enrutadores.begin();
         it != enrutadores.end(); ++it) {
        it->second.reiniciarTabla();
    }
}

void Red::mostrarRed() const {
    cout << "=== Red (" << enrutadores.size() << " enrutadores) ===" << endl;
    for (map<string, Enrutador>::const_iterator it = enrutadores.begin();
         it != enrutadores.end(); ++it) {
        cout << it->first << " ->";
        const map<string, int>& vec = it->second.getVecinos();
        for (map<string, int>::const_iterator v = vec.begin();
             v != vec.end(); ++v) {
            cout << " " << v->first << "(" << v->second << ")";
        }
        cout << endl;
    }
}

void Red::mostrarTablas() const {
    for (map<string, Enrutador>::const_iterator it = enrutadores.begin();
         it != enrutadores.end(); ++it) {
        it->second.mostrarTabla();
    }
}