// NetworkDelayTime.cpp
// Contexto: Determinar el tiempo mínimo necesario para que una señal enviada desde un nodo fuente alcance todos los nodos en una red representada como un grafo ponderado.

#include <iostream>
#include <climits>

// Estructura para representar una arista en la lista de adyacencia
struct AdjListNode {
    int dest;
    int peso;
    AdjListNode* siguiente;

    AdjListNode(int d, int p) : dest(d), peso(p), siguiente(nullptr) {}
};

// Clase para representar una lista de adyacencia
class ListaAdyacencia {
public:
    AdjListNode* cabeza;

    ListaAdyacencia() : cabeza(nullptr) {}

    void agregarArista(int dest, int peso) {
        AdjListNode* nuevoNodo = new AdjListNode(dest, peso);
        nuevoNodo->siguiente = cabeza;
        cabeza = nuevoNodo;
    }
};

// Clase para representar el grafo
class Grafo {
public:
    int V;
    ListaAdyacencia* array;

    Grafo(int V) {
        this->V = V;
        array = new ListaAdyacencia[V + 1]; // Nodos etiquetados desde 1
    }

    void agregarArista(int src, int dest, int peso) {
        array[src].agregarArista(dest, peso);
    }

    ~Grafo() {
        for(int i = 1; i <= V; ++i) {
            AdjListNode* actual = array[i].cabeza;
            while(actual) {
                AdjListNode* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }
        delete[] array;
    }
};

// Estructura para un nodo en el montículo (heap)
struct NodoHeap {
    int vertice;
    int distancia;
};

// Clase para implementar un montículo mínimo (min-heap)
class MinHeap {
public:
    NodoHeap* harr;
    int capacidad;
    int tamaño;
    int* posicion; // Posición de cada vértice en el heap

    MinHeap(int cap) {
        capacidad = cap;
        tamaño = 0;
        harr = new NodoHeap[cap];
        posicion = new int[cap + 1];
        for(int i = 0; i <= cap; ++i)
            posicion[i] = -1;
    }

    void intercambiar(NodoHeap& x, NodoHeap& y) {
        NodoHeap temp = x;
        x = y;
        y = temp;
    }

    void heapify(int idx) {
        int menor = idx;
        int izquierdo = 2 * idx + 1;
        int derecho = 2 * idx + 2;

        if (izquierdo < tamaño && harr[izquierdo].distancia < harr[menor].distancia)
            menor = izquierdo;

        if (derecho < tamaño && harr[derecho].distancia < harr[menor].distancia)
            menor = derecho;

        if (menor != idx) {
            // Actualizar posiciones
            posicion[harr[menor].vertice] = idx;
            posicion[harr[idx].vertice] = menor;

            // Intercambiar
            intercambiar(harr[menor], harr[idx]);

            heapify(menor);
        }
    }

    bool estaVacio() {
        return tamaño == 0;
    }

    NodoHeap extraerMin() {
        if (estaVacio())
            return NodoHeap{ -1, INT_MAX };

        NodoHeap root = harr[0];
        NodoHeap lastNode = harr[tamaño - 1];
        harr[0] = lastNode;

        posicion[root.vertice] = tamaño - 1;
        posicion[lastNode.vertice] = 0;

        tamaño--;
        heapify(0);

        return root;
    }

    void disminuirClave(int vertice, int distancia) {
        int i = posicion[vertice];
        harr[i].distancia = distancia;

        while (i && harr[i].distancia < harr[(i - 1) / 2].distancia) {
            // Actualizar posiciones
            posicion[harr[i].vertice] = (i - 1) / 2;
            posicion[harr[(i - 1) / 2].vertice] = i;

            // Intercambiar
            intercambiar(harr[i], harr[(i - 1) / 2]);

            i = (i - 1) / 2;
        }
    }

    void insertar(NodoHeap k) {
        if (tamaño == capacidad)
            return;

        int i = tamaño;
        harr[i] = k;
        posicion[k.vertice] = i;
        tamaño++;

        while (i && harr[i].distancia < harr[(i - 1) / 2].distancia) {
            // Actualizar posiciones
            posicion[harr[i].vertice] = (i - 1) / 2;
            posicion[harr[(i - 1) / 2].vertice] = i;

            // Intercambiar
            intercambiar(harr[i], harr[(i - 1) / 2]);

            i = (i - 1) / 2;
        }
    }

    ~MinHeap() {
        delete[] harr;
        delete[] posicion;
    }
};

// Función para calcular el tiempo de retraso en la red utilizando Dijkstra
int networkDelayTime(Grafo& grafo, int N, int K) {
    // Crear un arreglo para almacenar las distancias
    int dist[N + 1];
    for(int i = 1; i <= N; ++i)
        dist[i] = INT32_MAX;
    dist[K] = 0;

    // Crear un montículo y agregar todos los vértices
    MinHeap heap(N);
    for(int v = 1; v <= N; ++v) {
        heap.harr[v - 1].vertice = v;
        heap.harr[v - 1].distancia = dist[v];
        heap.posicion[v] = v - 1;
    }
    heap.tamaño = N;

    // Heapify el montículo
    for(int i = (heap.tamaño - 1) / 2; i >= 0; --i)
        heap.heapify(i);

    // Procesar el montículo hasta que esté vacío
    while (!heap.estaVacio()) {
        // Extraer el vértice con la distancia mínima
        NodoHeap minNode = heap.extraerMin();
        int u = minNode.vertice;

        // Iterar sobre todos los vecinos de u
        AdjListNode* actual = grafo.array[u].cabeza;
        while(actual) {
            int v = actual->dest;
            int peso = actual->peso;

            // Relajar la arista
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                heap.disminuirClave(v, dist[v]);
            }
            actual = actual->siguiente;
        }
    }

    // Encontrar el máximo tiempo de retraso
    int maxDist = 0;
    for(int i = 1; i <= N; ++i){
        if(dist[i] == INT32_MAX)
            return -1;
        if(dist[i] > maxDist)
            maxDist = dist[i];
    }
    return maxDist;
}

// Función main para probar
int main() {
    // Definir el número de vértices y aristas
    int N = 4;
    int E = 5;
    Grafo grafo(N);

    // Agregar aristas
    grafo.agregarArista(2, 1, 1);
    grafo.agregarArista(2, 3, 1);
    grafo.agregarArista(3, 4, 1);
    grafo.agregarArista(1, 3, 1);
    grafo.agregarArista(4, 2, 1);

    // Nodo fuente
    int K = 2;

    // Calcular el tiempo de retraso en la red
    int tiempo = networkDelayTime(grafo, N, K);
    std::cout << "Tiempo de Retraso en la Red: " << tiempo << std::endl;

    return 0;
}
