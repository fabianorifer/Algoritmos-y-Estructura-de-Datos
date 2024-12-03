// ArbolBinario.cpp
#include "ArbolBinario.h"

// Método para insertar un nodo en el árbol binario
void ArbolBinario::insertar(int valor) {
    Nodo* nuevoNodo = new Nodo(valor);

    if (raiz == nullptr) {
        raiz = nuevoNodo;
        return;
    }

    // Utilizamos BFS para encontrar el primer lugar disponible
    queue<Nodo*> q;
    q.push(raiz);

    while (!q.empty()) {
        Nodo* actual = q.front();
        q.pop();

        if (actual->izquierda == nullptr) {
            actual->izquierda = nuevoNodo;
            return;
        } else {
            q.push(actual->izquierda);
        }

        if (actual->derecha == nullptr) {
            actual->derecha = nuevoNodo;
            return;
        } else {
            q.push(actual->derecha);
        }
    }
}

// Método para destruir el árbol y liberar memoria
void ArbolBinario::destruirArbol(Nodo* nodo) {
    if (nodo == nullptr)
        return;

    destruirArbol(nodo->izquierda);
    destruirArbol(nodo->derecha);
    delete nodo;
}
