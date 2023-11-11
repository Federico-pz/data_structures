/*
Sue Mi Zamarrón Orrantia A01781507
Federico Pérez Zorrilla A01029967
07-11-2021
Actividad integral de Bst
*/

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
#include "user.hpp"
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
Función que crea un BST con conexiones, y llama a su método topN_Diario O(1) [El método es O(log n)]
Param: Un string que representa la fecha, un entero con el tamaño del top que se requiere, el vector con los registros y un apuntador a un mapa
*/
void top_diario(std::string fecha, int n, std::vector<User> usuarios, std::map<std::string, int>* mapa)
{
    //Se crea el BST
    std::map<std::string, int> dominios = conexionesPorDia(fecha, usuarios);
    Bst<int>* aux = new Bst<int>();
    for(auto i: dominios)
    { 
        //Se agregan las hojas, que fueron modificadas para tener un string con el dominio y un int con la frecuencia
       aux->insert(new TreeNode<int>(i.first, i.second)); 
      
    }
    std::cout << "Top " << n << "  " << fecha << std::endl << "-----------------------------" << std::endl;
    aux->topN_diario(aux->getRoot(), n, 0, mapa);
};

/*
Función que crea un BST con conexiones, y llama a su método topN_Consecutivo O(1) [El método es O(log n)]
Param: Un string que representa la fecha, un entero con el tamaño del top que se requiere, el vector con los registros y un apuntador a un mapa
*/
void top_consecutivo(std::string fecha, int n, std::vector<User> usuarios, std::map<std::string, int>* mapa2)
{
    std::map<std::string, int> dominios = conexionesPorDia(fecha, usuarios);
    Bst<int>* aux = new Bst<int>();
    for(auto i: dominios)
    {
       aux->insert(new TreeNode<int>(i.first, i.second));
    }
    aux->topN_Consecutivo(aux->getRoot(), n, 0, mapa2);
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
Función que genera un set con las fechas que hay registradas en el csv O(n)
Param: El vector con los registros
Return: Un set con las fechas
*/
std::set<std::string> fechas(std::vector<User> usuarios)
{
    std::set<std::string> fechas;
    for(auto f: usuarios)
    {
        fechas.insert(f.getDate());
    }
    return fechas;
}

/*
Función que indica los dominios que una vez aparecen en el top 5, se mantienen ahí el resto de los días O(n^2)
Param: Un set con las fechas registradas, un vector con los registros
*/
void get_topConsecutivo(std::set<std::string> dates, std::vector<User> registros)
{
    //Se crean dos mapas, el mapa 1 se crea con valores auxiliares que sirven para el inicio, y el 2 es una copia del 1
    std::map<std::string, int> mapa1;
    std::map<std::string, int> mapa2;
    mapa1["a"]++;
    mapa1["b"]++;
    mapa1["c"]++;
    mapa1["d"]++;
    mapa1["e"]++;
    for(auto m: mapa1)
    {
        mapa2[m.first]++;
    }
    for(auto i: dates)
    {
        //Se llama la función que guardará el top n de un día en el mapa 2
        top_consecutivo(i, 5, registros, &mapa2);

        //Se eliminan del mapa 2, todos los elementos del mapa 1 que no hayan aumentado su valor en el mapa 2
        for(auto r: mapa1)
        {
            if(mapa2[r.first] <= r.second)
            {
                mapa2.erase(r.first);
            }
        }

        //Se vacía el mapa 1 y se convierte en una copia del mapa 2
        mapa1.clear();
        for(auto j: mapa2)
        {
            mapa1.insert(std::make_pair(j.first, j.second));
        }
    }

    //Se imprimen los dominios, naturalmente se imprimirán todos los del último día adicionalmente de los que cumplen con la condición
    std::cout << "Dominios que se mantiene en el top 5 desde que aparece por primera vez:" << std::endl;
    for(auto p: mapa2)
    {
        std::cout << p.first << " " << p.second << " veces." << std::endl;
    }
};

/*
Función que imprime los dominios que tienen más conexiones de lo normal cada día, del top n O(n^2)
Param: Un set con las fechas registradas, un vector con los registros
*/
void conexionesAnormales(std::set<std::string> dates, std::vector<User> registros)
{
    int promedio = 0;
    for(auto i: dates)
    {
        std::map<std::string, int> anormales;
        std::cout << "Dominios con trafico anormal el dia " << i << ": " << std::endl;
        top_anormal(i, 5, registros, &anormales);
        
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
                std::cout << a.first << std::endl; //Se imprimen las frecuencias arriba del promedio, al haber diferencias enormes los anormales quedan arriba siempre
            }
        }
        std::cout << std::endl;
        anormales.clear();
    }
};

int main() 
{
    std::vector<User> registros = read_csv_user("equipo2.csv");
    std::set<std::string> dates = fechas(registros);
    std::map<std::string, int> tops;

    
    //Imprimir el top 5 de todos los dias
    for(auto i: dates)
    {
        top_diario(i, 5, registros, &tops);
        std::cout << std::endl;
    }
    
    std::cout << "----------------" << std::endl << "|  Pregunta 1  |" << std::endl << "----------------" << std::endl;
    //Ver que dominios estan en el top 5 todos los dias
    std::cout << "Dominios en el top 5 todo el tiempo:" <<std::endl;
    for(auto t: tops)
    {
        if(t.second == dates.size())
        {
            std::cout << t.first << std::endl;
        }
    }
    
    //Obtener los dominios que entran al top 5 y se mantienen el resto de los días
    std::cout << std::endl;
    std::cout << "----------------" << std::endl << "|  Pregunta 2  |" << std::endl << "----------------" << std::endl;
    get_topConsecutivo(dates, registros);

    //Obtener los dominios que tienen una frecuencia anormal
    std::cout << std::endl;
    std::cout << "----------------" << std::endl << "|  Pregunta 3  |" << std::endl << "----------------" << std::endl;
    conexionesAnormales(dates, registros);
    
    return 0;
};
