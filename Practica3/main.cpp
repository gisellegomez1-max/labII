#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include "funciones.h"
using namespace std;

const int MAX = 1000;

int main() {
    int opcion = -1;

    while (opcion != 4) {
        cout << "\n========== MENU ==========" << endl;
        cout << "1. Probar RLE (comprimir/descomprimir)" << endl;
        cout << "2. Probar LZ78 (comprimir/descomprimir)" << endl;
        cout << "3. Probar Encriptacion (rotacion + XOR)" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            // El usuario ingreso algo que no es un numero
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida, intente de nuevo." << endl;
            continue;
        }

        try {
            switch (opcion) {

            case 1: { //
                string original;
                cout << "\nIngrese el texto a comprimir: ";
                cin.ignore(); // limpiar el salto de linea pendiente
                getline(cin, original);

                string comprimido = comprimirRLE(original);
                cout << "Texto original:      " << original << endl;
                cout << "Texto comprimido:    " << comprimido << endl;

                string descomprimido = descomprimirRLE(comprimido);
                cout << "Texto descomprimido: " << descomprimido << endl;

                cout << (descomprimido == original
                             ? "Coincide con el original."
                             : "No coincide.")
                     << endl;
                break;
            }

            case 2: { //
                char texto[MAX];
                cout << "\nIngrese el texto a comprimir: ";
                cin.ignore();
                cin.getline(texto, MAX);

                int cantidadPares = 0;
                ParLZ78* pares = comprimirLZ78(texto, cantidadPares);

                cout << "Texto original: " << texto << endl;
                cout << "Pares generados (indice, caracter):" << endl;
                for (int i = 0; i < cantidadPares; i++) {
                    if (pares[i].esFinal) {
                        cout << "  (" << pares[i].indice << ")" << endl;
                    } else {
                        cout << "  (" << pares[i].indice << ", '"
                             << pares[i].caracter << "')" << endl;
                    }
                }

                char* reconstruido = descomprimirLZ78(pares, cantidadPares);
                cout << "Texto reconstruido: " << reconstruido << endl;

                cout << (strcmp(texto, reconstruido) == 0
                             ? "Coincide con el original."
                             : "No coincide.")
                     << endl;

                delete[] pares;
                delete[] reconstruido;
                break;
            }

            case 3: {
                char texto[MAX];
                cout << "\nIngrese el texto a encriptar: ";
                cin.ignore();
                cin.getline(texto, MAX);

                int n;
                cout << "Ingrese el valor de rotacion n (0 < n < 8): ";
                cin >> n;

                int claveInt;
                cout << "Ingrese la clave K (0-255): ";
                cin >> claveInt;
                unsigned char clave = (unsigned char)claveInt;

                int longitud = strlen(texto);
                unsigned char* datos = (unsigned char*)texto;

                unsigned char* encriptado = encriptarDatos(datos, longitud, n, clave);
                cout << "Datos encriptados (hex): ";
                for (int i = 0; i < longitud; i++) {
                    cout << hex << setw(2) << setfill('0') << (int)encriptado[i] << " ";
                }
                cout << dec << endl;

                unsigned char* desencriptado = desencriptarDatos(encriptado, longitud, n, clave);
                cout << "Texto desencriptado: ";
                for (int i = 0; i < longitud; i++) cout << (char)desencriptado[i];
                cout << endl;

                bool coincide = true;
                for (int i = 0; i < longitud; i++) {
                    if (desencriptado[i] != datos[i]) { coincide = false; break; }
                }
                cout << (coincide ? "Coincide con el original." : "No coincide.") << endl;

                delete[] encriptado;
                delete[] desencriptado;
                break;
            }

            case 4:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opcion invalida, intente de nuevo." << endl;
            }
        } catch (const exception& e) {
            cerr << "Ocurrio un error: " << e.what() << endl;
        }
    }

    return 0;
}