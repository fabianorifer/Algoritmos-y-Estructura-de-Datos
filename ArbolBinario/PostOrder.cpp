// PostOrder.cpp
#include "ArbolBinario.h"

// Función para realizar el recorrido PostOrder de manera recursiva
void postOrderRecursivo(Nodo* nodo) {
    if (nodo == nullptr)
        return;

    postOrderRecursivo(nodo->izquierda);
    postOrderRecursivo(nodo->derecha);
    cout << nodo->dato << " ";
}

// Función para realizar el recorrido PostOrder de manera iterativa
void postOrderIterativo(Nodo* raiz) {
    if (raiz == nullptr)
        return;

    stack<Nodo*> pila1, pila2;
    pila1.push(raiz);

    while (!pila1.empty()) {
        Nodo* nodo = pila1.top();
        pila1.pop();
        pila2.push(nodo);

        if (nodo->izquierda)
            pila1.push(nodo->izquierda);
        if (nodo->derecha)
            pila1.push(nodo->derecha);
    }

    while (!pila2.empty()) {
        Nodo* nodo = pila2.top();
        pila2.pop();
        cout << nodo->dato << " ";
    }
}

int main() {
    ArbolBinario arbol;

    // Insertar nodos en el árbol
    arbol.insertar(1);
    arbol.insertar(2);
    arbol.insertar(3);
    arbol.insertar(4);
    arbol.insertar(5);
    arbol.insertar(6);
    arbol.insertar(7);

    cout << "Recorrido PostOrder Recursivo: ";
    postOrderRecursivo(arbol.getRaiz());
    cout << endl;

    cout << "Recorrido PostOrder Iterativo: ";
    postOrderIterativo(arbol.getRaiz());
    cout << endl;

    return 0;
}
