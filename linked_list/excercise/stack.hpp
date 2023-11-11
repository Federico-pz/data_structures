#include <iostream>
#include "linkedList.hpp"


#pragma once
template <class T>
class Stack : private LinkedList<T>
{
    public:
        Stack(){}
        Stack(Node<T>* first) : LinkedList<T>(first){}
        void setFirst(Node<T>* node){this->firstElement = node;}
        Node<T>* top();
        Node<T>* pop();
        void push(Node<T>* node);
        using LinkedList<T>::size;
};

/*
Función que regresa el elemento superior de la pila O(1)
Return: La direccion del nodo de hasta arriba en la pila
*/
template <class T>
Node<T>* Stack<T>::top()
{
    return this->firstElement;
}

/*
Función que elimina y regresa el elemento superior de la pila O(1)
Return: El apuntador al nodo que se eliminó
*/
template <class T>
Node<T>* Stack<T>::pop()
{
    if(this->size() == 0)
    {
        std::cout << "No elements to pop, stack is empty." << std::endl;
        return nullptr;
    }
    else
    {
        Node<T>* tempNode = this->firstElement->getNext();
        Node<T>* retNode = this->firstElement;
        this->firstElement->setNext(nullptr);
        this->setFirst(tempNode);
        return retNode;
    }
}

/*
Función que inserta un elemento hasta arriba de la pila O(1)
Param: Un apuntador al nodo a insertar
*/
template <class T>
void Stack<T>::push(Node<T>* node)
{
    node->setNext(this->top());
    this->setFirst(node);
}