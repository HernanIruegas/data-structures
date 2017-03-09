#include <stddef.h>
#include "node.h"

template <class T>
class LinkedList{

	public:

		LinkedList();//decirle que está vacia
		~LinkedList();
		int getSize();
		bool empty();
		void addFirst(T data);
		void addLast(T data);
		bool add(T data, int pos);
		T deleteFirst();
		T deleteLast();
		T del(int pos);
		int deleteAll();
		T getInfoAnyPosition(int position);
		T setInfoAnyPosition(T data, int position);
		T swapInfoAnyPosition(int position, int secondPosition);
		void reverse();
		void shift(int times);
		void spin(int iN);
		bool operator==(const LinkedList<T> &otherList);
		void operator+=(T data);
		void operator+=(const LinkedList<T> &otherList);
		LinkedList(const LinkedList<T> &myLinkedList);
		void operator=(const LinkedList<T> &otherList);
		void print();

	private:
		
		node<T> *head;//head es un apuntador a un nodo
		int size;
		void borraTodo();
};


template <typename T>
void LinkedList<T>::borraTodo(){

	node<T> *aux = head;
	while(head != NULL){

		head = head->getNext();
		delete aux;
		size--;
		aux = head;
	}
}

//al liberar un apuntador, se libera la direccion de memoria a la que está apuntando
//sola se invoca el destructor, cuando nota que un objeto deja de existir
//puedes hacer un for con deleteFirst
template <typename T>
LinkedList<T>::~LinkedList(){

	borraTodo();
}

template <typename T>
LinkedList<T>::LinkedList(){
	
	head = NULL;
	size=0;
}

template <typename T>
int LinkedList<T>::getSize(){
	
	return size;
}

template <typename T>
bool LinkedList<T>::empty(){

	return head == NULL; //is a condition
}

template <typename T>
void LinkedList<T>::addFirst(T data){

	head = new node<T>(data, head);//we are first passing head as a parameter (which points to NULL)
	size++;
}

template <typename T>
void LinkedList<T>::addLast(T data){

	if(empty())
		addFirst(data);
	else{

		node<T> *aux = head; //apunta a la misma dirección que head

		while(aux->getNext() != NULL){

			aux =  aux->getNext();
		}
		aux->setNext(new node<T>(data));
		size++;
	}
}

template <typename T>
bool LinkedList<T>::add(T data, int pos){

	if(pos<0 || pos>size)
		return false;

	if(pos==0)
		addFirst(data);
	else{

		if(pos==size)
			addLast(data);
		else{

			node<T> *aux= head;
			for(int i=0; i<pos-1; i++){

				aux = aux->getNext();
			}

			aux->setNext(new node<T>(data, aux->getNext()));
			size++;
		}
		return true;
	}
}

//precondiconón = sabes que existe un nodo en la linked list
template <typename T>
T LinkedList<T>::deleteFirst(){

	T dataAux = head->getData();//we save the data (just because the problem asks us to do so, is not necessary)
	node<T> *aux = head;
	head = head->getNext();
	delete aux;
	return dataAux;

}

template <typename T>
T LinkedList<T>::deleteLast(){

	if(size == 1)
		return deleteFirst();
	else{

		node<T> *aux = head;
		while(aux->getNext()->getNext() != NULL){
			aux = aux->getNext();
		}

		T dataAux = aux->getNext()->getData();
		delete aux->getNext();
		aux->setNext(NULL);
		return dataAux;
	}
}

template <typename T>
T LinkedList<T>::del(int pos){

	if(pos==0)
		return deleteFirst();
	if(pos==size-1)
		return deleteLast();

	node<T> *aux = head;
	for(int i = 0; i<pos-1; i++){

		aux = aux->getNext();
	}

	node<T> *aux2 = aux->getNext();
	aux->setNext(aux2->getNext());
	T dataAux = aux->getData();
	delete aux2;
	size--;
	return dataAux;
}

template <typename T>
int LinkedList<T>::deleteAll(){

	borraTodo();
	int tam = size;
	size = 0;
	return tam;
}


template <typename T>
T LinkedList<T>::getInfoAnyPosition(int position){

	if(position<0 || position>size-1)
		return 'N'; //NULL;

	node<T> *aux = head;

	for(int i=0; i<position; i++){
		aux = aux->getNext();
	}

	return aux->getData();	 
}


template <typename T>
T LinkedList<T>::setInfoAnyPosition(T data, int position){

	if(position<0 || position>size-1)
		return NULL;

	node<T> *aux = head;

	for(int i=0; i<position; i++){
		aux = aux->getNext();
	}

	T dataAux = aux->getData();//we first save the info. that is going to be modified
	aux->setData(data); 

	return dataAux;
}


template <typename T>
T LinkedList<T>::swapInfoAnyPosition(int position, int secondPosition){

	if(position<0 || position>size-1 || secondPosition<0 || secondPosition>size-1)
		return false;

	node<T> *aux = head;
	node<T> *secondAux = head;

	/*	proffessor solution

		if(pos1 == pos2)
			return true;

		int posmen = (pos1<pos2) ? pos1 : pos2;
		int posmay = (pos1>pos2) ? pos1 : pos2;

		node<T> *aux1 = head, *aux2;
		for(int i = 0; i<posmen; i++){
			aux1 = aux->getNext();
		}

		aux2=aux1;
		for(int i = posmen; i<posmay; i++){
			aux2 = aux->getNext();
		}
	
		T dataAux = aux1->getData();
		aux1->setData(aux2->getData());
		aux2->setData(dataAux);

	*/

	for(int i=0; i<position; i++){
		aux = aux->getNext();
	}

	for(int i=0; i<secondPosition; i++){
		secondAux = aux->getNext();
	}

	T dataAux = aux->getData();
	T dataAux2 = secondAux->getData();

	aux->setData(dataAux2);
	secondAux->setData(dataAux);

	return true;
		
}

template <typename T>
void LinkedList<T>::reverse(){

	if(size>1){

		node<T> *aux = head;
		node<T> *aux2 = head;

		for(int i=0; i<size; i++){

			if(i==0){
				aux = aux->getNext();
				aux2->setNext(NULL);
			}else{

				aux2 = aux;
				aux = aux->getNext();
				aux2->setNext(head);
				head = aux2;

				if(i==size-1)
					aux2 = NULL;
			}
		}
	}
}

template <typename T>
void LinkedList<T>::shift(int times){

	int auxTimes = 0;

	if(times<0){
		reverse();
		auxTimes = times;
		times*=-1;
	}

	//we first need to create a circular linkedList
	//with the last node pointing to the first
	node<T> *aux = head;
	while(aux->getNext()!=NULL){
		aux = aux->getNext();
	}
	aux->setNext(head);

	node<T> *aux2 = head;
	node<T> *aux3 = head;

	//now we locate our head pointer to the new beggining of the linkedList
	for(int i = 0; i<size-times-1; i++){
		aux2 = aux2->getNext();
	}
	head = aux2->getNext();
	
	//now we set to NULL the pointer of the new last node
	aux2->setNext(NULL);

	if(auxTimes<0)
		reverse();
}

template <typename T>
void LinkedList<T>::spin(int iN){

    if(iN < 2 || size < 2)
        return;

    if(iN >= size){
        reverse();
        return;
    }

    int iC = 0;
    node<T> *current = head, *first = NULL, *first2 = NULL;

    while(current != NULL){

        node<T> *prev = NULL;
        first2 = current;

        for (int i = 0; i < iN && current != NULL; i++){
            node<T> *aux = current->getNext();
            current->setNext(prev);
            prev = current;
            current = aux;
            iC++;
        }

        if(iC == iN)
            head = prev;
        else 
        	first->setNext(prev);
        
        first = first2;
    }
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &otherList){

	if(this->size != otherList.size)
		return false;

	node<T> *aux = this->head;
	node<T> *aux2 = otherList.head;

	for(int i=0; i<size;i++){

		if(aux->getData() !=  aux2->getData())
			return false;

		aux = aux->getNext();
		aux2 = aux2->getNext();
	}

	return true;
}

template <typename T>
void LinkedList<T>::operator+=(T data){

	addLast(data);
}

template <typename T>
void LinkedList<T>::operator+=(const LinkedList<T> &otherList){

	node<T> *aux = this->head;
	node<T> *aux2 = otherList.head;

	while(aux->getNext()!= NULL){
		aux = aux->getNext();
	}

	while(aux2 != NULL){

		aux->setNext(new node<T>(aux2->getData()));
		aux2 = aux2->getNext();
		aux = aux->getNext();
	}

	aux = NULL;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &myLinkedList){

	node<T> *aux = myLinkedList.head;
    this->size = 0;

	//we need to create the first node to set the beggining of new linked list
	this->head = new node<T>(aux->getData());
	this->size++;
	node<T> *aux2 = head; 

	aux = aux->getNext();

	while(aux != NULL){

		aux2->setNext(new node<T>(aux->getData()));
		aux = aux->getNext();
		aux2 = aux2->getNext();
		this->size++;
	}
}

template <typename T>
void LinkedList<T>::operator=(const LinkedList<T> &otherList){

	borraTodo();
	
	node<T> *aux = this->head;
	node<T> *aux2 = otherList.head;

	if(otherList.size>0){

		head = new node<T>(aux2->getData());
		aux = head;
		aux2 = aux2->getNext();

		while(aux2 != NULL){

			aux->setNext(new node<T>(aux2->getData()));
			aux = aux->getNext();
			aux2 = aux2->getNext();
		}

		aux = NULL;
	}
}

template <typename T>
void LinkedList<T>::print(){

	node<T> *aux = head;
	while(aux!=NULL){
		cout<<aux->getData()<<" ";
		aux = aux->getNext();
	}
	cout<<endl;
}















