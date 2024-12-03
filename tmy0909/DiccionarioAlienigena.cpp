// AlienDictionary.cpp
// Contexto: Determinar el orden de las letras en un idioma alienígena basado en una lista de palabras ordenadas lexicográficamente.

#include <iostream>
#include <vector>
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

// Clase para implementar el Ordenamiento Topológico (Kahn's Algorithm)
class TopologicalSort {
public:
    Grafo* grafo;
    int V;

    TopologicalSort(Grafo* g){
        grafo = g;
        V = g->V;
    }

    // Implementación manual de una cola usando arrays
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

        bool estaVacio(){
            return final < frente;
        }

        void encolar(int val){
            if(final +1 >= capacidad)
                return; // Cola llena
            final++;
            elementos[final] = val;
        }

        int desencolar(){
            if(estaVacio())
                return -1;
            return elementos[frente++];
        }

        ~Cola(){
            delete[] elementos;
        }
    };

    // Función para realizar el ordenamiento topológico
    bool ordenarTopologico(char* resultado){
        // Calcular in-degree de cada vértice
        int* in_degree = new int[V];
        for(int i = 0; i < V; ++i)
            in_degree[i] = 0;

        for(int u = 0; u < V; ++u){
            AdjListNode* actual = grafo->array[u];
            while(actual){
                in_degree[actual->dest]++;
                actual = actual->siguiente;
            }
        }

        // Crear una cola y encolar vértices con in-degree 0
        Cola q(V);
        for(int i = 0; i < V; ++i)
            if(in_degree[i] == 0)
                q.encolar(i);

        int idx = 0;
        while(!q.estaVacio()){
            int u = q.desencolar();
            resultado[idx++] = 'a' + u; // Asumiendo que las letras son 'a' a 'z'

            AdjListNode* actual = grafo->array[u];
            while(actual){
                in_degree[actual->dest]--;
                if(in_degree[actual->dest] == 0)
                    q.encolar(actual->dest);
                actual = actual->siguiente;
            }
        }

        // Verificar si hay ciclo
        for(int i = 0; i < V; ++i)
            if(in_degree[i] > 0){
                delete[] in_degree;
                return false; // Ciclo detectado
            }

        resultado[idx] = '\0'; // Terminar la cadena
        delete[] in_degree;
        return true;
    }
};

// Función para determinar el orden de las letras
string alienOrder(vector<string>& words) {
    // Encontrar el número de letras
    bool letras[26];
    memset(letras, false, sizeof(letras));
    for(auto &word : words)
        for(char c : word)
            letras[c - 'a'] = true;

    int numLetters = 0;
    for(int i = 0; i < 26; ++i)
        if(letras[i])
            numLetters++;

    Grafo grafo(numLetters);

    // Mapear letras a índices
    int* mapa = new int[26];
    memset(mapa, -1, sizeof(int)*26);
    int idx = 0;
    for(int i = 0; i < 26; ++i)
        if(letras[i])
            mapa[i] = idx++;

    // Construir el grafo comparando palabras adyacentes
    for(int i = 0; i < words.size()-1; ++i){
        string w1 = words[i];
        string w2 = words[i+1];
        int len = min(w1.length(), w2.length());
        bool diferenciaEncontrada = false;
        for(int j = 0; j < len; ++j){
            if(w1[j] != w2[j]){
                grafo.agregarArista(mapa[w1[j]-'a'], mapa[w2[j]-'a']);
                diferenciaEncontrada = true;
                break;
            }
        }
        if(!diferenciaEncontrada && w1.length() > w2.length()){
            delete[] mapa;
            return ""; // Orden inválido
        }
    }

    // Realizar el ordenamiento topológico
    TopologicalSort ts(&grafo);
    char* resultado = new char[numLetters +1];
    bool esValido = ts.ordenarTopologico(resultado);

    string orden = "";
    if(esValido){
        orden = string(resultado);
    }

    // Liberar memoria
    delete[] mapa;
    delete[] resultado;

    return orden;
}

// Función main para probar
int main(){
    vector<string> words = {"wrt","wrf","er","ett","rftt"};
    string orden = alienOrder(words);
    if(orden != "")
        cout << "Orden de las Letras: " << orden << endl;
    else
        cout << "No es posible determinar un orden válido." << endl;

    return 0;
}
