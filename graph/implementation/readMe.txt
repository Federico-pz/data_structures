Es importante agregar las siguientes cosas para que funcione:
    El método:
        std::vector < Vertex<V, E> * > getNodes(){return this->nodes;}
    a "Graph.hpp"

    Los métodos:
        void visit(){this->visited = true;}
        bool isVisited(){return this->visited;}
    a "Vertex.hpp", y también el atributo:
        bool visited = false;

Igual están adjuntos los archivos .hpp al zip
    
El método DFS tiene el nodo 0, y el método BFS si empieza en el 1