/*
Sue Mi Zamarrón Orrantia A01781507
Federico Pérez Zorrilla A01029967
12-09-2021
Programa para administrar una agencia de autos
*/

#include<iostream>
#include "ventas.hpp"
#include "camioneta.hpp"
#include "moto.hpp"
#include<vector>

/*
Buscar vehículos de cierto año y con mas de cierto kilometraje
Parametros: Un apuntador a un vector, el año y kilometraje a comparar
Retorno: Imprime datos
*/
template<class T>
void busquedaEspecifica(std::vector<T>* vector, int year, int km)
{
    for(int i = 0; i < vector->size(); i++)
    {
        if((*vector)[i].getModelo() == year && (*vector)[i].getKm() >= km){   //Se comparan tanto el año y el kilometraje
            (*vector)[i].print(); //Se imprimen los datos de la venta
            std::cout << "-------------------------------------" << std::endl;
        }
    }
}

/*
Busca las compras de una persona
Parametros: Un apuntador a un vector, la persona
Return: Imprime datos
*/
template <class T>
void busquedaPersona(std::vector<T>* vector, std::string valor)
{
    for(int i = 0; i < vector->size(); i++)
    {
        if((*vector)[i].getComprador()->getNombre() == valor){    //Se comparan las dos cadenas de string con el nombre
            (*vector)[i].print();       //Se imprimen los datos de la venta
            std::cout << "-------------------------------------" << std::endl;
            std::cout << "-------------------------------------" << std::endl;
        }
    }
}

/*
Método de ordenamiento quicksorting de forma descendente
Parámetros: Un vector, el lugar de inicio y de fin del ordenamiento
Return: El vector ordenado
*/
template <class T>
std::vector<T> quicksort(std::vector<T> vector, int primero, int ultimo)
{
    int izquierdo = primero;
    int derecho = ultimo;
    T temp;
    
    //Se selecciona pivote
    T pivote = vector[primero];
    
    if ( primero < ultimo) // Paso base
    {
        // particion
        while ( izquierdo < derecho)
        {
            while ( (izquierdo < derecho) && (vector[izquierdo] >= pivote)) izquierdo++; // >=   Se sobrecargaron los operadores en la clase Venta
            while (vector[derecho] < pivote) derecho--;                                  // <    Estos signos hacen el orden descendente
            
            if ( izquierdo < derecho) // se intercambian los contenidos
            {
                temp = vector[derecho];
                vector[derecho] = vector[izquierdo];
                vector[izquierdo] = temp;
            }
        }
        
        // Se intercambia el pivote con el elemento de la posición derecha
        temp = vector[derecho];
        vector[derecho] = vector[primero];
        vector[primero] = temp;
        
        // Paso recursivo
        vector = quicksort ( vector, primero, derecho-1);
        vector = quicksort ( vector, izquierdo, ultimo);
    }
    
    return vector;
}

/*
Crear una nueva venta
Parámetros: Apuntadores con los objetos de Vehiculo y Comprador para la venta
Return: Un objeto de la clase Venta 
*/
Venta nuevaVenta(Vehiculo* vehiculo, Comprador* comprador)
{
    float monto;        
    std::cout << "Monto de la venta:" << std::endl;
    std::cout << "> ";
    std::cin >> monto;      //Se pide el monto de la venta al usuario

    return Venta(monto, vehiculo, comprador);
};

/*
Imprime los elementos de un vector de forma generica
Parámetro: Un apuntador a un vector
Return: Imprime los datos
*/
template<class T>
void menuDisplay(std::vector<T>* menuA)
{
    for(int i = 0; i < menuA->size(); i++)
    {
        std::cout << i + 1 << ". ";
        (*menuA)[i].print();
        std::cout << "-------------------------------------" << std::endl;
    }
}

int main()
{
    Vehiculo A1("Sedan",101,"Nissan",2018,123);
    Vehiculo A2("Deportivo",102,"Corvette",1973,3000);
    Vehiculo A3("Muscle",103,"Chevrolet",1956,2500);
    Vehiculo A4("Electrico",104,"Tesla",2021,0);
    Vehiculo A5("Mini",105,"Fiat",2017,300);

    Camioneta C1("SUV",201,"Toyota",2015,400,"4x4");
    Camioneta C2("SUV",202,"Nissan",2019,230,"4x2");
    Camioneta C3("Pickup",203,"Ford",2021,0,"4WD");
    Camioneta C4("Pickup",204,"Chevrolet",2018,560,"4x4");
    Camioneta C5("SUV",205,"Toyota",2011,400,"AWD");

    Motocicleta M1("Scooter",301,"Vespa",2014,303,"150cc");
    Motocicleta M2("Clasica",302,"Nissan",2020,0,"250cc");
    Motocicleta M3("Deportiva",303,"Suzuki",2022,0,"600cc");
    Motocicleta M4("Deportiva",304,"BMW",2014,0,"450cc");
    Motocicleta M5("Clasica",305,"Yamaha",2014,3000,"150cc");

    Comprador P1("Bustamante", "Miguel Angel", "MAB0219847");
    Comprador P2("Ochoa", "Andrea", "AOZ1034869");
    Comprador P3("Gutierrez", "Luis Eduardo", "LEG0123938");

    std::vector<Vehiculo> menuV{A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,M1,M2,M3,M4,M5};
    std::vector<Comprador> menuC{P1,P2,P3};

    Venta V1(150000,&M5,&P1);
    Venta V2(500000,&A3,&P3);
    Venta V3(250000,&C5,&P2);
    Venta V4(450000,&A4,&P1);
    Venta V5(400000,&C3,&P2);

    std::vector<Venta> ventas{V1,V2,V3,V4,V5};
    
    int menu = 0;
    while(menu != 5){
        std::cout << "Elige una opcion" << std::endl;
        std::cout << "1. Agregar una venta" << std::endl;
        std::cout << "2. Mostrar las ventas en orden descendente" << std::endl;
        std::cout << "3. Mostrar todos los vehiculos comprados por una persona" << std::endl;
        std::cout << "4. Mostrar vehiculos de un anio con kilometraje mayor al elejido" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "> ";
        std::cin >> menu;

        switch(menu){
            case 1:
                int opcionV;
                Vehiculo* x;
                std::cout<<"Elige un vehiculo:" << std::endl;
                menuDisplay(&menuV);
                std::cin >> opcionV;

                switch (opcionV)
                {
                    case 1:
                        x = &A1;
                        break;
                    case 2:
                        x = &A2;
                        break;
                    case 3:
                        x = &A3;
                        break;
                    case 4:
                        x = &A4;
                        break;
                    case 5:
                        x = &A5;
                        break;
                    case 6:
                        x = &C1;
                        break;
                    case 7:
                        x = &C2;
                        break;
                    case 8:
                        x = &C3;
                        break;
                    case 9:
                        x = &C4;
                        break;
                    case 10:
                        x = &C5;
                        break;
                    case 11:
                        x = &M1;
                        break;
                    case 12:
                        x = &M2;
                        break;
                    case 13:
                        x = &M3;
                        break;
                    case 14:
                        x = &M4;
                        break;
                    case 15:
                        x = &M5;
                        break;
                }

                int opcionC;
                Comprador* y;
                std::cout<<"Elige un comprador:" << std::endl;
                menuDisplay(&menuC);
                std::cin >> opcionC;
                
                switch (opcionC)
                {
                    case 1:
                        y = &P1;
                        break;
                    case 2:
                        y = &P2;
                        break;
                    case 3:
                        y = &P3;
                        break;
                }
                
                ventas.push_back(nuevaVenta(x,y));

                for(int i = 0; i < ventas.size(); i++)
                {
                    std::cout << "Venta " << i+1 << std::endl;
                    ventas[i].print();
                    std::cout << std::endl;
                }

                break;

            case 2: 
            {
                std::vector<Venta> porMonto = quicksort(ventas,0,ventas.size()-1);
                menuDisplay(&porMonto);
                break;
            }     
            case 3:
                std::cout<<"Elige un comprador:" << std::endl;
                menuDisplay(&menuC);
                std::cin >> opcionC;
                
                switch (opcionC)
                {
                    case 1:
                        std::cout << "Compras por Miguel Angel Bustamante" << std::endl;
                        busquedaPersona(&ventas, "Miguel Angel");;
                        break;
                    case 2:
                        std::cout << "Compras por Andrea Ochoa" << std::endl;
                        busquedaPersona(&ventas, "Andrea");;
                        break;
                    case 3:
                        std::cout << "Compras por Luis Eduardo Gutierrez" << std::endl;
                        busquedaPersona(&ventas, "Luis Eduardo");;
                        break;
                }   
                break;
            
            case 4:
                int year;
                int km;
                std::cout<<"Elige un anio:";
                std::cin >> year;

                std::cout<<"Elige un kilometraje:";
                std::cin >> km;
                std::cout << std::endl;
                
                busquedaEspecifica(&menuV, year, km); 
                break;
        }
    }

    return 0;

};