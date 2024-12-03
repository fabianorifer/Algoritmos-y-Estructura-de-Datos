// BFS.h
#ifndef BFS_H
#define BFS_H

#include <iostream>

// Estructura para representar una arista en la lista de adyacencia
struct AdjListNode {
    int dest;
    AdjListNode* next;
};

// Estructura para representar la lista de adyacencia
struct AdjList {
    AdjListNode* head;
};

// Clase para representar el Grafo
class Graph {
private:
    int V;          // Número de vértices
    AdjList* array; // Arreglo de listas de adyacencia

public:
    // Constructor
    Graph(int V);

    // Destructor
    ~Graph();

    // Método para crear un nuevo nodo de lista de adyacencia
    AdjListNode* newAdjListNode(int dest);

    // Método para agregar una arista al grafo (no dirigido)
    void addEdge(int src, int dest);

    // Método para imprimir el grafo
    void printGraph();
};

// Clase para implementar BFS
class BFS {
private:
    Graph* graph;
    bool* visitado;

public:
    // Constructor
    BFS(Graph* g);

    // Destructor
    ~BFS();

    // Método para realizar BFS desde un vértice dado
    void bfs(int inicio);
};

#endif // BFS_H
