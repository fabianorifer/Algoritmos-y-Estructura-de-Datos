// DFS.cpp
#include "DFS.h"

using namespace std;

// Implementación de la clase Graph

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
        cout << "Vértice " << v << ":";
        while(pCrawl) {
            cout << " -> " << pCrawl->dest;
            pCrawl = pCrawl->next;
        }
        cout << endl;
    }
}

// Implementación de la clase DFS

// Constructor
DFS::DFS(Graph* g) {
    graph = g;
    visitado = new bool[graph->V];
    for(int i = 0; i < graph->V; ++i)
        visitado[i] = false;
}

// Destructor para liberar memoria
DFS::~DFS() {
    delete[] visitado;
}

// Método auxiliar para DFS
void DFS::dfsAux(int vertice) {
    visitado[vertice] = true;
    cout << vertice << " ";

    AdjListNode* crawl = graph->array[vertice].head;
    while(crawl) {
        int adj = crawl->dest;
        if(!visitado[adj])
            dfsAux(adj);
        crawl = crawl->next;
    }
}

// Método para realizar DFS desde un vértice dado
void DFS::dfs(int inicio) {
    cout << "Recorrido DFS desde el vértice " << inicio << ": ";
    dfsAux(inicio);
    cout << endl;
}

// Función main para probar la implementación de DFS
int main() {
    // Crear un grafo con 6 vértices
    int V = 6;
    Graph g(V);

    // Agregar aristas
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    // Imprimir el grafo
    cout << "Representación del Grafo:" << endl;
    g.printGraph();
    cout << endl;

    // Realizar DFS desde el vértice 0
    DFS dfsAlgo(&g);
    dfsAlgo.dfs(0);

    return 0;
}
