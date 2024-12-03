// BellmanFord.h
#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <iostream>
#include <vector>
#include <climits>

// Usamos namespace std según lo solicitado
using namespace std;

// Estructura para representar una arista
struct Arista {
    int src;
    int dest;
    int peso;
};

// Clase para representar el Grafo
class Graph {
public:
    int V; // Número de vértices
    int E; // Número de aristas
    Arista* aristas; // Array de aristas

    // Constructor
    Graph(int V, int E);

    // Destructor
    ~Graph();
};

// Clase para implementar el Algoritmo de Bellman-Ford
class BellmanFord {
private:
    Graph* graph;
    int src;
    int* dist; // Arreglo de distancias

public:
    // Constructor
    BellmanFord(Graph* g, int src);

    // Destructor
    ~BellmanFord();

    // Método para ejecutar el algoritmo
    bool encontrarCaminosMasCortos();

    // Método para imprimir las distancias
    void imprimirDistancias();
};

#endif // BELLMANFORD_H
