// ShortestPathUnweighted.cpp
// Contexto: Encontrar la distancia más corta entre dos nodos en un grafo no ponderado utilizando la Búsqueda en Anchura (BFS). Esto es esencial en aplicaciones como redes de comunicación y navegación.

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

// Clase para implementar una cola manualmente usando arrays
struct Cola {
    int frente;
    int final;
    int capacidad;
    int* elementos;

    Cola(int cap){
        capacidad = cap;
        frente = 0;
        final = -1;
        elementos = new int[cap];
    }

    bool estaVacia(){
        return final < frente;
    }

    void encolar(int val){
        if(final +1 >= capacidad)
            return; // Cola llena
        elementos[++final] = val;
    }

    int desencolar(){
        if(estaVacia())
            return -1;
        return elementos[frente++];
    }

    ~Cola(){
        delete[] elementos;
    }
};

// Clase para implementar BFS y encontrar el camino más corto
class BFS {
public:
    Grafo* grafo;
    int V;
    bool* visitado;
    int* distancia;

    BFS(Grafo* g){
        grafo = g;
        V = g->V;
        visitado = new bool[V];
        distancia = new int[V];
        for(int i = 0; i < V; ++i){
            visitado[i] = false;
            distancia[i] = -1;
        }
    }

    int caminoMasCorto(int fuente, int objetivo){
        Cola q(V);
        q.encolar(fuente);
        visitado[fuente] = true;
        distancia[fuente] = 0;

        while(!q.estaVacia()){
            int u = q.desencolar();
            AdjListNode* actual = grafo->array[u];
            while(actual){
                int v = actual->dest;
                if(!visitado[v]){
                    visitado[v] = true;
                    distancia[v] = distancia[u] + 1;
                    q.encolar(v);
                    if(v == objetivo)
                        return distancia[v];
                }
                actual = actual->siguiente;
            }
        }
        return distancia[objetivo];
    }

    ~BFS(){
        delete[] visitado;
        delete[] distancia;
    }
};

// Función principal para probar
int main(){
    int V = 6;
    Grafo grafo(V);
    // Definir las aristas
    grafo.agregarArista(0,1);
    grafo.agregarArista(0,2);
    grafo.agregarArista(1,3);
    grafo.agregarArista(2,3);
    grafo.agregarArista(3,4);
    grafo.agregarArista(4,5);

    BFS bfs(&grafo);
    int fuente = 0;
    int objetivo = 5;
    int distancia = bfs.caminoMasCorto(fuente, objetivo);
    if(distancia != -1)
        std::cout << "La distancia más corta desde " << fuente << " hasta " << objetivo << " es: " << distancia << std::endl;
    else
        std::cout << "No existe un camino desde " << fuente << " hasta " << objetivo << "." << std::endl;

    return 0;
}
