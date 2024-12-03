// ArbolB.cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Orden mínimo (t) del árbol B
#define T 2

// Clase para representar un nodo en el Árbol B
class BTreeNode {
public:
    bool leaf; // Indica si el nodo es hoja
    int n; // Número actual de claves
    int keys[2*T-1]; // Arreglo de claves
    BTreeNode* children[2*T]; // Punteros a hijos

    // Constructor
    BTreeNode(bool leaf) {
        this->leaf = leaf;
        n = 0;
        for(int i = 0; i < 2*T; ++i)
            children[i] = nullptr;
    }

    // Función para insertar una nueva clave en el subárbol enraizado en este nodo
    void insertNonFull(int key);

    // Función para dividir el hijo y actualizar las claves del nodo
    void splitChild(int i, BTreeNode* y);

    // Función para buscar una clave en el subárbol enraizado en este nodo
    BTreeNode* search(int key);
};

// Clase para representar el Árbol B
class BTree {
public:
    BTreeNode* root; // Puntero a la raíz del árbol

    // Constructor
    BTree() {
        root = nullptr;
    }

    // Función para buscar una clave en el árbol
    BTreeNode* search(int key) {
        if(root == nullptr)
            return nullptr;
        else
            return root->search(key);
    }

    // Función para insertar una nueva clave en el árbol
    void insert(int key);
};

// Implementación de la función search en BTreeNode
BTreeNode* BTreeNode::search(int key) {
    int i = 0;
    while(i < n && key > keys[i])
        i++;

    if(i < n && keys[i] == key)
        return this;

    if(leaf)
        return nullptr;

    return children[i]->search(key);
}

// Implementación de la función insertNonFull en BTreeNode
void BTreeNode::insertNonFull(int key) {
    int i = n-1;

    if(leaf) {
        // Encontrar la posición donde se debe insertar la nueva clave
        while(i >= 0 && keys[i] > key) {
            keys[i+1] = keys[i];
            i--;
        }

        keys[i+1] = key;
        n = n + 1;
    }
    else {
        // Encontrar el hijo que debe contener la nueva clave
        while(i >= 0 && keys[i] > key)
            i--;

        if(children[i+1]->n == 2*T-1) {
            // Si el hijo está lleno, dividirlo
            splitChild(i+1, children[i+1]);

            if(keys[i+1] < key)
                i++;
        }
        children[i+1]->insertNonFull(key);
    }
}

// Implementación de la función splitChild en BTreeNode
void BTreeNode::splitChild(int i, BTreeNode* y) {
    // Crear un nuevo nodo que contendrá (T-1) claves de y
    BTreeNode* z = new BTreeNode(y->leaf);
    z->n = T - 1;

    for(int j = 0; j < T-1; j++)
        z->keys[j] = y->keys[j+T];

    if(!y->leaf) {
        for(int j = 0; j < T; j++)
            z->children[j] = y->children[j+T];
    }

    y->n = T - 1;

    // Crear espacio para el nuevo hijo
    for(int j = n; j >= i+1; j--)
        children[j+1] = children[j];

    children[i+1] = z;

    // Mover las claves mayores de y a este nodo
    for(int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];

    keys[i] = y->keys[T-1];

    n = n + 1;
}

// Implementación de la función insert en BTree
void BTree::insert(int key) {
    if(root == nullptr) {
        root = new BTreeNode(true);
        root->keys[0] = key;
        root->n = 1;
    }
    else {
        if(root->n == 2*T-1) {
            // Si la raíz está llena, crear una nueva raíz y dividir la antigua raíz
            BTreeNode* s = new BTreeNode(false);
            s->children[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if(s->keys[0] < key)
                i++;
            s->children[i]->insertNonFull(key);

            root = s;
        }
        else {
            root->insertNonFull(key);
        }
    }
}

// Función para imprimir el árbol B (recorrido InOrder)
void imprimirBTree(BTreeNode* nodo, int nivel) {
    if(nodo != nullptr) {
        for(int i = 0; i < nodo->n; i++) {
            if(!nodo->leaf)
                imprimirBTree(nodo->children[i], nivel+1);
            for(int j = 0; j < nivel; j++) cout << "    ";
            cout << nodo->keys[i] << endl;
        }
        if(!nodo->leaf)
            imprimirBTree(nodo->children[nodo->n], nivel+1);
    }
}

// Función main para probar la implementación del Árbol B
int main() {
    BTree tree;
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys)/sizeof(keys[0]);

    for(int i = 0; i < n; i++)
        tree.insert(keys[i]);

    cout << "Árbol B después de las inserciones:" << endl;
    imprimirBTree(tree.root, 0);

    // Buscar algunas claves
    int buscar[] = {6, 15};
    for(int key : buscar) {
        BTreeNode* resultado = tree.search(key);
        if(resultado != nullptr)
            cout << "Clave " << key << " encontrada en el árbol." << endl;
        else
            cout << "Clave " << key << " no encontrada en el árbol." << endl;
    }

    return 0;
}
