/*
    Sue Mi Zamarron Orrantia
    Federico Perez Zorrilla
    Activity 1.3
    23/09/2021
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include "user.hpp"

/*
We use the csv processing funtion from the github platform that was given to us.
This code was adapt for the resolution of our problem :)
*/
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

//This function search the vector for the given value, if the value is inside the vector it returns a boolean value.
//Params: A vector and a variable
//Return: True or False
template <class T>
bool inVector(std::vector<T>* vec, T x){
    int test = 0;
    for(int i = 0; i < vec->size(); i++)
    {
        if((*vec)[i] == x){
            test = 1;
            break;
        }
    }
    if(test == 1){
        return true;
    }
    else{
        return false;
    }
};

//This function print all the elements of the vector
//Params: A vector
template<class T>
void vectorDisplay(std::vector<T>* vec)
{
    for(int i = 0; i < vec->size(); i++)
    {
        std::cout << (*vec)[i] << std::endl;
    }
}

//"Bubble method" search algorithm, from the class' github
template<class T>
std::vector<T> burbuja(std::vector<T> vec)
{
    int n = vec.size();
    
    for (int i = 0; i < n; ++i) {
        for (int j = n-1; j > i; --j) {
            if (vec[j] < vec[j-1]) {
                std::swap(vec[j], vec[j-1]);
            }
        }
    }
    return vec;
}


int main(){
    std::vector< User > users = read_csv_user("./equipo2.csv");
    
    int opt = 0;
    while(opt != 8)
    {
        std::cout << "Choose an option" << std::endl;
        std::cout << "1. How many registers are there in the file? " << std::endl;
        std::cout << "2. How many records are there in the second day?" << std::endl;
        std::cout << "3. Is there any computer that belongs to Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel or Raymond?, Whom?" << std::endl;
        std::cout << "4. What is the internal direction of the company?" << std::endl;
        std::cout << "5. Is there any computer called server.reto.com" << std::endl;
        std::cout << "6. Which email server do they use?" << std::endl;
        std::cout << "7. Only considering the target port, Which ports under 1000 are being used?" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "> ";
        std::cin >> opt;

        switch (opt)
        {
            //Calls the vector function .size() to get the lenght
            case 1:
                // Question 1
                std::cout << "There are " << users.size() << " registers." << std::endl;
                break;


            case 2:
            {
                // Question 2
                int temp = 0; //Variable to count registers
                std::string tempDate;
                for(int i = 0; i < users.size(); i++) //Loop to go through all the users vector
                {
                    //Uses stoi to be able to know if it is the second day
                    if (stoi(users[i].getDate().substr(0,2)) == stoi(users[0].getDate().substr(0,2)) + 1)
                    {
                        temp += 1;
                        tempDate = users[i].getDate(); //Stores the date of the correct register, several times
                    }  
                } 
                std::cout << temp << " registers on " << tempDate << std::endl;
                break;
            }


            case 3:
            {
                // Question 3 
                std::vector<std::string> nameList{"jeffrey","betty","katherine","scott","benjamin","samuel","raymond"};
                std::vector<std::string> nameYes; //Vector to store the names included
                for(int i = 0; i < users.size(); i++)
                {
                    //x is a string that only contains the users name, it deletes the .reto.com string
                    std::string x = users[i].getOriginName().erase(users[i].getOriginName().find("."), users[i].getOriginName().size());
                    if(inVector(&nameList, x) && !inVector(&nameYes, x))
                    {
                        nameYes.push_back(x); //Appends names that are in the register, of those required.
                    }
                }

                if(nameYes.size() == 0)
                {
                    std::cout << "Names not in register" << std::endl;
                }
                else
                {
                    vectorDisplay(&nameYes); //If there are names in the vector, it gets printed
                }
                        break;    
            }


            case 4:
            {
            // Question 4
                std::vector<int> test;
                std::cout << "Company's IP address:" << std::endl;
                for(int i = 0; i < users.size(); i++)
                {
                    std::string x = users[i].getOriginIP().substr(0,3);
                    if( x == "10." && !inVector(&test, 1))
                    {
                        std::cout << users[i].getOriginIP().erase(users[i].getOriginIP().find_last_of(".")) << std::endl;
                        test.push_back(1);
                    }
                    if( x == "172" && !inVector(&test, 2))
                    {
                        std::cout << users[i].getOriginIP().erase(users[i].getOriginIP().find_last_of(".")) << std::endl;
                        test.push_back(2);
                    }
                    if( x == "192" && !inVector(&test, 3))
                    {
                        std::cout << users[i].getOriginIP().erase(users[i].getOriginIP().find_last_of(".")) << std::endl;
                        test.push_back(3);
                    }
                }
                break;
            }
            case 5:
            {
                // Question 5
                std::vector<std::string> names; //This vector saves all the users
                std::string server = "server.reto.com";
                for(int i = 0; i < users.size(); i++)
                {
                    names.push_back(users[i].getOriginName()); //Here are saved all the origin names in a vector
                }
                if(inVector(&names, server)) //Checks if the user is in the vector or not
                {
                    std::cout << "Computer: server.reto.com is in register." << std::endl;
                }
                else
                {
                    std::cout << "Computer: server.reto.com is not in register." << std::endl;
                }
                break;
            }

            case 6:
            {
                // Question 6
                std::vector<std::string> mails; //This vector saves the mails of the user
                for(int i = 0; i < users.size(); i++) 
                {   
                    if(users[i].getTargetName().find("mail") != std::string::npos && !inVector(&mails, users[i].getTargetName()))
                    {
                        mails.push_back(users[i].getTargetName()); //This function saves the new mail into mails vector 
                    }
                }
                std::cout << "Mail services used:" << std::endl;
                vectorDisplay(&mails);
                break;
            }
            
            //This function searches every target port from the users vector and creates a new vector with those which are smaller than 1000.
            case 7:
            {
                // Question 7
                std::vector<int> ports; //This vector stores the ports as ints
                for(int i = 0; i < users.size(); i++)
                {
                    if(users[i].getTargetPort() != "-") //examinates the vector when there is a char "-"
                    {
                        if(stoi(users[i].getTargetPort()) < 1000 && !inVector(&ports, stoi(users[i].getTargetPort())))
                        {
                            ports.push_back(stoi(users[i].getTargetPort())); //Adds value to the new vector.
                        }           
                    }
                }
                std::cout << "Ports are:" << std::endl;
                std::vector<int> newPorts = burbuja(ports);
                vectorDisplay(&newPorts);

                break;
            }
            case 8:
                break;

        }
    }
    return 0;
};

    

    
