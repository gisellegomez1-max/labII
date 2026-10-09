#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include "rle.h"
#include "lz78.h"
#include "encriptacion.h"

using namespace std;

const int MAX = 1000;       // tamano de buffer para entrada por teclado
const int MAX_RUTA = 256;   // tamano maximo de una ruta de archivo

int main() {
    int opcion = -1;

    while (opcion != 5) {
        cout << "\n========== PRACTICA 3 - MENU ==========" << endl;
        cout << "1. Probar RLE (comprimir/descomprimir)" << endl;
        cout << "2. Probar LZ78 (comprimir/descomprimir)" << endl;
        cout << "3. Probar Encriptacion (rotacion + XOR)" << endl;
        cout << "4. Integracion completa (leer archivo, comprimir, encriptar, verificar)" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            // El usuario ingreso algo que no es un numero
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = -1;
            cout << "Opcion invalida, intente de nuevo." << endl;
            continue;
        }

        try {
            switch (opcion) {

            case 1: { //  5.1 RLE
                char texto[MAX];
                cout << "\nIngrese el texto a comprimir: ";
                cin.ignore(); // limpiar el salto de linea pendiente
                cin.getline(texto, MAX);

                char* comprimido = comprimirRLE(texto);
                cout << "Texto original:      " << texto << endl;
                cout << "Texto comprimido:    " << comprimido << endl;

                char* descomprimido = descomprimirRLE(comprimido);
                cout << "Texto descomprimido: " << descomprimido << endl;

                cout << (strcmp(texto, descomprimido) == 0
                             ? "[OK] Coincide con el original."
                             : "[ERROR] No coincide.")
                     << endl;

                delete[] comprimido;
                delete[] descomprimido;
                break;
            }

            case 2: { //  5.2 LZ78
                char texto[MAX];
                cout << "\nIngrese el texto a comprimir: ";
                cin.ignore();
                cin.getline(texto, MAX);

                int cantidadPares = 0;
                ParLZ78* pares = comprimirLZ78(texto, cantidadPares);

                cout << "Texto original: " << texto << endl;
                cout << "Pares generados (indice, caracter):" << endl;
                for (int i = 0; i < cantidadPares; i++) {
                    if (pares[i].esFinal) {
                        cout << "  (" << pares[i].indice << ")" << endl;
                    } else {
                        cout << "  (" << pares[i].indice << ", '"
                             << pares[i].caracter << "')" << endl;
                    }
                }

                char* reconstruido = descomprimirLZ78(pares, cantidadPares);
                cout << "Texto reconstruido: " << reconstruido << endl;

                cout << (strcmp(texto, reconstruido) == 0
                             ? "[OK] Coincide con el original."
                             : "[ERROR] No coincide.")
                     << endl;

                delete[] pares;
                delete[] reconstruido;
                break;
            }

            case 3: { //  5.3 Encriptacion
                char texto[MAX];
                cout << "\nIngrese el texto a encriptar: ";
                cin.ignore();
                cin.getline(texto, MAX);

                int n;
                cout << "Ingrese el valor de rotacion n (0 < n < 8): ";
                cin >> n;

                int claveInt;
                cout << "Ingrese la clave K (0-255): ";
                cin >> claveInt;
                unsigned char clave = (unsigned char)claveInt;

                int longitud = strlen(texto);
                unsigned char* datos = (unsigned char*)texto;

                unsigned char* encriptado = encriptarDatos(datos, longitud, n, clave);
                cout << "Datos encriptados (hex): ";
                for (int i = 0; i < longitud; i++) {
                    cout << hex << setw(2) << setfill('0') << (int)encriptado[i] << " ";
                }
                cout << dec << endl;

                unsigned char* desencriptado = desencriptarDatos(encriptado, longitud, n, clave);
                cout << "Texto desencriptado: ";
                for (int i = 0; i < longitud; i++) cout << (char)desencriptado[i];
                cout << endl;

                bool coincide = true;
                for (int i = 0; i < longitud; i++) {
                    if (desencriptado[i] != datos[i]) { coincide = false; break; }
                }
                cout << (coincide ? "[OK] Coincide con el original." : "[ERROR] No coincide.") << endl;

                delete[] encriptado;
                delete[] desencriptado;
                break;
            }

            case 4: { // 5.4 Integracion completa
                // 1. Pedir todos los datos primero (y validarlos antes de reservar memoria)
                char rutaEntrada[MAX_RUTA];
                char rutaSalida[MAX_RUTA];

                cout << "\nIngrese la ruta del archivo de entrada: ";
                cin.ignore();
                cin.getline(rutaEntrada, MAX_RUTA);

                int metodo;
                cout << "Seleccione el metodo de compresion:\n";
                cout << "  1. RLE\n  2. LZ78\nOpcion: ";
                cin >> metodo;
                if (cin.fail() || (metodo != 1 && metodo != 2)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw invalid_argument("Metodo de compresion invalido, debe ser 1 (RLE) o 2 (LZ78).");
                }

                int n;
                cout << "Ingrese el valor de rotacion n (0 < n < 8): ";
                cin >> n;
                if (cin.fail() || n <= 0 || n >= 8) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw out_of_range("El valor de rotacion n debe cumplir 0 < n < 8.");
                }

                int claveInt;
                cout << "Ingrese la clave K (0-255): ";
                cin >> claveInt;
                if (cin.fail() || claveInt < 0 || claveInt > 255) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw out_of_range("La clave K debe estar entre 0 y 255.");
                }
                unsigned char clave = (unsigned char)claveInt;

                cout << "Ingrese la ruta del archivo de salida: ";
                cin.ignore();
                cin.getline(rutaSalida, MAX_RUTA);

                // Ruta del archivo de detalle:
                char rutaDetalle[MAX_RUTA + 20];
                strcpy(rutaDetalle, rutaSalida);
                char* punto = strrchr(rutaDetalle, '.');
                char* ultimaBarra = strrchr(rutaDetalle, '\\');
                char* barraNormal = strrchr(rutaDetalle, '/');
                if (barraNormal != nullptr && (ultimaBarra == nullptr || barraNormal > ultimaBarra)) {
                    ultimaBarra = barraNormal;
                }
                if (punto != nullptr && (ultimaBarra == nullptr || punto > ultimaBarra)) {
                    *punto = '\0'; // quitar la extension
                }
                strcat(rutaDetalle, "_detalle.txt");

                // Leer el archivo de entrada completo
                ifstream archivoEntrada(rutaEntrada, ios::binary);
                if (!archivoEntrada.is_open()) {
                    throw runtime_error("No se pudo abrir el archivo de entrada.");
                }

                archivoEntrada.seekg(0, ios::end);
                long tamanoArchivo = archivoEntrada.tellg();
                archivoEntrada.seekg(0, ios::beg);

                if (tamanoArchivo <= 0) {
                    archivoEntrada.close();
                    throw runtime_error("El archivo de entrada esta vacio.");
                }

                char* textoOriginal = new char[tamanoArchivo + 1];
                archivoEntrada.read(textoOriginal, tamanoArchivo);
                textoOriginal[tamanoArchivo] = '\0';
                archivoEntrada.close();

                // Archivo de detalle: aqui se van guardando las etapas del proceso
                ofstream archivoDetalle(rutaDetalle, ios::binary);
                if (!archivoDetalle.is_open()) {
                    delete[] textoOriginal;
                    throw runtime_error("No se pudo crear el archivo de detalle.");
                }
                archivoDetalle << "DETALLE DEL PROCESO \n";
                archivoDetalle << "Metodo: " << (metodo == 1 ? "RLE" : "LZ78") << "\n";
                archivoDetalle << "Rotacion n = " << n << " | Clave K = " << claveInt << "\n\n";
                archivoDetalle << "1. TEXTO ORIGINAL \n" << textoOriginal << "\n\n";

                char* textoFinal = nullptr; // resultado de comprimir+encriptar+desencriptar+descomprimir

                if (metodo == 1) {
                    // ---- Camino RLE ----
                    char* comprimido = comprimirRLE(textoOriginal);
                    int longitud = (int)strlen(comprimido);

                    archivoDetalle << "2. TEXTO COMPRIMIDO (RLE) \n";
                    for (int i = 0; i < longitud; i++) {
                        // Los saltos de linea se muestran como \n para que sea legible
                        if (comprimido[i] == '\n') archivoDetalle << "\\n";
                        else if (comprimido[i] == '\r') archivoDetalle << "\\r";
                        else archivoDetalle << comprimido[i];
                    }
                    archivoDetalle << "\n\n";

                    unsigned char* encriptado = encriptarDatos((const unsigned char*)comprimido, longitud, n, clave);

                    archivoDetalle << "3. DATOS ENCRIPTADOS (hex)\n";
                    for (int i = 0; i < longitud; i++) {
                        archivoDetalle << hex << setw(2) << setfill('0') << (int)encriptado[i] << " ";
                    }
                    archivoDetalle << dec << "\n\n";

                    unsigned char* desencriptado = desencriptarDatos(encriptado, longitud, n, clave);

                    // Se arma el comprimido recuperado como C-string para descomprimirlo
                    char* comprimidoRecuperado = new char[longitud + 1];
                    memcpy(comprimidoRecuperado, desencriptado, longitud);
                    comprimidoRecuperado[longitud] = '\0';

                    textoFinal = descomprimirRLE(comprimidoRecuperado);

                    delete[] comprimido;
                    delete[] encriptado;
                    delete[] desencriptado;
                    delete[] comprimidoRecuperado;

                } else {
                    //  Camino LZ78
                    int cantidadPares = 0;
                    ParLZ78* pares = comprimirLZ78(textoOriginal, cantidadPares);

                    archivoDetalle << " 2. PARES COMPRIMIDOS (LZ78) \n";
                    for (int i = 0; i < cantidadPares; i++) {
                        if (pares[i].esFinal) {
                            archivoDetalle << "(" << pares[i].indice << ") ";
                        } else {
                            archivoDetalle << "(" << pares[i].indice << ",'";
                            if (pares[i].caracter == '\n') archivoDetalle << "\\n";
                            else if (pares[i].caracter == '\r') archivoDetalle << "\\r";
                            else archivoDetalle << pares[i].caracter;
                            archivoDetalle << "') ";
                        }
                    }
                    archivoDetalle << "\n\n";

                    // Se serializa cada par a bytes para poder encriptarlo
                    int tamPorPar = sizeof(int) + 2;
                    int longitud = cantidadPares * tamPorPar;
                    unsigned char* serializado = new unsigned char[longitud];

                    for (int i = 0; i < cantidadPares; i++) {
                        int base = i * tamPorPar;
                        memcpy(&serializado[base], &pares[i].indice, sizeof(int));
                        serializado[base + sizeof(int)] = (unsigned char)pares[i].caracter;
                        serializado[base + sizeof(int) + 1] = pares[i].esFinal ? 1 : 0;
                    }

                    unsigned char* encriptado = encriptarDatos(serializado, longitud, n, clave);

                    archivoDetalle << "3. DATOS ENCRIPTADOS (hex) \n";
                    for (int i = 0; i < longitud; i++) {
                        archivoDetalle << hex << setw(2) << setfill('0') << (int)encriptado[i] << " ";
                    }
                    archivoDetalle << dec << "\n\n";

                    unsigned char* desencriptado = desencriptarDatos(encriptado, longitud, n, clave);

                    // Se deserializa de vuelta a pares
                    ParLZ78* paresRecuperados = new ParLZ78[cantidadPares];
                    for (int i = 0; i < cantidadPares; i++) {
                        int base = i * tamPorPar;
                        memcpy(&paresRecuperados[i].indice, &desencriptado[base], sizeof(int));
                        paresRecuperados[i].caracter = (char)desencriptado[base + sizeof(int)];
                        paresRecuperados[i].esFinal = (desencriptado[base + sizeof(int) + 1] == 1);
                    }

                    textoFinal = descomprimirLZ78(paresRecuperados, cantidadPares);

                    delete[] serializado;
                    delete[] encriptado;
                    delete[] desencriptado;
                    delete[] pares;
                    delete[] paresRecuperados;
                }

                archivoDetalle << "4. TEXTO FINAL (desencriptado y descomprimido) \n"
                               << textoFinal << "\n\n";

                // Imprimir el texto final en el archivo de salida
                ofstream archivoSalida(rutaSalida, ios::binary);
                if (!archivoSalida.is_open()) {
                    delete[] textoOriginal;
                    delete[] textoFinal;
                    throw runtime_error("No se pudo crear el archivo de salida.");
                }
                archivoSalida << textoFinal;
                archivoSalida.close();

                // Verificar el archivo  original con el final
                ifstream archivoVerif(rutaSalida, ios::binary);
                if (!archivoVerif.is_open()) {
                    delete[] textoOriginal;
                    delete[] textoFinal;
                    throw runtime_error("No se pudo reabrir el archivo de salida para verificar.");
                }
                archivoVerif.seekg(0, ios::end);
                long tamanoSalida = archivoVerif.tellg();
                archivoVerif.seekg(0, ios::beg);

                bool coincide = false;
                if (tamanoSalida == tamanoArchivo) {
                    char* textoLeido = new char[tamanoSalida + 1];
                    archivoVerif.read(textoLeido, tamanoSalida);
                    textoLeido[tamanoSalida] = '\0';
                    coincide = (memcmp(textoLeido, textoOriginal, tamanoArchivo) == 0);
                    delete[] textoLeido;
                }
                archivoVerif.close();

                archivoDetalle << "Verificacion (releyendo el archivo de salida): "
                               << (coincide ? "[OK] El texto final coincide con el original."
                                            : "[ERROR] El texto final NO coincide con el original.")
                               << "\n";
                archivoDetalle.close();

                cout << "\nArchivo leido:         " << rutaEntrada << endl;
                cout << "Resultado guardado en: " << rutaSalida << endl;
                cout << "Detalle del proceso:   " << rutaDetalle << endl;
                cout << (coincide ? "[OK] El texto final coincide con el original."
                                  : "[ERROR] El texto final NO coincide con el original.")
                     << endl;

                delete[] textoOriginal;
                delete[] textoFinal;
                break;
            }

            case 5:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opcion invalida, intente de nuevo." << endl;
            }
        } catch (const exception& e) {
            // Ningun error inesperado cierra el programa.
            cerr << "Ocurrio un error: " << e.what() << endl;
        }
    }

    return 0;
}
