#include "vehiculo.hpp"

#pragma once
class Camioneta : public Vehiculo
{
    protected:
        std::string traccion;
    public:
        Camioneta(){}
        Camioneta(std::string,int,std::string,int,int,std::string);
        std::string getTraccion(){return traccion;}
        void print();
};

Camioneta::Camioneta(std::string tipo, int codigo, std::string marca, int modelo, int kilometraje, std::string traccion)
            : Vehiculo(tipo, codigo, marca, modelo, kilometraje), traccion(traccion){}
void Camioneta::print()
{
    std::cout << "Camioneta" << std::endl;
    std::cout << "Tipo: " << tipo << std::endl;
    std::cout << "Codigo: " << codigo << std::endl;
    std::cout << "Marca:" << marca << std::endl;
    std::cout << "Modelo: "<< modelo << std::endl;
    std::cout << "Kilometraje: " << kilometraje << std::endl;
    std::cout << "Traccion: "<< traccion << std::endl;
}