#include <iostream>
#include "linkedList.hpp"

#pragma once
template <class T>
class Queue : private LinkedList<T>
{
    private:
    Node<T>* last;
    public:
        Queue(){}
        Queue(Node<T>* first) : LinkedList<T>(first){}
        void arrive(Node<T>* node);
        Node<T>* leave();
        Node<T>* first();
        using LinkedList<T>::size;
};

/*
Función que agrega un elemento al final de la lista O(1)
Param: El nodo a a agregar
*/
template <class T>
void Queue<T>::arrive(Node<T>* node)
{
    if(this->size() == 0)
    {
        this->last = this->firstElement = node;
    }
    else
    {
        this->last->setNext(node);
        this->last = node;
    }
}

/*
Función que elimina y regresa el primer elemento de la fila O(1)
Return: Un apuntador al nodo que salió de la fila
*/
template <class T>
Node<T>* Queue<T>::leave()
{
    if(this->size() == 0){std::cout << "No element to remove, queue is empty." << std::endl;}
    else
    {
        Node<T>* temp = this->first();
        this->firstElement = this->first()->getNext();
        temp->setNext(nullptr);
        delete temp;
    }
}

/*
Función que regresa el primer elemento de la lista O(1)
Return: El apuntador al nodo que está al principio
*/
template <class T>
Node<T>* Queue<T>::first()
{
    return this->firstElement;
}