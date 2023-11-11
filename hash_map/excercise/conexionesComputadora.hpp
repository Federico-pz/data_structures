#include <stack>
#include <queue>
#include <string>

#pragma once
template <class T>
class ConexionesComputadoras
{
    private:
        std::string ip;
        std::string name;
        std::stack<T> inConection;
        std::queue<T> outConection;
    
    public:
        ConexionesComputadoras(){}
        // ConexionesComputadoras(std::string ip, std::string name, std::stack<T>* inConection, std::queue<T>* outConection)
        //                     : ip(ip), name(name), inConection(inConection), outConection(outConection){}
        ConexionesComputadoras(std::string ip)
        {
            this->ip = ip;
        }
        
        std::stack<T> getInConections(){return inConection;}
        std::queue<T> getOutConections(){return outConection;}
        void in(T value){this->inConection.push(value);}
        void out(T value){this->outConection.push(value);}
        void setName(T name){this->name = name;}
        std::string getName(){return this->name;}
};
