// NumberOfIslands.cpp
// Contexto: Contar el número de islas en una matriz binaria donde '1' representa tierra y '0' representa agua. Las islas están formadas por tierras conectadas horizontal o verticalmente.

#include <iostream>

// Estructura para representar una fila en la matriz
struct Fila {
    char* datos;
    int columnas;

    Fila(int cols) {
        columnas = cols;
        datos = new char[cols];
        for(int i = 0; i < cols; ++i)
            datos[i] = '0';
    }

    ~Fila() {
        delete[] datos;
    }
};

// Clase para representar la matriz
class Matriz {
public:
    Fila** grid;
    int filas;
    int columnas;

    Matriz(int filas, int columnas) {
        this->filas = filas;
        this->columnas = columnas;
        grid = new Fila*[filas];
        for(int i = 0; i < filas; ++i)
            grid[i] = new Fila(columnas);
    }

    void setValor(int i, int j, char valor) {
        if(i >=0 && i < filas && j >=0 && j < columnas)
            grid[i]->datos[j] = valor;
    }

    char getValor(int i, int j) const {
        if(i >=0 && i < filas && j >=0 && j < columnas)
            return grid[i]->datos[j];
        return '0';
    }

    ~Matriz() {
        for(int i = 0; i < filas; ++i)
            delete grid[i];
        delete[] grid;
    }
};

// Clase para implementar BFS
class BFS {
public:
    Matriz* matriz;
    int filas;
    int columnas;

    BFS(Matriz* m) {
        matriz = m;
        filas = m->filas;
        columnas = m->columnas;
    }

    // Estructura para representar una posición en la matriz
    struct Posicion {
        int x;
        int y;
    };

    // Cola implementada con listas enlazadas
    struct NodoCola {
        Posicion pos;
        NodoCola* siguiente;
        NodoCola(Posicion p) : pos(p), siguiente(nullptr) {}
    };

    class Cola {
    public:
        NodoCola* frente;
        NodoCola* final;

        Cola() : frente(nullptr), final(nullptr) {}

        void encolar(Posicion p) {
            NodoCola* nuevo = new NodoCola(p);
            if(final == nullptr){
                frente = final = nuevo;
                return;
            }
            final->siguiente = nuevo;
            final = nuevo;
        }

        Posicion desencolar() {
            if(frente == nullptr)
                return Posicion{ -1, -1 };
            NodoCola* temp = frente;
            Posicion p = temp->pos;
            frente = frente->siguiente;
            if(frente == nullptr)
                final = nullptr;
            delete temp;
            return p;
        }

        bool estaVacio() {
            return frente == nullptr;
        }

        ~Cola() {
            while(!estaVacio())
                desencolar();
        }
    };

    // Método para realizar BFS y marcar todas las tierras conectadas
    void bfsExplorar(int i, int j, bool** visitado) {
        Cola q;
        Posicion inicio = {i, j};
        q.encolar(inicio);
        visitado[i][j] = true;

        // Direcciones: arriba, abajo, izquierda, derecha
        int direcciones[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

        while(!q.estaVacio()) {
            Posicion actual = q.desencolar();
            for(int d = 0; d < 4; ++d) {
                int ni = actual.x + direcciones[d][0];
                int nj = actual.y + direcciones[d][1];
                if(ni >=0 && ni < filas && nj >=0 && nj < columnas &&
                   matriz->getValor(ni, nj) == '1' && !visitado[ni][nj]) {
                    Posicion vecino = {ni, nj};
                    q.encolar(vecino);
                    visitado[ni][nj] = true;
                }
            }
        }
    }

    // Método para contar el número de islas
    int contarIslas() {
        // Crear una matriz de visitados
        bool** visitado = new bool*[filas];
        for(int i = 0; i < filas; ++i) {
            visitado[i] = new bool[columnas];
            for(int j = 0; j < columnas; ++j)
                visitado[i][j] = false;
        }

        int contador = 0;
        for(int i = 0; i < filas; ++i) {
            for(int j = 0; j < columnas; ++j) {
                if(matriz->getValor(i, j) == '1' && !visitado[i][j]) {
                    bfsExplorar(i, j, visitado);
                    contador++;
                }
            }
        }

        // Liberar memoria de visitado
        for(int i = 0; i < filas; ++i)
            delete[] visitado[i];
        delete[] visitado;

        return contador;
    }
};

// Función main para probar
int main() {
    int filas = 4;
    int columnas = 5;
    Matriz matriz(filas, columnas);

    // Configurar la matriz con islas
    /*
    1 1 0 0 0
    1 1 0 0 0
    0 0 1 0 0
    0 0 0 1 1
    */
    matriz.setValor(0, 0, '1');
    matriz.setValor(0, 1, '1');
    matriz.setValor(1, 0, '1');
    matriz.setValor(1, 1, '1');
    matriz.setValor(2, 2, '1');
    matriz.setValor(3, 3, '1');
    matriz.setValor(3, 4, '1');

    // Crear una instancia de BFS y contar islas
    BFS bfs(&matriz);
    int numeroIslas = bfs.contarIslas();
    std::cout << "Número de Islas: " << numeroIslas << std::endl;

    return 0;
}
