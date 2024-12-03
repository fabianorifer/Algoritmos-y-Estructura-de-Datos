// BellmanFord.cpp
#include "BellmanFord.h"

// Constructor de Graph
Graph::Graph(int V, int E) {
    this->V = V;
    this->E = E;
    aristas = new Arista[E];
}

// Destructor de Graph
Graph::~Graph() {
    delete[] aristas;
}

// Constructor de BellmanFord
BellmanFord::BellmanFord(Graph* g, int src) {
    graph = g;
    this->src = src;
    dist = new int[graph->V];
    for(int i = 0; i < graph->V; ++i)
        dist[i] = INT32_MAX;
    dist[src] = 0;
}

// Destructor de BellmanFord
BellmanFord::~BellmanFord() {
    delete[] dist;
}

// Método para ejecutar el Algoritmo de Bellman-Ford
bool BellmanFord::encontrarCaminosMasCortos() {
    // Relajar todas las aristas V-1 veces
    for(int i = 1; i <= graph->V - 1; ++i) {
        for(int j = 0; j < graph->E; ++j) {
            int u = graph->aristas[j].src;
            int v = graph->aristas[j].dest;
            int peso = graph->aristas[j].peso;
            if(dist[u] != INT32_MAX && dist[u] + peso < dist[v])
                dist[v] = dist[u] + peso;
        }
    }

    // Verificar ciclos de peso negativo
    for(int j = 0; j < graph->E; ++j) {
        int u = graph->aristas[j].src;
        int v = graph->aristas[j].dest;
        int peso = graph->aristas[j].peso;
        if(dist[u] != INT32_MAX && dist[u] + peso < dist[v])
            return false; // Existe ciclo de peso negativo
    }

    return true; // No hay ciclos de peso negativo
}

// Método para imprimir las distancias
void BellmanFord::imprimirDistancias() {
    cout << "Vértice\tDistancia desde la fuente " << src << endl;
    for(int i = 0; i < graph->V; ++i)
        cout << i << "\t\t" << (dist[i] == INT32_MAX ? -1 : dist[i]) << endl;
}

// Función main para probar la implementación de Bellman-Ford
int main() {
    int V = 5; // Número de vértices
    int E = 8; // Número de aristas
    Graph* grafo = new Graph(V, E);

    // Agregar aristas
    grafo->aristas[0].src = 0;
    grafo->aristas[0].dest = 1;
    grafo->aristas[0].peso = -1;

    grafo->aristas[1].src = 0;
    grafo->aristas[1].dest = 2;
    grafo->aristas[1].peso = 4;

    grafo->aristas[2].src = 1;
    grafo->aristas[2].dest = 2;
    grafo->aristas[2].peso = 3;

    grafo->aristas[3].src = 1;
    grafo->aristas[3].dest = 3;
    grafo->aristas[3].peso = 2;

    grafo->aristas[4].src = 1;
    grafo->aristas[4].dest = 4;
    grafo->aristas[4].peso = 2;

    grafo->aristas[5].src = 3;
    grafo->aristas[5].dest = 2;
    grafo->aristas[5].peso = 5;

    grafo->aristas[6].src = 3;
    grafo->aristas[6].dest = 1;
    grafo->aristas[6].peso = 1;

    grafo->aristas[7].src = 4;
    grafo->aristas[7].dest = 3;
    grafo->aristas[7].peso = -3;

    // Crear una instancia de BellmanFord y ejecutar el algoritmo
    BellmanFord bf(grafo, 0);
    if(bf.encontrarCaminosMasCortos()) {
        bf.imprimirDistancias();
    } else {
        cout << "El grafo contiene un ciclo de peso negativo." << endl;
    }

    delete grafo;
    return 0;
}
