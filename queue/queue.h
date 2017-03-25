#include "node.h"

template <class T>
class queue{
	
	public:

		queue();
		~queue();
		bool empty();
		int size();
		void push(T data);
		void pop();
		T front();

	private:
		node<T> *last;
		int length;
};

template <typename T>
queue<T>::queue(){
	
	last = NULL;
	length = 0;
}

template <typename T>
queue<T>::~queue(){
	
	if(!empty()){
		node<T> *aux = last->getNext();
		last->setNext(NULL);
		last = aux;

		while(last != NULL){
			last = last->getNext();
			delete aux;
			aux = last;
		}
	}

}

template <typename T>
bool queue<T>::empty(){
	
	return (last == NULL);
}

template <typename T>
int queue<T>::size(){
	
	return length;
}

template <typename T>
void queue<T>::pop(){
	
	//precondicion: que exista un nodo
	node<T> *aux = last->getNext();
	if(last->getNext() == last){
		last = NULL;
	}else{
		last->setNext(aux->getNext());
	}

	delete aux;
}

template <typename T>
void queue<T>::push(T data){
	
	if(empty()){
		last = new node<T>(data);
		last->setNext(last);
	}
	else{
		last->setNext(new node<T>(data, last->getNext()));
		last = last->getNext();
	}
	length++;
}

template <typename T>
T queue<T>::front(){

	return last->getNext()->getData();
}








