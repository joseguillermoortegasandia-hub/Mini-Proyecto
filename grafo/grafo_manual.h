#ifndef GRAFO_MANUAL_H
#define GRAFO_MANUAL_H

#include <iostream>
#include <limits> 
#include <utility> 

// Constante para el tamaño maximo del grafo
const int MAX_NODOS = 100;

// Estructura para representar un nodo en la lista de adyacencia (un vecino)
struct Arista {
    int destino;
    int peso; // Se añade peso para el camino más corto
    Arista* siguiente;
};

// Estructura para representar la cabecera de la lista de adyacencia
struct NodoGrafo {
    int id; // Identificador del nodo (útil para la visualización, aunque el índice es clave)
    Arista* adyacentes;
};

// MINI LIBRERIA DE GRAFOS
class Grafo {
public:
    // Constructor
    Grafo();

    // Destructor (para liberar la memoria de las aristas)
    ~Grafo();
    
    // Funciones principales
    void agregarNodo(int id);
    void agregarArista(int origenId, int destinoId, int peso, bool dirigido = false);
    void mostrarGrafo() const;
    
    // Recorridos
    void recorrerDFS(int inicioId);
    void recorrerBFS(int inicioId);
    
    // Algoritmo de Camino Más Corto
    void dijkstra(int inicioId) const;
    
private:
    NodoGrafo nodos[MAX_NODOS];
    int numNodos;
    bool visitado[MAX_NODOS];
    
    // Funciones auxiliares
    int buscarIndice(int id) const;
    void agregarAristaSimple(int indiceOrigen, int destinoId, int peso);
    void resetearVisitados();
    void dfsRecursivo(int indiceActual);
    void liberarMemoria();

    // Auxiliar para Dijkstra: Simulación de Cola de Prioridad con Array Min-Heap
    void heapify(int arr[][2], int n, int i, int distancias[]) const;
    void construirMinHeap(int arr[][2], int n, int distancias[]) const;
    void extraerMinimo(int arr[][2], int& n, int distancias[]) const;
};

#endif // GRAFO_MANUAL_H
