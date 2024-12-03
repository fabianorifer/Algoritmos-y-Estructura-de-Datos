// IsGraphBipartite.cpp
// Contexto: Determinar si un grafo puede dividirse en dos conjuntos disjuntos de nodos tal que no haya aristas entre nodos del mismo conjunto. Esto es útil en problemas de asignación de recursos sin conflictos.

#include <iostream>

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

// Clase para implementar BFS y verificar si el grafo es bipartito
class BFS {
public:
    Grafo* grafo;
    int V;
    int* color; // 0: no coloreado, 1 y -1: dos colores

    BFS(Grafo* g){
        grafo = g;
        V = g->V;
        color = new int[V];
        for(int i = 0; i < V; ++i)
            color[i] = 0;
    }

    bool esBipartito(){
        for(int i = 0; i < V; ++i){
            if(color[i] == 0){
                // Iniciar BFS desde el nodo i
                if(!bfsColorear(i))
                    return false;
            }
        }
        return true;
    }

    bool bfsColorear(int src){
        // Implementar una cola manual usando arrays
        int capacidad = V;
        int frente = 0;
        int final = -1;
        int* cola = new int[capacidad];

        // Encolar
        cola[++final] = src;
        color[src] = 1;

        while(frente <= final){
            int u = cola[frente++];

            AdjListNode* actual = grafo->array[u];
            while(actual){
                int v = actual->dest;
                if(color[v] == 0){
                    color[v] = -color[u];
                    cola[++final] = v;
                }
                else if(color[v] == color[u]){
                    delete[] cola;
                    return false;

