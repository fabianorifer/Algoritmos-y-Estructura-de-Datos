//
// Created by luisr on 27/08/2024.
//
/*
#include <iostream>
using namespace std;

template<typename T>
struct Nodo{
    T dato;
    Nodo *anterior;
    Nodo *siguiente;

};

template<typename T>
class Double_List{
private:
    Nodo<T> *head;
    Nodo<T> *tail;
public:
    Double_List(): head(nullptr), tail(nullptr) {}

    void push_front(T valor){
        Nodo<T> *nuevo_nodo = new Nodo<T>; // Creacion de nuevo nodo.
        nuevo_nodo -> dato = valor; // Accedemos al dato del nuevo nodo y le asignamos el valor pasado como parametro.
        if (head == nullptr) {
            head = tail = nuevo_nodo; // Si la cabeza apunta a nulo, el nuevo nodo sera cabeza y cola a la vez.
        } else {
            nuevo_nodo->siguiente = head; // Si es que no, el siguiente del nuevo nodo apuntara a la cabeza, que ya no sera cabeza.
            head->anterior = nuevo_nodo; // El anterior a la antigua cabeza sera igual al nuevo nodo.
            head = nuevo_nodo; // Actualizamos la cabeza, indicando que sera el nuevo nodo.
        }
    }

    void push_back(T valor){
        Nodo<T> *nuevo_nodo = new Nodo<T>; // Creacion de nuevo nodo.
        nuevo_nodo -> dato = valor; // Accedemos al dato del nuevo nodo y le asignamos el valor.
        if(head == nullptr){ // Si la cabeza apunta a nulo.
            head = tail = nuevo_nodo; // El nuevo nodo sera cabeza y cola a la vez.
        }
        else{
            nuevo_nodo -> anterior = tail; // Si es que la cabeza no apunta a nulo el anterior al nuevo nodo sera la cola.
            tail->siguiente = nuevo_nodo; // El siguiente a la cola sera el nuevo nodo.
            tail = nuevo_nodo; // Actualizamos el valor de cola a que sea el nuevo nodo.
        }
    }

    void pop_front(){
        if(head == nullptr){ // Si es que la cabeza apunta a nulo no se realiza nada.
            return;
        }

        Nodo<T> *temp = head; // Creamos una variable temporal que se ubique en cabeza.
        if(head == tail){ // Si cabeza es igual a la cola.
            head = tail = nullptr; // Entonces tanto la cabeza como cola, que son uno solo apuntaran a nulo.
        }
        else{
            head = head -> siguiente; // Si es que no, hacemos que la nueva cabeza sea ahora la siguiente de cabeza antigua.
            head -> anterior = nullptr; // Hacemos que el anterior de la nueva cabeza apunte a nulo.
        }
        delete temp; // Eliminamos el temporal donde antes estaba ubicada la cabeza antigua.
    }

    void pop_back(){
        if(tail == nullptr){ // Si la cola es nula, no se realiza nada.
            return;
        }
        Nodo<T> *temp = tail; // Declaramos un nodo temporal y la asignamos en la cola.
        if(tail == head){ // Si la cola es igual a la cabeza
            tail = head = nullptr; // Tanto la cabeza como la cola apuntaran a nulo.
        }
        else{
            tail = tail -> anterior; // Si es que no, hacemos que el anterior a la antigua cola sea la nueva cola
            tail -> siguiente = nullptr; // y el siguiente de la nueva cola apuntara a nulo para asegurarnos.
        }
        delete temp; // Eliminamos la cola antigua que ahora apunta hacia la anterior de ella misma.
    }

    void insert(int pos, T valor) {

        // Si la insercion es al inicio de la lista.
        Nodo<T> *nuevo_nodo = new Nodo<T>; // Creamos un nodo con memoria dinamica.
        nuevo_nodo -> dato = valor; // Accedemos al dato del nuevo nodo y le asignamos el valor de la funcion.

        if (pos == 1) { // Si la posicion indicada es 1.
            nuevo_nodo->siguiente = head; // Se insertara el nodo al inicio de la lista haciendo que el siguiente del nuevo nodo sea la cabeza.
            if (head != nullptr) { // Si la cabeza es diferente de nulo.
                head->anterior = nuevo_nodo; // El anterior de la cabeza sera el nuevo nodo, para asegurarnos.
            }
            head = nuevo_nodo; // Actualizamos a que la cabeza sea el nuevo nodo.
            if (tail == nullptr) { // Si la cola apunta a nulo.
                tail = nuevo_nodo; // El nuevo nodo sera la cola.
            }
            return;
        }

        // Insercion en medio de la lista.
        Nodo<T> *temp = head; // Creamos una variable temporal y la asignamos a la cabeza.
        int i = 0; // Inicializamos nuestro contador.
        while (i ++ < pos - 1 && temp != nullptr) { // Mientras que i aumente, sea menor que la posicion elegida por el usuario -1 y temporal sea diferente de nulo.
            temp = temp->siguiente; // Recorreremos la lista avanzando hacia el siguiente.
        }
        nuevo_nodo->siguiente = temp->siguiente; // El siguiente al nuevo nodo lo asignamos lo que era el siguiente al temporal.
        nuevo_nodo->anterior = temp; // El anterior del nuevo nodo lo asignamos al temporal, lo incrustamos luego de temp.
        if (temp->siguiente != nullptr) { // Si el siguiente a temporal es distinto a nulo.
            temp->siguiente->anterior = nuevo_nodo; // Accedemos al siguiente de temp y definimos que su anterior sea el nuevo nodo.
        }
        temp->siguiente = nuevo_nodo; // Actualizamos a que el siguiente de temporal sea el nuevo nodo.


        // Si la insercion es al final de la lista.
        if (temp == nullptr || temp->siguiente == nullptr) { // Si temporal apunta a nulo o el siguiente de temporal es nulo.
            nuevo_nodo->anterior = tail; // El anterior del nuevo nodo la asignamos a la cola.
            if (tail != nullptr) { // Si la cola no apunta a nulo.
                tail->siguiente = nuevo_nodo; // El siguiente de la cola le asignamos el nuevo nodo.
            }
            tail = nuevo_nodo; // Actualizamos que la cola sera el nuevo nodo.
            if (head == nullptr) { // Si la cabeza apunta a nulo.
                head = nuevo_nodo; // Actualizamos que la cabeza sea el nuevo nodo.
            }
        }
    }

    void remove(int pos){
        Nodo<T> *temp = head;
        int i = 1;
        while (i ++ < pos-1 && temp != nullptr){
            temp = temp -> siguiente;
        }
        temp -> anterior -> siguiente = temp -> siguiente;
        temp -> siguiente -> anterior = temp -> anterior;

        delete temp;
    }


    // Funcion para imprimir la lista
    void print_list(){
        Nodo<T> *temp = head;
        while (temp != nullptr) {
            cout << temp->dato << " ";
            temp = temp->siguiente;
        }
        cout << endl;
    }

    int saber_cantidad(){
        Nodo<T> *temp = head;
        int a = 0;
        while (temp != nullptr) {
            a++;
            temp = temp->siguiente;
        }
        return a;
    }

    void Verificar(){
        bool esPalindromo = true;

        Nodo<T> *temp1 = head;
        Nodo<T> *temp2 = tail;

        int b = saber_cantidad();
        for (int i = 0; i < b/2; ++i) {
            if(temp1 -> dato != temp2 -> dato) {
                esPalindromo = false;
                break;
            }
            temp1 = temp1->siguiente;
            temp2 = temp2->anterior;
        }


        if(esPalindromo){
            cout << "es palindromo";
        }
        else{
            cout << "no es palindromo";
            }
    }
};





int main(){
    Double_List<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    list.push_front(40);
    list.push_front(50);
    list.push_back(5);
    list.push_back(1);
    list.push_back(3);
    //list.pop_front(); // Elimina el 69
    //list.pop_back(); // Elimina el 200
    list.insert(7,15); //Imprime entre el 20 - 10 osea 30 -> 15 -> 20
    list.remove(4);
    list.print_list();
    // Imprime 50,40,30,20,10,5,1


    return 0;
}
*/