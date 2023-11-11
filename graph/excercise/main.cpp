#include <iostream>
#include "Graph.hpp"
#include "user.hpp"
#include <fstream>
#include <sstream>
#include <set>
#include <time.h>
#include <map>
#include "bst.hpp"

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

// Función que obtiene las fechas registradas en el csv
std::set<std::string> fechas(std::vector<User> usuarios)
{
    std::set<std::string> fechas;
    for(auto f: usuarios)
    {
        fechas.insert(f.getDate());
    }
    return fechas;
}

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

/*
Función que genera un grafo multilista con ips internas que se conectan entre si. 
O(n)[Aunque adentro llama a otras funciones con otra complejidad]
Params: El vector con los registros del csv, el apuntador al grafo, la fecha que se va a estudiar
*/
void loadGraph(std::vector<User> registros, Graph<std::string, int> * grafo, std::string date)
{

    std::set<std::string> ipInternas;
    for(auto i: registros)
    // Se llena un set con todas las ips internas en el registro.
        {
            if(i.getDate() == date){
                std::string origin = i.getOriginIP();
                std::string target = i.getTargetIP();

                if(origin.substr(0,3) == "192")
                {
                    ipInternas.insert(origin);
                }

                if(target.substr(0,3) == "192")
                {
                    ipInternas.insert(target);
                }
            }
        }

    // Se agregan todas las ips como vértices
    for(auto n: ipInternas)
    {
        grafo->addVertex(n);
    }


    for(auto r: registros)
    {
        if(r.getDate() == date)
        {
            std::string origin = r.getOriginIP();
            std::string target = r.getTargetIP();
            std::vector < Vertex<std::string, int> *> nodos = grafo->getNodes();

            if(origin.substr(0,3) == "192" && target.substr(0,3) == "192")
            {
                // Se obtienen las posiciones de los nodos involucrados en cada conexión
                int posOrigin = grafo->posInNodos(origin);
                int posTarget = grafo->posInNodos(target);

                if(posOrigin > 0 && posTarget > 0)
                {
                    // Si la conexión aún no existe se agrega al grafo
                    if(!grafo->edgeExist(nodos[posOrigin], nodos[posTarget]))
                    {
                        grafo->addEdge(nodos[posOrigin], nodos[posTarget], 0);
                    }
                }
            }    
        }
    }
}

/*
Función que genera un grafo multilista con ips internas que se conectan a dominios. 
O(n)[Aunque adentro llama a otras funciones con otra complejidad]
Params: El vector con los registros del csv, el apuntador al grafo, la fecha que se va a estudiar
*/
void loadGraph2(std::vector<User> registros, Graph<std::string, int> * grafo, std::string date)
{
    // Para más información ver comentarios de loadGraph
    std::set<std::string> ipsAndWeb;
    std::set< std::pair<std::string, std::string> > conexiones;

    for(auto i: registros)
        {
            if(i.getDate() == date){
                std::string origin = i.getOriginIP();

                if(origin.substr(0,3) == "192" && i.getTargetName() != "-")
                {
                    // Se insertan las ips internas y los dominios que tuvieron conexiones ese día
                    ipsAndWeb.insert(origin);
                    ipsAndWeb.insert(i.getTargetName());
                    conexiones.insert(std::make_pair(origin, i.getTargetName()));
                }
            }
        }
    
    for(auto j: ipsAndWeb)
    {
        grafo->addVertex(j);
    }
   
    std::vector < Vertex<std::string, int> *> nodos = grafo->getNodes();
    for(auto p: conexiones)
    {
        int posOrigin = grafo->posInNodos(p.first);
        int posDomain = grafo->posInNodos(p.second);
        grafo->addEdge(nodos[posOrigin], nodos[posDomain], 0);
    }
    
}

/*
Función que indica si un elemento esta dentro de un vector O(n)
Param: El apuntador al vector y el valor a buscar en el vector
Return: Un valor booleano
*/
template <class T>
bool inVector(std::vector<T>* vec, T x){
    int test = 0;
    for(int i = 0; i < vec->size(); i++)
    {
        if((*vec)[i] == x){
            test = 1; //Se usa una variable para guardar el momento en el que el valor se encuentra dentro del vector.
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

/*
Funcion que hace un mapa con la cantidad de conexiones que recibió un dominio en un día dado O(n)
Param: Un string que indica la fecha, el vector de registros de conexiones
Return: El mapa con los dominios y su frecuencia de conexión
*/
std::map<std::string, int> conexionesPorDia(std::string fecha, std::vector<User> usuarios)
{
    // Se usa un vector que contiene los dominios que no debemos usar.
    std::vector<std::string> excluir{"-", "reto.com"};
    std::map<std::string, int> conexiones;
    for(auto i: usuarios)
    {
        //Checar si la fecha corresponde y excluir los dominios - y reto.com 
        if(!inVector(&excluir, i.getTargetName()) && (i.getDate() == fecha))
        {
            // Hacer el mapa aumentando los valores de las llaves
            conexiones[i.getTargetName()]++;
        }
    }
    return conexiones;
};

/*
Función que crea un BST con conexiones, y llama a su método topN_anormal O(1) [El método es O(log n)]
Param: Un string que representa la fecha, un entero con el tamaño del top que se requiere, el vector con los registros y un apuntador a un mapa
*/
void top_anormal(std::string fecha, int n, std::vector<User> usuarios, std::map<std::string, int>* mapa)
{
    std::map<std::string, int> dominios = conexionesPorDia(fecha, usuarios);
    Bst<int>* aux = new Bst<int>();
    for(auto i: dominios)
    {
       aux->insert(new TreeNode<int>(i.first, i.second));
    }
    aux->topN_anormal(aux->getRoot(), n, 0, mapa);
};

/*
Función que genera un vector con los dominios que tienen más conexiones de lo normal un día, del top n O(n^2)
Param: Un set con las fechas registradas, un vector con los registros
Return: El vector con las conexiones inusuales del día.
*/
std::vector<std::string> conexionesAnormales(std::string date, std::vector<User> registros)
{
    std::vector<std::string> cAnormales;
    int promedio = 0; 
    std::map<std::string, int> anormales;
    std::cout << "Dominios con trafico anormal: " << std::endl;
    top_anormal(date, 5, registros, &anormales);
    
    for(auto x: anormales)
    {
        // Se suman las frecuencias de los dominios
        promedio += x.second;
    }
    promedio = promedio / anormales.size(); // Se obtienen los dominios
    for(auto a: anormales)
    {
        if(a.second > promedio)
        {
            cAnormales.push_back(a.first);
        }
    } 
    return cAnormales;
};

int main()
{
    std::vector<User> registros = read_csv_user("equipo2.csv");
    std::set<std::string> dates = fechas(registros);

    // Se obtiene la ip con la que vamos a trabajar
    int ipNum = randomNum();
    std::string y = getIP(&registros);
    std::string ourIp = y + "." + std::to_string(ipNum);

    std::cout << "Trabajando con la ip: " << ourIp << std::endl;

    for(auto d: dates)
    {
        std::cout << "Conexiones de " << d << std::endl;
        Graph<std::string, int> * grafoInterno = new Graph<std::string, int>();
        
        // Preguntas 1 y 2
        loadGraph(registros, grafoInterno, d);
        grafoInterno->mostConnections(ourIp);
        int connectionsToA = grafoInterno->connectionsTo(ourIp);
        std::cout << ourIp << " ha recibido " << connectionsToA << " conexiones." << std::endl;
        
        Graph<std::string, int> * grafoWeb = new Graph<std::string, int>();

        loadGraph2(registros, grafoWeb, d);

        // Pregunta 3
        int connectionsToB1 = grafoWeb->connectionsTo("7rszfis6fls3zzwhnvm8.net");
        int connectionsToB2 = grafoWeb->connectionsTo("86boe9v31ro4yi83dxsj.com");
        std::cout << "7rszfis6fls3zzwhnvm8.net recibio conexion de " << connectionsToB1 << " computadoras." << std::endl;
        std::cout << "86boe9v31ro4yi83dxsj.com recibio conexion de " << connectionsToB2 << " computadoras." << std::endl;
        
        // Pregunta 4
        std::vector<std::string> anormales = conexionesAnormales(d, registros);
        for(auto a: anormales){
            int connectionsToC = grafoWeb->connectionsTo(a);
            std::cout << a << " recibio conexion de " << connectionsToC << " computadoras." << std::endl;
        }
        std::cout << std::endl;
    }

}
