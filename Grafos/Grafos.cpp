// Grafos.cpp
#include "Grafos.h"

// Constructor
Graph::Graph(int V) {
    this->V = V;
    array = new AdjList[V];
    for(int i = 0; i < V; ++i)
        array[i].head = nullptr;
}

// Destructor para liberar memoria
Graph::~Graph() {
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
AdjListNode* Graph::newAdjListNode(int dest) {
    AdjListNode* newNode = new AdjListNode;
    newNode->dest = dest;
    newNode->next = nullptr;
    return newNode;
}

// Método para agregar una arista al grafo (no dirigido)
void Graph::addEdge(int src, int dest) {
    // Agregar arista desde src a dest
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = array[src].head;
    array[src].head = newNode;

    // Agregar arista desde dest a src (para grafo no dirigido)
    newNode = newAdjListNode(src);
    newNode->next = array[dest].head;
    array[dest].head = newNode;
}

// Método para imprimir el grafo
void Graph::printGraph() {
    for(int v = 0; v < V; ++v) {
        AdjListNode* pCrawl = array[v].head;
        std::cout << "Vértice " << v << ":";
        while(pCrawl) {
            std::cout << " -> " << pCrawl->dest;
            pCrawl = pCrawl->next;
        }
        std::cout << std::endl;
    }
}

// Función main para probar la implementación
int main() {
    // Crear un grafo con 5 vértices
    int V = 5;
    Graph g(V);

    // Agregar algunas aristas
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // Imprimir el grafo
    g.printGraph();

    return 0;
}
