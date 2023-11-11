#include "stack.hpp"
#include "queue.hpp"
#include <time.h>
#include <vector>
#include "user.hpp"
#include <sstream>
#include <fstream>
#include <string>
#include "conexionesComputadora.hpp"


//Función que genera un número aleatorio
int randomNum()
{
    srand(time(NULL)); //Semilla basada en el tiempo
    int x = rand() % 150 + 1;
    return x;
}

/*
Función que obtiene la red IP interna del servidor O(n)
Param: Un apuntador a un vector
Return: La dirección IP en un string
*/
template <class T>
std::string getIP(std::vector<T>* vec)
{
    for(int i = 0; i < vec->size(); i++)
    {
        std::string x = (*vec)[i].getOriginIP().substr(0,3);
        if( x == "10.")
        {
            return (*vec)[i].getOriginIP().erase((*vec)[i].getOriginIP().find_last_of("."));
        }
        if( x == "172")
        {
            return (*vec)[i].getOriginIP().erase((*vec)[i].getOriginIP().find_last_of("."));
        }
        if( x == "192")
        {
            return (*vec)[i].getOriginIP().erase((*vec)[i].getOriginIP().find_last_of("."));
        }
    }
    return "a";
};


auto read_csv_user(std::string filename)
{
    /* Crear un vector de vector de strings */
    std::vector< User > lineas;

    /* Crear un input filestream para leer el archivo CSV */
    std::ifstream file(filename);

    /* Verificar si no hubo error al abrir el archivo */
    if(!file.is_open()) throw std::runtime_error("Could not open the file");

    /* Definir variable que almacena cada línea */
    std::string linea;
    
    /* Leer datos línea a línea */
    while(std::getline(file, linea))
    {
        /* Crear un steam de la línea */
        std::stringstream ss(linea);
    
        /* Variables que almacenan cada campo leído */
        std::string date;
        std::string hour;
        std::string origin_IP;
        std::string origin_Port;
        std::string origin_Name;
        std::string target_IP;
        std::string target_Port;
        std::string target_Name;
        
        /* Iterar sobre la línea para extraer cada campo */
        getline(ss, date, ',');
        getline(ss, hour, ',');
        getline(ss, origin_IP, ',');
        getline(ss, origin_Port, ',');
        getline(ss, origin_Name, ',');
        getline(ss, target_IP, ',');
        getline(ss, target_Port, ',');
        ss >> target_Name;
        
        /* Insertar la fila con los campos separados en un vector */
        lineas.push_back(User(date, hour, origin_IP, origin_Port, origin_Name, target_IP, target_Port, target_Name));
    }

    /* Cerrar el archivo */
    file.close();

    /* Regresar el vector de líneas leídas */
    return lineas;
};


int main()
{
    std::vector< User > users = read_csv_user("equipo2.csv");
    
    //Generando nuestro IP
    int ipNum = randomNum();
    std::string y = getIP(&users);
    std::string ourIp = y + "." + std::to_string(ipNum);
    std::cout << "Checking the IP: " << ourIp << std::endl;
    std::string name = "Computadora";


    ConexionesComputadoras<User> computer(ourIp, name, new Stack<User>, new Queue<User>());

    // Se van guardando las conexiones con el IP con el que trabajaremos O(n)
    for(int i = 0; i < users.size(); i++)
    {
        if(users[i].getOriginIP() == ourIp)
        {
            computer.getOutConections()->arrive(new Node<User> (users[i]));
        }
        else if(users[i].getTargetIP() == ourIp)
        {
            computer.getInConections()->push(new Node<User> (users[i]));
        }
    }

    //Pregunta 2
    std::cout << "Last in connection is: " << computer.getInConections()->top()->info.getOriginIP() << std::endl;
    if(computer.getInConections()->top()->info.getOriginIP().substr(0,10) == y)
    {
        std::cout << "Internal address." << std::endl;
    }
    else
    {
        std::cout << "External address." << std::endl;
    }

    //Pregunta 3
    std::cout << "There are " << computer.getInConections()->size() << " in conections." << std::endl;

    //Pregunta 4
    std::cout << "There are " << computer.getOutConections()->size() << " out conections." << std::endl;

    return 0;
};