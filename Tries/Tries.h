// Trie.h
#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>

using namespace std;

// Definición del número de caracteres (suponiendo solo letras minúsculas a-z)
#define ALPHABET_SIZE 26

// Estructura para representar un nodo en la Trie
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    // Constructor
    TrieNode() {
        isEndOfWord = false;
        for(int i = 0; i < ALPHABET_SIZE; ++i)
            children[i] = nullptr;
    }
};

// Clase para representar la Trie
class Trie {
private:
    TrieNode* root;

public:
    // Constructor
    Trie();

    // Destructor
    ~Trie();

    // Método para insertar una palabra en la Trie
    void insertar(const string& key);

    // Método para buscar una palabra en la Trie
    bool buscar(const string& key);

    // Método para eliminar una palabra de la Trie
    bool eliminar(const string& key);

    // Método auxiliar para eliminar una palabra de la Trie
    bool eliminarAux(TrieNode* nodo, const string& key, int profundidad);
};

#endif // TRIE_H
