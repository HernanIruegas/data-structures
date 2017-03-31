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
		void print(int type);
		void ancestors(int data);
		int whereLevelAmI(int data);
		int maxWidth();
		int  nearstRelative(int num1, int num2);
		bool search2(nodeT *aux, int data);
		BST(const BST &copyTree);
		bool isBalanced();
		bool operator==(const BST &otherTree);
		int smallest();
		int descendants(int num);
		int count3(nodeT *aux);
		int printNodesAtLevel(int level);

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
		void printByLevel(nodeT *aux);
		void populate(nodeT* aux, nodeT* aux2);
		bool isBalanced2(nodeT *r, int &aux);
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

void BST::add(int data){//father se queda siempre un nodo atras de aux, de tal manera 
	//que cuando aux apunte a NULL, father está apuntando al nodo al que se le creará 
	//un nuevo hijo con la info. del parametro
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
		
		father->getData() > data ? father->setLeft(new nodeT(data)) : father->setRight(new nodeT(data));
	}
}

void BST::erase(int data){

	nodeT *father = NULL;
	nodeT *aux = root;

	//aux identifica el nodo a borrar, father se queda uno antes de aux (en el padre del nodo a borrar)
	while(aux != NULL && aux->getData() != data){
		father = aux;
		aux = aux->getData() > data ? aux->getLeft() : aux->getRight();
	}

	if(aux == NULL)//no se encontro el número en el arbol
		return;

	int howMany = howManyChildren(aux);

	if(howMany == 0){
		if(father == NULL)//significa que el nodo que se quiere borrar es el primer y unico elemento del arbol, es unico porque howMany es igual a 0
			root = NULL;
		else
			father->getData() > data ? father->setLeft(NULL) : father->setRight(NULL); 

		delete aux;
	}

	if(howMany == 1){

		if(father == NULL){//quiero borrar a root y tiene un hijo
			aux->getLeft() != NULL ? root = aux->getLeft() : root = aux->getRight();	
		}
		else{
			if(father->getData() > data)//se determina si father va a tener nuevo hijo a su izquierda o a su derecha
				aux->getLeft() != NULL ? father->setLeft(aux->getLeft()) : father->setLeft(aux->getRight());
			else
				aux->getLeft() != NULL ? father->setRight(aux->getLeft()) : father->setRight(aux->getRight());
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
	if(r != NULL)
		return 1 + count2(r->getLeft()) + count2(r->getRight());
	else
		return 0;
}

int BST::howManyChildren(nodeT *r){
	int count = 0;
	if(r->getLeft() != NULL)
		count++;
	if(r->getRight() != NULL)
		count++;

	return count;
}

int BST::predecessor(nodeT *r){
	nodeT *aux = r->getLeft();
	while(aux->getRight() != NULL){
		aux = aux->getRight();
	}

	return aux->getData();
}

int BST::successor(nodeT *r){

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
	stack<int> myStack;

	while(aux != NULL && aux->getData() != data){
		myStack.push(aux->getData());
		aux = (aux->getData() > data) ? aux->getLeft() : aux->getRight();
	}

	if(aux == NULL) return; 

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

//calcula la anchura de todos los niveles del arbol
//regresa el nivel más ancho (en número)
int BST::maxWidth(){
	queue <nodeT*> myQueue;
	nodeT *aux = root;

	if(root == NULL) 
		return 0;

	int maxWidth = 0, width;
	myQueue.push(aux);

	while(!myQueue.empty()){
		width = myQueue.size();

		if(width > maxWidth) 
			maxWidth = width;

		while(width > 0){
			if(myQueue.front()->getLeft() != NULL) 
				myQueue.push(myQueue.front()->getLeft());
			if(myQueue.front()->getRight() != NULL) 
				myQueue.push(myQueue.front()->getRight());

			myQueue.pop();
			width--;
		}
	}
	return maxWidth;
}

//Regrese el ancestro mas cercano de dos enteros.
int BST::nearstRelative(int num1, int num2){
	nodeT *aux = root, *aux2;
	while(aux != NULL && aux->getData() != num1 && aux->getData() != num2){
			if(aux->getData() > num1 && aux->getData() > num2){
				aux2 = aux;
				aux = aux->getLeft();
				
			}else if(aux->getData() < num1 && aux->getData() < num2){
				aux2 = aux;
				aux = aux->getRight();
			}else{
				if(search2(aux,num1) && search2(aux,num2))
					return aux->getData();
				else 
					return -1;
			}
	}
	if(aux == NULL) 
		return -1;
	else 
		return aux2->getData();
}

bool BST::search2(nodeT *aux, int data){
	while (aux != NULL){
		if (aux->getData() == data)
			return true;
		aux = (aux->getData() > data) ? aux->getLeft() : aux->getRight();
	}
	return false;
}

//first solution to nearstRelative
/*
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
*/

BST::BST(const BST &copyTree){
	nodeT *aux2 = copyTree.root;
	root = new nodeT(aux2->getData());
	nodeT *aux = root;
	populate(aux, aux2);
}

void BST::populate(nodeT* aux, nodeT* aux2){
	nodeT *a,*b;
	if(aux2->getLeft() != NULL){
		aux->setLeft(new nodeT(aux2->getLeft()->getData()));
		a = aux->getLeft();
		b = aux2->getLeft();
		populate(a,b);
	}
	if(aux2->getRight() != NULL){
		aux->setRight(new nodeT(aux2->getRight()->getData()));
		a = aux->getRight();
		b = aux2->getRight();
		populate(a,b);
	}
}

/*
 Regresa true si el arbol tiene todos sus nodos parcialmente balanceados 
 (maximo 1 de diferencia de altura de los subarboles de cada nodo)
*/
bool BST::isBalanced(){
	int aux = 0;
	return isBalanced2(root, aux);
}

bool BST::isBalanced2(nodeT *r, int &aux){
	int a1 =0, a2=0;
	if(r== NULL) return true;
	else{
		if(isBalanced2(r->getLeft(),a1) && isBalanced2(r->getRight(),a2)){
			aux = 1 + (a1>a2?a1:a2);
			return (abs(a1-a2)<=1);
		}
		else return false;
	}
}

bool BST::operator==(const BST &otherTree){
	queue <nodeT*> myQueue;

	nodeT *aux = root;
	nodeT *aux2 = otherTree.root;

	if(aux == NULL && aux2 == NULL) return true;
	if(aux == NULL || aux2 == NULL) return false;

	myQueue.push(aux);
	myQueue.push(aux2);

	while(!myQueue.empty()){
		aux = myQueue.front();
		myQueue.pop();
		if(myQueue.empty()) return false;
		else{
			aux2 = myQueue.front();
			myQueue.pop();
		}

		if(aux->getData() != aux2->getData()) return false;

		if(aux->getLeft() != NULL) myQueue.push(aux->getLeft());
		if(aux2->getLeft() != NULL) myQueue.push(aux2->getLeft());
		if(aux->getRight() != NULL) myQueue.push(aux->getRight());
		if(aux2->getRight() != NULL) myQueue.push(aux2->getRight());

	}

	return true;
}

int BST::smallest(){
	nodeT *aux = root;
	while(aux->getLeft() != NULL)
		aux = aux->getLeft();

	return aux->getData();
}

int BST::descendants(int num){
	nodeT *aux = root;
	if(!search(num))
		return -1;
	while(aux->getData() != num)
		aux->getData() > num ? aux = aux->getLeft() : aux = aux->getRight();

	return (1 - (count3(aux))) * -1;
}

int BST::count3(nodeT *aux){
	if(aux != NULL)
		return 1 + count3(aux->getLeft()) + count3(aux->getRight());
	else
		return 0;
}

int BST::printNodesAtLevel(int level){
	nodeT *aux = root;
	if(aux==NULL) return 0;
	int n=0, size;
	queue <nodeT*> myQueue;
	myQueue.push(aux);

	while(!myQueue.empty()){
		size = myQueue.size();
		if(n == level) return size;
		n++;
		while(size--){
			aux = myQueue.front();
			myQueue.pop();
			if(aux->getLeft() != NULL) myQueue.push(aux->getLeft());
			if(aux->getRight() != NULL) myQueue.push(aux->getRight());
		}
	}

	return 0;
}

void BST::print(int type){

	switch(type){

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
















