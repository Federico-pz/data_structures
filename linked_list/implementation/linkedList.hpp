#include "node.hpp"

#pragma once
template <class T>
class LinkedList
{
    protected:
        Node<T>* firstElement = nullptr;
    public:
        LinkedList(){}
        LinkedList(Node<T>* first): firstElement(first){}
        Node<T>* get(int index);
        void remove(int index);
        void add(Node<T>* element);
        int size();
        
// ---------------------------Actividad 2.1------------------------------------
        LinkedList<T> * subList(int from, int to);
        void deleteRange(int from, int to);
        LinkedList<T>* unionList(LinkedList<T> * B);
        LinkedList<T> * intersection(LinkedList<T> * B);
        LinkedList<T> * except(LinkedList<T> * B);

        // El destructor de la lista va de atras para adelante borrando cada nodo
        virtual ~LinkedList()
        { 
            for(int i = this->size() - 1; i > 0; i--){
                delete this->get(i);
            }
            delete this;
        }


};

/*
Funcion que regresa el tamaño de una lista. O(n)
Return: Un contador con el tamaño
*/
template <class T>
int LinkedList<T>::size()
{
    if(firstElement == nullptr){return 0;} //Checa si hay nodos en la lista
    else{
        Node<T>* currentElement = firstElement;
        int count = 1;
        while(currentElement->getNext() != 0){
            count += 1;
            currentElement = currentElement->getNext(); //Va recorriendo la lista hasta el final, contando cada nodo.
        }
        return count;
    }
}

/*
Funcion que obtiene el nodo que está en la posición n de una lista. O(n)
Param: Un entero, la posición a buscar
Return: Un apuntador a un nodo
*/
template <class T>
Node<T>* LinkedList<T>::get(int index)
{
    Node<T>* currentElement = firstElement; //Una variable que guarda el apuntador actual en el recorrido
    int n = 0;
    while(n < index){
        currentElement = currentElement->getNext(); //Se actualiza la variable con el apuntador en la siguiente posición
        n += 1;
    }   
    return currentElement;
}

/*
Función que elimina el nodo en una posición de la lista O(n)
Param: Un entero, la posición a eliminar
*/
template <class T>
void LinkedList<T>::remove(int index)
{
    Node<T>* currentElement = firstElement;
    int n = 0;
    while(n < index - 1){
        currentElement = currentElement->getNext(); //Recorre la lista hasta encontrar el nodo de antes del que se va a eliminar
        n += 1;
    }
    Node<T>* x = currentElement->getNext()->getNext(); //Se guarda el nodo siguiente del que se elimina en una variable auxiliar
    currentElement->getNext()->setNext(nullptr); //Se elimina el next del nodo a eliminar
    currentElement->setNext(x); //Se pone el nuevo next al nodo previo

}

/*
Función que agrega un nodo a la lista. O(n)
Param: El apuntador al nodo que se quiere agregar
*/
template <class T>
void LinkedList<T>::add(Node<T>* element)
{
    if(firstElement == nullptr){
        firstElement = element; //Si no hay más nodos, se agrega al inicio
    }
    else{
        Node<T>* currentElement = firstElement;
        while(currentElement->getNext() != nullptr){
            currentElement = currentElement->getNext(); //Se recorre la lista hasta llegar al último nodo
        }
        currentElement->setNext(element); //Se agrega el nuevo nodo
    }
}

/*
Función que regresa una lista nueva con los elementos que se encuentren entre la posición from y to de una lista. O(n)
Param: El inicio y el fin del rango a copiar
Return: El apuntador a la nueva lista
*/
template <class T>
LinkedList<T>* LinkedList<T>::subList(int from, int to)
{
    LinkedList<T>* newList = new LinkedList<T>();
    int i = from;
    while(i <= to)
    {
        newList->add(new Node<T>(this->get(i)->info)); //Se crea una copia del Nodo original, y se agrega a la lista
        i++;
    }
    return newList;
}

/*
Funcion que elimina los elementos que se encuentren entre la posición from y to de una lista. O(n)
Param: El inicio y el fin del rango a copiar.
*/
template <class T>
void LinkedList<T>::deleteRange(int from, int to)
{  
    int i = 0;
    while(i < (to + 1) - from)
    {
        this->remove(from);
        i++;
    }
    
}

/*
Función que regresa la unión de dos listas en una lista nueva. O(n)
Param: El apuntador a la lista para unir
Return: El apuntador a la nueva lista
*/
template<class T>
LinkedList<T>* LinkedList<T>::unionList(LinkedList<T> * B)
{
    LinkedList<T>* newList = new LinkedList<T>();
    for(int i = 0; i < this->size(); i++)
    {
        newList->add(new Node<T>(this->get(i)->info)); // Agrega los nodos de la lista A a la nueva lista
    }
    for(int i = 0; i < B->size(); i++)
    {
        newList->add(new Node<T>(B->get(i)->info)); // Agrega los nodos de la lista B a la nueva lista
    }
    return newList;
}

/*
Función que regresa la intersección entre dos listas. O(n^2)
Param: El apuntador a la lista para hacer la intersección
Return: El apuntador a la nueva lista
*/
template<class T>
LinkedList<T>* LinkedList<T>::intersection(LinkedList<T> * B)
{
    LinkedList<T>* newList = new LinkedList<T>();
    for(int i = 0; i < B->size(); i++) //Se recorre una de las listas
    {
        for(int j = 0; j < this->size(); j++) //Por cada elemento de la otra lista, se recorre esta lista
        {
            if(B->get(i)->info == this->get(j)->info) //Se compara si los nodos de las listas son iguales
            {
                newList->add(new Node<T>(B->get(i)->info)); // Si son iguales, se agrega a la nueva lista
            }
        }
    }

    return newList;
}

/*
Función que regresa una lista con los elementos que la lista A tiene que la B no O(n)
Param: El apuntador de la lista a comparar
Return: El apuntador a la nueva lista
*/
template<class T>
LinkedList<T>* LinkedList<T>::except(LinkedList<T> * B)
{
    LinkedList<T>* newList = new LinkedList<T>();
    int x;
    for(int i = 0; i < this->size(); i++)
    {
        x = 0;
        for(int j = 0; j < B->size(); j++)
        {
            if(this->get(i)->info != B->get(j)->info) //Si el elemento de la lista A no es igual a un elemento de la lista B se cuenta
            {
                x++;
            }
        }
        if(x == B->size()) //Si el elemento de la lista A no es igual a ninguno de B, se agrega a la lista
        {  
            newList->add(new Node<T>(this->get(i)->info));
        }
    }

    return newList;
}
