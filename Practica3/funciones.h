#ifndef RLE_H
#define RLE_H

#include <string>
using namespace std;

//ejercicio 5.1
string comprimirRLE(const string& texto);
string descomprimirRLE(const string& comprimido);

//ejercicio 5.2
struct EntradaDiccionario {
    int prefijo;
    char caracter;
};
struct ParLZ78 {
    int indice;
    char caracter;
    bool esFinal;
};

ParLZ78* comprimirLZ78(const char* texto, int& cantidadPares);
char* descomprimirLZ78(const ParLZ78* pares, int cantidadPares);

//ejercicio 5.3
unsigned char rotarIzquierda(unsigned char byte, int n);
unsigned char rotarDerecha(unsigned char byte, int n);
unsigned char encriptarByte(unsigned char byte, int n, unsigned char clave);
unsigned char desencriptarByte(unsigned char byte, int n, unsigned char clave);
unsigned char* encriptarDatos(const unsigned char* datos, int longitud, int n, unsigned char clave);
unsigned char* desencriptarDatos(const unsigned char* datos, int longitud, int n, unsigned char clave);
#endif