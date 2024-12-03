// ReorderRoutes.cpp
// Contexto: En una red de ciudades conectadas por rutas dirigidas, determinar el mínimo número de rutas que deben reorientarse para que todas las rutas conduzcan a una ciudad específica (Ciudad 0). Esto es útil en la optimización de redes de transporte.

#include <iostream>

// Estructura para representar una lista de adyacencia con dirección
struct AdjListNode {
    int dest;
    bool direccion; // true: original dirección, false: reorientada
    AdjListNode* siguiente;

    AdjListNode(int d, bool dir) : dest(d), direccion(dir), siguiente(nullptr) {}
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

    void agregarArista(int src, int dest, bool direccion){
        AdjListNode* nuevoNodo = new AdjListNode(dest, direccion);
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

// Clase para implementar DFS y contar las reorientaciones necesarias
class DFS {
public:
    Grafo* grafo;
    int V;
    bool* visitado;
    int reorientaciones;

    DFS(Grafo* g){
        grafo = g;
        V = g->V;
        visitado = new bool[V];
        for(int i = 0; i < V; ++i)
            visitado[i] = false;
        reorientaciones = 0;
    }

    void dfsExplorar(int u){
        visitado[u] = true;
        AdjListNode* actual = grafo->array[u];
        while(actual){
            int v = actual->dest;
            if(!visitado[v]){
                if(actual->direccion)
                    reorientaciones++;
                dfsExplorar(v);
            }
            actual = actual->siguiente;
        }
    }

    int contarReorientaciones(){
        dfsExplorar(0);
        return reorientaciones;
    }

    ~DFS(){
        delete[] visitado;
    }
};

// Función para reordenar rutas
int minReorder(int n, int** connections, int E) {
    Grafo grafo(n);
    for(int i = 0; i < E; ++i)
        grafo.agregarArista(connections[i][0], connections[i][1], true); // Dirección original

    // Agregar aristas en sentido contrario sin dirección original
    for(int i = 0; i < E; ++i)
        grafo.agregarArista(connections[i][1], connections[i][0], false);

    DFS dfs(&grafo);
    return dfs.contarReorientaciones();
}

// Función main para probar
int main(){
    int n = 6;
    int E = 5;
    int** connections = new int*[E];
    connections[0] = new int[2]{0,1};
    connections[1] = new int[2]{1,3};
    connections[2] = new int[2]{2,3};
    connections[3] = new int[2]{4,0};
    connections[4] = new int[2]{4,5};

    int resultado = minReorder(n, connections, E);
    std::cout << "Número mínimo de reorientaciones necesarias: " << resultado << std::endl;

    // Liberar memoria
    for(int i = 0; i < E; ++i)
        delete[] connections[i];
    delete[] connections;

    return 0;
}
