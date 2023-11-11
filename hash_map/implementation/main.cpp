/*
Sue Mi Zamarrón Orrantia A01781507
Federico Pérez Zorrilla A01029967
24-11-2021
Act 5.1 - Implementación individual de operaciones sobre conjuntos 
*/

#include <iostream>
#include "hashMap.hpp"
#include "hashChain.hpp"

int main(int argc, const char * argv[]) {
    
    int capacity = 5;

    std::cout << "Ejemplo de Hash Map:" << std::endl << "-----------------------------" << std::endl;
    /* Crear un HashChain */
    HashMap<int, int> * tabla = new HashMap<int, int>(capacity);
    
    /* Insertar elementos */
    std::cout << tabla->put(1, 1) << std::endl;
    std::cout << tabla->put(5, 5) << std::endl;
    std::cout << tabla->put(11, 11) << std::endl;
    std::cout << tabla->put(15, 15) << std::endl;
    std::cout << tabla->put(2, 2) << std::endl;
    std::cout << tabla->put(8, 8) << std::endl;
    
    std::cout << tabla->get(5) << std::endl;
    std::cout << tabla->get(15) << std::endl;
    std::cout << tabla->get(8) << std::endl;
    
    std::cout << *tabla;
    
    std::cout << std::endl << "Ejemplo de Hash Chain:" << std::endl << "-----------------------------" << std::endl;
    
    /* Crear un HashChain */
    HashChain<int, int> * tabla2 = new HashChain<int, int>(capacity);
    
    /* Insertar elementos */
    std::cout << tabla2->put(1, 1) << std::endl;
    std::cout << tabla2->put(5, 5) << std::endl;
    std::cout << tabla2->put(11, 11) << std::endl;
    std::cout << tabla2->put(15, 15) << std::endl;
    std::cout << tabla2->put(2, 2) << std::endl;
    std::cout << tabla2->put(8, 8) << std::endl;
    
    std::cout << tabla2->get(5) << std::endl;
    std::cout << tabla2->get(15) << std::endl;
    std::cout << tabla2->get(8) << std::endl;
    
    std::cout << *tabla2;
    
    /* Eliminar la tabla */
    delete tabla;
    delete tabla2;
    
    return 0;
}