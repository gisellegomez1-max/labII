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
        char sala[FILAS][COLUMNAS];
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

                if (reservarAsiento(sala, fila, asiento)) {
                    cout << "Asiento " << fila << asiento << " reservado con exito." << endl;
                } else {
                    cout << "No se pudo reservar (dato invalido o ya reservado)." << endl;
                }

            } else if (opcion == 3) {
                char fila;
                int asiento;
                cout << "Fila (A-O): ";
                cin >> fila;
                fila = toupper(fila);
                cout << "Asiento (1-20): ";
                cin >> asiento;

                if (cancelarAsiento(sala, fila, asiento)) {
                    cout << "Reserva del asiento " << fila << asiento << " cancelada." << endl;
                } else {
                    cout << "No se pudo cancelar (dato invalido o ya estaba disponible)." << endl;
                }
            }

        } while (opcion != 4);

        break;
    }
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    default:
        cout << "Ingresaste una opcion invalida";
    }
 return 0;
}
