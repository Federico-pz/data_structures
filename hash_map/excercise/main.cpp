/*
Sue Mi Zamarrón Orrantia A01781507
Federico Pérez Zorrilla A01029967
29-11-2021
Act 5.2 - Actividad Integral sobre el uso de diccionarios y conjuntos (Evidencia Competencia) 
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include "user.hpp"
#include <vector>
#include <set>
#include "conexionesComputadora.hpp"
#include <map>


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


/*
Función que genera un mapa con una ip de llave, y una objeto de la clase conexionesComputadora como valor O(n)
Params: El vector con los registros, un conjunto con todas las ips distintas en el registro
Return: El mapa generado
*/
std::map<std::string, ConexionesComputadoras<std::string>*> ipOcurrences(std::vector< User > users, std::set<std::string> ips)
{
    std::map<std::string, ConexionesComputadoras<std::string>*> ipConections;

    for(auto i: ips)
    {
        //Se insertan todas las ips como llaves al mapa
        ipConections.insert(std::make_pair(i, new ConexionesComputadoras<std::string>(i)));
    }

    for(auto u: users)
    {
        std::string origin = u.getOriginIP();
        std::string target = u.getTargetIP();
        std::string originN = u.getOriginName();
        std::string targetN = u.getTargetName();
        std::string port = u.getTargetPort();

        if(port != "67")       
        { 
            //Por cada registro se agregan a las dos ips involucradas su conexión correspondiente
            ipConections.find(origin)->second->out(target);
            ipConections.find(origin)->second->setName(originN);

            ipConections.find(target)->second->in(origin);
            ipConections.find(target)->second->setName(targetN);
        }
    }
    return ipConections;
}

/*
Función que regresa la cantidad de ips en el registro que tienen conexiones entrantes O(n)
Params: El mapa con las conexiones de cada ip
Return: El entero con la cantidad de ips con conexiones entrantes
*/
int ipsWithInConections(std::map<std::string, ConexionesComputadoras<std::string>*> ipConnections)
{
    int cont = 0;
    for(auto c: ipConnections)
    {
        ConexionesComputadoras<std::string>* con = c.second;
        if(con->getName().find("reto.com") != std::string::npos && con->getInConections().size() > 0)
        {
            cont++;
        }
    }
    return cont;
}

/*
Función que imprime todas las conexiones entrantes a un número n de computadoras, y te indica si se conecta con ips extrañas O(n^2) 
Params: El mapa con las conexiones de cada ip, la cantidad de ips a estudiar, las ip raras
*/
void uniqueInConnections(int n, std::map<std::string, ConexionesComputadoras<std::string>*> ipConnections, std::string wA, std::string wB)
{
    int times = 0;
    std::set<std::string> uCon;
    for(auto i: ipConnections)
    {
        if(i.first.substr(0,3) == "192" && i.second->getName() != "-" && i.second->getName() != "server.reto.com" && i.second->getInConections().size() > 0)
        // if(i.first == "192.168.86.22") //Se usa para probar la posible ip infectada
        {
            bool weird = false;
            times ++;
            std::cout << "Connections to " << i.second->getName() << ":" << std::endl;
            std::stack<std::string> ins = i.second->getInConections();
            while(!ins.empty())
            {
                //Se crea el conjunto con las conexiones entrantes
                uCon.insert(ins.top());
                ins.pop();
            }
            for(auto p: uCon)
            {
                //Se imprimen las conexiones y se verifica si cada conexión es hacia una ip extraña
                std::cout << p << "  ";
                if(p == wA || p == wB)
                {
                    weird = true;
                }
            }
            uCon.clear();
            std::cout << std::endl;
            if(weird){std::cout << "Se conecta con ips raras";}
            else{std::cout << "No se conecta con ips raras";}
            std::cout << std::endl << std::endl;

        }
        if(times == n){break;}
        // std::cout << i.first << ", " << i.second->getName() << std::endl;
    }
}

/*
Función que regresa un conjunto con las conexiones salientes únicas de una ip dada O(n)
Params: El mapa con las conexiones de cada ip, la ip a estudiar
Return: El conjunto con las conexiones
*/
std::set<std::string> uniqueOutConnections(std::map<std::string, ConexionesComputadoras<std::string>*> ipConnections, std::string ip)
{
    std::set<std::string> uCon;

    std::queue<std::string> outs = ipConnections.find(ip)->second->getOutConections();
    while(!outs.empty())
    {
        uCon.insert(outs.front());
        outs.pop();
    }
    return uCon;
}

/*
Función que imprime la fecha de la primera conexión entre dos ips dadas O(n)
Params: El vector con los registros, la ip origen y la ip destino
*/
void firstConnection(std::vector< User > users, std::string origin, std::string target)
{
    for(auto u: users)
    {
        std::string ori = u.getOriginIP();
        std::string tar = u.getTargetIP();
        if(ori == origin && tar == target)
        {
            std::cout << "La primera conexion entre " << origin << " y " << target << "fue el: " << u.getDate() 
            << ", con el protocolo " << u.getTargetPort() <<std::endl;
            return;
        }

    }
}

int main()
{
    std::vector< User > users = read_csv_user("equipo2.csv");
    std::set<std::string> domains;
    std::set<std::string> ips;
    std::map<std::string, std::string> domIP;

    //Se crea un mapa auxiliar con los dominios y sus ips correspondientes
    for(auto i: users)
    {
        std::string origin = i.getOriginName();
        std::string target = i.getTargetName();
        std::string originIp = i.getOriginIP();
        std::string targetIp = i.getTargetIP();
        
        ips.insert(originIp);
        ips.insert(targetIp);

        if(origin.find("reto.com") == std::string::npos)
        {
            domains.insert(origin);
            domIP.insert(std::make_pair(origin, originIp));
        }

        if(target.find("reto.com") == std::string::npos)
        {
            domains.insert(target);
            domIP.insert(std::make_pair(target, targetIp));
        }

    }

    std::map<std::string, ConexionesComputadoras<std::string>*> ipConnections = ipOcurrences(users, ips);

    std::string weirdA = "7rszfis6fls3zzwhnvm8.net";
    std::string weirdB = "86boe9v31ro4yi83dxsj.com";

    std::cout << "Dominios raros: " << std::endl;
    std::cout << weirdA << ": " << domIP.find(weirdA)->second << std::endl;
    std::cout << weirdB << ": " << domIP.find(weirdB)->second << std::endl;

    std::cout << "-------------------------------------" << std::endl;

    std::cout << "IPs internas con al menos una conexion entrante: " << ipsWithInConections(ipConnections) << "\n\n";

    std::cout << "Analisis de conexiones en los registros: " << std::endl;
    uniqueInConnections(10, ipConnections, domIP.find(weirdA)->second, domIP.find(weirdB)->second);

    std::set<std::string> infectedCon = uniqueOutConnections(ipConnections, "192.168.86.22");

    std::cout << "Hay " << infectedCon.size() << " conexiones unicas desde 192.168.86.22" << std::endl;

    for(auto k: uniqueOutConnections(ipConnections, "192.168.86.22"))
    {
        if(k == weirdA || k == domIP.find(weirdA)->second)
        {
            std::cout << "Se conecta con " << weirdA << ", ip: "<< k << std::endl;
            firstConnection(users, "192.168.86.22", k);
            std::cout << std::endl;
        } 
        
        if(k == weirdB || k == domIP.find(weirdB)->second)
        {
            std::cout << "Se conecta con " << weirdB << ", ip: "<< k << std::endl;
            firstConnection(users, "192.168.86.22", k);
            std::cout << std::endl;
        } 

    }


}