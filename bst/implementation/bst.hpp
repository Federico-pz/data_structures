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
        void visit(int method);
        void preOrder(TreeNode<T>* node);
        void inOrder(TreeNode<T>* node);
        void postOrder(TreeNode<T>* node);
        void byLevel(TreeNode<T>* node);
        int height();
        void ancestors(T info);
        int whatLevelAmI(T info);
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
            if(temp->getInfo() == node->getInfo())
            {
                delete node;  //Borra el nodo si este ya se encuentra en el árbol
                return false;
            }

            //Recorre hacia la derecha o izquierda dependiendo del valor, para hacer el árbol binario
            else if(temp->getInfo() > node->getInfo())
            {
                temp = temp->getLeft(); 
            }
            else if(temp->getInfo() < node->getInfo())
            {
                temp = temp->getRight();
            }
        }
        //Se le asigna el padre al nodo, y el nodo como hijo al padre.
        node->setParent(parent); 
        if(parent->getInfo() > node->getInfo())
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
Función recursiva que recorre el árbol en preOrden e imprime los nodos O(n)
Param: El nodo donde se empieza a recorrer el arbol
*/
template <class T>
void Bst<T>::preOrder(TreeNode<T>* node)
{
    if (node != nullptr) {
        std::cout << node->getInfo() << " ";
        
        preOrder( node->getLeft() );
        
        preOrder( node->getRight());
    }
}

/*
Función recursiva que recorre el árbol en inOrden e imprime los nodos O(n)
Param: El nodo donde se empieza a recorrer el arbol
*/
template <class T>
void Bst<T>::inOrder(TreeNode<T>* node)
{
    if (node != nullptr) {
        inOrder( node->getLeft() );

        std::cout << node->getInfo() << " ";
            
        inOrder( node->getRight() );
    }
}

/*
Función recursiva que recorre el árbol en postOrden e imprime los nodos O(n)
Param: El nodo donde se empieza a recorrer el arbol
*/
template <class T>
void Bst<T>::postOrder(TreeNode<T>* node)
{
    if (node != nullptr) {
        postOrder( node->getLeft() );

        postOrder( node->getRight() );

        std::cout << node->getInfo() << " ";      
    }
}

/*
Función que recorre el árbol e imprime los nodos nivel por nivel O(n)
Param: El nodo donde se empieza a recorrer el arbol
*/
template <class T>
void Bst<T>::byLevel(TreeNode<T>* node)
{
    std::queue <TreeNode<T>*> tempQ; //Se usa una cola auxiliar para guardar e imprimir los nodos
    TreeNode<T>* tempN;

    int level = 1; //Se le asigna el nivel a cada nodo, también sirve para imprimir por nivel
    node->setLevel(level);
    tempQ.push(node);
    
    

    while (!tempQ.empty())
    {
        tempN = tempQ.front();
        tempQ.pop();

        TreeNode<T>* left = tempN->getLeft();
        TreeNode<T>* right = tempN->getRight();

        if(left != nullptr)
        {
            left->setLevel(tempN->getLevel() + 1);
            tempQ.push(left);
        }

        if(right != nullptr)
        {
            right->setLevel(tempN->getLevel() + 1);
            tempQ.push(right);
        }

        if (level != tempN->getLevel())
        {
            std::cout << std::endl;
            level += 1;
        }

        std::cout << tempN->getInfo() << " , ";
    }
}


/*
Función que llama a las funciones que recorren el árbol
Param: Un entero que indica el método a usar
*/
template <class T>
void Bst<T>::visit(int method)
{
    if(method == 1)
    {
        this->preOrder(this->root);
    }
    else if(method == 2)
    {
        this->inOrder(this->root);
    }
    else if(method == 3)
    {
        this->postOrder(this->root);
    }
    else if(method == 4)
    {
        this->byLevel(this->root);
    }
}

/*
Función que regresa la altura del árbol O(n)
Return: El entero que indica la altura
*/
template <class T>
int Bst<T>::height()
{
    if(this->root == nullptr){return 0;}
    else
    {
        std::queue <TreeNode<T>*> tempQ;
        TreeNode<T>* tempN = this->root;

        int level = 1;
        tempN->setLevel(level);
        tempQ.push(tempN);
    
        while (!tempQ.empty())
        {
            tempN = tempQ.front();
            tempQ.pop();    
            TreeNode<T>* left = tempN->getLeft();
            TreeNode<T>* right = tempN->getRight();

            if(left != nullptr)
            {
                left->setLevel(tempN->getLevel() + 1);
                tempQ.push(left);
            }

            if(right != nullptr)
            {
                right->setLevel(tempN->getLevel() + 1);
                tempQ.push(right);
            }

            if (level != tempN->getLevel())
            {
                level += 1; //La única diferencia con el recorrido nivel por nivel es que no se asignan los niveles, solo se acumula el nivel para regresarlo
            }
        }
        return level;
    }
}

/*
Función que recorre el árbol, y cuando encuentra el nodo que buscamos, imprime padre por padre O(log n)
Param: La información del nodo a encontrar
*/
template <class T>
void Bst<T>::ancestors(T info)
{
    TreeNode<T>* aux = this->root;
    while(aux->getInfo() != info)
    {
        //Recorrido del árbol de forma binaria
        if(aux->getInfo() > info)
        {
            aux = aux->getLeft();
        }
        else
        {

            aux = aux->getRight();
        }
    }

    //Recorrido de la línea de ancestros
    TreeNode<T>* auxP = aux->getParent();
    while(auxP != nullptr)
    {
        std::cout << auxP->getInfo() << std::endl;
        auxP = auxP->getParent();
    }
}

/*
Función que indica en qué nivel se encuentra un nodo O(log n)
Param: La información del nodo a encontrar
Return: Un entero con el nivel del nodo
*/
template <class T>
int Bst<T>::whatLevelAmI(T info)
{
    //Recorre el árbol, y en cada instancia acumula la variable del nivel para regresarlo
    TreeNode<T>* aux = this->root;
    int level = 1;
    while(aux->getInfo() != info)
    {
        if(aux->getInfo() > info)
        {
            aux = aux->getLeft();
            level ++;
        }
        else
        {
            aux = aux->getRight();
            level++;
        }
    }
    return level;
}