#include <iostream>
#include "funciones.h"
using namespace std;

void calcularCombinacion(int *denominaciones, int *cantidades, int n, int *dinero) {
    for (int i = 0; i < n; i++) {
        *(cantidades + i) = *dinero / *(denominaciones + i);
        *dinero = *dinero % *(denominaciones + i);
    }
}
void imprimirResultado(int *denominaciones, int *cantidades, int n, int *dinero) {
    for (int i = 0; i < n; i++) {
        cout << *(denominaciones + i) << " : " << *(cantidades + i) << endl;
    }
    if (*dinero > 0) {
        cout << "Faltante: " << *dinero << endl;
    }
}


bool compararCadenas(const char *cad1, const char *cad2) {
    const char *p1 = cad1;
    const char *p2 = cad2;
    int len1 = 0, len2 = 0;

    while (*p1 != '\0') {
        len1++;
        p1++;
    }
    while (*p2 != '\0') {
        len2++;
        p2++;
    }
    if (len1 != len2) {
        return false;
    }

    p1 = cad1;
    p2 = cad2;

    while (*p1 != '\0') {
        if (*p1 != *p2) {
            return false;
        }
        p1++;
        p2++;
    }

    return true;
}


void intACadena(int numero, char *cadena) {
    int i = 0; // indice para escribir en 'cadena'
    bool esNegativo = false;

    if (numero == 0) {
        *(cadena + i) = '0';
        i++;
        *(cadena + i) = '\0';
        return;
    }

    if (numero < 0) {
        esNegativo = true;
        numero = -numero;
    }

    char temp[12];
    int j = 0;

    while (numero > 0) {
        int digito = numero % 10;
        temp[j] = digito + '0';
        j++;
        numero = numero / 10;
    }

    if (esNegativo) {
        *(cadena + i) = '-';
        i++;
    }

    while (j > 0) {
        j--;
        *(cadena + i) = temp[j];
        i++;
    }
    *(cadena + i) = '\0';
}


void eliminarRepetidos(const char *original, char *resultado) {
    const char *p = original;
    int i = 0;

    while (*p != '\0') {
        bool yaExiste = false;

        for (int k = 0; k < i; k++) {
            if (*(resultado + k) == *p) {
                yaExiste = true;
                break;
            }
        }
        if (!yaExiste) {
            *(resultado + i) = *p;
            i++;
        }
        p++;
    }

    *(resultado + i) = '\0';
}

long sumarPorGrupos(const char *cadena, int n) {
    const char *p = cadena;
    int len = 0;
    while (*p != '\0') {
        len++;
        p++;
    }

    int resto = len % n;
    long suma = 0;

    const char *ptr = cadena;


    if (resto != 0) {
        long numero = 0;
        for (int i = 0; i < resto; i++) {
            numero = numero * 10 + (*ptr - '0'); // acumulamos digito a digito
            ptr++;
        }
        suma += numero;
    }
    while (*ptr != '\0') {
        long numero = 0;
        for (int i = 0; i < n; i++) {
            numero = numero * 10 + (*ptr - '0');
            ptr++;
        }
        suma += numero;
    }

    return suma;
}

void inicializarSala(char sala[][COLUMNAS]) {
    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLUMNAS; c++) {
            // sala[f] es un puntero a la fila f (un arreglo de COLUMNAS chars)
            // *(sala[f] + c) equivale a sala[f][c]
            *(sala[f] + c) = DISPONIBLE;
        }
    }
}

void mostrarSala(char sala[][COLUMNAS]) {
    // Encabezado con el numero de cada asiento (1-20)
    cout << "     ";
    for (int c = 1; c <= COLUMNAS; c++) {
        cout << (c < 10 ? "  " : " ") << c << " ";
    }
    cout << endl;

    // Linea de borde superior: "    +----+----+...+"
    auto imprimirBorde = [&]() {
        cout << "    +";
        for (int c = 0; c < COLUMNAS; c++) {
            cout << "----+";
        }
        cout << endl;
    };

    imprimirBorde();
    for (int f = 0; f < FILAS; f++) {
        char letraFila = 'A' + f; // convertir indice de fila a letra
        cout << " " << letraFila << "  |";
        for (int c = 0; c < COLUMNAS; c++) {
            // *(sala[f] + c) equivale a sala[f][c]
            cout << "  " << *(sala[f] + c) << " |";
        }
        cout << endl;
        imprimirBorde(); // borde despues de cada fila, como en el ejemplo
    }
}

bool reservarAsiento(char sala[][COLUMNAS], char filaLetra, int asiento) {
    int f = filaLetra - 'A'; // convertir letra a indice de fila
    int c = asiento - 1;     // convertir numero de asiento a indice de columna

    // Validar que la fila y el asiento esten dentro del rango permitido
    if (f < 0 || f >= FILAS || c < 0 || c >= COLUMNAS) {
        return false;
    }

    // Solo se puede reservar si esta disponible
    if (*(sala[f] + c) == DISPONIBLE) {
        *(sala[f] + c) = RESERVADO;
        return true;
    }

    return false; // ya estaba reservado
}

bool cancelarAsiento(char sala[][COLUMNAS], char filaLetra, int asiento) {
    int f = filaLetra - 'A';
    int c = asiento - 1;

    if (f < 0 || f >= FILAS || c < 0 || c >= COLUMNAS) {
        return false;
    }

    // Solo se puede cancelar si estaba reservado
    if (*(sala[f] + c) == RESERVADO) {
        *(sala[f] + c) = DISPONIBLE;
        return true;
    }

    return false; // ya estaba disponible
}


