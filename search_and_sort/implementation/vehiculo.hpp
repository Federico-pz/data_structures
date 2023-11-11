#include<iostream>
#include<string>

#pragma once
class Vehiculo
{
    protected:
        std::string tipo;
        int codigo;
        std::string marca;
        int modelo;
        int kilometraje;
    public:
        Vehiculo(){}
        Vehiculo(std::string, int, std::string, int, int);

        int getCodigo(){return codigo;}
        std::string getMarca(){return marca;}
        int getModelo(){return modelo;}
        int getKm(){return kilometraje;}
        virtual void print(); //Se sobrecargara en las clases herederas
};

Vehiculo::Vehiculo(std::string tipo, int codigo, std::string marca, int modelo, int kilometraje)
                    :tipo(tipo),codigo(codigo),marca(marca),modelo(modelo),kilometraje(kilometraje){}

void Vehiculo::print()
{
    std::cout << "Automovil" << std::endl;
    std::cout << "Tipo: " << tipo << std::endl;
    std::cout << "Codigo: " << codigo << std::endl;
    std::cout << "Marca:" << marca << std::endl;
    std::cout << "Modelo: "<< modelo << std::endl;
    std::cout << "Kilometraje: " << kilometraje << std::endl;
}
