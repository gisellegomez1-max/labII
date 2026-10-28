#include "red.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <functional>
#include <utility>

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
    // 1. Cada enrutador vuelve a sus destinos directos
    for (map<string, Enrutador>::iterator it = enrutadores.begin();
         it != enrutadores.end(); ++it) {
        it->second.reiniciarTabla();
    }
    // 2. Se calcula el camino más corto desde cada enrutador
    for (map<string, Enrutador>::iterator it = enrutadores.begin();
         it != enrutadores.end(); ++it) {
        dijkstra(it->first);
    }
}

void Red::dijkstra(const string& origen) {
    map<string, int> dist;
    map<string, string> previo;
    priority_queue<pair<int, string>, vector<pair<int, string> >,
                   greater<pair<int, string> > > cola;

    dist[origen] = 0;
    cola.push(make_pair(0, origen));

    while (!cola.empty()) {
        pair<int, string> actual = cola.top();
        cola.pop();
        int d = actual.first;
        string u = actual.second;

        if (d > dist[u]) continue;   // entrada vieja de la cola

        const map<string, int>& vec = enrutadores[u].getVecinos();
        for (map<string, int>::const_iterator v = vec.begin(); v != vec.end(); ++v) {
            int nuevo = d + v->second;
            map<string, int>::iterator f = dist.find(v->first);
            if (f == dist.end() || nuevo < f->second) {
                dist[v->first] = nuevo;
                previo[v->first] = u;
                cola.push(make_pair(nuevo, v->first));
            }
        }
    }

    // Se le entregan al enrutador los costos y caminos encontrados
    Enrutador& r = enrutadores[origen];
    for (map<string, int>::const_iterator it = dist.begin(); it != dist.end(); ++it) {
        if (it->first == origen) continue;

        list<string> camino;
        string nodo = it->first;
        while (nodo != origen) {
            camino.push_front(nodo);
            nodo = previo[nodo];
        }
        camino.push_front(origen);

        r.actualizarCosto(it->first, it->second);
        r.actualizarCamino(it->first, camino);
    }
}

Camino Red::obtenerCamino(const string& origen, const string& destino) const {
    map<string, Enrutador>::const_iterator it = enrutadores.find(origen);
    if (it == enrutadores.end() || !existeEnrutador(destino)) {
        return Camino();                    // origen o destino no existen
    }
    int costo = it->second.getCosto(destino);
    if (costo == -1) {
        return Camino();                    // no hay ruta
    }
    return Camino(it->second.getCamino(destino), costo);
}

void Red::mostrarCamino(const string& origen, const string& destino) const {
    Camino c = obtenerCamino(origen, destino);
    if (!c.esValido()) {
        cout << "No hay camino de " << origen << " a " << destino << endl;
        return;
    }
    c.mostrar();
}

bool Red::cargarDesdeArchivo(const string& ruta) {
    ifstream archivo(ruta.c_str());
    if (!archivo.is_open()) {
        return false;
    }
    enrutadores.clear();            // la red cargada reemplaza a la actual

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty() || linea[0] == '#') continue;

        istringstream ss(linea);
        string tipo;
        ss >> tipo;

        if (tipo == "ROUTER") {
            string nombre;
            ss >> nombre;
            agregarEnrutador(nombre);
        } else if (tipo == "ENLACE") {
            string a, b;
            int costo;
            ss >> a >> b >> costo;
            agregarEnlace(a, b, costo);
        } else {
            cerr << "Linea ignorada: " << linea << endl;
        }
    }
    return true;
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

bool Red::mostrarTablaDe(const string& nombre) const {
    map<string, Enrutador>::const_iterator it = enrutadores.find(nombre);
    if (it == enrutadores.end()) {
        return false;
    }
    it->second.mostrarTabla();
    return true;
}