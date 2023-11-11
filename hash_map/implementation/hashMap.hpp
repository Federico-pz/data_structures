#include <vector>
#include <iostream>

template <class K, class V>
class HashMap {
    int _capacity = 0;
    
    std::vector<K> _keys;
    std::vector<V>  _values;
    std::vector<std::string> _status;
    
    int _size = 0;
    
    int hash_function(K) const;
    
public:
    HashMap(int);
    ~HashMap();
    
    bool empty() const;
    int size() const;
    int capacity() const;
    
    bool put(K,V);
    int rehash(int, int);
    V get(K);
    
    template <typename Kn, typename Vn>
    friend std::ostream & operator <<(std::ostream & os, const HashMap<Kn,Vn> & hm);
};

//Constructor del mapa
template <class K, class V>
HashMap<K,V>::HashMap(int capacity)
{
    this->_capacity = capacity;
    this->_status = std::vector<std::string>(capacity);
    this->_keys = std::vector<K>(capacity);
    this->_values = std::vector<V>(capacity);
    
    fill(_status.begin(), _status.end(), "vacio");
}

template <class K, class V>
HashMap<K,V>::~HashMap()
{
    /*
    delete this->_status;
    delete this->_values;
    delete this->_keys;
     */
}

/*
Función que te dice si el mapa está vacío o no O(1)
Return: Un valor booleano que dice si está vacío o no.
*/
template <class K, class V>
bool HashMap<K,V>::empty() const
{
    return this->_size == 0;
}

/*
Función que regresa el tamaño (cantidad de llaves con valor que han sido insertadas) del mapa O(1)
Return: El entero con el tamaño del mapa
*/
template <class K, class V>
int HashMap<K,V>::size() const
{
    return this->_size;
}

/*
Función que regresa la capacidad del mapa O(1)
Return: El entero con la capacidad del mapa
*/
template <class K, class V>
int HashMap<K,V>::capacity() const
{
    return this->_capacity;
}

/*
Función que pasa la llave a insertar por una función para definir el índice al que pertenece O(1)
Param: La llave
Return: El índice
*/
template <class K, class V>
int HashMap<K,V>::hash_function(K key) const
{
    return key % this->_capacity;
}

/*
Función que agrega una llave y un valor al mapa, con manejo de sobreflujo meddiante la función rehash que le busca otro índice a la llave O(1)
Param: La llave y el valor a agregar
Return: Un valor booleano que indica si se pudieron agregar los valores al mapa
*/
template <class K, class V>
bool HashMap<K,V>::put(K key,V value)
{
    if (this->_size == this->_capacity) {
        return false;
    }
    
    int indice = hash_function(key);

    if (this->_status[indice] == "ocupado") {
        indice = rehash(indice, 0); //Recalcular
    }
    
    if (indice > -1) {
        this->_keys[indice] = key;
        this->_values[indice] = value;
        this->_status[indice] = "ocupado";
        this->_size++;
        
        return true;
    }
    
    return false;
}

/*
Función recursiva que coloca una llave en el siguiente lugar disponible en caso de que el índice que le corresponde ya esté occupado
O(n)
Param: El índice y los pasos que lleva
Return: La misma función, el índice donde se va a insertar la llave o -1 en caso de que no haya donde insertar la llave
*/
template <class K, class V>
int HashMap<K,V>::rehash(int indice, int steps)
{
    if (indice < this->_capacity && steps < this->_capacity) {
        
        ++indice;
        
        if (indice == this->_capacity) indice = 0;
        
        if (this->_status[indice] == "ocupado")
        {
            indice = rehash(indice, ++steps);
        }
        
        return indice;
    }
    else {
        return -1;
    }
}

/*
Función que regresa el valor que le corresponde a la llave solicitada O(n)
Param: La llave
Return: El valor de la llave, o en caso de no existir, -1
*/
template <class K, class V>
V HashMap<K,V>::get(K key)
{
    bool found = false;
    int steps = 0;
    
    int indice = hash_function(key);
    
    while (!found && steps < this->_capacity) {
        if (this->_status[indice] == "ocupado") {
            if (this->_keys[indice] == key) {
                found = true;
            }
            else {
                found = false;
                ++indice;
                if (indice == this->_capacity) indice = 0;
            }
        }
        else {
            ++indice;
            if (indice == this->_capacity) indice = 0;
        }
        
        ++steps;
    }
   
    if (found) return this->_values[indice];
    else
        return -1;
}

template <class K, class V>
std::ostream & operator <<(std::ostream & os, const HashMap<K,V> & hm)
{
    for (int i = 0; i < hm._capacity; ++i) {
        if (hm._status[i] == "ocupado") {
            os << hm._keys[i] << " : " << hm._values[i] << std::endl;
            
        }
    }
    
    return os;
}