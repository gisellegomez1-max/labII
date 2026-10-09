#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H

unsigned char rotarIzquierda(unsigned char byte, int n);
unsigned char rotarDerecha(unsigned char byte, int n);
unsigned char encriptarByte(unsigned char byte, int n, unsigned char clave);
unsigned char desencriptarByte(unsigned char byte, int n, unsigned char clave);
unsigned char* encriptarDatos(const unsigned char* datos, int longitud, int n, unsigned char clave);
unsigned char* desencriptarDatos(const unsigned char* datos, int longitud, int n, unsigned char clave);

#endif