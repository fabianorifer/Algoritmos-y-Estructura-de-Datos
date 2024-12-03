// RedundantConnection.cpp
// Contexto: En un grafo no dirigido que inicialmente es un árbol, identificar una arista que al agregarla crea un ciclo. Esto es útil para detectar conexiones innecesarias en redes.

#include <iostream>

// Estructura para representar una arista
struct Edge {
    int src;
    int dest;

    Edge(int s, int d) : src(s), dest(d) {}
};

// Clase para implementar Union-Find
class UnionFind {
public:
    int* parent;
    int* rank;
    int n;

    UnionFind(int size){
        n = size;
        parent = new int[n+1];
        rank = new int[n+1];
        for(int i = 0; i <= n; ++i){
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // Encontrar el representante del conjunto
    int findSet(int x){
        if(parent[x] != x)
            parent[x] = findSet(parent[x]); // Compresión de caminos
        return parent[x];
    }

    // Unir dos conjuntos
    bool unionSet(int x, int y){
        int xRoot = findSet(x);
        int yRoot = findSet(y);
        if(xRoot == yRoot)
            return false; // Ya están en el mismo conjunto, ciclo detectado
        // Unión por rango
        if(rank[xRoot] < rank[yRoot]){
            parent[xRoot] = yRoot;
        }
        else if(rank[xRoot] > rank[yRoot]){
            parent[yRoot] = xRoot;
        }
        else{
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
        return true;
    }

    ~UnionFind(){
        delete[] parent;
        delete[] rank;
    }
};

// Función para encontrar la arista redundante
Edge findRedundantConnection(int V, Edge* edges, int E) {
    UnionFind uf(V);
    for(int i = 0; i < E; ++i){
        if(!uf.unionSet(edges[i].src, edges[i].dest))
            return edges[i]; // Arista que crea un ciclo
    }
    return Edge(-1, -1); // No hay arista redundante
}

// Función main para probar
int main(){
    int V = 3;
    int E = 3;
    Edge edgesArr[] = { Edge(1,2), Edge(1,3), Edge(2,3) };

    Edge redundante = findRedundantConnection(V, edgesArr, E);
    if(redundante.src != -1)
        std::cout << "Arista Redundante: (" << redundante.src << ", " << redundante.dest << ")" << std::endl;
    else
        std::cout << "No hay arista redundante." << std::endl;

    return 0;
}
