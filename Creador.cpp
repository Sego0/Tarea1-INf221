#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cmath>
using namespace std;

// Función para generar una lista desordenada aleatoriamente
vector<int> generarListaAleatoria(int tamano, int min_valor, int max_valor) {
    vector<int> lista(tamano);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(min_valor, max_valor);
    
    for (int i = 0; i < tamano; i++) {
        lista[i] = dist(gen);
    }
    return lista;
}

// Función para generar una lista parcialmente ordenada
vector<int> generarListaParcialmenteOrdenada(int tamano, int porcentaje_ordenado) {
    vector<int> lista = generarListaAleatoria(tamano, 0, 1000);
    int hasta = (tamano * porcentaje_ordenado) / 100;
    sort(lista.begin(), lista.begin() + hasta);
    return lista;
}

// Función para generar una lista inversamente ordenada
vector<int> generarListaInversa(int tamano) {
    vector<int> lista = generarListaAleatoria(tamano, 0, 1000);
    sort(lista.begin(), lista.end(), greater<int>());
    return lista;
}

// Función para guardar una lista en un archivo binario
void guardarEnBinario(const vector<int>& lista, const string& nombre_archivo) {
    ofstream archivo(nombre_archivo, ios::binary);
    if (archivo.is_open()) {
        for (int num : lista) {
            archivo.write(reinterpret_cast<const char*>(&num), sizeof(num));
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << endl;
    }
}

// Función para generar 10 listas por cada tipo de ordenamiento
void generarListasYGuardar(int tamano_lista) {
    // Listas parcialmente ordenadas (80% ordenadas)
    for (int i = 1; i <= 10; ++i) {
        std::vector<int> lista = generarListaParcialmenteOrdenada(tamano_lista, 80);
        guardarEnBinario(lista, "lista_parcialmente_ordenada_" + to_string(i) + ".bin");
    }

    // Listas inversamente ordenadas
    for (int i = 1; i <= 10; ++i) {
        vector<int> lista = generarListaInversa(tamano_lista);
        guardarEnBinario(lista, "lista_inversa_" + to_string(i) + ".bin");
    }

    // Listas con valores repetidos
    for (int i = 1; i <= 10; ++i) {
        vector<int> lista(tamano_lista, i * 10); // Todas con el valor i * 10
        guardarEnBinario(lista, "lista_valores_repetidos_" + to_string(i) + ".bin");
    }
}

void generarListasaleatoriasYGuardar(int tamano_lista,int elv) {
    // Listas desordenadas aleatoriamente
    for (int i = 1; i <= 10; ++i) {
        vector<int> lista = generarListaAleatoria(tamano_lista, 0, 1000);
        guardarEnBinario(lista, "lista_aleatoria_" + to_string(i)+"_"+ to_string(elv) + ".bin");
    }
}

int main() {
    int elv = 6;
    int tamano_lista = pow(10,elv); // Ejemplo con listas de 10,000 elementos

    //generarListasYGuardar(tamano_lista);
    generarListasaleatoriasYGuardar(tamano_lista, elv);

    std::cout << "Listas generadas y guardadas en archivos binarios." << std::endl;

    return 0;
}
