#include <iostream>
#include <sstream>
#include "red.h"

using namespace std;

// Lee una línea completa (evita ciclos infinitos con entradas inválidas)
string leerLinea(const string& mensaje) {
    string linea;
    cout << mensaje;
    getline(cin, linea);
    return linea;
}

// Lee la primera palabra de una línea
string leerPalabra(const string& mensaje) {
    istringstream ss(leerLinea(mensaje));
    string palabra;
    ss >> palabra;
    return palabra;
}

// Lee un entero; devuelve false si lo escrito no es un número
bool leerEntero(const string& mensaje, int& valor) {
    istringstream ss(leerLinea(mensaje));
    return !(ss >> valor).fail();
}

void mostrarMenu() {
    cout << "\n===== SIMULADOR DE RED =====" << endl;
    cout << "1. Cargar red desde archivo" << endl;
    cout << "2. Agregar enrutador" << endl;
    cout << "3. Eliminar enrutador" << endl;
    cout << "4. Agregar enlace (o cambiar su costo)" << endl;
    cout << "5. Eliminar enlace" << endl;
    cout << "6. Mostrar red" << endl;
    cout << "7. Mostrar tablas de todos los enrutadores" << endl;
    cout << "8. Mostrar tabla de un enrutador" << endl;
    cout << "9. Camino y costo entre dos enrutadores" << endl;
    cout << "0. Salir" << endl;
}

int main() {
    Red red;
    int opcion = -1;

    do {
        mostrarMenu();
        if (!leerEntero("Opcion: ", opcion)) {
            if (!cin) break;            // fin de entrada
            opcion = -1;
        }

        string a, b;
        int costo;

        switch (opcion) {
        case 1:
            a = leerLinea("Ruta del archivo: ");
            if (red.cargarDesdeArchivo(a)) cout << "Red cargada." << endl;
            else cout << "No se pudo abrir el archivo." << endl;
            break;
        case 2:
            a = leerPalabra("Nombre del enrutador: ");
            if (red.agregarEnrutador(a)) cout << "Enrutador agregado." << endl;
            else cout << "No se pudo agregar (repetido o invalido)." << endl;
            break;
        case 3:
            a = leerPalabra("Nombre del enrutador: ");
            if (red.eliminarEnrutador(a)) cout << "Enrutador eliminado." << endl;
            else cout << "El enrutador no existe." << endl;
            break;
        case 4:
            a = leerPalabra("Enrutador 1: ");
            b = leerPalabra("Enrutador 2: ");
            if (!leerEntero("Costo: ", costo)) {
                cout << "Costo invalido." << endl;
            } else if (red.agregarEnlace(a, b, costo)) {
                cout << "Enlace creado/actualizado." << endl;
            } else {
                cout << "No se pudo crear el enlace (revisa nombres y costo > 0)." << endl;
            }
            break;
        case 5:
            a = leerPalabra("Enrutador 1: ");
            b = leerPalabra("Enrutador 2: ");
            if (red.eliminarEnlace(a, b)) cout << "Enlace eliminado." << endl;
            else cout << "No se pudo eliminar el enlace." << endl;
            break;
        case 6:
            red.mostrarRed();
            break;
        case 7:
            red.mostrarTablas();
            break;
        case 8:
            a = leerPalabra("Enrutador: ");
            if (!red.mostrarTablaDe(a)) cout << "El enrutador no existe." << endl;
            break;
        case 9:
            a = leerPalabra("Origen: ");
            b = leerPalabra("Destino: ");
            red.mostrarCamino(a, b);
            break;
        case 0:
            cout << "Hasta luego." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);

    return 0;
}