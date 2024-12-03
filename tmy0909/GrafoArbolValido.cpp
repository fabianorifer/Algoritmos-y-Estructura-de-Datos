// GraphValidTree.cpp
// Contexto: Verificar si un grafo es un árbol, es decir, si es conectado y no tiene ciclos.

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// Clase para implementar Union-Find
class UnionFind {
public:
    int* parent;
    int* rank;
    int n;

    UnionFind(int size){
        n = size;
        parent = new int[n];
        rank = new int[n];
        for(int i = 0; i < n; ++i){
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // Encontrar el representante de un conjunto
    int findSet(int x){
        if(parent[x] != x)
            parent[x] = findSet(parent[x]); // Path compression
        return parent[x];
    }

    // Unir dos conjuntos
    bool unionSet(int x, int y){
        int xRoot = findSet(x);
        int yRoot = findSet(y);
        if(xRoot == yRoot)
            return false; // Ya están en el mismo conjunto, ciclo detectado
        // Union por rango
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

// Función para verificar si el grafo es un árbol válido
bool validTree(int n, vector<vector<int>>& edges) {
    // Un árbol debe tener exactamente n-1 aristas
    if(edges.size() != n - 1)
        return false;

    UnionFind uf(n);
    for(auto &edge : edges){
        if(!uf.unionSet(edge[0], edge[1]))
            return false; // Ciclo detectado
    }

    return true;
}

// Función main para probar
int main(){
    int n = 5;
    vector<vector<int>> edges = {{0,1},{0,2},{0,3},{1,4}};

    if(validTree(n, edges))
        cout << "El grafo es un árbol válido." << endl;
    else
        cout << "El grafo no es un árbol válido." << endl;

    return 0;
}
