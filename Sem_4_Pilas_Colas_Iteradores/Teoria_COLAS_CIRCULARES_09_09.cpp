//
// Created by luisr on 11/09/2024.
//

/*
#include <iostream>
using namespace std;

const int MAX_Q_SIZE = 100;

typedef struct{
    int key;
} element;

typedef struct{
    element list[MAX_Q_SIZE];
    int front, rear;
} queue;

// Funcion para verificar si la cola esta vacia
int isEmpty(queue *q){
    if(q -> front == q -> rear){
        return 1;
    }
    return 0;
}
// Funcion para verificar si la cola esta llena
int isFull(queue *q){
    if(q -> front == (q -> rear +1) % MAX_Q_SIZE){
        return 1; //la cola esta llena
    }
    return 0;
}
// Funcion para insertar un elemento en la cola
void enqueue(queue *q, element e){
    if(!isFull(q)){
        q -> rear = (q -> rear +1) % MAX_Q_SIZE;
        q -> list[q -> rear] = e;
    }
    else{
        cout << "Error, la cola esta llena";
    }
}
// Funcion para eliminar un elemento en la cola
void dequeue(queue *q){
    if(!isEmpty(q)){
        q -> front = (q -> front +1) % MAX_Q_SIZE;
    }
    else{
        cout << "Error, la cola esta vacia";
    }
}
// Funcion para mostrar el primer elemento del frente
element front(queue *q){
    if(!isEmpty(q)){
        return q -> list[q -> front];
    }
    else{
        cout << "Error, la cola esta vacia" << endl;
        element e;
        e.key = '\0';
        return e;
    }
}



 int main() {
    queue q;
    q.front = 0;  // Inicializamos el front
    q.rear = 0;   // Inicializamos el rear

    element e1, e2, e3, e4;  // Creamos varios elementos para insertar
    e1.key = 10;
    e2.key = 20;
    e3.key = 30;
    e4.key = 40;

    // Probamos si la cola está vacía
    if (isEmpty(&q)) {
        cout << "La cola está vacía" << endl;
    }

    // Insertamos elementos en la cola
    enqueue(&q, e1);
    enqueue(&q, e2);
    enqueue(&q, e3);

    // Mostramos el primer elemento de la cola
    cout << "Primer elemento (front): " << front(&q).key << endl;

    // Eliminamos un elemento
    dequeue(&q);
    cout << "Elemento eliminado. Nuevo front: " << front(&q).key << endl;

    // Insertamos otro elemento
    enqueue(&q, e4);
    cout << "Nuevo elemento insertado. Rear ahora contiene: " << q.list[q.rear].key << endl;

    // Volvemos a mostrar el primer elemento después de varias operaciones
    cout << "El front actual es: " << front(&q).key << endl;

    // Probamos si la cola está llena (no debería estarlo en este caso)
    if (isFull(&q)) {
        cout << "La cola está llena" << endl;
    } else {
        cout << "La cola NO está llena" << endl;
    }

    return 0;
}

*/

