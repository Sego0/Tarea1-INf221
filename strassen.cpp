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


// Función para sumar dos matrices
vector<vector<int>> sumarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> resultado(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            resultado[i][j] = A[i][j] + B[i][j];
        }
    }
    return resultado;
}

// Función para restar dos matrices
vector<vector<int>> restarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> resultado(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            resultado[i][j] = A[i][j] - B[i][j];
        }
    }
    return resultado;
}

// Función de Strassen para multiplicación de matrices
vector<vector<int>> multiplicarStrassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int newSize = n / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize));
    vector<vector<int>> A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize));
    vector<vector<int>> A22(newSize, vector<int>(newSize));
    vector<vector<int>> B11(newSize, vector<int>(newSize));
    vector<vector<int>> B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize));
    vector<vector<int>> B22(newSize, vector<int>(newSize));

    // Dividir las matrices en submatrices de tamaño n/2
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calcular los productos intermedios utilizando las sumas y restas
    vector<vector<int>> M1 = multiplicarStrassen(sumarMatrices(A11, A22), sumarMatrices(B11, B22));
    vector<vector<int>> M2 = multiplicarStrassen(sumarMatrices(A21, A22), B11);
    vector<vector<int>> M3 = multiplicarStrassen(A11, restarMatrices(B12, B22));
    vector<vector<int>> M4 = multiplicarStrassen(A22, restarMatrices(B21, B11));
    vector<vector<int>> M5 = multiplicarStrassen(sumarMatrices(A11, A12), B22);
    vector<vector<int>> M6 = multiplicarStrassen(restarMatrices(A21, A11), sumarMatrices(B11, B12));
    vector<vector<int>> M7 = multiplicarStrassen(restarMatrices(A12, A22), sumarMatrices(B21, B22));

    // Calcular las submatrices del resultado
    vector<vector<int>> C11 = sumarMatrices(restarMatrices(sumarMatrices(M1, M4), M5), M7);
    vector<vector<int>> C12 = sumarMatrices(M3, M5);
    vector<vector<int>> C21 = sumarMatrices(M2, M4);
    vector<vector<int>> C22 = sumarMatrices(restarMatrices(sumarMatrices(M1, M3), M2), M6);

    // Combinar las submatrices en la matriz final
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return C;
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

        auto inicio = chrono::high_resolution_clock::now();
        multiplicarStrassen(A, B);
        auto fin = chrono::high_resolution_clock::now();

        auto duracion = chrono::duration_cast<chrono::milliseconds >(fin - inicio).count();
        cout <<  duracion << endl;
        //std::cout << "Matriz aleatoria " << i << " cargada y algoritmo aplicado.\n";
    }
    return 0;
}
