// Prim.cpp
#include <iostream>
#include <climits>

using namespace std;

// Estructura para representar una arista en la lista de adyacencia
struct AdjListNode {
    int dest;
    int peso;
    AdjListNode* next;
};

// Estructura para representar la lista de adyacencia
struct AdjList {
    AdjListNode* head;
};

// Clase para representar el Grafo
class Graph {
public:
    int V;          // Número de vértices
    AdjList* array; // Arreglo de listas de adyacencia

    // Constructor
    Graph(int V) {
        this->V = V;
        array = new AdjList[V];
        for(int i = 0; i < V; ++i)
            array[i].head = nullptr;
    }

    // Destructor para liberar memoria
    ~Graph() {
        for(int v = 0; v < V; ++v) {
            AdjListNode* current = array[v].head;
            while(current) {
                AdjListNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] array;
    }

    // Método para crear un nuevo nodo de lista de adyacencia
    AdjListNode* newAdjListNode(int dest, int peso) {
        AdjListNode* newNode = new AdjListNode;
        newNode->dest = dest;
        newNode->peso = peso;
        newNode->next = nullptr;
        return newNode;
    }

    // Método para agregar una arista al grafo (no dirigido)
    void addEdge(int src, int dest, int peso) {
        // Agregar arista desde src a dest
        AdjListNode* newNode = newAdjListNode(dest, peso);
        newNode->next = array[src].head;
        array[src].head = newNode;

        // Agregar arista desde dest a src (para grafo no dirigido)
        newNode = newAdjListNode(src, peso);
        newNode->next = array[dest].head;
        array[dest].head = newNode;
    }

    // Método para imprimir el grafo
    void printGraph() {
        for(int v = 0; v < V; ++v) {
            AdjListNode* pCrawl = array[v].head;
            cout << "Vértice " << v << ":";
            while(pCrawl) {
                cout << " -> (" << pCrawl->dest << ", " << pCrawl->peso << ")";
                pCrawl = pCrawl->next;
            }
            cout << endl;
        }
    }
};

// Estructura para representar un nodo en el min-heap
struct MinHeapNode {
    int vertice;
    int distancia;
};

// Clase para implementar una cola de prioridad (min-heap)
class MinHeap {
private:
    int capacidad;  // Capacidad del heap
    int tamaño;      // Tamaño actual del heap
    int pos[100];    // Posición de cada vértice en el heap
    MinHeapNode** array; // Array de punteros a MinHeapNode

    // Métodos auxiliares
    void intercambiarMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
        MinHeapNode* t = *a;
        *a = *b;
        *b = t;
    }

    void minHeapify(int idx) {
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

public:
    // Constructor
    MinHeap(int capacidad) {
        this->capacidad = capacidad;
        tamaño = 0;
        array = new MinHeapNode*[capacidad];
        for(int i = 0; i < capacidad; ++i)
            array[i] = nullptr;
    }

    // Destructor para liberar memoria
    ~MinHeap() {
        for(int i = 0; i < tamaño; ++i)
            delete array[i];
        delete[] array;
    }

    // Método para verificar si el heap está vacío
    bool isEmpty() {
        return tamaño == 0;
    }

    // Método para extraer el nodo con la distancia mínima
    MinHeapNode* extractMin() {
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
    void decrementarDistancia(int vertice, int distancia) {
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
    void insertarMinHeap(int vertice, int distancia) {
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
};

// Clase para implementar el Algoritmo de Prim
class Prim {
private:
    Graph* graph;
    int src; // Vértice de inicio

public:
    // Constructor
    Prim(Graph* g, int src) {
        graph = g;
        this->src = src;
    }

    // Método para ejecutar el Algoritmo de Prim
    void ejecutarPrim() {
        int V = graph->V;
        int parent[V];    // Array para almacenar el MST
        int dist[V];      // Arreglo para almacenar las distancias mínimas
        bool inMST[V];    // Arreglo para saber si el vértice está incluido en el MST

        // Inicializar todas las distancias como infinito y marcar todos los vértices como no incluidos
        for(int i = 0; i < V; ++i) {
            dist[i] = INT32_MAX;
            inMST[i] = false;
        }

        // Crear un min-heap y insertar el primer vértice con distancia 0
        MinHeap minHeap(V);
        minHeap.insertarMinHeap(src, dist[src]);
        dist[src] = 0;
        minHeap.decrementarDistancia(src, dist[src]);

        // Asignar el primer vértice como el padre de sí mismo
        parent[src] = -1;

        while (!minHeap.isEmpty()) {
            // Extraer el vértice con la distancia mínima
            MinHeapNode* minHeapNode = minHeap.extractMin();
            int u = minHeapNode->vertice;
            inMST[u] = true;

            // Recorrer todos los vértices adyacentes de u
            AdjListNode* crawl = graph->array[u].head;
            while(crawl) {
                int v = crawl->dest;
                int peso = crawl->peso;

                // Si v no está en el MST y el peso de la arista u-v es menor que su distancia actual
                if (!inMST[v] && peso < dist[v]) {
                    dist[v] = peso;
                    parent[v] = u;
                    minHeap.insertarMinHeap(v, dist[v]);
                    minHeap.decrementarDistancia(v, dist[v]);
                }
                crawl = crawl->next;
            }
            delete minHeapNode;
        }

        // Imprimir el MST
        cout << "Aristas del Árbol de Expansión Mínima:\n";
        for(int i = 1; i < V; ++i)
            cout << parent[i] << " - " << i << " \tPeso: " << dist[i] << endl;
    }
};

// Función principal para probar la implementación del Algoritmo de Prim
int main() {
    int V = 5;
    Graph* grafo = new Graph(V);

    // Agregar aristas (no dirigido)
    grafo->addEdge(0, 1, 2);
    grafo->addEdge(0, 3, 6);
    grafo->addEdge(1, 3, 8);
    grafo->addEdge(1, 2, 3);
    grafo->addEdge(2, 3, 7);

    // Imprimir el grafo
    grafo->printGraph();
    cout << endl;

    // Crear una instancia de Prim y ejecutar el algoritmo desde el vértice 0
    Prim prim(grafo, 0);
    prim.ejecutarPrim();

    delete grafo;
    return 0;
}
