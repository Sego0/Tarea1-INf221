#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

// Función para cargar una lista desde un archivo binario
vector<int> cargarDesdeBinario(const string& nombre_archivo) {
    vector<int> lista;
    ifstream archivo(nombre_archivo, ios::binary);

    if (archivo.is_open()) {
        int valor;
        while (archivo.read(reinterpret_cast<char*>(&valor), sizeof(valor))) {
            lista.push_back(valor);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << std::endl;
    }

    return lista;
}

int partition(vector<int> &vec, int low, int high) {
    int pivot = vec[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[i + 1], vec[high]);
    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high) {
    if (low < high) {
        int p = partition(vec, low, high);
        quickSort(vec, low, p - 1);
        quickSort(vec, p + 1, high);
    }
}

int main() {
    string tipo_dataset;
    // Elige el dataset a trabajar (puede ser "lista_aleatoria", "lista_parcialmente_ordenada", "lista_inversa", o "lista_valores_repetidos")
    tipo_dataset = "lista_aleatoria";
    int exponente = 6;
    vector<int> lista;
    for (int i = 1; i <= 10; ++i) {
        string nombre_archivo = tipo_dataset + "_" + to_string(i) + "_" + to_string(exponente) + ".bin";
        lista = cargarDesdeBinario(nombre_archivo);
        int n = lista.size();

        auto inicio = chrono::high_resolution_clock::now();
        quickSort(lista, 0, n - 1);
        auto fin = chrono::high_resolution_clock::now();

         auto duracion = chrono::duration_cast<chrono::milliseconds >(fin - inicio).count();
        cout <<  duracion << " milisegundos" << endl;

        cout << "Lista " << tipo_dataset << " " << i << " cargada y algoritmo aplicado.\n";
    }
    return 0;
}
