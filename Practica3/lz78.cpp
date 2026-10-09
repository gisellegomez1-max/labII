#include "lz78.h"
#include <stdexcept>

using namespace std;

// Duplica la capacidad del arreglo dinamico del diccionario.
static void crecerDiccionario(EntradaDiccionario*& diccionario, int& capacidad) {
    int nuevaCapacidad = capacidad * 2;
    EntradaDiccionario* nuevo = new EntradaDiccionario[nuevaCapacidad];
    for (int j = 0; j < capacidad; j++) {
        nuevo[j] = diccionario[j];
    }
    delete[] diccionario;
    diccionario = nuevo;
    capacidad = nuevaCapacidad;
}

// Duplica la capacidad del arreglo dinamico de pares de salida.
static void crecerPares(ParLZ78*& pares, int& capacidad) {
    int nuevaCapacidad = capacidad * 2;
    ParLZ78* nuevo = new ParLZ78[nuevaCapacidad];
    for (int j = 0; j < capacidad; j++) {
        nuevo[j] = pares[j];
    }
    delete[] pares;
    pares = nuevo;
    capacidad = nuevaCapacidad;
}

ParLZ78* comprimirLZ78(const char* texto, int& cantidadPares) {
    if (texto == nullptr || texto[0] == '\0') {
        throw invalid_argument("El texto a comprimir esta vacio.");
    }

    int capacidadDicc = 4;
    int tamDicc = 0;
    EntradaDiccionario* diccionario = new EntradaDiccionario[capacidadDicc];

    int capacidadPares = 4;
    cantidadPares = 0;
    ParLZ78* pares = new ParLZ78[capacidadPares];

    int i = 0;
    int prefijoActual = 0; // 0 = cadena vacia

    while (texto[i] != '\0') {
        char c = texto[i];

        // Busqueda lineal de (prefijoActual, c) en el diccionario
        int encontrado = -1;
        for (int k = 0; k < tamDicc; k++) {
            if (diccionario[k].prefijo == prefijoActual && diccionario[k].caracter == c) {
                encontrado = k + 1; // indices 1-based
                break;
            }
        }

        if (encontrado != -1) {
            prefijoActual = encontrado;
            i++;
        } else {
            if (cantidadPares == capacidadPares) {
                crecerPares(pares, capacidadPares);
            }
            pares[cantidadPares].indice = prefijoActual;
            pares[cantidadPares].caracter = c;
            pares[cantidadPares].esFinal = false;
            cantidadPares++;

            if (tamDicc == capacidadDicc) {
                crecerDiccionario(diccionario, capacidadDicc);
            }
            diccionario[tamDicc].prefijo = prefijoActual;
            diccionario[tamDicc].caracter = c;
            tamDicc++;

            prefijoActual = 0;
            i++;
        }
    }

    // El texto termino en medio de una coincidencia: se emite solo el indice.
    if (prefijoActual != 0) {
        if (cantidadPares == capacidadPares) {
            crecerPares(pares, capacidadPares);
        }
        pares[cantidadPares].indice = prefijoActual;
        pares[cantidadPares].caracter = '\0';
        pares[cantidadPares].esFinal = true;
        cantidadPares++;
    }

    delete[] diccionario;
    return pares;
}

char* descomprimirLZ78(const ParLZ78* pares, int cantidadPares) {
    if (pares == nullptr || cantidadPares <= 0) {
        throw invalid_argument("No hay pares para descomprimir.");
    }

    int capacidadDicc = 4;
    int tamDicc = 0;
    EntradaDiccionario* diccionario = new EntradaDiccionario[capacidadDicc];

    char** frases = new char*[cantidadPares];
    int longitudTotal = 0;

    for (int p = 0; p < cantidadPares; p++) {
        int idx = pares[p].indice;

        if (idx < 0 || idx > tamDicc) {
            for (int j = 0; j < p; j++) delete[] frases[j];
            delete[] frases;
            delete[] diccionario;
            throw runtime_error("Indice invalido en los datos comprimidos (diccionario corrupto).");
        }

        int longFrase = 0;
        int temp = idx;
        while (temp != 0) {
            longFrase++;
            temp = diccionario[temp - 1].prefijo;
        }

        bool tieneCaracterNuevo = !pares[p].esFinal;
        int longTotalFrase = longFrase + (tieneCaracterNuevo ? 1 : 0);

        char* frase = new char[longTotalFrase + 1];
        frase[longTotalFrase] = '\0';

        int pos = longTotalFrase - 1;
        if (tieneCaracterNuevo) {
            frase[pos] = pares[p].caracter;
            pos--;
        }

        temp = idx;
        while (temp != 0) {
            frase[pos] = diccionario[temp - 1].caracter;
            pos--;
            temp = diccionario[temp - 1].prefijo;
        }

        frases[p] = frase;
        longitudTotal += longTotalFrase;

        if (tieneCaracterNuevo) {
            if (tamDicc == capacidadDicc) {
                crecerDiccionario(diccionario, capacidadDicc);
            }
            diccionario[tamDicc].prefijo = idx;
            diccionario[tamDicc].caracter = pares[p].caracter;
            tamDicc++;
        }
    }
    char* resultado = new char[longitudTotal + 1];
    int posGlobal = 0;
    for (int p = 0; p < cantidadPares; p++) {
        int len = 0;
        while (frases[p][len] != '\0') len++;
        for (int k = 0; k < len; k++) {
            resultado[posGlobal] = frases[p][k];
            posGlobal++;
        }
        delete[] frases[p];
    }
    resultado[posGlobal] = '\0';

    delete[] frases;
    delete[] diccionario;

    return resultado;
}
