// OrdenamientoTopologico.cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Estructura para representar una arista en el grafo
struct AdjListNode {
    int dest;
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
    AdjListNode* newAdjListNode(int dest) {
        AdjListNode* newNode = new AdjListNode;
        newNode->dest = dest;
        newNode->next = nullptr;
        return newNode;
    }

    // Método para agregar una arista al grafo (dirigido)
    void addEdge(int src, int dest) {
        AdjListNode* newNode = newAdjListNode(dest);
        newNode->next = array[src];
        array[src] = newNode;
    }

    // Método para imprimir el grafo
    void printGraph() {
        for(int v = 0; v < V; ++v) {
            AdjListNode* pCrawl = array[v];
            cout << "Vértice " << v << ":";
            while(pCrawl) {
                cout << " -> " << pCrawl->dest;
                pCrawl = pCrawl->next;
            }
            cout << endl;
        }
    }
};

// Clase para implementar el Ordenamiento Topológico
class OrdenamientoTopologico {
private:
    Graph* graph;

public:
    // Constructor
    OrdenamientoTopologico(Graph* g) {
        graph = g;
    }

    // Método para ejecutar el ordenamiento topológico
    void ejecutarOrdenamiento() {
        int V = graph->V;
        vector<int> in_degree(V, 0);

        // Calcular el in_degree de cada vértice
        for(int u = 0; u < V; u++) {
            AdjListNode* adj = graph->array[u];
            while(adj) {
                in_degree[adj->dest]++;
                adj = adj->next;
            }
        }

        // Crear una cola y encolar todos los vértices con in_degree 0
        queue<int> q;
        for(int i = 0; i < V; i++)
            if(in_degree[i] == 0)
                q.push(i);

        int cnt = 0;
        vector<int> orden;

        while(!q.empty()) {
            int u = q.front();
            q.pop();
            orden.push_back(u);

            AdjListNode* adj = graph->array[u];
            while(adj) {
                if(--in_degree[adj->dest] == 0)
                    q.push(adj->dest);
                adj = adj->next;
            }
            cnt++;
        }

        // Verificar si hay un ciclo
        if(cnt != V) {
            cout << "El grafo tiene un ciclo, no se puede realizar el ordenamiento topológico." << endl;
            return;
        }

        // Imprimir el orden topológico
        cout << "Ordenamiento Topológico: ";
        for(auto it = orden.begin(); it != orden.end(); ++it)
            cout << *it << " ";
        cout << endl;
    }
};

// Función main para probar la implementación del Ordenamiento Topológico
int main() {
    // Crear un grafo con 6 vértices
    int V = 6;
    Graph g(V);

    // Agregar aristas (dirigidas)
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    // Imprimir el grafo
    cout << "Representación del Grafo:" << endl;
    g.printGraph();
    cout << endl;

    // Crear una instancia de OrdenamientoTopologico y ejecutar el ordenamiento
    OrdenamientoTopologico ot(&g);
    ot.ejecutarOrdenamiento();

    return 0;
}
