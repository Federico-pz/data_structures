#include <iostream>
#include <vector>
#include <algorithm>
#include "Vertex.hpp"


#pragma once
template <class V, class E>
class Graph {
    
    std::vector < Vertex<V, E> * > nodes;
    
public:
    
    Graph() {}
    ~Graph();
    
    void addVertex(V & );
    void addVertex(Vertex<V,E> * );
    void addEdge(Vertex<V,E> *, Vertex<V,E> *, const E & );
    void removeEdge(Vertex<V,E> *, Vertex<V,E> *, const E & );
    std::vector < Vertex<V, E> * > getNodes(){return this->nodes;}

    int posInNodos(V value);
    bool edgeExist( Vertex<V, E> * origin,  Vertex<V, E> * target);

    void mostConnections(V value);
    int connectionsTo(V ip);

    template <class Vn, class En>
    friend std::ostream & operator <<(std::ostream &, const Graph<Vn,En> &);
};

template <class V, class E>
Graph<V,E>::~Graph()
{
    for (auto v: nodes) {
        delete v;
    }
    
    nodes.clear();
}

template <class V, class E>
void Graph<V,E>::addVertex(V & value )
{
    auto vertex = new Vertex<V, E>(value);
    
    nodes.push_back(vertex);
}

template <class V, class E>
void Graph<V,E>::addVertex(Vertex<V,E> * vertex )
{
    nodes.push_back(vertex);
}

template <class V, class E>
void Graph<V,E>::addEdge(Vertex<V,E> * source, Vertex<V,E> * target, const E & value)
{
    /* Buscar vertex origen */
    auto node = find(nodes.begin(), nodes.end(), source);
    
    /* Crear un edge y adicionarlo al vertex */
    Edge<V, E> * edge = new Edge<V,E>(value, target);
    
    (*node)->addEdge(edge);
}

template <class V, class E>
void Graph<V,E>::removeEdge(Vertex<V,E> * source, Vertex<V,E> * target, const E & value )
{
    /* Buscar vertex origen */
    auto node = find(nodes.begin(), nodes.end(), source);
    
    Vertex<V,E> * vertex = (*node);
    
    auto * edges = vertex->getEdges();
    
    Edge<V,E> * to_remove = nullptr;
    
    for (auto e : *edges) {
        if (e->getInfo() == value && e->getTarget() == target) {
            to_remove = e;
            break;
        }
    }
    
    if (to_remove) {
        vertex->removeEdge(to_remove);
    }
    
}

/*
Método que obtiene la posición de un nodo en el vector de nodos O(n)
Param: El valor que representa al nodo a buscar
Return: Un entero con la posición del nodo
*/
template<class V, class E>
int Graph<V,E>::posInNodos(V value)
{
    int count = -1;
    for(auto i : this->nodes)
    {
        count++;
        if(i->getInfo() == value)
        {
            return count;
        }
    }
    return -1;
}

/*
Método que te dice si existe una conexión dentro de un nodo O(n)
Params: Apuntadores a los vértices que se van a conectar
Return: Un valor booleano que te dice si la conexión existe
*/
template<class V, class E>
bool Graph<V,E>::edgeExist( Vertex<V, E> * origin,  Vertex<V, E> * target)
{
    auto node = find(this->nodes.begin(), this->nodes.end(), origin);
    std::vector< Edge<V, E> * > edges = *(*node)->getEdges();
    for(auto e: edges)
    {
        // Recorre el vértice origen buscando que tenga una conexión al vértice destino
        if(e->getTarget() == target){return true;}
    }
    
    return false;
}

/*
Método que te dice que vértice tiene más conexiones en el grafo, y si cierto vértice es ese. O(n)
Param: El valor que representa el vértice que quieres comprobar
*/
template<class V, class E>
void Graph<V,E>::mostConnections(V value)
{
    // Simplemente va actualizando la información del vertice "ganador"
    std::string maxConnections = "";
    int numConnections = 0;

    for(auto i: this->nodes)
    {
        if(i->getEdges()->size() > numConnections)
        {
            maxConnections = i->getInfo();
            numConnections = i->getEdges()->size();
        }
    }
    if(maxConnections == value)
    {
        std::cout << value << "es la ip con mas conexiones" << " con " << numConnections << " conexiones." << std::endl;
    }
    else{

        std::cout << value << " no es la ip con mas conexiones." << std::endl;
        std::cout << "La ip con mas conexiones es " << maxConnections << " con " << numConnections << " conexiones." << std::endl;
    }
}

/*
Método que regresa el número de conexiones que llegaron a un vértice O(n^2)
Params: Un valor que representa el vértice a estudiar
Return: Un entero con la cantidad de conexiones.
*/
template<class V, class E>
int Graph<V,E>::connectionsTo(V value)
{
    int counter = 0;
    for(auto i: this->nodes)
    {
        std::vector< Edge<std::string, int> * > edges = *i->getEdges();
        for(auto j: edges)
        {
            if(j->getTarget()->getInfo() == value)
            {
                counter++;
            }
        }
    }
    return counter;
}

template <class V, class E>
std::ostream & operator <<(std::ostream & os, const Graph<V,E> & graph)
{
    os << "--- Graph ---" << std::endl;
    
    for (auto v :  graph.nodes) {
        os << *v;
    }
    
    return os;
}