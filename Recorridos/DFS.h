// DFS.h
#ifndef DFS_H
#define DFS_H

#include <iostream>

// Reutilizamos las estructuras AdjListNode y AdjList de BFS.h
struct AdjListNode {
    int dest;
    AdjListNode* next;
};

struct AdjList {
    AdjListNode* head;
};

// Clase para representar el Grafo
class Graph {
public:
    int V;          // Número de vértices
    AdjList* array; // Arreglo de listas de adyacencia

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

// Clase para implementar DFS
class DFS {
private:
    Graph* graph;
    bool* visitado;

    // Método auxiliar para DFS
    void dfsAux(int vertice);

public:
    // Constructor
    DFS(Graph* g);

    // Destructor
    ~DFS();

    // Método para realizar DFS desde un vértice dado
    void dfs(int inicio);
};

#endif // DFS_H
