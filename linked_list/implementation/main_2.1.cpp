/*
Sue Mi Zamarrón Orrantia A01781507
Federico Pérez Zorrilla A01029967
01-10-2021
Nuevas funciones para una Linked List
*/


#include "linkedList.hpp"


main()
{  

    Node<int>* a = new Node<int>(1);
    Node<int>* b = new Node<int>(2);
    Node<int>* c = new Node<int>(3);
    Node<int>* d = new Node<int>(4);
    Node<int>* e = new Node<int>(5);

    Node<int>* f = new Node<int>(5);
    Node<int>* g = new Node<int>(4);
    Node<int>* h = new Node<int>(1);

    LinkedList<int>* test = new LinkedList<int>();
    LinkedList<int>* testB = new LinkedList<int>();
    
    test->add(a);
    test->add(b);
    test->add(c);
    test->add(d);
    test->add(e);

    testB->add(f);
    testB->add(g);
    testB->add(h);



    std::cout << "List A:" << std::endl;
    for(int i = 0; i < test->size(); i++)
    {
        test->get(i)->print();
        std::cout << ",";
    }
    std::cout << std::endl;
    std::cout << "---------------" << std::endl;

    std::cout << "List B:" << std::endl;
    for(int i = 0; i < testB->size(); i++)
    {
        testB->get(i)->print();
        std::cout << ",";
    }
    std::cout << std::endl;
    std::cout << "---------------" << std::endl;

    int opt = 0;
    while(opt != 6){
        std::cout << "Choose an option" << std::endl;
        std::cout << "1. SubList" << std::endl;
        std::cout << "2. DeleteRange" << std::endl;
        std::cout << "3. Union" << std::endl;
        std::cout << "4. Intersection" << std::endl;
        std::cout << "5. Exception" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "> ";
        std::cin >> opt;

        switch (opt)
        {
            case 1:
            {
                //Pregunta 1
                int from;
                int to;
                std::cout << "Size of list (" << test->size() << ")" << std::endl;
                std::cout <<"From: ";
                std::cin >> from;
                std::cout <<"To: ";
                std::cin >> to;               

                LinkedList<int>* testA = test->subList(from,to);
                std::cout << "Size of sublist: " << testA->size() << std::endl;
                //Ésta función se usa en todos los casos, e imprime una lista
                for(int i = 0; i < testA->size(); i++){
                    testA->get(i)->print();
                    std::cout << std::endl;
                }
                std::cout << "---------------" << std::endl;
                break;
            }

            case 2:
            {
                // Pregunta 2
                int from;
                int to;
                std::cout << "Size of list (" << test->size() << ")" << std::endl;;
                std::cout <<"From: ";
                std::cin >> from;
                std::cout <<"To: ";
                std::cin >> to;     

                test->deleteRange(from,to);
                std::cout << "New size of the list: " << test->size() << std::endl;
                for(int i = 0; i < test->size(); i++)
                {
                    test->get(i)->print(); 
                    std::cout << std::endl;
                }
                std::cout << "---------------" << std::endl;
                break;
            }

            case 3:
            {
                // Pregunta 3 
                LinkedList<int>* testC = test->unionList(testB);
                
                std::cout << "Size of the new list: " << testC->size() << std::endl;
                for(int i = 0; i < testC->size(); i++)
                {
                    testC->get(i)->print(); 
                    std::cout << std::endl;
                }
                std::cout << "---------------" << std::endl;
                break;
            }

            case 4:
            {
                // Pregunta 4 
                LinkedList<int>* testD = test->intersection(testB);

                std::cout << "Size of the intersection: " << testD->size() << std::endl;
                for(int i = 0; i < testD->size(); i++)
                {
                    testD->get(i)->print(); 
                    std::cout << std::endl;
                }
                std::cout << "---------------" << std::endl;
                break;
            }

            case 5:
            {
                // Pregunta 5
                LinkedList<int>* testE = test->except(testB);

                std::cout << "Size of the exception list: "<< testE->size() << std::endl;
                for(int i = 0; i < testE->size(); i++)
                {
                    testE->get(i)->print(); 
                    std::cout << std::endl;
                }
                std::cout << "---------------" << std::endl;
                break;
            }

            case 6:
            {
                break;
            }
        }

    }
    
    delete a;
    delete b;
    delete c;
    delete d;
    delete e;
    delete testB;
    delete test;

}