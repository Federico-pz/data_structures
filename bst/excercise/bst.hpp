#include "treeNode.hpp"
#include <queue>


template <class T>
class Bst
{
    protected:
        TreeNode<T>* root = nullptr;
    public:
        Bst<T>(){}
        bool insert(TreeNode<T>* node);
        void setRoot(TreeNode<T>* node){this->root = node;}
        TreeNode<T>* getRoot(){return this->root;}        
        int topN_diario(TreeNode<T>* nodo, int n, int cont, std::map<std::string, int>* mapa);
        int topN_Consecutivo(TreeNode<T>* nodo, int n, int cont, std::map<std::string, int>* mapa2);
        int topN_anormal(TreeNode<T>* nodo, int n, int cont, std::map<std::string, int>* mapa);
        void postOrderDelete(TreeNode<T>* node);
        virtual ~Bst()
        {
            this->postOrderDelete(this->root);
            delete this;
        }
        /*
        //Métodos no utilizados
        void visit(int method);
        void preOrder(TreeNode<T>* node);
        void inOrder(TreeNode<T>* node);
        
        void byLevel(TreeNode<T>* node);
        int height();
        void ancestors(T info);
        int whatLevelAmI(T info);
        */

};

/*
Función que agrega un valor al árbol de forma binaria O(log n)
Param: Un apuntador al nodo a agregar
Return: Un valor booleano
*/
template <class T>
bool Bst<T>::insert(TreeNode<T>* node)
{
    TreeNode<T>* temp = this->root; // Va recorriendo el árbol para encontrar donde hay que insertar el nodo
    TreeNode<T>* parent = nullptr; // Igual recorre, pero guarda el padre del nodo a agregar

    if(temp == nullptr)
    {
        this->setRoot(node); //Inserta a raíz si el árbol está vacío
        return true;
    }

    else
    {
        while (temp != nullptr) {
            parent = temp;
            if(temp->getDominio() == node->getDominio())
            {
                delete node;  //Borra el nodo si este ya se encuentra en el árbol
                return false;
            }

            //Recorre hacia la derecha o izquierda dependiendo del valor, para hacer el árbol binario
            else if(temp->getFrecuencia() > node->getFrecuencia())
            {
                temp = temp->getLeft(); 
            }
            else if(temp->getFrecuencia() <= node->getFrecuencia())
            {
                temp = temp->getRight();
            }
        }
        //Se le asigna el padre al nodo, y el nodo como hijo al padre.
        node->setParent(parent); 
        if(parent->getFrecuencia() > node->getFrecuencia())
        {
            parent->setLeft(node);
        }
        else
        {
            parent->setRight(node);
        }
        return true;
    }
}

/*
Función recursiva que imprime el top n elementos en orden ascendente del BST, y agrega los dominios del top n a un mapa O(log n)
Param: El apuntador al nodo donde se empieza la búsqueda, el entero del top n, un contador entero, el apuntador al mapa
Return: El contador entero
*/
template<class T>
int Bst<T>::topN_diario(TreeNode<T>* nodo, int n, int cont, std::map<std::string, int>* mapa)
{
    if (nodo != nullptr && cont < n) 
    {
        //Busqueda in-orden
        cont = topN_diario( nodo->getRight(), n, cont, mapa);
        if (cont < n ) {
            std::cout << ++cont << ". " << nodo->getDominio() << ": " << nodo->getFrecuencia() << std::endl; //Se imprimen los top n
            (*mapa)[nodo->getDominio()]++; // Se agregan los top n, o si ya están, se suma 1 a su valor
        }
        else return cont;

        cont = topN_diario( nodo->getLeft(), n, cont, mapa);
        
    }
    return cont;
}

/*
Función recursiva que agrega los dominios de los top n elementos del Bst a un mapa O(log n)
Param: El apuntador al nodo donde se empieza la búsqueda, el entero del top n, un contador entero, el apuntador al mapa
Return: El contador entero
*/
template<class T>
int Bst<T>::topN_Consecutivo(TreeNode<T>* nodo, int n, int cont, std::map<std::string, int>* mapa2)
{
    if (nodo != nullptr && cont < n) 
    {
        //Recorrido in-orden
        cont = topN_Consecutivo( nodo->getRight(), n, cont, mapa2);
        if (cont < n ) {
            cont ++; //Se actualiza el contador
            (*mapa2)[nodo->getDominio()]++; //Se agregan las hojas al mapa, o en su defecto se suma 1 a su valor
        }
        else return cont;

        cont = topN_Consecutivo( nodo->getLeft(), n, cont, mapa2);
        
    }
    return cont;
}


/*
Función recursiva que agrega el dominio y la frecuencia del top n elementos del Bst a un mapa O(log n)
Param: El apuntador al nodo donde se empieza la búsqueda, el entero del top n, un contador entero, el apuntador al mapa
Return: El contador entero
*/
template<class T>
int Bst<T>::topN_anormal(TreeNode<T>* nodo, int n, int cont, std::map<std::string, int>* mapa)
{
    if (nodo != nullptr && cont < n) 
    {
        //Recorrido in-orden
        cont = topN_anormal( nodo->getRight(), n, cont, mapa);
        if (cont < n ) {
            mapa->insert(std::make_pair(nodo->getDominio(), nodo->getFrecuencia())); //Se insertan las hojas al mapa con make_pair
            cont++;
        }
        else return cont;

        cont = topN_anormal( nodo->getLeft(), n, cont, mapa);
        
    }
    return cont;
}

/*
Función recursiva que recorre el árbol en postOrden y borra los nodos O(n)
Param: El nodo donde se empieza a recorrer el arbol
*/
template <class T>
void Bst<T>::postOrderDelete(TreeNode<T>* node)
{
    if (node != nullptr) {
        postOrderDelete( node->getLeft() );

        postOrderDelete( node->getRight() );

        delete node;      
    }
}

// /*
// Función recursiva que recorre el árbol en preOrden e imprime los nodos O(n)
// Param: El nodo donde se empieza a recorrer el arbol
// */
// template <class T>
// void Bst<T>::preOrder(TreeNode<T>* node)
// {
//     if (node != nullptr) {
//         std::cout << node->getInfo() << " ";
        
//         preOrder( node->getLeft() );
        
//         preOrder( node->getRight());
//     }
// }

// /*
// Función recursiva que recorre el árbol en inOrden e imprime los nodos O(n)
// Param: El nodo donde se empieza a recorrer el arbol
// */
// template <class T>
// void Bst<T>::inOrder(TreeNode<T>* node)
// {
//     if (node != nullptr) {
//         inOrder( node->getLeft() );

//         std::cout << node->getInfo() << " ";
            
//         inOrder( node->getRight() );
//     }
// }


// /*
// Función que recorre el árbol e imprime los nodos nivel por nivel O(n)
// Param: El nodo donde se empieza a recorrer el arbol
// */
// template <class T>
// void Bst<T>::byLevel(TreeNode<T>* node)
// {
//     std::queue <TreeNode<T>*> tempQ; //Se usa una cola auxiliar para guardar e imprimir los nodos
//     TreeNode<T>* tempN;

//     int level = 1; //Se le asigna el nivel a cada nodo, también sirve para imprimir por nivel
//     node->setLevel(level);
//     tempQ.push(node);
    
    

//     while (!tempQ.empty())
//     {
//         tempN = tempQ.front();
//         tempQ.pop();

//         TreeNode<T>* left = tempN->getLeft();
//         TreeNode<T>* right = tempN->getRight();

//         if(left != nullptr)
//         {
//             left->setLevel(tempN->getLevel() + 1);
//             tempQ.push(left);
//         }

//         if(right != nullptr)
//         {
//             right->setLevel(tempN->getLevel() + 1);
//             tempQ.push(right);
//         }

//         if (level != tempN->getLevel())
//         {
//             std::cout << std::endl;
//             level += 1;
//         }

//         std::cout << tempN->getInfo() << " , ";
//     }
// }


// /*
// Función que llama a las funciones que recorren el árbol
// Param: Un entero que indica el método a usar
// */
// template <class T>
// void Bst<T>::visit(int method)
// {
//     if(method == 1)
//     {
//         this->preOrder(this->root);
//     }
//     else if(method == 2)
//     {
//         this->inOrder(this->root);
//     }
//     else if(method == 3)
//     {
//         this->postOrder(this->root);
//     }
//     else if(method == 4)
//     {
//         this->byLevel(this->root);
//     }
// }

// /*
// Función que regresa la altura del árbol O(n)
// Return: El entero que indica la altura
// */
// template <class T>
// int Bst<T>::height()
// {
//     if(this->root == nullptr){return 0;}
//     else
//     {
//         std::queue <TreeNode<T>*> tempQ;
//         TreeNode<T>* tempN = this->root;

//         int level = 1;
//         tempN->setLevel(level);
//         tempQ.push(tempN);
    
//         while (!tempQ.empty())
//         {
//             tempN = tempQ.front();
//             tempQ.pop();    
//             TreeNode<T>* left = tempN->getLeft();
//             TreeNode<T>* right = tempN->getRight();

//             if(left != nullptr)
//             {
//                 left->setLevel(tempN->getLevel() + 1);
//                 tempQ.push(left);
//             }

//             if(right != nullptr)
//             {
//                 right->setLevel(tempN->getLevel() + 1);
//                 tempQ.push(right);
//             }

//             if (level != tempN->getLevel())
//             {
//                 level += 1; //La única diferencia con el recorrido nivel por nivel es que no se asignan los niveles, solo se acumula el nivel para regresarlo
//             }
//         }
//         return level;
//     }
// }

// /*
// Función que recorre el árbol, y cuando encuentra el nodo que buscamos, imprime padre por padre O(log n)
// Param: La información del nodo a encontrar
// */
// template <class T>
// void Bst<T>::ancestors(T info)
// {
//     TreeNode<T>* aux = this->root;
//     while(aux->getInfo() != info)
//     {
//         //Recorrido del árbol de forma binaria
//         if(aux->getInfo() > info)
//         {
//             aux = aux->getLeft();
//         }
//         else
//         {

//             aux = aux->getRight();
//         }
//     }

//     //Recorrido de la línea de ancestros
//     TreeNode<T>* auxP = aux->getParent();
//     while(auxP != nullptr)
//     {
//         std::cout << auxP->getInfo() << std::endl;
//         auxP = auxP->getParent();
//     }
// }

// /*
// Función que indica en qué nivel se encuentra un nodo O(log n)
// Param: La información del nodo a encontrar
// Return: Un entero con el nivel del nodo
// */
// template <class T>
// int Bst<T>::whatLevelAmI(T info)
// {
//     //Recorre el árbol, y en cada instancia acumula la variable del nivel para regresarlo
//     TreeNode<T>* aux = this->root;
//     int level = 1;
//     while(aux->getInfo() != info)
//     {
//         if(aux->getInfo() > info)
//         {
//             aux = aux->getLeft();
//             level ++;
//         }
//         else
//         {
//             aux = aux->getRight();
//             level++;
//         }
//     }
//     return level;
// }
