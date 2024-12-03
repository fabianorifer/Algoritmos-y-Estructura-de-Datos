// DetectCycleDirected.cpp
// Contexto: En un grafo dirigido, determinar si existe al menos un ciclo. Esto es crucial para aplicaciones como la detección de dependencias circulares en sistemas de compilación.

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

// Clase para implementar DFS y detectar ciclos
class DFS {
public:
    Grafo* grafo;
    int V;
    bool* visitado;
    bool* enRecursivo;
    bool cicloEncontrado;

    DFS(Grafo* g){
        grafo = g;
        V = g->V;
        visitado = new bool[V];
        enRecursivo = new bool[V];
        cicloEncontrado = false;
        for(int i = 0; i < V; ++i){
            visitado[i] = false;
            enRecursivo[i] = false;
        }
    }

    void detectarCiclo(int u){
        if(cicloEncontrado)
            return;
        visitado[u] = true;
        enRecursivo[u] = true;

        AdjListNode* actual = grafo->array[u];
        while(actual){
            int v = actual->dest;
            if(!visitado[v]){
                detectarCiclo(v);
            }
            else if(enRecursivo[v]){
                cicloEncontrado = true;
                return;
            }
            actual = actual->siguiente;
        }

        enRecursivo[u] = false;
    }

    bool tieneCiclo(){
        for(int i = 0; i < V; ++i){
            if(!visitado[i]){
                detectarCiclo(i);
                if(cicloEncontrado)
                    break;
            }
        }
        return cicloEncontrado;
    }

    ~DFS(){
        delete[] visitado;
        delete[] enRecursivo;
    }
};

// Función principal para probar
int main(){
    int V = 4;
    Grafo grafo(V);
    // Definir las aristas
    grafo.agregarArista(0,1);
    grafo.agregarArista(1,2);
    grafo.agregarArista(2,0);
    grafo.agregarArista(2,3);

    DFS dfs(&grafo);
    if(dfs.tieneCiclo())
        std::cout << "El grafo contiene un ciclo." << std::endl;
    else
        std::cout << "El grafo no contiene ningún ciclo." << std::endl;

    return 0;
}
