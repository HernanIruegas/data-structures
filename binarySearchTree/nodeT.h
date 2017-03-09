class nodeT{
	
	public:

		nodeT(int data);
		nodeT(int data, nodeT* left, nodeT* right);
		int getData();
		nodeT* getLeft();
		nodeT* getRight();
		void setData(int data);
		void setLeft(nodeT *left);
		void setRight(nodeT *right);

	private:

		int data;
		nodeT *left; //left es un apuntador a un nodo
		nodeT *right;
};

nodeT::nodeT(int data){
	
	this->data = data;
	this->left = NULL;
	this->right = NULL;
}

nodeT::nodeT(int data, nodeT* left, nodeT* right){
	
	this->data = data;
	this->left = left;
	this->right = right;
}

int nodeT::getData(){
	
	return this->data;
}

nodeT* nodeT::getLeft(){
	
	return this->left;
}

nodeT* nodeT::getRight(){
	
	return this->right;
}

void nodeT::setData(int data){
	
	this->data = data;
}

void nodeT::setLeft(nodeT *left){
	
	this->left = left;
}

void nodeT::setRight(nodeT *right){
	
	this->right = right;
}














