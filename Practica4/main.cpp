#include <iostream>
#include "red.h"

int main() {
    Red red;

    // Red de la Figura 1
    red.agregarEnrutador("A");
    red.agregarEnrutador("B");
    red.agregarEnrutador("C");
    red.agregarEnrutador("D");

    red.agregarEnlace("A", "B", 4);
    red.agregarEnlace("A", "C", 10);
    red.agregarEnlace("A", "D", 5);
    red.agregarEnlace("B", "C", 3);
    red.agregarEnlace("B", "D", 1);
    red.agregarEnlace("D", "C", 2);

    red.mostrarRed();
    cout << endl;
    red.mostrarTablas();

    cout << "\n--- Eliminando el enlace A-C ---" << endl;
    red.eliminarEnlace("A", "C");
    red.mostrarRed();

    cout << "\n--- Eliminando el enrutador D ---" << endl;
    red.eliminarEnrutador("D");
    red.mostrarRed();

    return 0;
}