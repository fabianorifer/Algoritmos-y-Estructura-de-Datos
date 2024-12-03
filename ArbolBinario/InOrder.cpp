// InOrder.cpp
#include "ArbolBinario.h"

// Función para realizar el recorrido InOrder de manera recursiva
void inOrderRecursivo(Nodo* nodo) {
    if (nodo == nullptr)
        return;

    inOrderRecursivo(nodo->izquierda);
    cout << nodo->dato << " ";
    inOrderRecursivo(nodo->derecha);
}

// Función para realizar el recorrido InOrder de manera iterativa
void inOrderIterativo(Nodo* raiz) {
    stack<Nodo*> pila;
    Nodo* actual = raiz;

    while (actual != nullptr || !pila.empty()) {
        // Llegar al nodo más a la izquierda
        while (actual != nullptr) {
            pila.push(actual);
            actual = actual->izquierda;
        }

        // Extraer el último nodo de la pila
        actual = pila.top();
        pila.pop();

        cout << actual->dato << " ";

        // Cambiar al subárbol derecho
        actual = actual->derecha;
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

    cout << "Recorrido InOrder Recursivo: ";
    inOrderRecursivo(arbol.getRaiz());
    cout << endl;

    cout << "Recorrido InOrder Iterativo: ";
    inOrderIterativo(arbol.getRaiz());
    cout << endl;

    return 0;
}
