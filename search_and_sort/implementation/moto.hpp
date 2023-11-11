#include "vehiculo.hpp"

#pragma once
class Motocicleta : public Vehiculo
{
    protected:
        std::string cilindraje;
    public:
        Motocicleta(){}
        Motocicleta(std::string,int,std::string,int,int,std::string);
        std::string getCilindraje(){return cilindraje;}
        void print();
};

Motocicleta::Motocicleta(std::string tipo, int codigo, std::string marca, int modelo, int kilometraje, std::string cilindraje)
            : Vehiculo(tipo, codigo, marca, modelo, kilometraje), cilindraje(cilindraje){}

void Motocicleta::print()
{
    std::cout << "Motocicleta" << std::endl;
    std::cout << "Tipo: " << tipo << std::endl;
    std::cout << "Codigo: " << codigo << std::endl;
    std::cout << "Marca:" << marca << std::endl;
    std::cout << "Modelo: "<< modelo << std::endl;
    std::cout << "Kilometraje: " << kilometraje << std::endl;
    std::cout << "Cilindraje: "<< cilindraje << std::endl;
}