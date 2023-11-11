#include <iostream>
#include <string>

template <class T>
class TreeNode
{
    protected:
        std::string dominio;
        int frecuencia; 
        TreeNode<T>* left = nullptr;
        TreeNode<T>* right = nullptr;
        TreeNode<T>* parent = nullptr;
        int level = 0;

    public:
        TreeNode(){}
        TreeNode(std::string dominio, int frecuencia):dominio(dominio), frecuencia(frecuencia){}

        void setLeft(TreeNode<T>* left){this->left = left;}
        void setRight(TreeNode<T>* right){this->right = right;}
        void setParent(TreeNode<T>* parent){this->parent = parent;}
        void setLevel(int level) {this->level = level;}

        TreeNode<T>* getLeft(){return this->left;}
        TreeNode<T>* getRight(){return this->right;}    
        TreeNode<T>* getParent(){return this->parent;}
        std::string getDominio(){return this->dominio;}
        int getFrecuencia(){return this->frecuencia;}
        int getLevel(){return this->level;}
};