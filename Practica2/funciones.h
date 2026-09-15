#ifndef FUNCIONES_H
#define FUNCIONES_H

void calcularCombinacion(int *denominaciones, int *cantidades, int n, int *dinero);
void imprimirResultado(int *denominaciones, int *cantidades, int n, int *dinero);

bool compararCadenas(const char *cad1, const char *cad2);

void intACadena(int numero, char *cadena);

void eliminarRepetidos(const char *original, char *resultado);

long sumarPorGrupos(const char *cadena, int n);

const int FILAS = 15;
const int COLUMNAS = 20;
const char DISPONIBLE = '-';
const char RESERVADO = '+';
void inicializarSala(char sala[][COLUMNAS]);
void mostrarSala(char sala[][COLUMNAS]);
bool reservarAsiento(char sala[][COLUMNAS], char filaLetra, int asiento);
bool cancelarAsiento(char sala[][COLUMNAS], char filaLetra, int asiento);


#endif