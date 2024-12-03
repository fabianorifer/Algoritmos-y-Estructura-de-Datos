//
// Created by luisr on 27/08/2024.
//

/*
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
struct Nodo{
    T dato;
    Nodo *siguiente;

};


template<typename T>
class List{
private:
    Nodo<T> *head;
public:
    List() : head(nullptr){}

    // HOMEWORK - SEMANA 1 - LISTAS ENLAZADAS

    // T front()
    ///////////////////////////////
    T front(){
        if(head == nullptr){
            throw std::out_of_range("No hay valores, lista vacia");  // ->>> Verificamos si la lista esta vacia, y arrojamos una excepcion
        }
        return head -> dato;  // ->>> Retornamos el valor del primer nodo (cabeza)
    }

    // T back()
    T back(){
        Nodo<T> temp = head;
        while(temp -> siguiente != nullptr){  // ->>> Recorre hasta que el siguiente sea un nulo.
            temp = temp -> siguiente;         // ->>> Actualiza el temporal hacia el siguiente (bucle).
        }
        return temp -> dato;                  // ->>> Retorna el dato final del nodo temporal que hizo el recorrido.
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //  void push_front(T) --> agrega elemento al inicio de la lista
    void push_front(T valor){
        Nodo<T> *nuevoNodo = new Nodo<T>;     // ->>> Creamos un nuevo nodo que usaremos para asignarlo al siguiente que seria la cabeza.
        nuevoNodo -> dato = valor;            // ->>> Accedemos al dato del nuevo nodo y le asignamos el valor pasado.
        nuevoNodo -> siguiente = head;        // ->>> Hacemos que el nuevo nodo apunte a la que seria la "antigua cabeza".
        head = nuevoNodo;                     // ->>> Actualizamos el valor de cabeza sea ahora el nuevo nodo.
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // void push_back(T) --> agrega elemento al final
    void push_back(T valor){
        Nodo<T> *nuevoNodo = new Nodo<T>;     // ->>> Creamos un nuevo nodo con memoria dinamica.
        nuevoNodo -> dato = valor;            // ->>> Accedemos al dato del nuevo nodo y le asignamos el valor pasado por la funcion.
        Nodo<T> *temp = head;                 // ->>> Creamos una variable temporal y hacemos que apunte a la cabeza.
        while(temp -> siguiente != nullptr){  // ->>> Cremos un bucle que itere hasta que el siguiente sea nulo.
            temp = temp -> siguiente;         // ->>> Recorremos para que el temporal sea el siguiente y luego el siguiente y asi sucesivamente, el temporal se desplaza toda la lista.
        }
        temp -> siguiente = nuevoNodo;        // ->>> Hacemos que el siguiente al temporal que era nuestro ultimo nodo apunte a hacia nuestro nuevo nodo.
        nuevoNodo -> siguiente = nullptr;     // ->>> Por ultimo hacemos que nuestro nuevo nodo su siguiente sea un nullptr.
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // void pop_front() --> elimina el primer nodo
    void pop_front(){
        Nodo<T> *temp = head;                 // ->>> Guardar la cabeza actual en un puntero temporal.
        head = head -> siguiente;             // ->>> Asignamos el valor de cabeza hacia el siguiente nodo osea el segundo nodo.
        delete temp;                          // ->>> Se elimina el nodo que estaba almacenado en temp (el nodo que era la antigua cabeza).
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // void pop_back(T) --> elimina el ultimo nodo
    void pop_back(){
        if(head -> siguiente == nullptr){    // ->>> Verificamos si el siguiente a la cabeza es es nulo, si es que esto es cierto:
            delete head;                     // ->>> Eliminaremos la cabeza.
            head = nullptr;                 // ->>> Y asignamos que la cabeza sea nulo, lista vacia.
        }
        else{                                // ->>> SI ES QUE NO ES ASI:
            Nodo<T> *temp = head;             // ->>> Guardamos la cabeza en un puntero temporal.
            while(temp -> siguiente -> siguiente != nullptr){  // ->>> Se ejecutara el bucle hasta que el siguiente del siguiente apunte a nullptr.
                temp = temp -> siguiente;                      // ->>> Haremos recorrer la variable temporal por toda la lista.
            }
            delete temp -> siguiente;                          // ->>> Una vez que temp apunta al penúltimo nodo, el nodo siguiente de temp (que es el último nodo de la lista) se elimina.
            temp -> siguiente = nullptr;                       // ->>> Después de eliminar el último nodo, se establece temp->siguiente a nullptr, indicando que ahora temp es el último nodo de la lista.
        }
    }

    T at(int indice){
        if(head == nullptr){
            throw std::out_of_range("La lista esta vacia");
        }
        Nodo<T> *temp = head;
        int currentIndex = 0;
        while(temp != nullptr && currentIndex < indice){
            temp = temp -> siguiente;
            currentIndex ++;
        }
        if(temp == nullptr){
            throw std::out_of_range("Indice fuera de rango");
        }
        return temp -> dato;
    }

    bool empty() const{
        return head == nullptr;
    }

    T size() const{
        int count = 0;
        Nodo<T> *temp = head;
        while(temp != nullptr){
            count ++;
            temp = temp -> siguiente;
        }
        return count;
    }

    void clear(){
        while(head != nullptr){
            Nodo<T> *temp = head;
            head = head -> siguiente;
            delete temp;
        }
    }

    void reverse() {
        Nodo<T>* prev = nullptr;
        Nodo<T>* current = head;
        Nodo<T>* next = nullptr;

        while (current != nullptr) {
            next = current->siguiente;
            current->siguiente = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    List<T> intersect(const List<T>& list1, const List<T>& list2) {
        List<T> result;
        Nodo<T>* ptr1 = list1.head;
        Nodo<T>* ptr2 = list2.head;

        while (ptr1 != nullptr && ptr2 != nullptr) {
            if (ptr1->dato == ptr2->dato) {
                result.push_back(ptr1->dato);
                ptr1 = ptr1->siguiente;
                ptr2 = ptr2->siguiente;
            } else if (ptr1->dato < ptr2->dato) {
                ptr1 = ptr1->siguiente;
            } else {
                ptr2 = ptr2->siguiente;
            }
        }

        return result;
    }

    std::vector<int> intersect(const std::vector<int>& list1, const std::vector<int>& list2) {
        std::vector<int> result;
        int i = 0, j = 0;

        while (i < list1.size() && j < list2.size()) {
            if (list1[i] == list2[j]) {
                result.push_back(list1[i]);
                i++;
                j++;
            } else if (list1[i] < list2[j]) {
                i++;
            } else {
                j++;
            }
        }

        return result;
    }


    void recorrer(){
        Nodo<T> *temp = head;
        while(temp != nullptr){
            cout<<temp -> dato << " ";
            temp = temp -> siguiente;
        }
    }
};




int main() {
    List<int> myfirstlist;
    myfirstlist.push_front(1);
    myfirstlist.push_front(0);
    myfirstlist.push_front(1);
}
*/