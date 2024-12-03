
/*
#include <iostream>
using namespace std;

class TablaHash {
private:
    int* tabla;
    bool* ocupado;
    int capacidad;
    int elementos;
    int p, a, b;

    // Función hash universal: h(k) = ((a * k + b) % p) % m
    int funcionHash(int clave) {
        return ((a * clave + b) % p) % capacidad;
    }

    void inicializarTabla() {
        for (int i = 0; i < capacidad; ++i) {
            tabla[i] = -1;   // Usamos -1 para indicar casilla vacía
            ocupado[i] = false;  // Bandera para indicar ocupación
        }
        elementos = 0;
    }

public:
    TablaHash(int tam, int primo, int coefA, int coefB) {
        capacidad = tam;
        p = primo;   // Primo grande para la función hash
        a = coefA;   // Coeficiente 'a' para la función hash
        b = coefB;   // Coeficiente 'b' para la función hash
        tabla = new int[capacidad];
        ocupado = new bool[capacidad];
        inicializarTabla();
    }

    // Insertar un elemento en la tabla hash
    void insertar(int clave) {
        if (elementos == capacidad) {
            cout << "Tabla esta llena. Necesita rehashing." << endl;
            return;
        }
        int indice = funcionHash(clave);
        while (ocupado[indice]) {
            indice = (indice + 1) % capacidad;  // Linear probing
        }
        tabla[indice] = clave;
        ocupado[indice] = true;
        elementos++;
    }

    // Buscar un elemento en la tabla hash
    bool buscar(int clave) {
        int indice = funcionHash(clave);
        int inicio = indice;
        while (ocupado[indice]) {
            if (tabla[indice] == clave) {
                return true;
            }
            indice = (indice + 1) % capacidad;
            if (indice == inicio) break;  // Volvió al inicio, no encontrado
        }
        return false;
    }

    // Eliminar un elemento de la tabla hash
    void eliminar(int clave) {
        int indice = funcionHash(clave);
        int inicio = indice;
        while (ocupado[indice]) {
            if (tabla[indice] == clave) {
                tabla[indice] = -1;
                ocupado[indice] = false;
                elementos--;
                return;
            }
            indice = (indice + 1) % capacidad;
            if (indice == inicio) break;
        }
        cout << "Clave no encontrada." << endl;
    }

    // Rehashing (redimensionar la tabla)
    void rehash(int nuevoTam) {
        int* nuevaTabla = new int[nuevoTam];
        bool* nuevoOcupado = new bool[nuevoTam];
        int viejaCapacidad = capacidad;

        int* viejaTabla = tabla;
        bool* viejoOcupado = ocupado;

        capacidad = nuevoTam;
        tabla = nuevaTabla;
        ocupado = nuevoOcupado;
        inicializarTabla();

        for (int i = 0; i < viejaCapacidad; ++i) {
            if (viejoOcupado[i]) {
                insertar(viejaTabla[i]);
            }
        }
        delete[] viejaTabla;
        delete[] viejoOcupado;
    }

    // Verificar si la tabla está vacía
    bool estaVacia() {
        return elementos == 0;
    }

    // Mostrar el contenido de la tabla (para depuración)
    void mostrar() {
        for (int i = 0; i < capacidad; ++i) {
            if (ocupado[i])
                cout << "Indice " << i << ": " << tabla[i] << endl;
            else
                cout << "Indice " << i << ": vacio" << endl;
        }
    }

    // Destructor
    ~TablaHash() {
        delete[] tabla;
        delete[] ocupado;
    }
};

int main() {
    // Inicializamos la tabla hash con tamaño 7, primo 11, a=2, b=3
    TablaHash tabla(7, 11, 2, 3);

    tabla.insertar(10);
    tabla.insertar(22);
    tabla.insertar(31);
    tabla.insertar(4);
    tabla.insertar(15);
    tabla.insertar(69);
    tabla.insertar(69);
    tabla.insertar(69);
    tabla.insertar(69);
    tabla.mostrar();

    cout << "\nBuscando el elemento 22: " << (tabla.buscar(22) ? "Encontrado" : "No encontrado") << endl;
    cout << "Eliminando el elemento 22..." << endl;
    tabla.eliminar(22);
    cout << "Buscando el elemento 22: " << (tabla.buscar(22) ? "Encontrado" : "No encontrado") << endl;

    cout << "\nRealizando rehash a tamaño 10..." << endl;
    tabla.rehash(10);
    tabla.mostrar();

    cout << "\nLa tabla está vacía: " << (tabla.estaVacia() ? "Sí" : "No") << endl;

    return 0;
}
*/