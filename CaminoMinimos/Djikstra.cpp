// Dijkstra.cpp
#include "Djikstra.h"

// Implementación de la clase Graph

// Constructor
Graph::Graph(int V) {
    this->V = V;
    array = new AdjListNode*[V];
    for(int i = 0; i < V; ++i)
        array[i] = nullptr;
}

// Destructor para liberar memoria
Graph::~Graph() {
    for(int v = 0; v < V; ++v) {
        AdjListNode* current = array[v];
        while(current) {
            AdjListNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] array;
}

// Método para crear un nuevo nodo de lista de adyacencia
AdjListNode* Graph::newAdjListNode(int dest, int peso) {
    AdjListNode* newNode = new AdjListNode;
    newNode->dest = dest;
    newNode->peso = peso;
    newNode->next = nullptr;
    return newNode;
}

// Método para agregar una arista al grafo (dirigido)
void Graph::addEdge(int src, int dest, int peso) {
    AdjListNode* newNode = newAdjListNode(dest, peso);
    newNode->next = array[src];
    array[src] = newNode;
}

// Método para imprimir el grafo
void Graph::printGraph() {
    for(int v = 0; v < V; ++v) {
        AdjListNode* pCrawl = array[v];
        cout << "Vértice " << v << ":";
        while(pCrawl) {
            cout << " -> (" << pCrawl->dest << ", " << pCrawl->peso << ")";
            pCrawl = pCrawl->next;
        }
        cout << endl;
    }
}

// Implementación de la clase MinHeap

// Constructor
MinHeap::MinHeap(int capacidad) {
    this->capacidad = capacidad;
    this->tamaño = 0;
    array = new MinHeapNode*[capacidad];
    for(int i = 0; i < capacidad; ++i)
        array[i] = nullptr;
}

// Destructor para liberar memoria
MinHeap::~MinHeap() {
    for(int i = 0; i < tamaño; ++i)
        delete array[i];
    delete[] array;
}

// Método para intercambiar dos nodos del heap
void MinHeap::intercambiarMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Método para heapify hacia abajo
void MinHeap::minHeapify(int idx) {
    int smallest = idx;
    int izquierda = 2 * idx + 1;
    int derecha = 2 * idx + 2;

    if (izquierda < tamaño && array[izquierda]->distancia < array[smallest]->distancia)
        smallest = izquierda;

    if (derecha < tamaño && array[derecha]->distancia < array[smallest]->distancia)
        smallest = derecha;

    if (smallest != idx) {
        // Actualizar posiciones
        pos[array[smallest]->vertice] = idx;
        pos[array[idx]->vertice] = smallest;

        intercambiarMinHeapNode(&array[smallest], &array[idx]);
        minHeapify(smallest);
    }
}

// Método para verificar si el heap está vacío
bool MinHeap::isEmpty() {
    return tamaño == 0;
}

// Método para extraer el nodo con la distancia mínima
MinHeapNode* MinHeap::extractMin() {
    if (isEmpty())
        return nullptr;

    // Guardar la raíz
    MinHeapNode* root = array[0];

    // Reemplazar la raíz con el último nodo
    MinHeapNode* lastNode = array[tamaño - 1];
    array[0] = lastNode;

    // Actualizar posiciones
    pos[root->vertice] = tamaño - 1;
    pos[lastNode->vertice] = 0;

    // Reducir el tamaño y heapify la raíz
    tamaño--;
    minHeapify(0);

    return root;
}

// Método para decrementar la distancia de un vértice
void MinHeap::decrementarDistancia(int vertice, int distancia) {
    int i = pos[vertice];
    array[i]->distancia = distancia;

    // Subir en el heap mientras sea necesario
    while (i && array[i]->distancia < array[(i - 1)/2]->distancia) {
        pos[array[i]->vertice] = (i-1)/2;
        pos[array[(i-1)/2]->vertice] = i;
        intercambiarMinHeapNode(&array[i], &array[(i-1)/2]);
        i = (i - 1)/2;
    }
}

// Método para insertar un nuevo nodo en el heap
void MinHeap::insertarMinHeap(int vertice, int distancia) {
    if (tamaño == capacidad)
        return;

    // Crear un nuevo nodo y añadirlo al final
    MinHeapNode* node = new MinHeapNode;
    node->vertice = vertice;
    node->distancia = distancia;
    array[tamaño] = node;

    // Posición del vértice en el heap
    pos[vertice] = tamaño;
    tamaño++;

    // Subir en el heap mientras sea necesario
    int i = tamaño - 1;
    while (i && array[i]->distancia < array[(i - 1)/2]->distancia) {
        pos[array[i]->vertice] = (i-1)/2;
        pos[array[(i-1)/2]->vertice] = i;
        intercambiarMinHeapNode(&array[i], &array[(i-1)/2]);
        i = (i - 1)/2;
    }
}

// Implementación de la clase Dijkstra

// Constructor
Dijkstra::Dijkstra(Graph* g) {
    graph = g;
}

// Método para encontrar los caminos más cortos desde una fuente
void Dijkstra::encontrarCaminosMasCortos(int src) {
    int V = graph->V;
    int dist[V]; // Arreglo para almacenar las distancias

    // Crear un min-heap con capacidad igual al número de vértices
    MinHeap minHeap(V);

    // Inicializar todas las distancias como infinito y añadir al heap
    for(int v = 0; v < V; ++v) {
        dist[v] = INT32_MAX;
        minHeap.insertarMinHeap(v, dist[v]);
    }

    // La distancia de la fuente a sí misma es 0
    dist[src] = 0;
    minHeap.decrementarDistancia(src, dist[src]);

    while (!minHeap.isEmpty()) {
        // Extraer el vértice con la distancia mínima
        MinHeapNode* minHeapNode = minHeap.extractMin();
        if(minHeapNode == nullptr) break; // Seguridad
        int u = minHeapNode->vertice;

        // Obtener todos los vecinos de u
        AdjListNode* adj = graph->array[u];
        while(adj) {
            int v = adj->dest;
            int peso = adj->peso;

            // Si existe un camino más corto a v a través de u
            if(dist[u] != INT32_MAX && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                minHeap.decrementarDistancia(v, dist[v]);
            }
            adj = adj->next;
        }
        delete minHeapNode;
    }

    // Imprimir las distancias
    cout << "Vértice\tDistancia desde la fuente " << src << endl;
    for(int i = 0; i < V; ++i)
        cout << i << "\t\t" << (dist[i] == INT32_MAX ? -1 : dist[i]) << endl;
}

// Función main para probar la implementación del Algoritmo de Dijkstra
int main() {
    // Crear un grafo con 9 vértices
    int V = 9;
    Graph g(V);

    // Agregar aristas con sus pesos
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    // Imprimir el grafo
    cout << "Representación del Grafo:" << endl;
    g.printGraph();
    cout << endl;

    // Crear una instancia de Dijkstra y encontrar caminos más cortos desde el vértice 0
    Dijkstra dj(&g);
    cout << "Caminos más cortos desde el vértice 0:" << endl;
    dj.encontrarCaminosMasCortos(0);
    cout << endl;

    return 0;
}
