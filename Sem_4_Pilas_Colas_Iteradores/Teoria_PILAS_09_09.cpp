//
// Created by luisr on 9/09/2024.
//
/*
#include <iostream>
#include <string>
using namespace std;

// PILAS: Ultimo en entrar, PRIMERO en salir (LIFO)

const int MAX_STACK_SIZE = 100;

// DEFINICION DEL TIPO DE DATO QUE ALMACENAREMOS EN LA PILA
typedef struct {
    char key;
} element;

// DEFINICION DE LA ESTRUCTURA DE LA PILA
typedef struct{
    element list[MAX_STACK_SIZE];
    int top;
} stack;

// Funcion para verificar si la pila esta vacia
int isEmpty(stack *s){
    if(s -> top == -1){
        return 1;
    }
    return 0;
}

// Funcion para verificar si la pila esta llena
int isFull(stack *s){
    if(s -> top >= MAX_STACK_SIZE -1){
        return 1;
    }
    return 0;
}

// Funcion para insertar un elemento en la pila
void push(stack *s, element e){
    if(!isFull(s)){
        (s -> top) ++;
        s -> list[s -> top] = e; // Actualizamos el valor del top
    }
    else{
        cout << "Error, la pila esta llena" << endl;
    }
};

// Funcion para eliminar el elemento de la cima de la pila
void pop(stack *s){
    if(!isEmpty(s)){
        (s -> top)--;
    }
    else{
        cout << "Error, la pila esta vacia";
    }
};

// Funcion para mostrar el primer elemento o cima de la pila
element top(stack *s){
    return s -> list[s -> top];
}



bool esBalanceada(string expr){
    stack pila; //Creamos una pila llamada "pila"
    pila.top = -1; // La inicializamos vacia

    for (char &ch : expr){ // Iteramos por cada char de la expresion
        if (ch == '(' || ch == '{' || ch == '['){ // Si el ch es igual a un parentesis de entrada
            element e; // Creamos un elemento e
            e.key = ch; // Accedemos al valor del elemento e y lo asignamos al char
            push(&pila, e); // Agregamos el valor de e a la pila
        } else if (ch == ')' || ch == '}' || ch == ']'){ // Si es que es un parantesis de cierre
            if (isEmpty(&pila)){ //Verificamos si la pila esta vacia, retorne falso
                return false;
            }
            char topChar = top(&pila).key; // Creamos una variable que la asignaremos al primer valor de la pila
            pop(&pila); // Eliminamos el primer elemento de la pila

            if((ch == ')' && topChar != '(') || // Si el caracter es igual al parentesis de apertura y top char es diferente del de cierre, retornamos false
            (ch == '}' && topChar != '{') ||
            (ch == ']' && topChar != '[')){
                return false;
            }
        }
    }
    return isEmpty(&pila); // Si la pila esta vacia significa que hubo emparejamiento perfecto
}


int main() {
    stack s;
    s.top = -1;  // Inicializamos la pila vacía

    element e1, e2, e3;
    e1.key = 'A';
    e2.key = 'B';
    e3.key = 'C';

    // Verificamos si la pila está vacía al inicio
    if (isEmpty(&s)) {
        cout << "La pila esta vacia" << endl;
    }

    // Insertamos algunos elementos
    push(&s, e1);
    push(&s, e2);
    push(&s, e3);

    // Mostramos el elemento en la cima de la pila
    cout << "El elemento en la cima es: " << top(&s).key << endl;

    // Eliminamos el elemento de la cima
    pop(&s);
    cout << "Elemento eliminado. Nuevo top: " << top(&s).key << endl;

    // Insertamos un nuevo elemento
    element e4;
    e4.key = 'D';
    push(&s, e4);
    cout << "Elemento insertado. Nuevo top: " << top(&s).key << endl;

    // Verificamos si la pila está llena (no debería estarlo)
    if (isFull(&s)) {
        cout << "La pila esta llena" << endl;
    } else {
        cout << "La pila NO esta llena" << endl;
    }

    // Prueba de balanceo de paréntesis
    string expr;
    cout << "Introduce una expresion de parentesis: ";
    cin >> expr;

    if (esBalanceada(expr)) {
        cout << "La expresion esta balanceada" << endl;
    } else {
        cout << "La expresion NO esta balanceada" << endl;
    }

    return 0;
}*/