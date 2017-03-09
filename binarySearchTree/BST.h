#include "nodeT.h"
class BST{
	
	public:

		BST();
		~BST();
		bool search(int data);
		void add(int data);
		void print(int tipo);

	private:

		nodeT *root;
		void preorder(nodeT *r);
		void inorder(nodeT *r);
		void postorder(nodeT *r);
		void freeT(nodeT *r);
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
	}
}
















