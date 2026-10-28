#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include <list>
#include "enrutador.h"
#include "camino.h"

using namespace std;

class Red {
private:
    map<string, Enrutador> enrutadores;   // nombre -> enrutador

    void dijkstra(const string& origen);  // calcula costos y caminos desde origen

public:
    Red();

    bool existeEnrutador(const string& nombre) const;

    bool agregarEnrutador(const string& nombre);
    bool eliminarEnrutador(const string& nombre);

    bool agregarEnlace(const string& a, const string& b, int costo);
    bool eliminarEnlace(const string& a, const string& b);

    bool cargarDesdeArchivo(const string& ruta);

    void actualizarTablas();
    Camino obtenerCamino(const string& origen, const string& destino) const;
    void mostrarCamino(const string& origen, const string& destino) const;

    void mostrarRed() const;              // enrutadores y sus vecinos
    void mostrarTablas() const;           // tabla de cada enrutador
    bool mostrarTablaDe(const string& nombre) const;   // tabla de uno solo
};

#endif // RED_H