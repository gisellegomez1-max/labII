#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>
#include <list>

using namespace std;

class Enrutador {
private:
    string nombre;                            // identificador del enrutador
    map<string, int> vecinos;                 // vecino -> costo del enlace directo
    map<string, int> tablaCostos;             // destino -> costo mínimo
    map<string, list<string> > tablaCaminos;  // destino -> camino completo

public:
    Enrutador();                              // necesario para map<string, Enrutador>
    Enrutador(const string& nombre);

    string getNombre() const;
    const map<string, int>& getVecinos() const;
    const map<string, int>& getTablaCostos() const;

    void agregarVecino(const string& vecino, int costo);
    void eliminarVecino(const string& vecino);

    void actualizarCosto(const string& destino, int costo);
    int getCosto(const string& destino) const;   // -1 si el destino no está en la tabla

    void actualizarCamino(const string& destino, const list<string>& camino);
    list<string> getCamino(const string& destino) const;   // vacía si no hay camino

    void mostrarTabla() const;
    void reiniciarTabla();   // deja solo: costo 0 a sí mismo + vecinos directos
};

#endif // ENRUTADOR_H