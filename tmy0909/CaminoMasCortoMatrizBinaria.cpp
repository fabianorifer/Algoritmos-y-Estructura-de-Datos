// ShortestPathBinaryMatrix.cpp
// Contexto: Encontrar el camino más corto en una matriz binaria desde la esquina superior izquierda hasta la inferior derecha, moviéndose en 8 direcciones.

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// Estructura para representar una posición en la matriz
struct Pos {
    int x;
    int y;
};

// Clase para implementar BFS
class BFS {
public:
    int n;
    int** grid;

    BFS(int size, int** matriz) {
        n = size;
        grid = new int*[n];
        for(int i = 0; i < n; ++i){
            grid[i] = new int[n];
            for(int j = 0; j < n; ++j)
                grid[i][j] = matriz[i][j];
        }
    }

    // Función para verificar si una posición es válida y no bloqueada
    bool esValida(int x, int y, bool** visitado){
        return (x >=0 && x < n && y >=0 && y < n && grid[x][y] == 0 && !visitado[x][y]);
    }

    // Función para encontrar el camino más corto
    int shortestPath(){
        if(grid[0][0] != 0 || grid[n-1][n-1] != 0)
            return -1;

        // Crear una matriz de visitados
        bool** visitado = new bool*[n];
        for(int i = 0; i < n; ++i){
            visitado[i] = new bool[n];
            for(int j = 0; j < n; ++j)
                visitado[i][j] = false;
        }

        // Definir las 8 direcciones
        int direcciones[8][2] = { {-1, -1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1} };

        // Crear una cola para BFS
        queue<Pos> q;
        Pos inicio = {0,0};
        q.push(inicio);
        visitado[0][0] = true;
        int nivel = 1;

        while(!q.empty()){
            int tamaño = q.size();
            for(int i = 0; i < tamaño; ++i){
                Pos actual = q.front();
                q.pop();

                // Si llegamos al destino
                if(actual.x == n-1 && actual.y == n-1)
                    return nivel;

                // Explorar todas las direcciones
                for(int d = 0; d < 8; ++d){
                    int nx = actual.x + direcciones[d][0];
                    int ny = actual.y + direcciones[d][1];
                    if(esValida(nx, ny, visitado)){
                        Pos vecino = {nx, ny};
                        q.push(vecino);
                        visitado[nx][ny] = true;
                    }
                }
            }
            nivel++;
        }

        // Liberar memoria
        for(int i = 0; i < n; ++i)
            delete[] visitado[i];
        delete[] visitado;

        return -1;
    }

    ~BFS(){
        for(int i = 0; i < n; ++i)
            delete[] grid[i];
        delete[] grid;
    }
};

// Función main para probar
int main(){
    int n = 3;
    // Definir la matriz
    int** grid = new int*[n];
    for(int i = 0; i < n; ++i){
        grid[i] = new int[n];
        for(int j = 0; j < n; ++j)
            grid[i][j] = 0;
    }
    // Bloquear algunas celdas
    grid[0][1] = 1;
    grid[1][1] = 1;
    grid[2][1] = 1;

    BFS bfs(n, grid);
    int resultado = bfs.shortestPath();
    cout << "Longitud del Camino Más Corto: " << resultado << endl;

    // Liberar memoria
    for(int i = 0; i < n; ++i)
        delete[] grid[i];
    delete[] grid;

    return 0;
}
