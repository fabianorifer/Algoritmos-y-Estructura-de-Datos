// Dijkstra.h
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <climits>

// Usamos namespace std según lo solicitado
using namespace std;

// Estructura para representar una arista en la lista de adyacencia
struct AdjListNode {
    int dest;
    int peso;
    AdjListNode* next;
};

// Clase para representar el Grafo
class Graph {
public:
    int V;          // Número de vértices
    AdjListNode** array; // Arreglo de listas de adyacencia

    // Constructor
    Graph(int V);

    // Destructor
    ~Graph();

    // Método para crear un nuevo nodo de lista de adyacencia
    AdjListNode* newAdjListNode(int dest, int peso);

    // Método para agregar una arista al grafo (dirigido)
    void addEdge(int src, int dest, int peso);

    // Método para imprimir el grafo
    void printGraph();
};

// Estructura para un elemento en el min-heap
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
    void intercambiarMinHeapNode(MinHeapNode** a, MinHeapNode** b);
    void minHeapify(int idx);

public:
    // Constructor
    MinHeap(int capacidad);

    // Destructor
    ~MinHeap();

    // Método para verificar si el heap está vacío
    bool isEmpty();

    // Método para extraer el nodo con la distancia mínima
    MinHeapNode* extractMin();

    // Método para decrementar la distancia de un vértice
    void decrementarDistancia(int vertice, int distancia);

    // Método para insertar un nuevo nodo en el heap
    void insertarMinHeap(int vertice, int distancia);
};

// Clase para implementar el Algoritmo de Dijkstra
class Dijkstra {
private:
    Graph* graph;

public:
    // Constructor
    Dijkstra(Graph* g);

    // Método para encontrar los caminos más cortos desde una fuente
    void encontrarCaminosMasCortos(int src);
};

#endif // DIJKSTRA_H
