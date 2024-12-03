// AEstrella.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// Estructura para representar una arista en el grafo
struct AdjListNode {
    int dest;
    double peso;
    AdjListNode* next;
};

// Clase para representar el Grafo
class Graph {
public:
    int V; // Número de vértices
    AdjListNode** array; // Arreglo de listas de adyacencia

    // Constructor
    Graph(int V) {
        this->V = V;
        array = new AdjListNode*[V];
        for(int i = 0; i < V; ++i)
            array[i] = nullptr;
    }

    // Destructor para liberar memoria
    ~Graph() {
        for(int v = 0; v < V; ++v) {
            AdjListNode* current = array[v];
            while(current) {
                AdjListNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] array;
    }

    // Método para crear un nuevo nodo de lista de adyacencia
    AdjListNode* newAdjListNode(int dest, double peso) {
        AdjListNode* newNode = new AdjListNode;
        newNode->dest = dest;
        newNode->peso = peso;
        newNode->next = nullptr;
        return newNode;
    }

    // Método para agregar una arista al grafo (dirigido)
    void addEdge(int src, int dest, double peso) {
        AdjListNode* newNode = newAdjListNode(dest, peso);
        newNode->next = array[src];
        array[src] = newNode;
    }

    // Método para imprimir el grafo
    void printGraph() {
        for(int v = 0; v < V; ++v) {
            AdjListNode* pCrawl = array[v];
            cout << "Vértice " << v << ":";
            while(pCrawl) {
                cout << " -> (" << pCrawl->dest << ", " << pCrawl->peso << ")";
                pCrawl = pCrawl->next;
            }
            cout << endl;
        }
    }
};

// Estructura para representar un nodo en la cola de prioridad
struct NodoPrioridad {
    int vertice;
    double f;

    bool operator<(const NodoPrioridad& other) const {
        return f > other.f; // Para que el min-heap funcione correctamente
    }
};

// Clase para implementar el Algoritmo A*
class AEstrella {
private:
    Graph* graph;
    vector<pair<int, int>> coordenadas; // Coordenadas (x, y) de cada vértice

    // Función heurística (distancia Euclidiana)
    double heuristica(int a, int b) {
        double dx = coordenadas[a].first - coordenadas[b].first;
        double dy = coordenadas[a].second - coordenadas[b].second;
        return sqrt(dx*dx + dy*dy);
    }

public:
    // Constructor
    AEstrella(Graph* g, vector<pair<int, int>> coords) {
        graph = g;
        coordenadas = coords;
    }

    // Método para encontrar el camino más corto desde start hasta goal
    void encontrarCamino(int start, int goal) {
        // Vector para almacenar las distancias g(n)
        vector<double> g_score(graph->V, INFINITY);
        g_score[start] = 0.0;

        // Vector para almacenar las direcciones anteriores
        vector<int> came_from(graph->V, -1);

        // Cola de prioridad para seleccionar el nodo con menor f(n) = g(n) + h(n)
        priority_queue<NodoPrioridad> open_set;
        NodoPrioridad np;
        np.vertice = start;
        np.f = heuristica(start, goal);
        open_set.push(np);

        // Vector para marcar nodos ya evaluados
        vector<bool> closed_set(graph->V, false);

        while(!open_set.empty()) {
            NodoPrioridad current = open_set.top();
            open_set.pop();
            int u = current.vertice;

            if(u == goal)
                break;

            if(closed_set[u])
                continue;
            closed_set[u] = true;

            AdjListNode* adj = graph->array[u];
            while(adj) {
                int v = adj->dest;
                double tentative_g_score = g_score[u] + adj->peso;
                if(tentative_g_score < g_score[v]) {
                    came_from[v] = u;
                    g_score[v] = tentative_g_score;
                    NodoPrioridad np;
                    np.vertice = v;
                    np.f = g_score[v] + heuristica(v, goal);
                    open_set.push(np);
                }
                adj = adj->next;
            }
        }

        // Reconstruir el camino
        if(came_from[goal] == -1) {
            cout << "No se encontró un camino desde " << start << " hasta " << goal << "." << endl;
            return;
        }

        vector<int> camino;
        int current = goal;
        while(current != -1) {
            camino.push_back(current);
            current = came_from[current];
        }

        // Imprimir el camino
        cout << "Camino encontrado desde " << start << " hasta " << goal << ": ";
        for(auto it = camino.rbegin(); it != camino.rend(); ++it)
            cout << *it << " ";
        cout << endl;

        // Imprimir la distancia total
        cout << "Distancia total: " << g_score[goal] << endl;
    }
};

// Función main para probar la implementación del Algoritmo A*
int main() {
    // Crear un grafo con 6 vértices
    int V = 6;
    Graph g(V);

    // Agregar aristas (dirigidas)
    g.addEdge(0, 1, 1.0);
    g.addEdge(0, 2, 4.0);
    g.addEdge(1, 2, 2.0);
    g.addEdge(1, 3, 5.0);
    g.addEdge(2, 3, 1.0);
    g.addEdge(3, 4, 3.0);
    g.addEdge(4, 5, 2.0);
    g.addEdge(2, 5, 7.0);

    // Coordenadas de cada vértice (para la heurística)
    vector<pair<int, int>> coords = {
            {0, 0}, // Vértice 0
            {2, 0}, // Vértice 1
            {2, 2}, // Vértice 2
            {4, 2}, // Vértice 3
            {4, 4}, // Vértice 4
            {6, 4}  // Vértice 5
    };

    // Imprimir el grafo
    cout << "Representación del Grafo:" << endl;
    g.printGraph();
    cout << endl;

    // Crear una instancia de AEstrella y encontrar el camino
    AEstrella aStar(&g, coords);
    aStar.encontrarCamino(0, 5);

    return 0;
}
