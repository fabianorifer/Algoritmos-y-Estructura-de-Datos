// FindAllReachableNodes.cpp
// Contexto: En un grafo dirigido, identificar todos los nodos que son alcanzables desde un nodo fuente específico. Esto es útil en análisis de redes y propagación de información.

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

// Clase para implementar BFS y encontrar nodos alcanzables
class BFS {
public:
    Grafo* grafo;
    int V;
    bool* visitado;

    BFS(Grafo* g){
        grafo = g;
        V = g->V;
        visitado = new bool[V];
        for(int i = 0; i < V; ++i)
            visitado[i] = false;
    }

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

    void encontrarAlcanzables(int fuente){
        Cola q(V);
        q.encolar(fuente);
        visitado[fuente] = true;

        while(!q.estaVacia()){
            int u = q.desencolar();
            AdjListNode* actual = grafo->array[u];
            while(actual){
                int v = actual->dest;
                if(!visitado[v]){
                    visitado[v] = true;
                    q.encolar(v);
                }
                actual = actual->siguiente;
            }
        }
    }

    void imprimirAlcanzables(){
        std::cout << "Nodos alcanzables desde la fuente: ";
        for(int i = 0; i < V; ++i){
            if(visitado[i])
                std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    ~BFS(){
        delete[] visitado;
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

    int fuente = 0;
    BFS bfs(&grafo);
    bfs.encontrarAlcanzables(fuente);
    bfs.imprimirAlcanzables();

    return 0;
}
