//
// Created by luisr on 27/08/2024.
//

#include <iostream>
using namespace std;

struct Nodo{
    int dato;
    Nodo *siguiente;

};


class List{
private:
    Nodo *head;
public:
    List() : head(nullptr){}

    // Forward List (Push Front)
    void agregar_nodo_al_inicio(int valor){
        Nodo *nuevoNodo = new Nodo;
        nuevoNodo -> dato = valor;
        nuevoNodo -> siguiente = head;
        head = nuevoNodo;
    }

    // Forward List (Push Back)
    void agregar_nodo_al_final(){
        Nodo *nuevoNodo = new Nodo;
        nuevoNodo -> dato = 5;
        Nodo *temp = head;
        while(temp -> siguiente != nullptr){
            temp = temp -> siguiente;
        }
        temp -> siguiente = nuevoNodo;
        nuevoNodo -> siguiente = nullptr;
    }
    // Forward List (Recorrer la lista)
    void recorrer(){
        Nodo *temp = head;
        while(temp != nullptr){
            cout<<temp -> dato << " ";
            temp = temp -> siguiente;
        }
    }
    // Forward List (Pop Front)
    void eliminar_nodo_al_inicio(){
        Nodo *temp = head;
        head = head -> siguiente;
        delete temp;
    }

    void eliminar_nodo_al_final(){


    }
};


int main() {
    List myfirstlist;
    myfirstlist.agregar_nodo_al_inicio(5);
    myfirstlist.agregar_nodo_al_inicio(4);
    myfirstlist.agregar_nodo_al_inicio(3);
    myfirstlist.agregar_nodo_al_final();
    myfirstlist.eliminar_nodo_al_inicio();
    myfirstlist.recorrer();


    return 0;
}
