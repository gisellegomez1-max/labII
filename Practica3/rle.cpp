#include "rle.h"
#include <string>
#include <cstring>
#include <cctype>
#include <stdexcept>

using namespace std;

const char ESCAPE = '\\';

static char* copiarArreglo(const string& s) {
    char* resultado = new char[s.size() + 1];
    memcpy(resultado, s.c_str(), s.size() + 1);
    return resultado;
}

char* comprimirRLE(const char* texto) {
    if (texto == nullptr || texto[0] == '\0') {
        throw invalid_argument("El texto a comprimir esta vacio.");
    }

    string original(texto);
    string resultado = "";
    int contador = 1;

    for (size_t i = 1; i <= original.size(); i++) {
        if (i < original.size() && original[i] == original[i - 1]) {
            contador++;
        } else {
            char c = original[i - 1];
            resultado += to_string(contador);
            // El caracter se escapa si se puede confundir con un contador
            if (isdigit((unsigned char)c) || c == ESCAPE) {
                resultado += ESCAPE;
            }
            resultado += c;
            contador = 1;
        }
    }

    return copiarArreglo(resultado);
}

char* descomprimirRLE(const char* comprimidoC) {
    if (comprimidoC == nullptr || comprimidoC[0] == '\0') {
        throw invalid_argument("El texto comprimido esta vacio.");
    }

    string comprimido(comprimidoC);
    string resultado = "";
    size_t i = 0;

    while (i < comprimido.size()) {
        // Leer el contador (todos los digitos seguidos)
        string numStr = "";
        while (i < comprimido.size() && isdigit((unsigned char)comprimido[i])) {
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

        if (repeticiones <= 0) {
            throw runtime_error("Formato invalido: el contador debe ser mayor que 0.");
        }

        // Leer el caracter, si viene escapado se toma el siguiente tal cual
        char c = comprimido[i];
        if (c == ESCAPE) {
            i++;
            if (i >= comprimido.size()) {
                throw runtime_error("Formato invalido: falta el caracter luego del escape.");
            }
            c = comprimido[i];
        }
        i++;

        // Repetir el caracter
        for (int j = 0; j < repeticiones; j++) {
            resultado += c;
        }
    }

    return copiarArreglo(resultado);
}