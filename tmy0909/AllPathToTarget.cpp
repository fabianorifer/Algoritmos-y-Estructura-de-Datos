// AllPathsSourceTarget.cpp
// Contexto: Encontrar todos los caminos posibles desde el nodo fuente hasta el nodo objetivo en un DAG.

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// Estructura para representar una lista de adyacencia
struct AdjListNode {
    int dest;
    AdjListNode* siguiente;

    AdjListNode(int d) : dest(d), siguiente(nullptr) {}
};

// Clase para representar el grafo
class Grafo {
public:
    int V;
    AdjListNode** array;

    Grafo(int V){
        this->V = V;
        array = new AdjListNode*[V];
        for(int i = 0; i < V; ++i)
            array[i] = nullptr;
    }

    void agregarArista(int src, int dest){
        AdjListNode* nuevoNodo = new AdjListNode(dest);
        nuevoNodo->siguiente = array[src];
        array[src] = nuevoNodo;
    }

    ~Grafo(){
        for(int i = 0; i < V; ++i){
            AdjListNode* actual = array[i];
            while(actual){
                AdjListNode* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }
        delete[] array;
    }
};

// Clase para implementar DFS y encontrar todos los caminos
class DFS {
public:
    Grafo* grafo;
    int destino;
    vector<vector<int>>* todosLosCaminos;
    int* caminoActual;
    int profundidad;

    DFS(Grafo* g, int dest, int maxProfundidad){
        grafo = g;
        destino = dest;
        todosLosCaminos = new vector<vector<int>>();
        caminoActual = new int[maxProfundidad];
        profundidad = 0;
    }

    void dfsExplorar(int u){
        caminoActual[profundidad++] = u;

        if(u == destino){
            // Guardar el camino actual
            vector<int> camino;
            for(int i = 0; i < profundidad; ++i)
                camino.push_back(caminoActual[i]);
            todosLosCaminos->push_back(camino);
        }
        else{
            AdjListNode* actual = grafo->array[u];
            while(actual){
                dfsExplorar(actual->dest);
                actual = actual->siguiente;
            }
        }

        profundidad--;
    }

    vector<vector<int>> obtenerCaminos(){
        dfsExplorar(0);
        return *todosLosCaminos;
    }

    ~DFS(){
        delete todosLosCaminos;
        delete[] caminoActual;
    }
};

// Función para encontrar todos los caminos desde la fuente hasta el destino
vector<vector<int>> allPathsSourceTarget(int n, vector<vector<int>>& edges) {
    Grafo grafo(n);
    for(auto &edge : edges)
        grafo.agregarArista(edge[0], edge[1]);

    DFS dfs(&grafo, n-1, n);
    return dfs.obtenerCaminos();
}

// Función main para probar
int main(){
    int n = 4;
    vector<vector<int>> edges = {{0,1},{0,2},{1,3},{2,3}};

    vector<vector<int>> caminos = allPathsSourceTarget(n, edges);

    cout << "Todos los Caminos desde 0 hasta " << n-1 << ":" << endl;
    for(auto &camino : caminos){
        for(auto it = camino.begin(); it != camino.end(); ++it){
            cout << *it;
            if(it != camino.end()-1)
                cout << " -> ";
        }
        cout << endl;
    }

    return 0;
}
