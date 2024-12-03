// FindTownJudge.cpp
// Contexto: En una comunidad, determinar si existe una persona que es confiada por todos los demás pero no confía en nadie. Esto es útil en sistemas de reputación y liderazgo.

#include <iostream>

// Función para encontrar al juez del pueblo
int findJudge(int N, int** trust, int E) {
    if(E < N-1)
        return -1; // No puede haber un juez

    int* confianza = new int[N+1];
    for(int i = 0; i <= N; ++i)
        confianza[i] = 0;

    for(int i = 0; i < E; ++i){
        int a = trust[i][0];
        int b = trust[i][1];
        confianza[a]--; // a confía en alguien
        confianza[b]++; // b es confiado por alguien
    }

    for(int i = 1; i <= N; ++i){
        if(confianza[i] == N-1)
            return i;
    }

    delete[] confianza;
    return -1;
}

// Función main para probar
int main(){
    int N = 3;
    int E = 2;
    int** trust = new int*[E];
    trust[0] = new int[2]{1,3};
    trust[1] = new int[2]{2,3};

    int juez = findJudge(N, trust, E);
    if(juez != -1)
        std::cout << "El juez del pueblo es: " << juez << std::endl;
    else
        std::cout << "No hay un juez del pueblo." << std::endl;

    // Liberar memoria
    for(int i = 0; i < E; ++i)
        delete[] trust[i];
    delete[] trust;

    return 0;
}
