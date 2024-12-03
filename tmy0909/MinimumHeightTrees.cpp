// MinimumHeightTrees.cpp
// Contexto: Encontrar las raíces que minimizan la altura del árbol eliminando hojas iterativamente.

#include <iostream>
#include <vector>
#include <queue>
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

        // Como es no dirigido, agregar src a la lista de dest
        nuevoNodo = new AdjListNode(src);
        nuevoNodo->siguiente = array[dest];
        array[dest] = nuevoNodo;
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

// Función para encontrar los árboles de altura mínima
vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if(n == 1)
        return {0};

    // Crear el grafo
    Grafo grafo(n);
    for(auto &edge : edges)
        grafo.agregarArista(edge[0], edge[1]);

    // Calcular el grado de cada nodo
    int* grado = new int[n];
    for(int i = 0; i < n; ++i)
        grado[i] = 0;
    for(int i = 0; i < n; ++i){
        AdjListNode* actual = grafo.array[i];
        while(actual){
            grado[i]++;
            actual = actual->siguiente;
        }
    }

    // Inicializar la cola con las hojas
    queue<int> q;
    for(int i = 0; i < n; ++i)
        if(grado[i] <= 1)
            q.push(i);

    int restantes = n;
    vector<int> hojas;

    while(restantes > 2){
        int tamaño = q.size();
        restantes -= tamaño;
        hojas.clear();
        for(int i = 0; i < tamaño; ++i){
            int hoja = q.front();
            q.pop();
            hojas.push_back(hoja);

            // Reducir el grado de los vecinos
            AdjListNode* actual = grafo.array[hoja];
            while(actual){
                int vecino = actual->dest;
                grado[vecino]--;
                if(grado[vecino] == 1)
                    q.push(vecino);
                actual = actual->siguiente;
            }
        }
    }

    // Los nodos restantes son las raíces
    hojas.clear();
    while(!q.empty()){
        hojas.push_back(q.front());
        q.pop();
    }

    delete[] grado;
    return hojas;
}

// Función main para probar
int main(){
    int n = 4;
    vector<vector<int>> edges = {{1,0},{1,2},{1,3}};

    vector<int> roots = findMinHeightTrees(n, edges);
    cout << "Raíces de los Árboles de Altura Mínima: ";
    for(auto &root : roots)
        cout << root << " ";
    cout << endl;

    return 0;
}
