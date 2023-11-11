#include<iostream>
#include<string>

#pragma once
class Comprador
{
    protected:
        std::string apellido;
        std::string nombre;
        std::string ine;
    public:
        Comprador(){}
        Comprador(std::string apellido, std::string nombre, std::string ine):apellido(apellido), nombre(nombre), ine(ine){}

        std::string getApellido(){return apellido;}
        std::string getNombre(){return nombre;}
        std::string getIne(){return ine;}
        void print()
        {
            std::cout << apellido << std::endl;
            std::cout << nombre << std::endl;
            std::cout << ine << std::endl;
        }
};
