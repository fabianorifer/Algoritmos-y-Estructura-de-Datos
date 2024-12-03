// BFS.cpp
#include "BFS.h"

using namespace std;

// Implementación de la clase Graph

// Constructor
Graph::Graph(int V) {
    this->V = V;
    array = new AdjList[V];
    for(int i = 0; i < V; ++i)
        array[i].head = nullptr;
}

// Destructor para liberar memoria
Graph::~Graph() {
    for(int v = 0; v < V; ++v) {
        AdjListNode* current = array[v].head;
        while(current) {
            AdjListNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] array;
}

// Método para crear un nuevo nodo de lista de adyacencia
AdjListNode* Graph::newAdjListNode(int dest) {
    AdjListNode* newNode = new AdjListNode;
    newNode->dest = dest;
    newNode->next = nullptr;
    return newNode;
}

// Método para agregar una arista al grafo (no dirigido)
void Graph::addEdge(int src, int dest) {
    // Agregar arista desde src a dest
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = array[src].head;
    array[src].head = newNode;

    // Agregar arista desde dest a src (para grafo no dirigido)
    newNode = newAdjListNode(src);
    newNode->next = array[dest].head;
    array[dest].head = newNode;
}

// Método para imprimir el grafo
void Graph::printGraph() {
    for(int v = 0; v < V; ++v) {
        AdjListNode* pCrawl = array[v].head;
        cout << "Vértice " << v << ":";
        while(pCrawl) {
            cout << " -> " << pCrawl->dest;
            pCrawl = pCrawl->next;
        }
        cout << endl;
    }
}

// Implementación de la clase BFS

// Constructor
BFS::BFS(Graph* g) {
    graph = g;
    visitado = new bool[graph->V];
    for(int i = 0; i < graph->V; ++i)
        visitado[i] = false;
}

// Destructor para liberar memoria
BFS::~BFS() {
    delete[] visitado;
}

// Estructura para la cola
struct QueueNode {
    int data;
    QueueNode* next;
};

// Clase para implementar una cola simple
class Queue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    // Constructor
    Queue() : front(nullptr), rear(nullptr) {}

    // Método para verificar si la cola está vacía
    bool isEmpty() {
        return front == nullptr;
    }

    // Método para encolar un elemento
    void enqueue(int value) {
        QueueNode* temp = new QueueNode;
        temp->data = value;
        temp->next = nullptr;
        if(rear == nullptr) {
            front = rear = temp;
            return;
        }
        rear->next = temp;
        rear = temp;
    }

    // Método para desencolar un elemento
    int dequeue() {
        if(isEmpty()) {
            return -1; // Indicador de error
        }
        QueueNode* temp = front;
        front = front->next;
        if(front == nullptr)
            rear = nullptr;
        int val = temp->data;
        delete temp;
        return val;
    }
};

// Método para realizar BFS desde un vértice dado
void BFS::bfs(int inicio) {
    // Crear una cola para BFS
    Queue q;

    // Marcar el vértice actual como visitado y encolarlo
    visitado[inicio] = true;
    q.enqueue(inicio);

    while(!q.isEmpty()) {
        // Desencolar un vértice y procesarlo
        int s = q.dequeue();
        cout << s << " ";

        // Obtener todos los vértices adyacentes de s
        AdjListNode* crawl = graph->array[s].head;
        while(crawl) {
            int adj = crawl->dest;
            if(!visitado[adj]) {
                visitado[adj] = true;
                q.enqueue(adj);
            }
            crawl = crawl->next;
        }
    }
}

// Función main para probar la implementación de BFS
int main() {
    // Crear un grafo con 6 vértices
    int V = 6;
    Graph g(V);

    // Agregar aristas
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    // Imprimir el grafo
    cout << "Representación del Grafo:" << endl;
    g.printGraph();
    cout << endl;

    // Realizar BFS desde el vértice 0
    BFS bfsAlgo(&g);
    cout << "Recorrido BFS desde el vértice 0: ";
    bfsAlgo.bfs(0);
    cout << endl;

    return 0;
}
