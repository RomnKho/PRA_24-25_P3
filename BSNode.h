#ifndef BSNODE_h
#define BSNODE_h

#include <ostream>

template <typename T>
class BSNode {
	public:
		T elem; 
		BSNode<T> *left; // Nodo a la izquierda
		BSNode<T> *right; // Nodo a la izquierda
				  
		// Constructor del nodo
		BSNode(T elem, BSNode<T> *left = nullptr, BSNode<T> *right = nullptr) {
			this->elem = elem;
			this->left = left;
			this->right = right;
		}

		// Sobrecarga del operador
		friend std::ostream operator<<(std::ostream &out, const BSNode<T> &bsn) {
			out << bsn.elem << std::endl;
			return out;
		}
};

#endif
