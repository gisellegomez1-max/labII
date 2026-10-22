#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include "enrutador.h"

using namespace std;

class Red {
private:
    map<string, Enrutador> enrutadores;   // nombre -> enrutador

public:
    Red();

    bool existeEnrutador(const string& nombre) const;

    bool agregarEnrutador(const string& nombre);
    bool eliminarEnrutador(const string& nombre);

    bool agregarEnlace(const string& a, const string& b, int costo);
    bool eliminarEnlace(const string& a, const string& b);

    void actualizarTablas();      //  tablas con destinos directos
    void mostrarRed() const;      // enrutadores y sus vecinos
    void mostrarTablas() const;   // tabla de costos de cada enrutador
};

#endif