// CloneGraph.cpp
// Contexto: Crear una copia exacta de un grafo dado, duplicando todos sus nodos y aristas sin utilizar estructuras de datos de la STL.

#include <iostream>

// Definición de la estructura del nodo del grafo
struct Node {
    int val;
    Node** neighbors;
    int numNeighbors;

    Node(int _val) : val(_val), neighbors(nullptr), numNeighbors(0) {}
};

// Clase para representar el grafo
class Grafo {
public:
    int V;
    Node** array;

    Grafo(int V) {
        this->V = V;
        array = new Node*[V];
        for(int i = 0; i < V; ++i)
            array[i] = nullptr;
    }

    void agregarNodo(int val) {
        array[val] = new Node(val);
    }

    void agregarArista(int src, int dest) {
        // Agregar dest a los vecinos de src
        Node* nodoSrc = array[src];
        Node* nodoDest = array[dest];
        if(nodoSrc && nodoDest) {
            nodoSrc->neighbors = (Node**)realloc(nodoSrc->neighbors, sizeof(Node*) * (nodoSrc->numNeighbors + 1));
            nodoSrc->neighbors[nodoSrc->numNeighbors] = nodoDest;
            nodoSrc->numNeighbors++;
        }
    }

    ~Grafo() {
        for(int i = 0; i < V; ++i)
            if(array[i])
                delete array[i];
        delete[] array;
    }
};

// Clase para implementar DFS y clonar el grafo
class CloneGraphDFS {
public:
    Grafo* original;
    Grafo* clone;
    Node** mapa; // Mapa para almacenar la correspondencia entre nodos originales y clonados

    CloneGraphDFS(Grafo* g) {
        original = g;
        clone = new Grafo(g->V);
        mapa = new Node*[g->V];
        for(int i = 0; i < g->V; ++i)
            mapa[i] = nullptr;
    }

    Node* clonarNodo(int u) {
        if(mapa[u] != nullptr)
            return mapa[u];

        // Crear el nodo clonado
        Node* nuevoNodo = new Node(original->array[u]->val);
        clone->array[u] = nuevoNodo;
        mapa[u] = nuevoNodo;

        // Clonar todos los vecinos
        if(original->array[u]->numNeighbors > 0) {
            nuevoNodo->neighbors = new Node*[original->array[u]->numNeighbors];
            nuevoNodo->numNeighbors = original->array[u]->numNeighbors;
            for(int i = 0; i < original->array[u]->numNeighbors; ++i) {
                nuevoNodo->neighbors[i] = clonarNodo(original->array[u]->neighbors[i]->val);
            }
        }

        return nuevoNodo;
    }

    Grafo* clonarGrafo() {
        for(int i = 0; i < original->V; ++i)
            if(original->array[i])
                clonarNodo(i);
        return clone;
    }

    ~CloneGraphDFS() {
        delete[] mapa;
    }
};

// Clase para implementar DFS utilizando una pila manual
class CloneGraphDFSIterative {
public:
    Grafo* original;
    Grafo* clone;
    Node** mapa; // Mapa para almacenar la correspondencia entre nodos originales y clonados

    CloneGraphDFSIterative(Grafo* g) {
        original = g;
        clone = new Grafo(g->V);
        mapa = new Node*[g->V];
        for(int i = 0; i < g->V; ++i)
            mapa[i] = nullptr;
    }

    Grafo* clonarGrafo() {
        // Implementar una pila manual usando arrays
        int stackSize = original->V;
        int top = -1;
        int* stack = new int[stackSize];

        // Iniciar con el primer nodo
        for(int i = 0; i < original->V; ++i) {
            if(original->array[i] != nullptr) {
                stack[++top] = i;
                // Clonar el nodo
                clone->array[i] = new Node(original->array[i]->val);
                mapa[i] = clone->array[i];
                break;
            }
        }

        // Procesar la pila
        while(top != -1) {
            int u = stack[top--];
            Node* nodoOriginal = original->array[u];
            Node* nodoClonado = clone->array[u];

            for(int i = 0; i < nodoOriginal->numNeighbors; ++i) {
                int v = nodoOriginal->neighbors[i]->val;
                if(mapa[v] == nullptr) {
                    // Clonar el vecino
                    clone->array[v] = new Node(original->array[v]->val);
                    mapa[v] = clone->array[v];
                    // Agregar a la pila
                    stack[++top] = v;
                }
                // Agregar la arista en el clon
                nodoClonado->neighbors = (Node**)realloc(nodoClonado->neighbors, sizeof(Node*) * (nodoClonado->numNeighbors + 1));
                nodoClonado->neighbors[nodoClonado->numNeighbors] = clone->array[v];
                nodoClonado->numNeighbors++;
            }
        }

        delete[] stack;
        delete[] mapa;
        return clone;
    }

    ~CloneGraphDFSIterative() {
        delete[] mapa;
    }
};

// Función para imprimir el grafo
void imprimirGrafo(Grafo* grafo) {
    for(int i = 0; i < grafo->V; ++i) {
        if(grafo->array[i]) {
            std::cout << "Nodo " << grafo->array[i]->val << " conectado a: ";
            for(int j = 0; j < grafo->array[i]->numNeighbors; ++j)
                std::cout << grafo->array[i]->neighbors[j]->val << " ";
            std::cout << std::endl;
        }
    }
}

// Función main para probar
int main() {
    // Crear un grafo original
    int V = 4;
    Grafo original(V, 4);
    for(int i = 0; i < V; ++i)
        original.agregarNodo(i);

    // Agregar aristas
    original.agregarArista(0, 0, 1, 1);
    original.agregarArista(1, 1, 2, 2);
    original.agregarArista(2, 2, 3, 3);
    original.agregarArista(3, 3, 0, 4);

    std::cout << "Grafo Original:" << std::endl;
    imprimirGrafo(&original);

    // Clonar usando DFS Recursivo
    CloneGraphDFS clonarDFS(&original);
    Grafo* clonadoDFS = clonarDFS.clonarGrafo();

    std::cout << "\nGrafo Clonado (DFS Recursivo):" << std::endl;
    imprimirGrafo(clonadoDFS);

    // Clonar usando DFS Iterativo
    CloneGraphDFSIterative clonarDFSIter(&original);
    Grafo* clonadoDFSIter = clonarDFSIter.clonarGrafo();

    std::cout << "\nGrafo Clonado (DFS Iterativo):" << std::endl;
    imprimirGrafo(clonadoDFSIter);

    // Liberar memoria
    delete clonadoDFS;
    delete clonadoDFSIter;

    return 0;
}
