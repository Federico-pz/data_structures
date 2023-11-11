/*
Sue Mi Zamarrón Orrantia A01781507
Federico Pérez Zorrilla A01029967
22-10-2021
Operaciones avanzadas en un BST
*/


#include "bst.hpp"

int main()
{
    Bst<int>* tree = new Bst<int>();

    TreeNode<int>* a = new TreeNode<int> (10);
    TreeNode<int>* b = new TreeNode<int> (8);
    TreeNode<int>* c = new TreeNode<int> (12);
    TreeNode<int>* d = new TreeNode<int> (6);
    TreeNode<int>* e = new TreeNode<int> (11);
    TreeNode<int>* f = new TreeNode<int> (2);

    tree->insert(a);
    tree->insert(b);
    tree->insert(c);
    tree->insert(d);
    tree->insert(e);
    tree->insert(f);

    std::cout << "Impresion en pre-orden:" << std::endl;
    tree->visit(1);
    std::cout << std::endl;
    std::cout << "Impresion en in-orden:" << std::endl;
    tree->visit(2);
    std::cout << std::endl;
    std::cout << "Impresion en post-orden:" << std::endl;
    tree->visit(3);
    std::cout << std::endl;
    std::cout << "Impresion nivel por nivel:" << std::endl;
    tree->visit(4);
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "La altura del arbol es: " << tree->height() << std::endl;

    std::cout << "Los ancestros del nodo 2 son: " << std::endl;
    tree->ancestors(2);

    std::cout << "El nodo 6 esta en el nivel: " << tree->whatLevelAmI(6);

    delete a;
    delete b;
    delete c;
    delete d;
    delete e;
    delete f;
    
    delete tree;

};