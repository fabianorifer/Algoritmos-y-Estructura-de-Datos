// SparseMatrix.cpp
#include <iostream>
#include <vector>

using namespace std;

// Estructura para representar un elemento no nulo en la matriz
struct Elemento {
    int fila;
    int columna;
    int valor;
};

// Clase para representar una Sparse Matrix utilizando Lista de Tripletas
class SparseMatrix {
public:
    int filas;
    int columnas;
    int numElementos;
    vector<Elemento> elementos;

    // Constructor
    SparseMatrix(int filas, int columnas) {
        this->filas = filas;
        this->columnas = columnas;
        numElementos = 0;
    }

    // Método para insertar un elemento
    void insertar(int fila, int columna, int valor) {
        if(fila >= filas || columna >= columnas || fila < 0 || columna < 0) {
            cout << "Posición inválida: (" << fila << ", " << columna << ")" << endl;
            return;
        }
        if(valor != 0) {
            Elemento elem;
            elem.fila = fila;
            elem.columna = columna;
            elem.valor = valor;
            elementos.push_back(elem);
            numElementos++;
        }
    }

    // Método para imprimir la matriz
    void imprimir() {
        cout << "Sparse Matrix (" << filas << "x" << columnas << ") con " << numElementos << " elementos no nulos:" << endl;
        for(auto &elem : elementos)
            cout << "(" << elem.fila << ", " << elem.columna << ") = " << elem.valor << endl;
    }

    // Método para sumar dos matrices dispersas
    SparseMatrix sumar(SparseMatrix &A, SparseMatrix &B) {
        if(A.filas != B.filas || A.columnas != B.columnas) {
            cout << "Las matrices deben tener las mismas dimensiones para sumar." << endl;
            exit(1);
        }

        SparseMatrix C(A.filas, A.columnas);
        int i = 0, j = 0;

        while(i < A.elementos.size() && j < B.elementos.size()) {
            if(A.elementos[i].fila < B.elementos[j].fila ||
               (A.elementos[i].fila == B.elementos[j].fila && A.elementos[i].columna < B.elementos[j].columna)) {
                C.insertar(A.elementos[i].fila, A.elementos[i].columna, A.elementos[i].valor);
                i++;
            }
            else if(B.elementos[j].fila < A.elementos[i].fila ||
                    (B.elementos[j].fila == A.elementos[i].fila && B.elementos[j].columna < A.elementos[i].columna)) {
                C.insertar(B.elementos[j].fila, B.elementos[j].columna, B.elementos[j].valor);
                j++;
            }
            else {
                int suma = A.elementos[i].valor + B.elementos[j].valor;
                if(suma != 0)
                    C.insertar(A.elementos[i].fila, A.elementos[i].columna, suma);
                i++;
                j++;
            }
        }

        // Insertar los elementos restantes de A
        while(i < A.elementos.size()) {
            C.insertar(A.elementos[i].fila, A.elementos[i].columna, A.elementos[i].valor);
            i++;
        }

        // Insertar los elementos restantes de B
        while(j < B.elementos.size()) {
            C.insertar(B.elementos[j].fila, B.elementos[j].columna, B.elementos[j].valor);
            j++;
        }

        return C;
    }

    // Método para multiplicar dos matrices dispersas
    SparseMatrix multiplicar(SparseMatrix &A, SparseMatrix &B) {
        if(A.columnas != B.filas) {
            cout << "Las dimensiones de las matrices no son compatibles para multiplicar." << endl;
            exit(1);
        }

        SparseMatrix C(A.filas, B.columnas);

        // Vector para almacenar los elementos de B por fila
        vector<vector<Elemento>> B_por_fila(B.filas, vector<Elemento>());

        for(auto &elem : B.elementos)
            B_por_fila[elem.fila].push_back(elem);

        // Multiplicar
        for(auto &elemA : A.elementos) {
            int filaA = elemA.fila;
            int columnaA = elemA.columna;
            int valorA = elemA.valor;

            for(auto &elemB : B_por_fila[columnaA]) {
                int columnaB = elemB.columna;
                int valorB = elemB.valor;
                // Buscar si ya existe un elemento en C en (filaA, columnaB)
                bool encontrado = false;
                for(auto &elemC : C.elementos) {
                    if(elemC.fila == filaA && elemC.columna == columnaB) {
                        elemC.valor += valorA * valorB;
                        if(elemC.valor == 0) {
                            // Remover el elemento si el valor es cero
                            C.elementos.erase(remove(C.elementos.begin(), C.elementos.end(), elemC), C.elementos.end());
                            C.numElementos--;
                        }
                        encontrado = true;
                        break;
                    }
                }
                if(!encontrado && valorA * valorB != 0)
                    C.insertar(filaA, columnaB, valorA * valorB);
            }
        }

        return C;
    }
};

// Función main para probar la implementación de SparseMatrix
int main() {
    SparseMatrix A(3, 3);
    A.insertar(0, 0, 1);
    A.insertar(0, 2, 2);
    A.insertar(1, 1, 3);
    A.insertar(2, 0, 4);
    A.insertar(2, 2, 5);

    SparseMatrix B(3, 3);
    B.insertar(0, 0, 7);
    B.insertar(0, 1, 8);
    B.insertar(1, 1, 9);
    B.insertar(2, 0, 10);
    B.insertar(2, 2, 11);

    cout << "Matriz A:" << endl;
    A.imprimir();
    cout << endl;

    cout << "Matriz B:" << endl;
    B.imprimir();
    cout << endl;

    // Sumar A + B
    SparseMatrix C = C.sumar(A, B);
    cout << "Matriz C = A + B:" << endl;
    C.imprimir();
    cout << endl;

    // Multiplicar A * B
    SparseMatrix D = D.multiplicar(A, B);
    cout << "Matriz D = A * B:" << endl;
    D.imprimir();
    cout << endl;

    return 0;
}
