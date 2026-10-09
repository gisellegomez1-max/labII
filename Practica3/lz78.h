#ifndef LZ78_H
#define LZ78_H

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

#endif
