#include "grafo_manual.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
    // 1. Inicialización
    Grafo miGrafo; 

    cout << "========================================\n";
    cout << " Mini Libreria de Grafos (Sin Vectores)\n";
    cout << "========================================\n";

    // 2. Agregar Nodos
    cout << "\n--- 1. Agregando Nodos ---\n";
    miGrafo.agregarNodo(10); // ID 10
    miGrafo.agregarNodo(20); // ID 20
    miGrafo.agregarNodo(30); // ID 30
    miGrafo.agregarNodo(40); // ID 40
    miGrafo.agregarNodo(50); // ID 50

    // 3. Agregar Aristas (Origen, Destino, Peso)
    cout << "\n--- 2. Agregando Aristas Ponderadas (No Dirigidas) ---\n";
    miGrafo.agregarArista(10, 20, 10);
    miGrafo.agregarArista(10, 50, 3);
    miGrafo.agregarArista(20, 30, 2);
    miGrafo.agregarArista(20, 40, 5);
    miGrafo.agregarArista(30, 40, 4);
    miGrafo.agregarArista(40, 50, 7);
    
    // Mostrar la estructura
    miGrafo.mostrarGrafo(); 

    // 4. Recorrido DFS (Profundidad)
    miGrafo.recorrerDFS(10); 
    
    // 5. Recorrido BFS (Amplitud)
    miGrafo.recorrerBFS(10); 

    // 6. Algoritmo de Dijkstra (Camino Más Corto) - Implementación Manual
    miGrafo.dijkstra(10);
    
    return 0;
}
