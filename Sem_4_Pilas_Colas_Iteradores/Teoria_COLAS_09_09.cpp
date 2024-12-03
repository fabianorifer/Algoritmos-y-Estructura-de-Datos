//
// Created by luisr on 9/09/2024.
//


#include <iostream>
using namespace std;

// COLAS: El primero en entrar es el primero en salir

const int MAX_STACK_SIZE = 100;

typedef struct{
    char key;
} element;

typedef struct{
    element list[MAX_STACK_SIZE];
    int front;
    int rear;
} queue;

// Funcion para verificar si la cola esta vacia
int isEmpty(queue *q){
    if(q -> front == -1 && q -> rear == -1){
        return 1;
    }
    return 0;
}
// Funcion para verificar si la pila esta llena
int isFull(queue *q){
    if(q -> rear >= MAX_STACK_SIZE -1){
        return 1;
    }
    return 0;
}
// Funcion para insertar un elemento en la cola
void enqueue(queue *q, element e){
    if(!isFull(q)){
        if(q -> front == -1){
            q -> front = 0;
        }
        q -> rear++;
        q -> list[q -> rear] = e;
    }
    else{
        cout << "La cola esta llena" << endl;
    }
}
// Funcion para eliminar un elemento en la cola
void dequeue(queue *q){
    if(!isEmpty(q)){
        if(q -> front == q -> rear){
            q -> front = -1;
            q -> rear = -1;
        }
        else{
            q -> front ++;
        }
    }
    else{
        cout << "Error la cola esta vacia" << endl;
    }
}
// Funcion para mostrar el primer elemento del frente
element front(queue *q){
    return q -> list[q -> front];
}


int main() {
    queue q;
    q.front = -1;  // Inicializamos front como vacía
    q.rear = -1;   // Inicializamos rear como vacía

    element e1, e2, e3;
    e1.key = 'A';
    e2.key = 'B';
    e3.key = 'C';

    // Verificamos si la cola está vacía al inicio
    if (isEmpty(&q)) {
        cout << "La cola esta vacia" << endl;
    }

    // Insertamos algunos elementos
    enqueue(&q, e1);
    enqueue(&q, e2);
    enqueue(&q, e3);

    // Mostramos el primer elemento
    cout << "El primer elemento (front): " << front(&q).key << endl;

    // Eliminamos un elemento
    dequeue(&q);
    cout << "Elemento eliminado. Nuevo front: " << front(&q).key << endl;

    // Verificamos si la cola está llena (no debería estarlo)
    if (isFull(&q)) {
        cout << "La cola esta llena" << endl;
    } else {
        cout << "La cola NO esta llena" << endl;
    }

    return 0;
}

