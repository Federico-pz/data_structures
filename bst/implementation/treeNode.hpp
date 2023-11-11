#include <iostream>

template <class T>
class TreeNode
{
    protected:
        T info; 
        TreeNode<T>* left = nullptr;
        TreeNode<T>* right = nullptr;
        TreeNode<T>* parent = nullptr;
        int level = 0;

    public:
        TreeNode(){}
        TreeNode(T info):info(info){}

        void setLeft(TreeNode<T>* left){this->left = left;}
        void setRight(TreeNode<T>* right){this->right = right;}
        void setParent(TreeNode<T>* parent){this->parent = parent;}
        void setLevel(int level) {this->level = level;}

        TreeNode<T>* getLeft(){return this->left;}
        TreeNode<T>* getRight(){return this->right;}
        TreeNode<T>* getParent(){return this->parent;}
        T getInfo(){return this->info;}
        int getLevel(){return this->level;}
};