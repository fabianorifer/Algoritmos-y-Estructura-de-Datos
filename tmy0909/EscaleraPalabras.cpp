// WordLadder.cpp
// Contexto: Transformar una palabra en otra cambiando una letra a la vez, asegurando que cada palabra intermedia sea válida.

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// Estructura para representar una fila en una tabla de búsqueda
struct Fila {
    char palabra[10];
    bool visitado;

    Fila() : visitado(false) {
        strcpy(palabra, "");
    }
};

// Cola implementada manualmente usando arrays
struct Cola {
    int frente;
    int final;
    int capacidad;
    Fila* elementos;

    Cola(int cap) {
        capacidad = cap;
        frente = 0;
        final = -1;
        elementos = new Fila[cap];
    }

    bool estaVacia() {
        return final < frente;
    }

    void encolar(Fila elemento) {
        if(final + 1 >= capacidad) return; // Cola llena
        final++;
        elementos[final] = elemento;
    }

    Fila desencolar() {
        if(estaVacia()) return Fila();
        return elementos[frente++];
    }

    ~Cola() {
        delete[] elementos;
    }
};

// Función para verificar si dos palabras difieren en una sola letra
bool unaLetraDiferente(const char* a, const char* b) {
    int count = 0;
    for(int i = 0; a[i] != '\0'; ++i){
        if(a[i] != b[i]){
            count++;
            if(count > 1)
                return false;
        }
    }
    return count == 1;
}

// Función para encontrar la longitud más corta de la escalera de palabras
int ladderLength(const char* beginWord, const char* endWord, vector<const char*>& wordList) {
    int N = wordList.size();
    // Crear una tabla de palabras
    Fila* tabla = new Fila[N];
    for(int i = 0; i < N; ++i){
        strcpy(tabla[i].palabra, wordList[i]);
    }

    // Inicializar la cola
    Cola q(N);
    Fila inicio;
    strcpy(inicio.palabra, beginWord);
    inicio.visitado = true;
    q.encolar(inicio);

    int nivel = 1;

    while(!q.estaVacia()){
        int tamaño = q.final - q.frente + 1;
        for(int i = 0; i < tamaño; ++i){
            Fila actual = q.desencolar();
            // Si encontramos la palabra final
            if(strcmp(actual.palabra, endWord) == 0){
                delete[] tabla;
                return nivel;
            }
            // Explorar todas las palabras no visitadas que difieren en una letra
            for(int j = 0; j < N; ++j){
                if(!tabla[j].visitado && unaLetraDiferente(actual.palabra, tabla[j].palabra)){
                    tabla[j].visitado = true;
                    q.encolar(tabla[j]);
                }
            }
        }
        nivel++;
    }

    delete[] tabla;
    return 0;
}

// Función main para probar
int main(){
    const char* beginWord = "hit";
    const char* endWord = "cog";
    vector<const char*> wordList = {"hot","dot","dog","lot","log","cog"};

    int resultado = ladderLength(beginWord, endWord, wordList);
    cout << "Longitud de la Escalera de Palabras: " << resultado << endl;

    return 0;
}
