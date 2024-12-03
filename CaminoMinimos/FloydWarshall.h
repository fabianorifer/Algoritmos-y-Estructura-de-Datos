// FloydWarshall.h
#ifndef FLOYDWARSHALL_H
#define FLOYDWARSHALL_H

#include <iostream>
#include <climits>

// Usamos namespace std según lo solicitado
using namespace std;

// Clase para representar el Grafo usando una matriz de adyacencia
class Graph {
public:
    int V; // Número de vértices
    int** matriz; // Matriz de adyacencia

    // Constructor
    Graph(int V);

    // Destructor
    ~Graph();

    // Método para agregar una arista
    void agregarArista(int src, int dest, int peso, bool dirigido = false);

    // Método para imprimir la matriz de adyacencia
    void imprimirMatriz();
};

// Clase para implementar el Algoritmo de Floyd-Warshall
class FloydWarshall {
private:
    Graph* graph;
    int** dist; // Matriz de distancias

public:
    // Constructor
    FloydWarshall(Graph* g);

    // Destructor
    ~FloydWarshall();

    // Método para ejecutar el algoritmo
    void ejecutarAlgoritmo();

    // Método para imprimir la matriz de distancias
    void imprimirDistancias();
};

#endif // FLOYDWARSHALL_H
