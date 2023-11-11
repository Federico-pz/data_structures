#include "stack.hpp"
#include "queue.hpp"
#include <string>

#pragma once
template <class T>
class ConexionesComputadoras
{
    private:
        std::string ip;
        std::string name;
        Stack<T>* inConection;
        Queue<T>* outConection;
    
    public:
        ConexionesComputadoras(){}
        ConexionesComputadoras(std::string ip, std::string name, Stack<T>* inConection, Queue<T>* outConection)
                            : ip(ip), name(name), inConection(inConection), outConection(outConection){}
        
        Stack<T>* getInConections(){return inConection;}
        Queue<T>* getOutConections(){return outConection;}
};
