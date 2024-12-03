// ArbolBinario.h
#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// Estructura para representar un nodo en el árbol binario
struct Nodo {
    int dato;
    Nodo* izquierda;
    Nodo* derecha;

    // Constructor
    Nodo(int valor) : dato(valor), izquierda(nullptr), derecha(nullptr) {}
};

// Clase para representar el Árbol Binario
class ArbolBinario {
private:
    Nodo* raiz;

public:
    // Constructor
    ArbolBinario() : raiz(nullptr) {}

    // Destructor
    ~ArbolBinario() {
        destruirArbol(raiz);
    }

    // Método para insertar un nodo en el árbol
    void insertar(int valor);

    // Método para destruir el árbol y liberar memoria
    void destruirArbol(Nodo* nodo);

    // Getter para la raíz
    Nodo* getRaiz() const { return raiz; }
};

#endif // ARBOLBINARIO_H
