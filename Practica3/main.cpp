#include <iostream>
#include <string>
#include "funciones.h"

using namespace std;

int main() {
    try {
        string original;
        cout << "Ingrese el texto a comprimir: ";
        getline(cin, original);

        string comprimido = comprimirRLE(original);
        cout << "\nTexto original:    " << original << endl;
        cout << "Texto comprimido:  " << comprimido << endl;

        string descomprimido = descomprimirRLE(comprimido);
        cout << "Texto descomprimido: " << descomprimido << endl;

        if (descomprimido == original) {
            cout << "\n[OK] La descompresion coincide con el texto original." << endl;
        } else {
            cout << "\n[ERROR] La descompresion NO coincide con el original." << endl;
        }

    } catch (const exception& e) {
        cerr << "Ocurrio un error: " << e.what() << endl;
        return 1;
    }

    return 0;
}