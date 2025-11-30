#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include "BSTree.h"
#include "TableEntry.h"
#include "Dict.h"
#include <ostream>
#include <string>

template <typename V>
class BSTreeDict : public Dict<V> {
	private:
		// Arbol binario donde cada nodo es una TableEntry (clave -> valor)
		BSTree<TableEntry<V>> *tree;
	
	public:
		// Constructor
		BSTreeDict() {
			tree = new BSTree<TableEntry<V>>;
		}

		// Destructor
		~BSTreeDict() {
			delete tree;
		}

		friend std::ostream &operator<<(std::ostream &out, const BSTreeDict<V> &bstd) {
			out << *(bstd.tree);
			return out;
		}

		V operator[](std::string key) {
			return tree->search(TableEntry<V>(key)).value;;
		}

		// Métodos heredados

		void insert(std::string key, V value) override {
			tree->insert(TableEntry<V>(key,value));
		}

		V search(std::string key) override {
			return tree->search(TableEntry<V>(key)).value;
		}

		V remove(std::string key) override {
			V value = tree->search(TableEntry<V>(key)).value;
			tree->remove(TableEntry<V>(key));
			return value;
		}

		int entries() override {
			return tree->size();
		}	


};

#endif

