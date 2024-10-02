//
// Created by luisr on 2/10/2024.
//

#ifndef ALGORITMOS_Y_ESTRUCTURA_DE_DATOS_NODE_H
#define ALGORITMOS_Y_ESTRUCTURA_DE_DATOS_NODE_H

#include <iostream>
template <typename T>
struct NodeBT{
    T data;
    int height;
    NodeBT<T>* left;
    NodeBT<T>* right;
    NodeBT():left(nullptr),right(nullptr),height(0){}
    explicit NodeBT(T value):data(value), height(0){
        left = right = nullptr;
    }    void killself(){
        if(left != nullptr){left->killself();}
        if(right != nullptr){right->killself();}
        delete this;
    }
};

#endif //ALGORITMOS_Y_ESTRUCTURA_DE_DATOS_NODE_H
