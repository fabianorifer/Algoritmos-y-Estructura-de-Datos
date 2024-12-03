// Kruskal.cpp
#include <iostream>
#include <vector>
#include <algorithm>

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
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
        aristas = new Arista[E];
    }

    // Destructor para liberar memoria
    ~Graph() {
        delete[] aristas;
    }

    // Método para agregar una arista
    void addEdge(int index, int src, int dest, int peso) {
        aristas[index].src = src;
        aristas[index].dest = dest;
        aristas[index].peso = peso;
    }

    // Método para imprimir las aristas
    void printAristas() {
        for(int i = 0; i < E; ++i)
            cout << aristas[i].src << " - " << aristas[i].dest << " \tPeso: " << aristas[i].peso << endl;
    }
};

// Clase para representar un conjunto disjunto
class DisjointSet {
public:
    int* padre;
    int* rango;

    // Constructor
    DisjointSet(int V) {
        padre = new int[V];
        rango = new int[V];
        for(int v = 0; v < V; ++v) {
            padre[v] = v;
            rango[v] = 0;
        }
    }

    // Destructor para liberar memoria
    ~DisjointSet() {
        delete[] padre;
        delete[] rango;
    }

    // Método para encontrar el conjunto al que pertenece un elemento (con compresión de caminos)
    int find(int u) {
        if (padre[u] != u)
            padre[u] = find(padre[u]);
        return padre[u];
    }

    // Método para unir dos conjuntos (por rango)
    void unionSets(int u, int v) {
        int u_root = find(u);
        int v_root = find(v);

        if (u_root == v_root)
            return;

        if (rango[u_root] < rango[v_root]) {
            padre[u_root] = v_root;
        }
        else if (rango[u_root] > rango[v_root]) {
            padre[v_root] = u_root;
        }
        else {
            padre[v_root] = u_root;
            rango[u_root]++;
        }
    }
};

// Comparador para ordenar las aristas por peso
bool compararAristas(Arista a, Arista b) {
    return a.peso < b.peso;
}

// Clase para implementar el Algoritmo de Kruskal
class Kruskal {
private:
    Graph* graph;

public:
    // Constructor
    Kruskal(Graph* g) {
        graph = g;
    }

    // Método para ejecutar el Algoritmo de Kruskal
    void ejecutarKruskal() {
        int V = graph->V;
        int E = graph->E;
        Arista result[V]; // Array para almacenar el MST
        int e = 0; // Índice para result[]
        int i = 0; // Índice para aristas ordenadas

        // Paso 1: Ordenar todas las aristas en orden no decreciente de su peso
        sort(graph->aristas, graph->aristas + E, compararAristas);

        // Crear una estructura de conjuntos disjuntos
        DisjointSet ds(V);

        // Paso 2: Iterar sobre las aristas ordenadas
        while (e < V - 1 && i < E) {
            // Paso 2a: Seleccionar la arista de menor peso
            Arista nextArista = graph->aristas[i++];

            int x = ds.find(nextArista.src);
            int y = ds.find(nextArista.dest);

            // Paso 2b: Verificar si incluir esta arista causa un ciclo
            if (x != y) {
                result[e++] = nextArista;
                ds.unionSets(x, y);
            }
            // Si causa un ciclo, se descarta la arista
        }

        // Imprimir el MST
        cout << "Aristas del Árbol de Expansión Mínima:\n";
        for(int i = 0; i < e; ++i)
            cout << result[i].src << " - " << result[i].dest << " \tPeso: " << result[i].peso << endl;
    }
};

// Función principal para probar la implementación del Algoritmo de Kruskal
int main() {
    int V = 4; // Número de vértices
    int E = 5; // Número de aristas
    Graph* grafo = new Graph(V, E);

    // Agregar aristas
    grafo->addEdge(0, 0, 1, 10);
    grafo->addEdge(1, 0, 2, 6);
    grafo->addEdge(2, 0, 3, 5);
    grafo->addEdge(3, 1, 3, 15);
    grafo->addEdge(4, 2, 3, 4);

    // Imprimir las aristas
    cout << "Aristas del Grafo:\n";
    grafo->printAristas();
    cout << endl;

    // Crear una instancia de Kruskal y ejecutar el algoritmo
    Kruskal kruskal(grafo);
    kruskal.ejecutarKruskal();

    delete grafo;
    return 0;
}
