#include <iostream>
#include "funciones.h"

using namespace std;

int main()
{

    cout << "======MENU======" << endl;
    cout << "1. Problema 1"<< endl;
    cout << "2. Problema 3"<< endl;
    cout << "3. Problema 5"<< endl;
    cout << "4. Problema 7"<< endl;
    cout << "5. Problema 9"<< endl;
    cout << "6. Problema 11"<< endl;
    cout << "7. Problema 13"<< endl;
    cout << "8. Problema 15"<< endl;
    cout << "9. Problema 17"<< endl;

    int opcion;
    cout << "Ingrese la opcion deseada: ";
    cin >> opcion;

    switch (opcion) {
    case 1:{
        const int N = 10;
        int denominaciones[N] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50};
        int cantidades[N] = {0};

        int dinero;
        cout << "Ingrese la cantidad de dinero: ";
        cin >> dinero;

        int *pdinero = &dinero;

        calcularCombinacion(denominaciones, cantidades, N, pdinero);
        imprimirResultado(denominaciones, cantidades, N, pdinero);

        return 0;
    }
    case 2:{
        const int tam = 100;
        char cadena1[tam];
        char cadena2[tam];

        cout << "Ingrese la primera cadena: ";
        cin >> cadena1;
        cout << "Ingrese la segunda cadena: ";
        cin >> cadena2;

        bool sonIguales = compararCadenas(cadena1, cadena2);

        if (sonIguales) {
            cout << "Las cadenas son iguales" << endl;
        } else {
            cout << "Las cadenas son diferentes" << endl;
        }

        break;
    }
    case 3:{
        int numero;
        cout << "Ingrese un numero entero: ";
        cin >> numero;

        char resultado[12];

        intACadena(numero, resultado);

        cout << "El numero " << numero << " convertido a cadena es: \"" << resultado << "\"" << endl;

        break;
    }
    case 4:{
        const int TAM = 100;
        char original[TAM];
        char resultado[TAM];

        cout << "Ingrese una cadena: ";
        cin >> original;

        eliminarRepetidos(original, resultado);

        cout << "Original: " << original << ". Sin repetidos: " << resultado << "." << endl;

        break;
    }
    case 5:{
        const int TAM = 100;
        char cadena[TAM];
        int n;

        cout << "Ingrese el numero de cifras por grupo (n): ";
        cin >> n;
        cout << "Ingrese la cadena de caracteres numericos: ";
        cin >> cadena;

        long suma = sumarPorGrupos(cadena, n);

        cout << "original: " << cadena << endl;
        cout << "Suma: " << suma << endl;

        break;
    }
    case 6:{
        char sala[FILAS * COLUMNAS];
        inicializarSala(sala);

        int opcion;
        do {
            cout << "\n--- SALA DE CINE ---" << endl;
            cout << "1. Mostrar sala" << endl;
            cout << "2. Reservar asiento" << endl;
            cout << "3. Cancelar reserva" << endl;
            cout << "4. Salir" << endl;
            cout << "Opcion: ";
            cin >> opcion;

            if (opcion == 1) {
                mostrarSala(sala);

            } else if (opcion == 2) {
                char fila;
                int asiento;
                cout << "Fila (A-O): ";
                cin >> fila;
                fila = toupper(fila);
                cout << "Asiento (1-20): ";
                cin >> asiento;

                if (!asientoValido(fila, asiento)) {
                    cout << "Dato invalido: la fila debe ser A-O y el asiento 1-20." << endl;
                } else if (reservarAsiento(sala, fila, asiento)) {
                    cout << "Asiento " << fila << asiento << " reservado con exito." << endl;
                } else {
                    cout << "El asiento " << fila << asiento << " ya estaba reservado." << endl;
                }

            } else if (opcion == 3) {
                char fila;
                int asiento;
                cout << "Fila (A-O): ";
                cin >> fila;
                fila = toupper(fila);
                cout << "Asiento (1-20): ";
                cin >> asiento;

                if (!asientoValido(fila, asiento)) {
                    cout << "Dato invalido: la fila debe ser A-O y el asiento 1-20." << endl;
                } else if (cancelarAsiento(sala, fila, asiento)) {
                    cout << "Reserva del asiento " << fila << asiento << " cancelada." << endl;
                } else {
                    cout << "El asiento " << fila << asiento << " ya estaba disponible." << endl;
                }
            }

        } while (opcion != 4);

        break;
    }

    case 7:{
        const int FILAS_IMG = 6;
        const int COLUMNAS_IMG = 8;

        int imagen[FILAS_IMG][COLUMNAS_IMG] = {
            {0, 3, 4, 0, 0, 0, 6, 8},
            {5, 13, 6, 0, 0, 0, 2, 3},
            {2, 6, 2, 7, 3, 0, 10, 0},
            {0, 0, 4, 15, 4, 1, 6, 0},
            {0, 0, 7, 12, 6, 9, 10, 4},
            {5, 0, 6, 10, 6, 4, 8, 0}
        };

        int estrellas = contarEstrellas(&imagen[0][0], FILAS_IMG, COLUMNAS_IMG);

        cout << "Numero de estrellas encontradas: " << estrellas << endl;

        break;
    }
    case 8: {
        int A[4], B[4], C[4];

        cout << "Rectangulo A" << endl;
        cout << "  x: "; cin >> A[0];
        cout << "  y: "; cin >> A[1];
        cout << "  ancho: "; cin >> A[2];
        cout << "  alto: "; cin >> A[3];

        cout << "Rectangulo B" << endl;
        cout << "  x: "; cin >> B[0];
        cout << "  y: "; cin >> B[1];
        cout << "  ancho: "; cin >> B[2];
        cout << "  alto: "; cin >> B[3];

        bool hayInterseccion = intersectarRectangulos(A, B, C);

        if (hayInterseccion) {
            cout << "Interseccion C = {" << C[0] << ", " << C[1] << ", "
                 << C[2] << ", " << C[3] << "}" << endl;
        } else {
            cout << "Los rectangulos no se intersectan." << endl;
        }

        break;
    }
    case 9:{
        int numero;
        cout << "Ingrese un numero: ";
        cin >> numero;

        long resultado;
        long *pResultado = &resultado;

        sumaAmigables(numero, pResultado);

        cout << "El resultado de la suma es: " << *pResultado << "." << endl;

        break;
    }
    default:
        cout << "Ingresaste una opcion invalida";
    }
 return 0;
}
