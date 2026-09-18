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
void inicializarSala(char *sala);
void mostrarSala(char *sala);
bool reservarAsiento(char *sala, char filaLetra, int asiento);
bool cancelarAsiento(char *sala, char filaLetra, int asiento);
bool asientoValido(char filaLetra, int asiento);

int contarEstrellas(int *matriz, int filas, int columnas);

bool intersectarRectangulos(const int *A, const int *B, int *C);

long sumaDivisores(int n);
void sumaAmigables(int limite, long *resultado);

#endif