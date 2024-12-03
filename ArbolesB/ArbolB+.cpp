// ArbolBPlus.cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Orden mínimo (t) del árbol B+
#define T 2

// Clase para representar un nodo en el Árbol B+
class BPlusTreeNode {
public:
    bool leaf;
    int n;
    int keys[2*T-1];
    BPlusTreeNode* children[2*T];
    BPlusTreeNode* next; // Puntero al siguiente nodo hoja (solo para hojas)

    // Constructor
    BPlusTreeNode(bool leaf) {
        this->leaf = leaf;
        n = 0;
        next = nullptr;
        for(int i = 0; i < 2*T; ++i)
            children[i] = nullptr;
    }
};

// Clase para representar el Árbol B+
class BPlusTree {
public:
    BPlusTreeNode* root;

    // Constructor
    BPlusTree() {
        root = nullptr;
    }

    // Función para insertar una clave en el árbol
    void insert(int key);

    // Función para buscar una clave en el árbol
    bool search(int key);

    // Función para imprimir el árbol (nivel por nivel)
    void print();
private:
    void insertNonFull(BPlusTreeNode* node, int key);
    void splitChild(BPlusTreeNode* parent, int index, BPlusTreeNode* child);
    bool searchHelper(BPlusTreeNode* node, int key);
};

// Implementación de la función searchHelper en BPlusTree
bool BPlusTree::searchHelper(BPlusTreeNode* node, int key) {
    int i = 0;
    while(i < node->n && key > node->keys[i])
        i++;

    if(i < node->n && node->keys[i] == key)
        return true;

    if(node->leaf)
        return false;

    return searchHelper(node->children[i], key);
}

// Implementación de la función search en BPlusTree
bool BPlusTree::search(int key) {
    if(root == nullptr)
        return false;
    return searchHelper(root, key);
}

// Implementación de la función insert en BPlusTree
void BPlusTree::insert(int key) {
    if(root == nullptr) {
        root = new BPlusTreeNode(true);
        root->keys[0] = key;
        root->n = 1;
    }
    else {
        if(root->n == 2*T-1) {
            // Si la raíz está llena, crear una nueva raíz
            BPlusTreeNode* s = new BPlusTreeNode(false);
            s->children[0] = root;
            splitChild(s, 0, root);

            // Insertar la nueva clave en la nueva raíz
            int i = 0;
            if(s->keys[0] < key)
                i++;
            insertNonFull(s->children[i], key);

            root = s;
        }
        else {
            insertNonFull(root, key);
        }
    }
}

// Implementación de la función insertNonFull en BPlusTree
void BPlusTree::insertNonFull(BPlusTreeNode* node, int key) {
    int i = node->n - 1;

    if(node->leaf) {
        // Insertar la clave en la hoja
        while(i >= 0 && node->keys[i] > key) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->n += 1;
    }
    else {
        // Encontrar el hijo adecuado
        while(i >= 0 && node->keys[i] > key)
            i--;

        if(node->children[i+1]->n == 2*T-1) {
            // Si el hijo está lleno, dividirlo
            splitChild(node, i+1, node->children[i+1]);

            if(node->keys[i+1] < key)
                i++;
        }
        insertNonFull(node->children[i+1], key);
    }
}

// Implementación de la función splitChild en BPlusTree
void BPlusTree::splitChild(BPlusTreeNode* parent, int index, BPlusTreeNode* child) {
    // Crear un nuevo nodo que contendrá T-1 claves
    BPlusTreeNode* z = new BPlusTreeNode(child->leaf);
    z->n = T-1;

    // Copiar las últimas T-1 claves de child a z
    for(int j = 0; j < T-1; j++)
        z->keys[j] = child->keys[j+T];

    // Si child no es una hoja, copiar los últimos T hijos de child a z
    if(!child->leaf) {
        for(int j = 0; j < T; j++)
            z->children[j] = child->children[j+T];
    }

    child->n = T-1;

    // Insertar z como hijo de parent
    for(int j = parent->n; j >= index+1; j--)
        parent->children[j+1] = parent->children[j];
    parent->children[index+1] = z;

    // Mover la última clave de child a parent
    for(int j = parent->n-1; j >= index; j--)
        parent->keys[j+1] = parent->keys[j];
    parent->keys[index] = child->keys[T-1];
    parent->n += 1;

    // Actualizar el puntero next si es hoja
    if(child->leaf) {
        z->next = child->next;
        child->next = z;
    }
}

// Implementación de la función print en BPlusTree
void BPlusTree::print() {
    if(root == nullptr) {
        cout << "El Árbol B+ está vacío." << endl;
        return;
    }

    // Nivel por nivel
    vector<BPlusTreeNode*> currentLevel;
    currentLevel.push_back(root);
    int nivel = 0;

    while(!currentLevel.empty()) {
        vector<BPlusTreeNode*> nextLevel;
        cout << "Nivel " << nivel << ": ";
        for(auto node : currentLevel) {
            for(int i = 0; i < node->n; i++)
                cout << node->keys[i] << " ";
            cout << " | ";
            if(!node->leaf) {
                for(int i = 0; i <= node->n; i++)
                    nextLevel.push_back(node->children[i]);
            }
        }
        cout << endl;
        currentLevel = nextLevel;
        nivel++;
    }
}

// Función main para probar la implementación del Árbol B+
int main() {
    BPlusTree tree;
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys)/sizeof(keys[0]);

    for(int i = 0; i < n; i++)
        tree.insert(keys[i]);

    cout << "Árbol B+ después de las inserciones:" << endl;
    tree.print();

    // Buscar algunas claves
    int buscar[] = {6, 15};
    for(int key : buscar) {
        bool encontrado = tree.search(key);
        if(encontrado)
            cout << "Clave " << key << " encontrada en el Árbol B+." << endl;
        else
            cout << "Clave " << key << " no encontrada en el Árbol B+." << endl;
    }

    return 0;
}
