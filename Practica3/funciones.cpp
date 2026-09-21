#include "funciones.h"
#include <cctype>
#include <stdexcept>
using namespace std;

string comprimirRLE(const string& texto) {
    if (texto.empty()) {
        throw invalid_argument("El texto a comprimir esta vacio.");
    }

    string resultado = "";
    int contador = 1;

    for (size_t i = 1; i <= texto.size(); i++) {
        if (i < texto.size() && texto[i] == texto[i - 1]) {
            contador++;
        } else {
            resultado += to_string(contador);
            resultado += texto[i - 1];
            contador = 1;
        }
    }

    return resultado;
}

string descomprimirRLE(const string& comprimido) {
    if (comprimido.empty()) {
        throw invalid_argument("El texto comprimido esta vacio.");
    }

    string resultado = "";
    size_t i = 0;

    while (i < comprimido.size()) {
        string numStr = "";
        while (i < comprimido.size() && isdigit(comprimido[i])) {
            numStr += comprimido[i];
            i++;
        }

        if (numStr.empty()) {
            throw runtime_error("Formato invalido: se esperaba un numero antes del caracter.");
        }

        if (i >= comprimido.size()) {
            throw runtime_error("Formato invalido: falta el caracter luego del numero.");
        }

        int repeticiones = stoi(numStr);
        char c = comprimido[i];
        i++;

        for (int j = 0; j < repeticiones; j++) {
            resultado += c;
        }
    }

    return resultado;
}