// CourseSchedule.cpp
// Contexto: Determinar si es posible completar todos los cursos dados sus prerequisitos, modelados como un grafo dirigido. Esto implica verificar si el grafo es acíclico.

#include <iostream>

// Clase para representar una lista de adyacencia usando listas enlazadas
struct NodoAdyacencia {
    int dest;
    NodoAdyacencia* siguiente;

    NodoAdyacencia(int d) : dest(d), siguiente(nullptr) {}
};

// Clase para representar el grafo
class Grafo {
public:
    int V; // Número de vértices
    NodoAdyacencia** array;

    Grafo(int V) {
        this->V = V;
        array = new NodoAdyacencia*[V];
        for(int i = 0; i < V; ++i)
            array[i] = nullptr;
    }

    void agregarArista(int src, int dest) {
        NodoAdyacencia* nuevoNodo = new NodoAdyacencia(dest);
        nuevoNodo->siguiente = array[src];
        array[src] = nuevoNodo;
    }

    ~Grafo() {
        for(int i = 0; i < V; ++i) {
            NodoAdyacencia* actual = array[i];
            while(actual) {
                NodoAdyacencia* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }
        delete[] array;
    }
};

// Clase para implementar el Ordenamiento Topológico (Kahn's Algorithm)
class TopologicalSort {
public:
    Grafo* grafo;

    TopologicalSort(Grafo* g) {
        grafo = g;
    }

    // Cola implementada manualmente con listas enlazadas
    struct NodoCola {
        int dato;
        NodoCola* siguiente;
        NodoCola(int d) : dato(d), siguiente(nullptr) {}
    };

    class Cola {
    public:
        NodoCola* frente;
        NodoCola* final;

        Cola() : frente(nullptr), final(nullptr) {}

        void encolar(int dato) {
            NodoCola* nuevo = new NodoCola(dato);
            if(final == nullptr){
                frente = final = nuevo;
                return;
            }
            final->siguiente = nuevo;
            final = nuevo;
        }

        int desencolar() {
            if(frente == nullptr)
                return -1;
            NodoCola* temp = frente;
            int val = temp->dato;
            frente = frente->siguiente;
            if(frente == nullptr)
                final = nullptr;
            delete temp;
            return val;
        }

        bool estaVacio() {
            return frente == nullptr;
        }

        ~Cola() {
            while(!estaVacio())
                desencolar();
        }
    };

    bool puedeCompletarCursos() {
        int V = grafo->V;
        int* in_degree = new int[V];
        for(int i = 0; i < V; ++i)
            in_degree[i] = 0;

        // Calcular in-degree de cada vértice
        for(int u = 0; u < V; ++u) {
            NodoAdyacencia* actual = grafo->array[u];
            while(actual) {
                in_degree[actual->dest]++;
                actual = actual->siguiente;
            }
        }

        // Crear una cola y encolar vértices con in-degree 0
        Cola q;
        for(int i = 0; i < V; ++i)
            if(in_degree[i] == 0)
                q.encolar(i);

        int cnt = 0;

        // Procesar la cola
        while(!q.estaVacio()) {
            int u = q.desencolar();
            cnt++;

            NodoAdyacencia* actual = grafo->array[u];
            while(actual) {
                if(--in_degree[actual->dest] == 0)
                    q.encolar(actual->dest);
                actual = actual->siguiente;
            }
        }

        delete[] in_degree;

        // Si el número de nodos procesados es igual a V, no hay ciclo
        return (cnt == V);
    }
};

// Función main para probar
int main() {
    int numCourses = 4;
    Grafo grafo(numCourses);

    // Prerequisitos: [[1,0],[2,1],[3,2]]
    grafo.agregarArista(0, 1); // Curso 1 depende de Curso 0
    grafo.agregarArista(1, 2); // Curso 2 depende de Curso 1
    grafo.agregarArista(2, 3); // Curso 3 depende de Curso 2

    TopologicalSort ts(&grafo);
    if(ts.puedeCompletarCursos())
        std::cout << "Es posible completar todos los cursos." << std::endl;
    else
        std::cout << "No es posible completar todos los cursos debido a un ciclo." << std::endl;

    return 0;
}
