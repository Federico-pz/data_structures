#include <vector>
#include <iostream>
#include <set>


template <class K, class V>
class HashChain {
    int _capacity = 0;
    
    std::vector<K> _keys;
    std::vector<V>  _values;
    std::vector<std::string> _status;
    std::vector<std::set<std::pair<K,V>>> _overflow;
    
    int _size = 0;
    
    int hash_function(K) const;
    
public:
    HashChain(int);
    ~HashChain(); 
    
    bool empty() const;
    int size() const;
    int capacity() const;
    
    bool put(K,V);

    V get(K);
    
    template <typename Kn, typename Vn>
    friend std::ostream & operator <<(std::ostream & os, const HashChain<Kn,Vn> & hm);
};

//Constructor del mapa
template <class K, class V>
HashChain<K,V>::HashChain(int capacity)
{
    this->_capacity = capacity;
    this->_status = std::vector<std::string>(capacity);
    this->_keys = std::vector<K>(capacity);
    this->_values = std::vector<V>(capacity);
    this->_overflow =  std::vector<std::set<std::pair<K,V>>>(capacity);
    
    fill(_status.begin(), _status.end(), "vacio");
}

template <class K, class V>
HashChain<K,V>::~HashChain()
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
bool HashChain<K,V>::empty() const
{
    return this->_size == 0;
}

/*
Función que regresa el tamaño (cantidad de llaves con valor que han sido insertadas) del mapa O(1)
Return: El entero con el tamaño del mapa
*/
template <class K, class V>
int HashChain<K,V>::size() const
{
    return this->_size;
}

/*
Función que regresa la capacidad del mapa O(1)
Return: El entero con la capacidad del mapa
*/
template <class K, class V>
int HashChain<K,V>::capacity() const
{
    return this->_capacity;
}

/*
Función que pasa la llave a insertar por una función para definir el índice al que pertenece O(1)
Param: La llave
Return: El índice
*/
template <class K, class V>
int HashChain<K,V>::hash_function(K key) const
{
    return key % this->_capacity;
}

/*
Función que agrega una llave y un valor al mapa, con manejo de sobreflujo meddiante un vector de conjuntos de pares O(1)
Param: La llave y el valor a agregar
Return: Un valor booleano que indica si se pudieron agregar los valores al mapa
*/
template <class K, class V>
bool HashChain<K,V>::put(K key,V value)
{
    int indice = hash_function(key);

    // Si el índice ya está ocupado, se agrega el par al vector de sobreflujo
    if (this->_status[indice] == "ocupado") {
        this->_overflow[indice].insert(std::make_pair(key, value));
        this->_size++;
        return true;
    }
    
    //Si el índice no está ocupado, simplemente se agregan los valores.
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
Función que regresa el valor que le corresponde a la llave solicitada O(n^2)
Param: La llave
Return: El valor de la llave, o en caso de no existir, -1
*/
template <class K, class V>
V HashChain<K,V>::get(K key)
{
    bool found = false;
    int steps = 0;
    
    int indice = hash_function(key);
    
    while (!found && steps < this->_size) {
        if (this->_status[indice] == "ocupado") {
            if (this->_keys[indice] == key) {
                found = true;
            }
            else {
                //Si la llave no está en el índice, se recorre el vector de sobreflujo a ver si la llave se encuentra ahí
                for(auto i: this->_overflow[indice])
                {
                    if(i.first == key)
                    {
                        return i.second;
                    }
                }
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
std::ostream & operator <<(std::ostream & os, const HashChain<K,V> & hm)
{
    for (int i = 0; i < hm._capacity; ++i) {
        if (hm._status[i] == "ocupado") {
            os << hm._keys[i] << " : " << hm._values[i] << std::endl;
            for(auto j: hm._overflow[i])
            {
                // También se imprimen los valores del sobreflujo con una pequeña sangría
                os << "   " << j.first << " : " << j.second << std::endl;
            }
            
        }
    }
    
    return os;
}