# Mini-Proyecto

Estructura del Proyecto
El proyecto sigue una estructura de librería estándar C++ (.h y .cpp). El archivo grafo_manual.h (en include/) es la Interfaz con las estructuras y prototipos. El archivo grafo_manual.cpp (en src/) contiene la Implementación completa de los métodos, incluyendo la simulación manual del Min-Heap para Dijkstra. El archivo main.cpp (en src/) es el archivo de demostración.

Funcionalidades Incluidas
La clase Grafo está optimizada para grafos basados en la Lista de Adyacencia y permite:

Manejo de Nodos y Aristas: Agregar nodos por ID y agregar aristas ponderadas (con peso) entre nodos.

Algoritmos de Recorrido: DFS (Búsqueda en Profundidad, recursiva) y BFS (Búsqueda en Amplitud, simula una cola con un array estático).

Algoritmo de Camino Más Corto: Dijkstra, cuya cola de prioridad (Min-Heap) se simula usando un array estático y funciones de manipulación de Heap (heapify).

Compilación y Ejecución
Para usar esta librería, asegúrate de tener instalada la herramienta g++ y de tener la estructura de carpetas ProyectoGrafo/include/ y ProyectoGrafo/src/ con los archivos correspondientes.

Compilación
Ejecuta el siguiente comando en tu terminal desde la carpeta ProyectoGrafo/:

g++ src/main.cpp src/grafo_manual.cpp -o grafo_manual_demo -I include

Ejecución
Una vez compilado, ejecuta el programa binario:

./grafo_manual_demo

Esto ejecutará la demostración, creará un grafo de ejemplo, mostrará su estructura, realizará los recorridos DFS y BFS, y calculará las distancias más cortas usando Dijkstra.
