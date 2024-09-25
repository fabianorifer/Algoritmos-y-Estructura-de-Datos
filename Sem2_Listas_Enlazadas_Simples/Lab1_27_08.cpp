//
// Created by luisr on 27/08/2024.
//
/*
#include <iostream>
#include <cmath>
using namespace std;

template<typename T>
struct Nodo{
    int valor;
    Nodo* siguiente;
};


template<typename T>
class List{
private:
    Nodo<T> *head;
public:
    List(): head(nullptr){}

    //  void push_front(T) --> agrega elemento al inicio de la lista
    void push_front(T valor){
        Nodo<T> *nuevoNodo = new Nodo<T>;
        nuevoNodo -> valor = valor;
        nuevoNodo -> siguiente = head;
        head = nuevoNodo;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // void push_back(T) --> agrega elemento al final
    void push_back(T valor){
        Nodo<T> *nuevoNodo = new Nodo<T>;
        nuevoNodo -> dato = valor;
        Nodo<T> *temp = head;
        while(temp -> siguiente != nullptr){
            temp = temp -> siguiente;
        }
        temp -> siguiente = nuevoNodo;
        nuevoNodo -> siguiente = nullptr;
    }

    void node_middle(){
        Nodo<T> *temp = head;
        while(temp != nullptr){

        }

    }






    /*
    void representacion_binaria(){
        int count{};
        int result{};
        Nodo<T> *temp = head;
        do{
            temp-> siguiente -> valor pow(2);
        }
        while(temp != nullptr);
        {
            temp = temp -> siguiente;
            return temp;

        }
    }

};

*/


