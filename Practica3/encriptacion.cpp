#include "encriptacion.h"
#include <stdexcept>

using namespace std;

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
    // Se deshace en orden inverso: primero el XOR, luego la rotacion.
    unsigned char sinXor = byte ^ clave;
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