// FloydWarshall.cpp
#include "FloydWarshall.h"

// Constructor de Graph
Graph::Graph(int V) {
    this->V = V;
    // Crear la matriz de adyacencia y inicializarla
    matriz = new int*[V];
    for(int i = 0; i < V; ++i) {
        matriz[i] = new int[V];
        for(int j = 0; j < V; ++j) {
            if(i == j)
                matriz[i][j] = 0;
            else
                matriz[i][j] = INT32_MAX;
        }
    }
}

// Destructor de Graph
Graph::~Graph() {
    for(int i = 0; i < V; ++i)
        delete[] matriz[i];
    delete[] matriz;
}

// Método para agregar una arista
void Graph::agregarArista(int src, int dest, int peso, bool dirigido) {
    matriz[src][dest] = peso;
    if(!dirigido)
        matriz[dest][src] = peso;
}

// Método para imprimir la matriz de adyacencia
void Graph::imprimirMatriz() {
    cout << "Matriz de Adyacencia:" << endl;
    for(int i = 0; i < V; ++i) {
        for(int j = 0; j < V; ++j) {
            if(matriz[i][j] == INT32_MAX)
                cout << "INF\t";
            else
                cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}

// Constructor de FloydWarshall
FloydWarshall::FloydWarshall(Graph* g) {
    graph = g;
    // Inicializar la matriz de distancias
    dist = new int*[graph->V];
    for(int i = 0; i < graph->V; ++i) {
        dist[i] = new int[graph->V];
        for(int j = 0; j < graph->V; ++j)
            dist[i][j] = graph->matriz[i][j];
    }
}

// Destructor de FloydWarshall
FloydWarshall::~FloydWarshall() {
    for(int i = 0; i < graph->V; ++i)
        delete[] dist[i];
    delete[] dist;
}

// Método para ejecutar el Algoritmo de Floyd-Warshall
void FloydWarshall::ejecutarAlgoritmo() {
    int V = graph->V;
    for(int k = 0; k < V; ++k) {
        for(int i = 0; i < V; ++i) {
            for(int j = 0; j < V; ++j) {
                if(dist[i][k] != INT32_MAX && dist[k][j] != INT32_MAX
                   && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

// Método para imprimir la matriz de distancias
void FloydWarshall::imprimirDistancias() {
    cout << "Matriz de Distancias Mínimas:" << endl;
    for(int i = 0; i < graph->V; ++i) {
        for(int j = 0; j < graph->V; ++j) {
            if(dist[i][j] == INT32_MAX)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

// Función main para probar la implementación de Floyd-Warshall
int main() {
    int V = 4;
    Graph* grafo = new Graph(V);

    // Agregar aristas
    grafo->agregarArista(0, 1, 5);
    grafo->agregarArista(0, 3, 10);
    grafo->agregarArista(1, 2, 3);
    grafo->agregarArista(2, 3, 1);

    // Imprimir la matriz de adyacencia
    grafo->imprimirMatriz();
    cout << endl;

    // Crear una instancia de FloydWarshall y ejecutar el algoritmo
    FloydWarshall fw(grafo);
    fw.ejecutarAlgoritmo();
    fw.imprimirDistancias();

    delete grafo;
    return 0;
}
