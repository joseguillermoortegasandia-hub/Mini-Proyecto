#include "grafo_manual.h"


// Estructuras Básicas

Grafo::Grafo() : numNodos(0) {
    for (int i = 0; i < MAX_NODOS; ++i) {
        nodos[i].id = -1;
        nodos[i].adyacentes = nullptr;
        visitado[i] = false;
    }
}

Grafo::~Grafo() {
    liberarMemoria();
}

void Grafo::liberarMemoria() {
    for (int i = 0; i < numNodos; ++i) {
        Arista* actual = nodos[i].adyacentes;
        while (actual != nullptr) {
            Arista* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        nodos[i].adyacentes = nullptr;
    }
}

// Manejo de Nodos y Aristas

int Grafo::buscarIndice(int id) const {
    for (int i = 0; i < numNodos; ++i) {
        if (nodos[i].id == id) {
            return i;
        }
    }
    return -1;
}

void Grafo::agregarNodo(int id) {
    if (buscarIndice(id) != -1) {
        std::cout << "Advertencia: El nodo " << id << " ya existe.\n";
        return;
    }
    if (numNodos < MAX_NODOS) {
        nodos[numNodos].id = id;
        nodos[numNodos].adyacentes = nullptr;
        numNodos++;
        std::cout << "Nodo " << id << " agregado correctamente.\n";
    } else {
        std::cout << "Error: El grafo esta lleno. No se puede agregar el nodo " << id << std::endl;
    }
}

void Grafo::agregarAristaSimple(int indiceOrigen, int destinoId, int peso) {
    Arista* nuevaArista = new Arista;
    nuevaArista->destino = destinoId;
    nuevaArista->peso = peso;
    nuevaArista->siguiente = nodos[indiceOrigen].adyacentes;
    nodos[indiceOrigen].adyacentes = nuevaArista;
}

void Grafo::agregarArista(int origenId, int destinoId, int peso, bool dirigido) {
    if (origenId == destinoId) {
        std::cout << "Advertencia: No se permiten lazos.\n";
        return;
    }
    int iOrigen = buscarIndice(origenId);
    int iDestino = buscarIndice(destinoId);

    if (iOrigen != -1 && iDestino != -1) {
        agregarAristaSimple(iOrigen, destinoId, peso);
        if (!dirigido) {
            agregarAristaSimple(iDestino, origenId, peso);
        }
        std::cout << "Arista (" << origenId << ", " << destinoId << ", peso: " << peso << ") agregada.\n";
    } else {
        std::cout << "Error: Uno o ambos nodos no existen.\n";
    }
}

void Grafo::mostrarGrafo() const {
    if (numNodos == 0) {
        std::cout << "El grafo esta vacio.\n";
        return;
    }
    std::cout << "\n--- Grafo (Lista de Adyacencia Ponderada) ---\n";
    for (int i = 0; i < numNodos; ++i) {
        std::cout << "Nodo " << nodos[i].id << ": ";
        Arista* actual = nodos[i].adyacentes;
        while (actual != nullptr) {
            std::cout << "-> (" << actual->destino << ", P: " << actual->peso << ") ";
            actual = actual->siguiente;
        }
        std::cout << "\n";
    }
    std::cout << "----------------------------------------------\n";
}

// Recorridos Básicos (DFS y BFS)

void Grafo::resetearVisitados() {
    for (int i = 0; i < numNodos; ++i) {
        visitado[i] = false;
    }
}

void Grafo::dfsRecursivo(int indiceActual) {
    visitado[indiceActual] = true;
    std::cout << nodos[indiceActual].id << " ";

    Arista* vecino = nodos[indiceActual].adyacentes;
    while (vecino != nullptr) {
        int indiceVecino = buscarIndice(vecino->destino);
        if (indiceVecino != -1 && !visitado[indiceVecino]) {
            dfsRecursivo(indiceVecino);
        }
        vecino = vecino->siguiente;
    }
}

void Grafo::recorrerDFS(int inicioId) {
    int indiceInicio = buscarIndice(inicioId);
    if (indiceInicio == -1) {
        std::cout << "Error: El nodo de inicio " << inicioId << " no existe.\n";
        return;
    }
    resetearVisitados();
    std::cout << "\n-> Recorrido DFS (Profundidad) desde " << inicioId << ": ";
    dfsRecursivo(indiceInicio);
    std::cout << "\n";
}

void Grafo::recorrerBFS(int inicioId) {
    int indiceInicio = buscarIndice(inicioId);
    if (indiceInicio == -1) {
        std::cout << "Error: El nodo de inicio " << inicioId << " no existe.\n";
        return;
    }
    resetearVisitados();

    // Simulacion de Cola FIFO con array estático
    int cola[MAX_NODOS];
    int frente = 0;
    int final = 0;

    cola[final++] = indiceInicio;
    visitado[indiceInicio] = true;

    std::cout << "\n-> Recorrido BFS (Amplitud) desde " << inicioId << ": ";
    
    while (frente != final) {
        int indiceActual = cola[frente++];
        std::cout << nodos[indiceActual].id << " ";

        Arista* vecino = nodos[indiceActual].adyacentes;
        while (vecino != nullptr) {
            int indiceVecino = buscarIndice(vecino->destino);
            
            if (indiceVecino != -1 && !visitado[indiceVecino]) {
                visitado[indiceVecino] = true;
                if (final < MAX_NODOS) {
                    cola[final++] = indiceVecino;
                }
            }
            vecino = vecino->siguiente;
        }
    }
    std::cout << "\n";
}

// Algoritmo de Dijkstra (Camino Más Corto) 

// Función auxiliar para mantener la propiedad de Min-Heap
void Grafo::heapify(int arr[][2], int n, int i, int distancias[]) const {
    int menor = i;
    int l = 2 * i + 1; // Hijo izquierdo
    int r = 2 * i + 2; // Hijo derecho

    // Compara usando la distancia (arr[x][0])
    if (l < n && arr[l][0] < arr[menor][0])
        menor = l;

    if (r < n && arr[r][0] < arr[menor][0])
        menor = r;

    if (menor != i) {
        // Intercambia el nodo completo (distancia y ID)
        std::swap(arr[i], arr[menor]);
        heapify(arr, n, menor, distancias);
    }
}

// Construye el Min-Heap
void Grafo::construirMinHeap(int arr[][2], int n, int distancias[]) const {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, distancias);
}

// Extrae el elemento con la distancia mínima (la raíz)
void Grafo::extraerMinimo(int arr[][2], int& n, int distancias[]) const {
    if (n <= 0) return;
    
    // El mínimo es arr[0]. Lo intercambia con el último para simular extracción.
    std::swap(arr[0], arr[n - 1]);
    n--; // Reduce el tamaño del heap
    
    // Restablece la propiedad de heap en la raíz
    heapify(arr, n, 0, distancias);
}

// Algoritmo principal de Dijkstra
void Grafo::dijkstra(int inicioId) const {
    int indiceInicio = buscarIndice(inicioId);
    if (indiceInicio == -1) {
        std::cout << "Error: El nodo de inicio " << inicioId << " no existe.\n";
        return;
    }

    // distancias[i] = distancia más corta al nodo con ID = nodos[i].id
    int distancias[MAX_NODOS];
    
    // Simulamos la Cola de Prioridad con un array Min-Heap
    // heap[i][0] = distancia; heap[i][1] = índice del nodo (no el ID)
    int heap[MAX_NODOS][2];
    int size = numNodos; // Tamaño actual del heap (número de nodos no procesados)

    // Inicialización: Distancias a 'infinito' y llenar el heap
    for (int i = 0; i < numNodos; ++i) {
        distancias[i] = std::numeric_limits<int>::max();
        heap[i][0] = distancias[i];
        heap[i][1] = i; // Guardamos el índice, no el ID
    }

    distancias[indiceInicio] = 0;
    heap[indiceInicio][0] = 0;

    // Construimos el Min-Heap inicialmente
    construirMinHeap(heap, size, distancias);

    std::cout << "\n--- Algoritmo de Dijkstra desde Nodo " << inicioId << " ---\n";

    while (size > 0) {
        // 1. Extraer el mínimo (Extraemos el índice del nodo no visitado con menor distancia)
        int u_distancia = heap[0][0];
        int u_indice = heap[0][1];
        extraerMinimo(heap, size, distancias);

        // Si la distancia es 'infinito', hemos terminado
        if (u_distancia == std::numeric_limits<int>::max()) break;

        // 2. Itera sobre los vecinos (relajación)
        Arista* vecino = nodos[u_indice].adyacentes;
        while (vecino != nullptr) {
            int v_id = vecino->destino;
            int v_indice = buscarIndice(v_id);
            int peso = vecino->peso;

            // Relajación: Si encontramos un camino más corto a 'v' a través de 'u'
            if (distancias[u_indice] != std::numeric_limits<int>::max() && distancias[u_indice] + peso < distancias[v_indice]) {
                
                distancias[v_indice] = distancias[u_indice] + peso;
                
                // Actualizar la distancia de v en el heap y restaurar la propiedad Min-Heap
                // (En una implementación real de heap, esto sería una operación de 'disminuir clave')
                for(int i = 0; i < size; ++i) {
                    if (heap[i][1] == v_indice) {
                        heap[i][0] = distancias[v_indice];
                        construirMinHeap(heap, size, distancias); // Reconstruir todo es ineficiente, pero simple.
                        break;
                    }
                }
            }
            vecino = vecino->siguiente;
        }
    }

    // Mostrar resultados
    for (int i = 0; i < numNodos; ++i) {
        std::cout << "  -> Dist(" << inicioId << " a " << nodos[i].id << "): ";
        if (distancias[i] == std::numeric_limits<int>::max()) {
            std::cout << "INACCESIBLE\n";
        } else {
            std::cout << distancias[i] << "\n";
        }
    }
}
