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

void merge(vector<int>& arr, int left, 
                     int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main()
{
    // Elige el dataset a trabajar (puede ser "lista_aleatoria", "lista_parcialmente_ordenada", "lista_inversa", o "lista_valores_repetidos")
    string tipo_dataset;
    tipo_dataset = "lista_aleatoria";
    int exponente = 6;
    vector<int> lista;
    for (int i = 1; i <= 10; ++i) {
        string nombre_archivo = tipo_dataset + "_" + to_string(i) + "_" + to_string(exponente) + ".bin";
        lista = cargarDesdeBinario(nombre_archivo);
        int n = lista.size();

        auto inicio = chrono::high_resolution_clock::now();
        mergeSort(lista, 0, n - 1);
        auto fin = chrono::high_resolution_clock::now();

         auto duracion = chrono::duration_cast<chrono::milliseconds >(fin - inicio).count();
        cout <<  duracion << " milisegundos" << endl;

        cout << "Lista " << tipo_dataset << " " << i << " cargada y algoritmo aplicado.\n";
    }


    int n = lista.size();
    mergeSort(lista, 0, n - 1);
    return 0;
}
