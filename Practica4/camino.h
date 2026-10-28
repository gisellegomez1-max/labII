#ifndef CAMINO_H
#define CAMINO_H

#include <string>
#include <list>

using namespace std;

class Camino {
private:
    list<string> nodos;   // enrutadores en orden: origen ... destino
    int costo;            // suma de los costos de los enlaces; -1 si no hay camino

public:
    Camino();                                       // camino vacío (no válido)
    Camino(const list<string>& nodos, int costo);

    const list<string>& getNodos() const;
    int getCosto() const;
    bool esValido() const;                          // true si tiene al menos un nodo
    void mostrar() const;
};

#endif // CAMINO_H