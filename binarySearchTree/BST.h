#include "nodeT.h"
class BST{
	
	public:

		BST();
		~BST();
		bool search(int data);
		void add(int data);
		void erase(int data);
		int count();
		void print(int tipo);

	private:

		nodeT *root;
		void preorder(nodeT *r);
		void inorder(nodeT *r);
		void postorder(nodeT *r);
		void freeT(nodeT *r);
		void printLeaves(nodeT *r);
		int count2(nodeT *r);
		int howManyChildren(nodeT *r);
		int prev(nodeT *r);
		int after(nodeT *r);
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

void BST::add(int data){
	if(root == NULL){
		root = new nodeT(data);
	}else{
		nodeT *father = NULL;
		nodeT *aux = root;
		while(aux != NULL){
			if(aux->getData() == data){
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

	if(aux == NULL)
		return;

	int howMany = howManyChildren(aux);

	if(howMany == 0){
		if(father == NULL){
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
		int newData = after(aux);
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

int BST::prev(nodeT *r){
	nodeT *aux = r->getLeft();
	while(aux->getRight() != NULL){
		aux = aux->getRight();
	}

	return aux->getData();
}

int BST::after(nodeT *r){

	nodeT *aux = r->getRight();
	while(aux->getLeft() != NULL){
		aux = aux->getLeft();
	}

	return aux->getData();
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
	}
}
















