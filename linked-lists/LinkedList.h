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
		
		node<T>* head;//head es un apuntador a un nodo
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

// Simplemente mover el head a un nuevo nodo y apuntar al pasado comienzo
template <typename T>
void LinkedList<T>::addFirst(T data){

	head = new node<T>(data, head);//we are first passing head as a parameter
	size++;
}

// 2 casos: Si la LL está vacia o no
// Si está vacia pues es un addFirst
// Si no está vacia es de posicionarse en el ultimo nodo
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

// Validar que no sean los casos del primero o el ultimo o fuera del rango
// Posicionarme un nodo atras
// Se maneja indice 0 para indicar posicion
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

//precondición = sabes que existe un nodo en la linked list
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
		//te quedas en el penultimo nodo, porque tienes que poner su apuntador a NULL
		while(aux->getNext()->getNext() != NULL){
			aux = aux->getNext();
		}

		T dataAux = aux->getNext()->getData();
		delete aux->getNext();
		aux->setNext(NULL);
		return dataAux;
	}
}

// Es importante que no se te olvide hacer delete al apuntador del nodo a ser borrado, por eso se crea un tercer apuntador
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

// Es mas eficiente la solucion del profesor porque asi no tienes que repetir el traverse por los nodos que ya se pasaron
// Imaginate que sea una LL de millones de nodos, traversing afecta
template <typename T>
T LinkedList<T>::swapInfoAnyPosition(int pos1, int pos2){

	if(pos1 < 0 || pos1 > size - 1 || pos2 < 0 || pos2 > size - 1)
		return false;

	int posmen = (pos1 < pos2) ? pos1 : pos2;
	int posmay = (pos1 > pos2) ? pos1 : pos2;

	// Te posicionas en posmenor
	node<T> *aux1 = head, *aux2 = head;
	for(int i = 0; i < posmen; i++){
		aux1 = aux1->getNext();
	}

	aux2=aux1; // Desde aqui (posmenor) arranca el nuevo recorrido y no desde el principio
	for(int i = posmen; i < posmay; i++){
		aux2 = aux2 -> getNext();
	}

	T dataAux = aux1 -> getData();
	aux1 -> setData(aux2 -> getData());
	aux2 -> setData(dataAux);

}

// Manejo de 3 apuntadores
// muevo aux, luego aux2, luego apunto a head, luego muevo head
template <typename T>
void LinkedList<T>::reverse(){

	if(size>1){

		node<T> *aux = head;
		node<T> *aux2 = head;

		// Me posiciono para empezar algoritmo, haciendo el primer nodo que apunte a NULL
		aux = aux->getNext();
		aux2->setNext(NULL);

		for(int i = 0; i < size - 1; i++){

			// Avanzas aux2 y luego aux
			aux2 = aux;
			aux = aux->getNext();
			// Haces que el nodo de aux2 apunte a head (que está atras)
			aux2->setNext(head);
			// Avanzas head
			head = aux2;

			if(i == size - 1)
				aux2 = NULL;
		}
	}
}

// Create circular LL, last node pointing to first node
// Solo funciona para numeros positivos
// Para negativos bastaria con hacer size + times, ya que times es negativo tonss va a dar un numero positivo
template <typename T>
void LinkedList<T>::shift(int times){

	// Creation of circular LL
	node<T> *aux = head;
	while(aux->getNext()!=NULL){
		aux = aux->getNext();
	}
	aux->setNext(head);

	node<T> *aux2 = head;
	node<T> *aux3 = head;

	// Now we locate our head pointer to the new beggining of the linkedList
	// Ponemos aux2 un nodo antes del nuevo head para poder hacer set a NULL en el nuevo ultimo nodo de LL
	for(int i = 0; i<size-times-1; i++){
		aux2 = aux2->getNext();
	}
	head = aux2->getNext();
	//now we set to NULL the pointer of the new last node
	aux2->setNext(NULL);
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

// Lo importante aqui es usar const para que no se pueda modificar la LL que se pasa como parametro por referencia
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

// Hacer un append de otro LL, es solo de ponerse en el final de una y principio de otra e ir creando nodos
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

// Crea una LL igual a la que se pasa de argumento
// Similar al del operador =, solo que no tienes que borrar todos los nodos
// Se crea el primer nodo primero y luego se sigue el algoritmo
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

// Se crea el primer nodo primero y luego se sigue el algoritmo
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















