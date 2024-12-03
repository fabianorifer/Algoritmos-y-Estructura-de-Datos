// Trie.cpp
#include "Tries.h"

// Constructor de la Trie
Trie::Trie() {
    root = new TrieNode();
}

// Destructor de la Trie
Trie::~Trie() {
    // Implementar un recorrido postOrder para eliminar nodos
    // (Opcional: Puedes implementar una función auxiliar para liberar la memoria de todos los nodos)
}

// Método para insertar una palabra en la Trie
void Trie::insertar(const string& key) {
    TrieNode* crawl = root;

    for(char c : key) {
        int index = c - 'a';
        if(index < 0 || index >= ALPHABET_SIZE) {
            cout << "Caracter inválido: " << c << endl;
            return;
        }

        if(!crawl->children[index])
            crawl->children[index] = new TrieNode();

        crawl = crawl->children[index];
    }

    // Marcar el final de la palabra
    crawl->isEndOfWord = true;
}

// Método para buscar una palabra en la Trie
bool Trie::buscar(const string& key) {
    TrieNode* crawl = root;

    for(char c : key) {
        int index = c - 'a';
        if(index < 0 || index >= ALPHABET_SIZE)
            return false;

        if(!crawl->children[index])
            return false;

        crawl = crawl->children[index];
    }

    return (crawl != nullptr && crawl->isEndOfWord);
}

// Método para eliminar una palabra de la Trie
bool Trie::eliminar(const string& key) {
    return eliminarAux(root, key, 0);
}

// Método auxiliar recursivo para eliminar una palabra de la Trie
bool Trie::eliminarAux(TrieNode* nodo, const string& key, int profundidad) {
    if(!nodo)
        return false;

    // Caso base: si hemos llegado al final de la palabra
    if(profundidad == key.size()) {
        // Si la palabra no existe en la Trie
        if(!nodo->isEndOfWord)
            return false;

        // Marcar el final de la palabra como falso
        nodo->isEndOfWord = false;

        // Si el nodo no tiene hijos, puede ser eliminado
        for(int i = 0; i < ALPHABET_SIZE; ++i)
            if(nodo->children[i])
                return false;

        return true;
    }

    // Obtener el índice del carácter actual
    int index = key[profundidad] - 'a';
    if(index < 0 || index >= ALPHABET_SIZE)
        return false;

    // Si no hay ningún nodo hijo para este carácter, la palabra no existe
    if(!nodo->children[index])
        return false;

    // Recursivamente eliminar la palabra del subárbol
    if(eliminarAux(nodo->children[index], key, profundidad + 1)) {
        // Eliminar el nodo hijo
        delete nodo->children[index];
        nodo->children[index] = nullptr;

        // Si el nodo actual no es el final de otra palabra y no tiene otros hijos, puede ser eliminado
        if(!nodo->isEndOfWord) {
            for(int i = 0; i < ALPHABET_SIZE; ++i)
                if(nodo->children[i])
                    return false;
            return true;
        }
    }

    return false;
}

// Función main para probar la implementación de la Trie
int main() {
    Trie trie;

    // Insertar palabras
    trie.insertar("hola");
    trie.insertar("mundo");
    trie.insertar("hermano");
    trie.insertar("hermana");
    trie.insertar("hermosa");

    // Buscar palabras
    cout << "Buscar 'hola': " << (trie.buscar("hola") ? "Encontrada" : "No encontrada") << endl;
    cout << "Buscar 'hermano': " << (trie.buscar("hermano") ? "Encontrada" : "No encontrada") << endl;
    cout << "Buscar 'hermosa': " << (trie.buscar("hermosa") ? "Encontrada" : "No encontrada") << endl;
    cout << "Buscar 'hermanoX': " << (trie.buscar("hermanoX") ? "Encontrada" : "No encontrada") << endl;

    // Eliminar palabras
    cout << "\nEliminando 'hermana'..." << endl;
    if(trie.eliminar("hermana"))
        cout << "'hermana' eliminada exitosamente." << endl;
    else
        cout << "No se pudo eliminar 'hermana'." << endl;

    cout << "Buscar 'hermana': " << (trie.buscar("hermana") ? "Encontrada" : "No encontrada") << endl;

    cout << "\nEliminando 'hola'..." << endl;
    if(trie.eliminar("hola"))
        cout << "'hola' eliminada exitosamente." << endl;
    else
        cout << "No se pudo eliminar 'hola'." << endl;

    cout << "Buscar 'hola': " << (trie.buscar("hola") ? "Encontrada" : "No encontrada") << endl;

    return 0;
}
