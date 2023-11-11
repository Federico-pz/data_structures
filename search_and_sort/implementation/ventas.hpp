#include<iostream>
#include "vehiculo.hpp"
#include "comprador.hpp"

#pragma once
class Venta
{
    protected:
        float monto;
        Vehiculo* vehiculo;
        Comprador* comprador;
    public:
        Venta(){}
        Venta(float, Vehiculo*, Comprador*);
        float getMonto(){return monto;}
        Vehiculo* getVehiculo(){return vehiculo;}
        Comprador* getComprador(){return comprador;}
        void print();
        
        //Se sobrecargan los operadores de comparacion para poder hacer el quicksorting
        bool operator<(Venta a){
            if(this->getMonto() < a.getMonto()){
                return true;
            }
            else{return false;}
        }
        bool operator>(Venta a){
            if(this->getMonto() > a.getMonto()){
                return true;
            }
            else{return false;}
        }
        bool operator<=(Venta a){
            if(this->getMonto() <= a.getMonto()){
                return true;
            }
            else{return false;}
        }
        bool operator>=(Venta a){
            if(this->getMonto() >= a.getMonto()){
                return true;
            }
            else{return false;}
        }
};

Venta::Venta(float monto, Vehiculo* vehiculo, Comprador* comprador):monto(monto),vehiculo(vehiculo),comprador(comprador){}

void Venta::print()
{
    std::cout << "Monto: $" << monto << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Datos del vehiculo:" << std::endl;
    vehiculo->print();
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Datos del comprador:" << std::endl;
    comprador->print();
    
}