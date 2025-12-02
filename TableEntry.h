#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry {
	public:
		std::string key;
		V value;
	
	public:
		// Constructor con todos los parámetros
		TableEntry(std::string key, V value) {
			this->key = key;
			this->value = value;
		}

		// Constructor sin valor
		TableEntry(std::string key) {
			this->key = key;
			this->value = V();
		}

		// Constructor sin parámetros
		TableEntry() {
			this->key = "";
			this->value = V();
		}

		friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2) {
			return (te1.key == te2.key);
		}

		friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2) {
			return (te1.key != te2.key);
		}

		friend std::ostream &operator<<(std::ostream &out, const TableEntry<V> &te) {
			out << "["  <<te.key << " -> " << te.value << "]";
			return out;
		}

		friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2) {
			return (te1.key < te2.key);
		}

		friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2) {
			return (te1.key > te2.key);
		}
};

#endif
