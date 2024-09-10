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

void bubbleSort(vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1])
                swap(v[j], v[j + 1]);
        }
    }
}

int main() {
    
    // Tamaño de la lista
    // Elige el dataset a trabajar (puede ser "lista_aleatoria", "lista_parcialmente_ordenada", "lista_inversa", o "lista_valores_repetidos")
    string tipo_dataset;
    tipo_dataset = "lista_aleatoria";
    int exponente = 6;
    vector<int> lista;
    for (int i = 1; i <= 10; ++i) {
        string nombre_archivo = tipo_dataset + "_" + to_string(i) + "_" + to_string(exponente)+".bin";
        lista = cargarDesdeBinario(nombre_archivo);
        
        auto inicio = chrono::high_resolution_clock::now();
        bubbleSort(lista);
        auto fin = chrono::high_resolution_clock::now();

         auto duracion = chrono::duration_cast<chrono::milliseconds >(fin - inicio).count();
        std::cout <<  duracion << " milisegundos" << std::endl;

        cout << "Lista " << tipo_dataset << " " << i << " cargada y algoritmo aplicado.\n";
    }
    // Cargar y aplicar el algoritmo solo a las listas del dataset seleccionado
    return 0;
}
