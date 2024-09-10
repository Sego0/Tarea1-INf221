#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> cargarMatrizDesdeBinario(const string& nombre_archivo, int filas, int columnas) {
    vector<vector<int>> matriz(filas, vector<int>(columnas));
    ifstream archivo(nombre_archivo, ios::binary);

    if (archivo.is_open()) {
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                archivo.read(reinterpret_cast<char*>(&matriz[i][j]), sizeof(int));
            }
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << endl;
    }

    return matriz;
}

// Función para realizar la multiplicación de matrices transponiendo la segunda matriz
void multiplicarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int filasA = A.size();
    int columnasA = A[0].size();
    int filasB = B.size();
    int columnasB = B[0].size();
    
    // Creamos la transpuesta de B dentro de la función
    vector<vector<int>> B_transpuesta(columnasB, vector<int>(filasB));
    for (int i = 0; i < filasB; ++i) {
        for (int j = 0; j < columnasB; ++j) {
            B_transpuesta[j][i] = B[i][j];  // Transponemos la matriz B
        }
    }
    
    // Realizamos la multiplicación usando B transpuesta
    for (int i = 0; i < filasA; ++i) {
        for (int j = 0; j < columnasB; ++j) {  // Columnas de la transpuesta son filas originales de B
            C[i][j] = 0;  // Inicializamos la celda
            for (int k = 0; k < columnasA; ++k) {
                C[i][j] += A[i][k] * B_transpuesta[j][k];  // Usamos la transpuesta
            }
        }
    }
}

int main() {
  // Definimos matrices de ejemplo
    vector<vector<int>> A;
    vector<vector<int>> B;
    int elv = 3;
    int filas = pow(10,elv);   
    int columnas = pow(10,elv); 

    // Cargar y aplicar un algoritmo a 10 matrices aleatorias
    for (int i = 1; i <= 10; i+=2) {
        string nombre_archivo_a = "matriz_aleatoria_" + to_string(i)+"_"+ to_string(elv) + ".bin";
        string nombre_archivo_b = "matriz_aleatoria_" + to_string(i+1)+"_"+ to_string(elv) + ".bin";
        A = cargarMatrizDesdeBinario(nombre_archivo_a, filas, columnas);
        B = cargarMatrizDesdeBinario(nombre_archivo_b, filas, columnas);
        vector<vector<int>> C(A.size(), vector<int>(B[0].size()));

        auto inicio = chrono::high_resolution_clock::now();
        multiplicarMatrices(A, B, C);
        auto fin = chrono::high_resolution_clock::now();

        auto duracion = chrono::duration_cast<chrono::milliseconds >(fin - inicio).count();
        cout <<  duracion << endl;
        //std::cout << "Matriz aleatoria " << i << " cargada y algoritmo aplicado.\n";
    }
    return 0;
}
