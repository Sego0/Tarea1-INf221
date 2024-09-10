#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <cmath>  
using namespace std;  

// Función para generar una matriz aleatoria
vector<vector<int>> generarMatrizAleatoria(int filas, int columnas, int valor_min, int valor_max) {
    vector<vector<int>> matriz(filas, vector<int>(columnas));
    
    // Rellenar la matriz con valores aleatorios
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = valor_min + rand() % (valor_max - valor_min + 1);
        }
    }

    return matriz;
}

// Función para guardar una matriz en un archivo binario
void guardarMatrizEnBinario(const string& nombre_archivo, const vector<vector<int>>& matriz) {
    ofstream archivo(nombre_archivo, ios::binary);
    
    if (archivo.is_open()) {
        for (const auto& fila : matriz) {
            for (const auto& elemento : fila) {
                archivo.write(reinterpret_cast<const char*>(&elemento), sizeof(elemento));
            }
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int elv = 3;
    // Dimensiones de las matrices
    int filas = pow(10,elv);   
    int columnas = pow(10,elv); 

    // Rango de los valores aleatorios (ejemplo: entre 0 y 1000)
    int valor_min = 0;
    int valor_max = 100;

    // Generar y guardar 10 matrices aleatorias
    for (int i = 1; i <= 20; ++i) {
        string nombre_archivo = "matriz_aleatoria_" + to_string(i)+"_"+ to_string(elv) + ".bin";

        // Generar la matriz aleatoria
        vector<vector<int>> matriz = generarMatrizAleatoria(filas, columnas, valor_min, valor_max);

        // Guardar la matriz en un archivo binario
        guardarMatrizEnBinario(nombre_archivo, matriz);

        cout << "Matriz aleatoria " << i << " generada y guardada en " << nombre_archivo << ".\n";
    }

    return 0;
}