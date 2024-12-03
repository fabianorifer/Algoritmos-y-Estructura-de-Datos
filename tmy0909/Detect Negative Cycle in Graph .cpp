// DetectNegativeCycle.cpp
// Contexto: Identificar si un grafo dirigido contiene al menos un ciclo cuyo peso total es negativo, lo cual puede indicar inconsistencias en la red de rutas o oportunidades de arbitraje.

#include <iostream>
#include <climits>

// Estructura para representar una arista
struct Arista {
    int src;
    int dest;
    int peso;
};

// Clase para representar el grafo
class Grafo {
public:
    int V; // Número de vértices
    int E; // Número de aristas
    Arista* aristas;

    Grafo(int V, int E) {
        this->V = V;
        this->E = E;
        aristas = new Arista[E];
    }

    void agregarArista(int index, int src, int dest, int peso) {
        aristas[index].src = src;
        aristas[index].dest = dest;
        aristas[index].peso = peso;
    }

    ~Grafo() {
        delete[] aristas;
    }
};

// Clase para implementar el Algoritmo de Bellman-Ford
class BellmanFord {
public:
    Grafo* grafo;
    int src;
    int* dist;

    BellmanFord(Grafo* g, int src) {
        grafo = g;
        this->src = src;
        dist = new int[grafo->V];
        for(int i = 0; i < grafo->V; ++i)
            dist[i] = INT32_MAX;
        dist[src] = 0;
    }

    bool detectarCicloNegativo() {
        // Relajar todas las aristas V-1 veces
        for(int i = 1; i <= grafo->V - 1; ++i) {
            for(int j = 0; j < grafo->E; ++j) {
                int u = grafo->aristas[j].src;
                int v = grafo->aristas[j].dest;
                int peso = grafo->aristas[j].peso;
                if(dist[u] != INT32_MAX && dist[u] + peso < dist[v])
                    dist[v] = dist[u] + peso;
            }
        }

        // Verificar ciclos de peso negativo
        for(int j = 0; j < grafo->E; ++j) {
            int u = grafo->aristas[j].src;
            int v = grafo->aristas[j].dest;
            int peso = grafo->aristas[j].peso;
            if(dist[u] != INT32_MAX && dist[u] + peso < dist[v])
                return true; // Existe ciclo negativo
        }
        return false; // No hay ciclo negativo
    }

    ~BellmanFord() {
        delete[] dist;
    }
};

// Función main para probar
int main() {
    int V = 5; // Número de vértices
    int E = 8; // Número de aristas
    Grafo grafo(V, E);

    // Agregar aristas
    grafo.agregarArista(0, 0, 1, -1);
    grafo.agregarArista(1, 0, 2, 4);
    grafo.agregarArista(2, 1, 2, 3);
    grafo.agregarArista(3, 1, 3, 2);
    grafo.agregarArista(4, 1, 4, 2);
    grafo.agregarArista(5, 3, 2, 5);
    grafo.agregarArista(6, 3, 1, 1);
    grafo.agregarArista(7, 4, 3, -3);

    // Crear una instancia de BellmanFord y detectar ciclo negativo
    BellmanFord bf(&grafo, 0);
    if(bf.detectarCicloNegativo())
        std::cout << "El grafo contiene un ciclo de peso negativo." << std::endl;
    else
        std::cout << "El grafo no contiene ningún ciclo de peso negativo." << std::endl;

    delete grafo;
    return 0;
}
