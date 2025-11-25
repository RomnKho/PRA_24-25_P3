#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../Pra_24-25_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
	private:
		int n; // Numero de elementos almacenados en la tabla hash
		int max; // Tamaño de la tabla hash (cantidad de cubetas)

		ListLinked<TableEntry<V>> *table; // Tabla de cubetas 
		
		int h(std::string key) {

			int ASCIIsum = 0;
			
			// Por cada carácter en key
			for(char c : key) {
				// Lo convierto en ASCII
				ASCIIsum += int(c);
			}
			// Devuelve la posición hash que resulta del resto de la suma de 
			// los carácteres ASCII y el tamaño de la tabla hash
			return (ASCIIsum % max);
		}

	public:
		// Constructor
		// Crea una tabla linkeada (ListLinked) donde cada nodo es una cubeta (TableEntry) y es de tamaño size;
		HashTable(int size) {
			n = 0;
			max = size;
			table = new ListLinked<TableEntry<V>>[size];
		}
		
		// Destructor
		~HashTable() {
			delete[] table;
		}

		// Devuelve la cantidad de cubetas
		int capacity() {
			return max;
		}

		// Te imprime una instancia de la hash table
		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
		
			out << "Hash Table [Elementos: " << th.n << ", Tamaño: " <<th.max << "]" << std::endl;
			for(int i = 0; i < th.max; i++) {
				out << i <<". " << th.table[i] << std::endl;
			}

			return out;
		}

		// Te devuelve el valor que tiene key
		V operator[](std::string key) {
			
			// Si encuentra el valor lo devuelve
			if(search(key) < 0) {
				throw std::runtime_error("No hay valor para esta clave");
			}

			// Si no lo encuentra
			return search(key);
		}	
		
		// Inserta el par key->value en la tabla
		void insert(std::string key, V value) override {
			
			// Bucle que pasa por todos los nodos de la lista en la cubeta
			for(int i = 0; i < table[h(key)].getSize(); i++) {
				// Si en la cubeta hay alguna clave que coincida con la de la entrada
				if(table[h(key)].get(i).key == key) {
					throw std::runtime_error("Ya hay una clave igual en la tabla");
				}
			}
			
			// Te pone en el array de la tabla en la posicion h(key) (funcion arriba)
			// el nodo cubeta y cada vez te lo pone al final
			table[h(key)].append(TableEntry<V>(key,value));
			n++;
		}
		
		// Busca el valor asociado a la clave
		V search(std::string key) override {
			
			// Recorre los nodos de la lista en la cubeta asociada a la clave
			for(int i = 0; i < table[h(key)].getSize(); i++) {
				// Si en la cubeta hay alguna clave que coincida con la de la entrada
				if(table[h(key)].get(i).key == key) {
					return table[h(key)].get(i).value;
				}
			}
			
			// Si no lo encuentra
			throw std::runtime_error("Clave no encontrada");
		}

		// Elimina el par asociado a la clave
		V remove(std::string key) override {
			
			// Recorre los nodos de la lista en la cubeta asociada a la clave
			for(int i = 0; i < table[h(key)].getSize(); i++) {
				// Si en la cubeta hay alguna clave que coincida con la de la entrada
				if(table[h(key)].get(i).key == key) {
					// Copio la cubeta
					TableEntry<V> entry = table[h(key)].remove(i);
					n--;
					return entry.value;
				}
			}
			
			// Si no lo encuentra
			throw std::runtime_error("Clave no encontrada");
		}		
		
		int entries() override {
			return n;
		}
};

#endif

