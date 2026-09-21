#include <iostream>
#include <iomanip>
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
            numero = numero * 10 + (*ptr - '0');
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

void inicializarSala(char *sala) {
    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLUMNAS; c++) {
            *(sala + f * COLUMNAS + c) = DISPONIBLE;
        }
    }
}

void mostrarSala(char *sala) {
    cout << "    ";
    for (int c = 1; c <= COLUMNAS; c++) {
        cout << setw(3) << c;
    }
    cout << endl;

    auto imprimirBorde = [&]() {
        cout << "   +";
        for (int c = 0; c < COLUMNAS; c++) {
            cout << "--+";
        }
        cout << endl;
    };

    imprimirBorde();
    for (int f = 0; f < FILAS; f++) {
        char letraFila = 'A' + f;
        cout << " " << letraFila << " |";
        for (int c = 0; c < COLUMNAS; c++) {
            cout << *(sala + f * COLUMNAS + c) << " |";
        }
        cout << endl;
    }
    imprimirBorde();
}

bool asientoValido(char filaLetra, int asiento) {
    int f = filaLetra - 'A';
    int c = asiento - 1;
    return (f >= 0 && f < FILAS && c >= 0 && c < COLUMNAS);
}

bool reservarAsiento(char *sala, char filaLetra, int asiento) {
    if (!asientoValido(filaLetra, asiento)) {
        return false;
    }

    int f = filaLetra - 'A';
    int c = asiento - 1;
    int indice = f * COLUMNAS + c;

    if (*(sala + indice) == DISPONIBLE) {
        *(sala + indice) = RESERVADO;
        cout<< &sala + indice;
        return true;
    }

    return false;
}

bool cancelarAsiento(char *sala, char filaLetra, int asiento) {
    if (!asientoValido(filaLetra, asiento)) {
        return false;
    }

    int f = filaLetra - 'A';
    int c = asiento - 1;
    int indice = f * COLUMNAS + c;

    if (*(sala + indice) == RESERVADO) {
        *(sala + indice) = DISPONIBLE;
        return true;
    }

    return false;
}

int contarEstrellas(int *matriz, int filas, int columnas) {
    int contador = 0;

    for (int i = 1; i < filas - 1; i++) {
        for (int j = 1; j < columnas - 1; j++) {
            int centro = *(matriz + i * columnas + j);
            int arriba  = *(matriz + (i - 1) * columnas + j);
            int abajo   = *(matriz + (i + 1) * columnas + j);
            int izq     = *(matriz + i * columnas + (j - 1));
            int der     = *(matriz + i * columnas + (j + 1));

            double promedio = (centro + izq + der + arriba + abajo) / 5.0;

            if (promedio > 6) {
                contador++;
            }
        }
    }

    return contador;
}

bool intersectarRectangulos(const int *A, const int *B, int *C) {
    int xA = *(A + 0), yA = *(A + 1), wA = *(A + 2), hA = *(A + 3);
    int xB = *(B + 0), yB = *(B + 1), wB = *(B + 2), hB = *(B + 3);

    int x1 = (xA > xB) ? xA : xB;
    int y1 = (yA > yB) ? yA : yB;

    int x2 = (xA + wA < xB + wB) ? (xA + wA) : (xB + wB);
    int y2 = (yA + hA < yB + hB) ? (yA + hA) : (yB + hB);

    if (x2 > x1 && y2 > y1) {
        *(C + 0) = x1;
        *(C + 1) = y1;
        *(C + 2) = x2 - x1;
        *(C + 3) = y2 - y1;
        return true;
    }

    *(C + 0) = 0;
    *(C + 1) = 0;
    *(C + 2) = 0;
    *(C + 3) = 0;
    return false;
}

long sumaDivisores(int n) {
    if (n <= 1) {
        return 0;
    }

    long suma = 1;

    for (int d = 2; (long)d * d <= n; d++) {
        if (n % d == 0) {
            suma += d;
            int otro = n / d;
            if (otro != d) {
                suma += otro;
            }
        }
    }

    return suma;
}

void sumaAmigables(int limite, long *resultado) {
    *resultado = 0;

    for (int a = 2; a < limite; a++) {
        long b = sumaDivisores(a);

        if (b != a && b >= 2 && sumaDivisores((int)b) == a) {
            *resultado += a;
        }
    }
}


