#include "nodeT.h"
#include "../stack/stack.h"
#include <queue>
class BST{
	
	public:

		BST();
		~BST();
		bool search(int data);
		void add(int data);
		void erase(int data);
		int count();
		int height();
		void print(int tipo);
		void ancestors(int data);
		int whereLevelAmI(int data);
		int maxWidth();
		int  nearstRelative(int num1, int num2);
		//bool operator==(BST &bst1);

	private:

		nodeT *root;
		void preorder(nodeT *r);
		void inorder(nodeT *r);
		void postorder(nodeT *r);
		void freeT(nodeT *r);
		void printLeaves(nodeT *r);
		int count2(nodeT *r);
		int howManyChildren(nodeT *r);
		int predecessor(nodeT *r);
		int successor(nodeT *r);
		int height(nodeT *aNode);
		void ancestors(nodeT *aux, int data);
		void printByLevel(nodeT *aux);
};

BST::BST(){
	root = NULL;
}

void BST::freeT(nodeT *r){

	if(r != NULL){
		freeT(r->getLeft());
		freeT(r->getRight());
		delete r;
	}
}

BST::~BST(){

	freeT(root);
}

bool BST::search(int data){
	nodeT *aux = root;
	while(aux != NULL){
		if(aux->getData() == data)
			return true;
		
		aux = (aux->getData() > data) ? aux->getLeft() : aux->getRight();
	}

	return false;
}

void BST::add(int data){//father se queda siempre un nodo atras de aux, de tal manera que cuando aux apunte a NULL, father está apuntando al nodo al que se le creará un nuevo hijo con la info. del parametro
	if(root == NULL){
		root = new nodeT(data);
	}else{
		nodeT *father = NULL;
		nodeT *aux = root;
		while(aux != NULL){
			if(aux->getData() == data){//we avoid the creation of duplicated data
				return;
			}
			father = aux;
			aux = aux->getData() > data ? aux->getLeft() : aux->getRight();
		}
		if(father->getData() > data){
			father->setLeft(new nodeT(data));
		}else{
			father->setRight(new nodeT(data));
		}
	}
}

void BST::erase(int data){

	nodeT *father = NULL;
	nodeT *aux = root;

	//aux identifica el nodo a borrar, father se queda uno antes de aux
	while(aux != NULL && aux->getData() != data){
		father = aux;
		aux = aux->getData() > data ? aux->getLeft() : aux->getRight();
	}

	if(aux == NULL)//no se encontro el número en el arbol
		return;

	int howMany = howManyChildren(aux);

	if(howMany == 0){
		if(father == NULL){//means that the node we want to erase is the first and only within the tree
			root = NULL;
		}else{
			if(father->getData() > data){
				father->setLeft(NULL);
			}else{
				father->setRight(NULL);
			}
		}
		delete aux;
	}

	if(howMany == 1){
		if(father == NULL){//quiero borrar a root y tiene un hijo
			if(aux->getLeft() != NULL)
				root = aux->getLeft();
			else
				root = aux->getRight();
		}
		else{
			if(father->getData() > data){
				if(aux->getLeft() != NULL)
					father->setLeft(aux->getLeft());
				else
					father->setLeft(aux->getRight());
			}
			else{
				if(aux->getLeft() != NULL)
					father->setRight(aux->getLeft());
				else{
					father->setRight(aux->getRight());
				}
			}
		}
		delete aux;
	}

	if(howMany == 2){
		int newData = successor(aux);
		erase(newData);
		aux->setData(newData);
	}


}

void BST::preorder(nodeT *r){//sirve para clonar un BST

	if(r != NULL){
		cout<<r->getData()<<" ";
		preorder(r->getLeft());
		preorder(r->getRight());
	}
}

void BST::inorder(nodeT *r){//sirve para desplegar los elementos en orden

	if(r != NULL){
		inorder(r->getLeft());
		cout<<r->getData()<<" ";
		inorder(r->getRight());
	}
}

void BST::postorder(nodeT *r){

	if(r != NULL){
		postorder(r->getLeft());
		postorder(r->getRight());
		cout<<r->getData()<<" ";
	}
}

void BST::printLeaves(nodeT *r){
	if(r != NULL){
		if(r->getLeft() == NULL && r->getRight() == NULL)
			cout<<r->getData()<<" ";
		else{
			printLeaves(r->getLeft());
			printLeaves(r->getRight());
		}
	}
}

int BST::count(){
	return count2(root);
}

int BST::count2(nodeT *r){
	if(r != NULL){
		return 1 + count2(r->getLeft()) + count2(r->getRight());

	}else{
		return 0;
	}
}

int BST::howManyChildren(nodeT *r){
	int count = 0;
	if(r->getLeft() != NULL)
		count++;
	if(r->getRight() != NULL)
		count++;

	return count;
}

int BST::predecessor(nodeT *r){//to get predecessor
	nodeT *aux = r->getLeft();
	while(aux->getRight() != NULL){
		aux = aux->getRight();
	}

	return aux->getData();
}

int BST::successor(nodeT *r){//to get sucessor

	nodeT *aux = r->getRight();
	while(aux->getLeft() != NULL){
		aux = aux->getLeft();
	}

	return aux->getData();
}

int BST::height(){
   
	if(root == NULL)
   		return 0;

	nodeT *aux = root;
	return height(aux);
}

int BST::height(nodeT *aux){

	int heightLeft = 0;
    int heightRight = 0;

    if(aux->getLeft() != NULL)
        heightLeft = height(aux->getLeft());
    if(aux->getRight() != NULL)
        heightRight = height(aux->getRight());

    if(heightLeft > heightRight)
        return heightLeft+1;
    else
        return heightRight+1;
}

void BST::ancestors(int data){
	nodeT *aux = root;
	return ancestors(aux, data);
}

void BST::ancestors(nodeT *aux, int data){

	stack<int> myStack;

	while(aux != NULL && aux->getData() != data){
		myStack.push(aux->getData());
		aux = (aux->getData() > data) ? aux->getLeft() : aux->getRight();
	}

	if(myStack.size() > 0){
		while(!myStack.empty()){
		cout<<myStack.top()<<" ";
		myStack.pop();
		}
		cout<<endl;
	}
}

int BST::whereLevelAmI(int data)
{
	if(!search(data))	
		return -1;
	else{
		nodeT *aux = root;
		int i = 0;
		while(aux->getData() != data){
			aux = (aux->getData() > data) ? aux->getLeft() : aux->getRight();
			i++;
		}
		return i;
	}
}

int BST::maxWidth(){
	queue<nodeT*> myQueue;
	queue<nodeT*> myQueue2;
	nodeT *aux = root;
	int max = 0;
	int counter = 0;

	myQueue.push(aux);

	while(!myQueue.empty()){
		aux = myQueue.front();

		while(!myQueue.empty()){
			myQueue2.push(aux);
			myQueue.pop();
			aux = myQueue.front();
		}

		aux = myQueue2.front();

		while(!myQueue2.empty()){
			if(aux->getLeft() != NULL)
				myQueue.push(aux->getLeft());
			if(aux->getRight() != NULL)
				myQueue.push(aux->getRight());
			myQueue2.pop();
			aux = myQueue2.front();
			counter++;
		}
		if(counter > max)
			max = counter;
		counter = 0;
	}
	return max;
}

/*
queue <nodeT*> myQueue;
	nodeT *aux = root;
	myQueue.push(aux);
	while(!myQueue.empty())
	{
		aux = myQueue.front();
		myQueue.pop();
		cout << aux->getData() << " ";
		if(aux->getLeft() != NULL) 
			myQueue.push(aux->getLeft());
		if(aux->getRight() != NULL) 
			myQueue.push(aux->getRight());
	}

	*/

int  BST::nearstRelative( int num1, int num2){
	stack<int> myStack;
	nodeT *aux = root;
	nodeT *aux2 = root;
	int arr[50];
	int size = 0;
	int i = 0;

	while(aux->getData() !=  num1){
		myStack.push(aux->getData());
		if(aux->getData() != num1)
			aux = (aux->getData() > num1) ? aux->getLeft() : aux->getRight();
	}

	while(aux2->getData() !=  num2){
		arr[i] = aux2->getData();
		if(aux2->getData() != num2)
			aux2 = (aux2->getData() > num2) ? aux2->getLeft() : aux2->getRight();
		i++;
		size++;
	}
	
	while(myStack.empty() == false){
		for(int iA = size - 1, iB = 0; iA>=0; iA--){
			if(myStack.top() == arr[iA])
				return myStack.top();
		}
		myStack.pop();
	}
	return 0; 
}

/*bool BST::operator==(BST &bst1){

	nodeT *aux = this.root;
	nodeT *aux2 = bst1.root;

	if(aux != NULL){
		
		preorder(->getLeft());
		preorder(r->getRight());
	}*/

/*
	if(this->size != otherList.size)
		return false;

	node<T> *aux = this->head;
	node<T> *aux2 = otherList.head;

	for(int i=0; i<size;i++){

		if(aux->getData() !=  aux2->getData())
			return false;

		aux = aux->getNext();
		aux2 = aux2->getNext();
	}*/

//	return true;
//}

void BST::printByLevel(nodeT *r)
{
	queue <nodeT*> myQueue;
	nodeT *aux = root;
	myQueue.push(aux);
	while(!myQueue.empty())
	{
		aux = myQueue.front();
		myQueue.pop();
		cout << aux->getData() << " ";
		if(aux->getLeft() != NULL) 
			myQueue.push(aux->getLeft());
		if(aux->getRight() != NULL) 
			myQueue.push(aux->getRight());
	}
}

void BST::print(int tipo){

	switch(tipo){

		case 1: 
			preorder(root);
			break;

		case 2:
			inorder(root);
			break;

		case 3:
			postorder(root);
			break;

		case 4: 
			printLeaves(root);
			break;

		case 5:
			printByLevel(root);
			break;
	}
}
















