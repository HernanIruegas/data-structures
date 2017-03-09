#include <stddef.h>
#include "node.h"
template <class T>
class stack{
	
	public:

		stack();
		~stack();
		bool empty();
		void push(T data);
		void pop();
		T top();
		int size();

	private:

		node<T> *tope;
		int length;
};

template <typename T>
stack<T>::stack(){

	tope = NULL;
	length = 0;
}

template <typename T>
stack<T>::~stack(){

	node<T> *aux = tope;

	while(aux!=NULL){

		tope = tope->getNext();
		delete aux;
		aux = tope;
	}
}

template <typename T>
bool stack<T>::empty(){

	return (tope == NULL); //is a condition
}

template <typename T>
void stack<T>::push(T data){

	tope = new node<T>(data, tope);
	length++;
}

template <typename T>
void stack<T>::pop(){

	node<T> *aux = tope;
	tope = tope->getNext();
	length--;
	delete aux;
}

template <typename T>
T stack<T>::top(){

	return tope->getData();
}

template <typename T>
int  stack<T>::size(){

	return length;
}





























