#include "funciones.h"
#include <cctype>
#include <stdexcept>
using namespace std;

//ejercicio 5.1
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

//ejercicio 5.2

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
    int prefijoActual = 0;

    while (texto[i] != '\0') {
        char c = texto[i];
        int encontrado = -1;
        for (int k = 0; k < tamDicc; k++) {
            if (diccionario[k].prefijo == prefijoActual && diccionario[k].caracter == c) {
                encontrado = k + 1;
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

            prefijoActual = 0; // reiniciamos, volvemos a la raiz
            i++;
        }
    }
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

//ejercicio 5.3
unsigned char rotarIzquierda(unsigned char byte, int n) {
    n = n % 8;
    return (unsigned char)((byte << n) | (byte >> (8 - n)));
}

unsigned char rotarDerecha(unsigned char byte, int n) {
    n = n % 8;
    return (unsigned char)((byte >> n) | (byte << (8 - n)));
}


unsigned char encriptarByte(unsigned char byte, int n, unsigned char clave) {
    unsigned char rotado = rotarIzquierda(byte, n);
    return rotado ^ clave;
}

unsigned char desencriptarByte(unsigned char byte, int n, unsigned char clave) {
    // Paso 1: deshacer el XOR (A ^ K ^ K = A)
    unsigned char sinXor = byte ^ clave;
    // Paso 2: deshacer la rotacion, rotando en sentido contrario
    return rotarDerecha(sinXor, n);
}

unsigned char* encriptarDatos(const unsigned char* datos, int longitud, int n, unsigned char clave) {
    if (datos == nullptr || longitud <= 0) {
        throw invalid_argument("Los datos a encriptar son invalidos o estan vacios.");
    }
    if (n <= 0 || n >= 8) {
        throw out_of_range("El valor de rotacion n debe cumplir 0 < n < 8.");
    }

    unsigned char* resultado = new unsigned char[longitud];
    for (int i = 0; i < longitud; i++) {
        resultado[i] = encriptarByte(datos[i], n, clave);
    }
    return resultado;
}

unsigned char* desencriptarDatos(const unsigned char* datos, int longitud, int n, unsigned char clave) {
    if (datos == nullptr || longitud <= 0) {
        throw invalid_argument("Los datos a desencriptar son invalidos o estan vacios.");
    }
    if (n <= 0 || n >= 8) {
        throw out_of_range("El valor de rotacion n debe cumplir 0 < n < 8.");
    }

    unsigned char* resultado = new unsigned char[longitud];
    for (int i = 0; i < longitud; i++) {
        resultado[i] = desencriptarByte(datos[i], n, clave);
    }
    return resultado;
}

