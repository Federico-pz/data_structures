/*
Sue Mi Zamarrón Orrantia A01781507
Federico Pérez Zorrilla A01029967
14-11-2021
Grafo: sus representaciones y sus recorridos 
*/

#include "Graph.hpp"
#include <queue>

/*
Función que genera un grafo en forma de multilista O(n^2) [Por el for booleano]
Param: El número de vértices, aristas, y un apuntador al grafo
*/
void loadGraph2(int v, int e, Graph<int, int> * graph)
{
    //Se agregan las listas de cada nodo
    for(int i = 1; i <= v; i++)
    {
        graph->addVertex(i);
    }

    
    for(int j = 0; j < e; j++)
    {
        int origen = rand() % v;
        int destino = rand() % v;
        std::vector< Edge<int, int> * >* auxEdges = graph->getNodes()[origen]->getEdges();
        bool test = false;

        //Verifica si la conexión ya existe
        for(auto x: *auxEdges)
        {
            if(x->getTarget() == graph->getNodes()[destino])
            {
                test = true;
            }
        }
        //Verifica que no se haga una conexión al mismo nodo también
        if(!test && origen != destino)
        {
            graph->addEdge(graph->getNodes()[origen], graph->getNodes()[destino], 0);
        }
        //Asegura la cantidad indicada de conexiones, sin repetidos ni ciclos
        else{j--;}

    }
}

/*
Función que genera un grafo en forma de matriz de adyacencia O(n+x) [Por que si hay conexiones inválidas aumenta n]
Param: El numero de columnas y filas (Es cuadrada), de conexiones y el grafo
*/
void loadGraph(int v, int e, std::vector < std::vector<int> > & graph)
{
    //Se crea la matriz y se llena de ceros
    for(int i = 0; i < v; i++)
    {
        graph[i] = std::vector<int> (v);
        std::fill(graph[i].begin(), graph[i].end(), 0);
    }
    for(int j = 0; j < e; j++)
    {
        int a = rand() % v;
        int b = rand() % v;
        //Se asegura de que no se repitan conexiones y que la diagonal sea de ceros
        if(graph[a][b] == 0 && a != b)
        {
            graph[a][b] = 2;
        }
        else {j--;}
    }
}

/*
Función recursiva que recorre el grafo desde un nodo, e imprime todas las conexiones que encuentra O(n)
Param: El grafo y el entero que representa al nodo donde se empezará
*/
void DFS(std::vector < std::vector<int> > & graph, int u)
{
    bool connected = false; //Variable para verificar si el nodo de inicio tiene alguna conexión
    graph[u][u] = 1;
    for(int i = 0; i < graph[0].size(); i++)
    {
        if(graph[u][i] == 2)
        {
            int w = i;
            std::cout << u << "--->" << w << std::endl;
            if(graph[w][w] == 0)
            {
                connected = true;
                DFS(graph, w);
            }
        }
    }
    if(!connected)
    {
        std::cout << "Nodo desconectado" << std::endl;
    }
}

/*
Función que recorre un grafo en forma de multilista, e imprime todas las conexiones. O(n^2)
Param: El apuntador al grafo y el entero que representa al nodo inicial
*/
void BFS(Graph<int, int> * graph, int u)
{
    std::queue<Vertex<int, int> *> Q;
    Vertex<int, int> * start = graph->getNodes()[u-1];
    Q.push(start);
    start->visit();
    //Checa si el nodo inicial está conectado.
    if(start->getEdges()->size() == 0)
    {
        std::cout << "Nodo desconectado" << std::endl;
    }

    while(!Q.empty())
    {
        Vertex<int, int> * temp = Q.front();
        Q.pop();
        for(auto i: *(temp->getEdges()))
        {
            Vertex<int, int> * target = i->getTarget();
            std::cout << temp->getInfo() << "--->" << target->getInfo() << std::endl;
            if(!target->isVisited())
            {
                target->visit();
                Q.push(target);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    
    /* Definir número de vértices y aristas */
    const int vertices = 10;
    const int aristas = 15;
    
    /* Declaración del grafo como matriz de adyacencia */
    std::vector < std::vector<int> > matriz_adyacencia(vertices);

    /* Generar el grafo como matriz de adyacencia */
    loadGraph(vertices, aristas, matriz_adyacencia);
    
    /* Recorrido con DFS */
    std::cout << "------ Matriz de adyacencia con DFS ------" << std::endl;
    int u = 1;
    DFS(matriz_adyacencia, u);
    
    /* Declaración del grafo como multilista */
    Graph<int, int> * multilista = new Graph<int, int>();

    /* Generar el grafo como multilista */
    loadGraph2(vertices, aristas, multilista);

    /* Recorrido con BFS */
    std::cout << "------ Multilista con BFS ------" << std::endl;
    u = 1;
    BFS(multilista, u);
    
    delete multilista;
    
    return 0;
}