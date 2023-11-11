#include<iostream>

#pragma once
template <class T>
class Node
{
    private:
        
        Node<T> * next = nullptr;
    public:
        T info;
        Node(){}
        Node(T info): info(info){}
        Node<T>* getNext(){return next;}
        void print()
        {
            std::cout << info;
        }
        void setNext(Node<T>* element)
        {
            next = element;
        }
        virtual ~Node()
        {
            delete this;
        }
};