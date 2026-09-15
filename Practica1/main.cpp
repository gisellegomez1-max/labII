#include <iostream>
using namespace std;

void problema2();
void problema4();
void problema6();
void problema8();
void problema10();
void problema12();
void problema14();
void problema16();

int main() {
    int opcion;


        cout << "\n===== MENU =====" << endl;
        cout << "1. Problema 2" << endl;
        cout << "2. Problema 4" << endl;
        cout << "3. Problema 6" << endl;
        cout << "4. Problema 8" << endl;
        cout << "5. Problema 10" << endl;
        cout << "6. Problema 12" << endl;
        cout << "7. Problema 14" << endl;
        cout << "8. Problema 16" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: problema2(); break;
        case 2: problema4(); break;
        case 3: problema6(); break;
        case 4: problema8(); break;
        case 5: problema10(); break;
        case 6: problema12(); break;
        case 7: problema14(); break;
        case 8: problema16(); break;
        default: cout << "Opcion invalida" << endl;
        }


    return 0;
}


void problema2() {

    int efectivo[10] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50};

    long dinero;
    cout << "Ingrese la cantidad de dinero: ";
    cin >> dinero;

    int cantidad[10];

    for (int i = 0; i < 10; i++) {
        cantidad[i] = dinero / efectivo[i];
        dinero = dinero % efectivo[i];
    }

    for (int i = 0; i < 10; i++) {
        cout << efectivo[i] << " : " << cantidad[i] << endl;
    }

    cout << "Faltante: " << dinero << endl;
}

void problema4() {

    int hora, duracion;
    cout << "Ingrese la hora: ";
    cin >> hora;
    cout << "Ingrese la duracion: ";
    cin >> duracion;

    int h1 = hora / 100;
    int m1 = hora % 100;
    int h2 = duracion / 100;
    int m2 = duracion % 100;

    bool valido = true;

    if ( h1 >= 24 || m1 >= 60 || hora < 0) {
        cout << hora << " es un tiempo invalido." << endl;
        valido = false;
    }

    if (m2 >= 60 || duracion < 0) {
        cout << duracion << " es un tiempo invalido." << endl;
        valido = false;
    }

    if (valido==false) {
        return;
    }

    int totalMinutos1 = h1 * 60 + m1;
    int totalMinutos2 = h2 * 60 + m2;

    int suma = totalMinutos1 + totalMinutos2;

    suma = suma % 1440;

    int horaFinal = suma / 60;
    int minutoFinal = suma % 60;

    int resultado = horaFinal * 100 + minutoFinal;

    cout << "La hora es " << resultado << endl;
}


void problema6() {
    int n;
    cout << "Ingrese el numero de elementos: ";
    cin >> n;

    double suma = 0.0;
    double factorial = 1.0;

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            factorial = factorial * i;
        }
        suma = suma + 1.0 / factorial;
    }

    cout << "e es aproximadamente: " << suma << endl;

}

void problema8() {

    int a, b, c;
    cout << "Ingrese a: ";
    cin >> a;
    cout << "Ingrese b: ";
    cin >> b;
    cout << "Ingrese c: ";
    cin >> c;

    long sumatoria = 0;
    string expresion = "";

    for (int i = a; i < c; i = i + a) {
        if (expresion != ""){
            expresion = expresion + " + ";
        }
        expresion = expresion + to_string(i);
        sumatoria = sumatoria + i;
    }


    for (int i = b; i < c; i = i + b) {
        if (i % a != 0) {
            if (expresion != "") {
                expresion = expresion + " + ";
            }
            expresion = expresion + to_string(i);
            sumatoria = sumatoria + i;
        }
    }

    cout << expresion << " = " << sumatoria ;

}

void problema10() {

int n;
cout << "Ingrese n: ";
cin >> n;

int contador = 0;
int numero = 2;
int primo = 0;

while (contador < n) {
    bool esPrimo = true;
    for (int i = 2; i * i <= numero; i++) {
        if (numero % i == 0) {
            esPrimo = false;
            break;
        }
    }

    if (esPrimo) {
        contador++;
        primo = numero;
    }
    numero = numero + 1;
}

cout << "El primo numero " << n << " es: " << primo << endl;

}

void problema12() {

long numero;
cout << "Ingrese un numero: ";
cin >> numero;

long original = numero;
long MayorFactor = 1;

for (long i = 2; i * i <= numero; i += 1) {
    while (numero % i == 0) {
        MayorFactor = i;
        numero /= i;
    }
}

if (numero > 2) {
    MayorFactor = numero;
}

cout << "El mayor factor primo de " << original << " es: " << MayorFactor << endl;

}


void problema14() {

int mejorA = 0, mejorB = 0;
long mejorPalindromo = 0;

for (int i = 999; i >= 100; i--) {

    for (int j = i; j >= 100; j--) {
        long producto = (long)i * j;

        if (producto <= mejorPalindromo) continue;

        long temp = producto;
        long invertido = 0;
        while (temp > 0) {
            invertido = invertido * 10 + temp % 10;
            temp /= 10;
        }

        if (producto == invertido) {
            mejorPalindromo = producto;
            mejorA = i;
            mejorB = j;
        }
    }
}

cout << mejorA << "*" << mejorB << "=" << mejorPalindromo << endl;

}


void problema16() {

    long k;
    cout << "Ingrese k: ";
    cin >> k;

    long mejorSemilla = 1;
    long mejorLargo = 0;

    for (long j = 1; j < k; j++) {
        long n = j;
        long largo = 1;

        while (n != 1) {
            if (n % 2 == 0) {
                n = n / 2;
            } else {
                n = 3 * n + 1;
            }
            largo++;
        }

        if (largo > mejorLargo) {
            mejorLargo = largo;
            mejorSemilla = j;
        }
    }

    cout << "La serie mas larga es con la semilla: " << mejorSemilla
         << ", teniendo " << mejorLargo << " terminos." << endl;

    cout << "Serie: ";
    long n = mejorSemilla;
    cout << n;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        cout << ", " << n;
    }
    cout << endl;
}