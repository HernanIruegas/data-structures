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
		int descendants(int num);
		int count3(nodeT *aux);
		int whereLevelAmI(int data);
		int maxWidth();
		int  nearstRelative(int num1, int num2);
		bool search2(nodeT *aux, int data);
		int smallest();
		int printNodesAtLevel(int level);
		bool operator==(const BST &otherTree);
		BST(const BST &copyTree);
		bool isBalanced();

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
	nodeT* aux = root;
	while(aux != NULL){
		if(aux->getData() == data)
			return true;
		
		aux = (aux->getData() > data) ? aux->getLeft() : aux->getRight();
	}

	return false;
}

//father se queda siempre un nodo atras de aux, de tal manera
//que cuando aux apunte a NULL, father está apuntando al nodo al que se le creará
//un nuevo hijo con la info. del parametro
void BST::add(int data){ 
	 
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

// Igual usamos a father y aux, aux debe quedar en el nodo a borrar
// Operacion para borrar nodo depende de cuantos hijos tiene el nodo (0,1,2)
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
			if(father->getData() > data)//se determina si father va a tener nuevo hijo a su izquierda o a su derecha, father no sabe si aux está a su izq or der
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

// Depth first traverse
// (Root, Left, Right)
void BST::preorder(nodeT *r){//sirve para clonar un BST

	if(r != NULL){
		cout<<r->getData()<<" ";
		preorder(r->getLeft());
		preorder(r->getRight());
	}
}

// Depth first traverse
// (Left, Root, Right)
void BST::inorder(nodeT *r){//sirve para desplegar los elementos en orden

	if(r != NULL){
		inorder(r->getLeft());
		cout<<r->getData()<<" ";
		inorder(r->getRight());
	}
}

// Depth first traverse
// (Left, Right, Root)
void BST::postorder(nodeT *r){

	if(r != NULL){
		postorder(r->getLeft());
		postorder(r->getRight());
		cout<<r->getData()<<" ";
	}
}

// Depth first traverse
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

// Returns the number of nodes in the given tree.
int BST::count(){
	return count2(root);
}

// explicación gráfica = https://www.youtube.com/watch?v=sqVefIEttT0
// Se hace un DSF
int BST::count2(nodeT *r){
	if(r != NULL)
		return 1 + count2( r->getLeft() ) + count2( r->getRight() ); //Add the size of the left and right trees, then add 1 (which is the current node)
	else
		return 0;
}

// Calcular el nivel maximo del BST
int BST::height(){
   
	if(root == NULL)
   		return 0;

	nodeT *aux = root;
	return height(aux);
}

// https://www.youtube.com/watch?v=_pnqMz5nrRs
int BST::height(nodeT *aux){

	/*
	//código del video 
	// En el video se entiende como height al numero de edges (regresar -1) desde el root hasta el leaf node, con wicho fue el numero de nodos (me hace mas sentido eso y tengo que regresar 0)
	if(aux == NULL ) return 0; // en el video se pone -1 pero se entiende de diferente manera a height
	int leftHeight = height( aux -> getLeft);
	int rightHeight = height( aux -> getRight);
	
	return max(leftHeight, rightHeight) + 1; // El height de un nodo es el greater value entre sus subtrees izq y der + 1
	*/


    //Misma solucion de arriba pero escrita mas corta
    if ( root == NULL ) return 0;
    return 1 + max( height( root -> left ), height( root -> right ) );
    

	/* Misma solucion pero escrita mas larga
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
	*/
}

// Es un search con la diferencia de meter los nodos a un stack
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

// Primero nos posicionamos en el nodo con el numero
// Luego Es lo mismo que la función de count para todo el arbol, solo tienes que pasar el nodo en el que estamos en lugar del root
// Si el numero no existe se regresa -1
int BST::descendants(int num){
	nodeT *aux = root;

	// Posicionar aux en el nodo con el numero 
	while(aux->getData() != num && aux != NULL) 
		aux->getData() > num ? aux = aux->getLeft() : aux = aux->getRight();

	if(aux == NULL)
		return -1

	// Le restamos 1 porque no se cuenta el nodo en el que estamos
	// El valor lo ponemos en positivo
	return (1 - (count3( aux ))) * -1; 
}

int BST::count3(nodeT *aux){ // Es lo mismo que la funcion count pero escrito de manera diferente
	if(aux != NULL)
		return 1 + count3(aux->getLeft()) + count3( aux->getRight());
	else
		return 0;
}

// Es un search con la diferencia de que incremento un contador en cada paso
int BST::whereLevelAmI(int data){

	int i = 0;
	while( aux != NULL && aux -> getData() != data){
		aux = (aux->getData() > data) ? aux->getLeft() : aux->getRight();
		i++;
	}

	if( aux == NULL ) return -1; // No se encontro el numero en el arbol

	return i;

}

// Es un traverse en bread first en donde haces print de los nodos
void BST::printByLevel(nodeT *r){

	queue <nodeT*> myQueue;
	nodeT *aux = root;
	myQueue.push(aux);
	while(!myQueue.empty()){

		aux = myQueue.front();
		myQueue.pop();
		cout << aux->getData() << " ";
		if(aux->getLeft() != NULL) 
			myQueue.push(aux->getLeft());
		if(aux->getRight() != NULL) 
			myQueue.push(aux->getRight());
	}
}

// Es un bread first en donde calculas el width por nivel y lo comparas contra el max width ya guardado
// calcula la anchura de todos los niveles del arbol
// regresa el nivel más ancho (en número)
int BST::maxWidth(){
	queue <nodeT*> myQueue;
	nodeT *aux = root;

	if(root == NULL) 
		return 0;

	int maxWidth = 0, width = 0;
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

// Regrese el ancestro mas cercano de dos enteros.
// El ancestro mas cercano es cuando los caminos para encontrar ambos numeros divergen
// Despues de divergir, solo tienes que asegurarte que existan en el arbol los dos numeros
int BST::nearstRelative(int num1, int num2){
	nodeT *aux = root, *aux2;
	while(aux != NULL && aux->getData() != num1 && aux->getData() != num2){
			if(aux->getData() > num1 && aux->getData() > num2){
				aux2 = aux;
				aux = aux->getLeft();
				
			}else if(aux->getData() < num1 && aux->getData() < num2){
				aux2 = aux;
				aux = aux->getRight();
			}else{ // aqui divergen
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

// Funcion auxiliar para ver si existe un numero en el arbol
bool BST::search2(nodeT *aux, int data){
	while (aux != NULL){
		if (aux->getData() == data)
			return true;
		aux = (aux->getData() > data) ? aux->getLeft() : aux->getRight();
	}
	return false;
}

int BST::smallest(){
	nodeT *aux = root;
	while(aux->getLeft() != NULL)
		aux = aux->getLeft();

	return aux->getData();
}

// Imprimir la cantidad de nodos de un cierto nivel en el arbol
// Es un BSF, solo le agregamos una variable para saber en que nivel estamos
int BST::printNodesAtLevel(int level){
	nodeT *aux = root;
	if(aux==NULL) return 0;
	int n=0, size=0;
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

BST::BST(const BST &copyTree){
	nodeT *aux2 = copyTree.root;
	root = new nodeT(aux2->getData());
	nodeT *aux = root;
	populate(aux, aux2);
}

// Es un BSF en los dos arboles, comparando los valores de los nodos
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

// Estas haciendo traverse en preorden del arbol existente pero con la maña de que estas creando los nodos en el nuevo arbol conforme vas recorriendo
// Lo mas facil pero ineficiente seria recorrer el arbol existente en preorden y guardar en un queue los nodos y volverlos a meter en un nuevo arbol,
// pero lo eficiente seria lo que estamos haciendo de recorrer el arbol existente en preorden y crear nodos in place
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
			aux = 1 + (a1 > a2 ? a1 : a2);
			return (abs(a1-a2)<=1);
		}
		else return false;
	}
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
















