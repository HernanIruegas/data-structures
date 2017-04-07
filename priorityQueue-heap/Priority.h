class Priority{

	public:
		Priority();
		Priority(bool priority);
		void push(int num);
		void pop();
		int top();
		int size();
		bool empty();
		void print();

	private:
		int a[101];
		bool priority;
		int howMany;
		bool compare(int x, int y);
};

Priority::Priority(){
	priority = true;
	howMany = 0;
}

Priority::Priority(bool priority){
	this->priority = priority;
	howMany = 0;
}

bool Priority::compare(int x, int y){
	return (priority ? x > y : x < y);
}

void Priority::push(int num){//recorrido de derecha a izquierda en el arreglo
	int aux = howMany+1;
	a[aux] = num;
	int temp;
	while (!compare(a[aux/2],a[aux]) && howMany>0 && aux>1){
		temp = a[aux/2];
		a[aux/2] = a[aux];
		a[aux] = temp;
		aux = aux/2;
	}
	howMany++;
}

void Priority::pop(){//recorrido de izquierda a derecha en el arreglo
	int aux = 1;
	a[aux] = a[howMany];
	int temp;
	int aux2 = compare(a[aux*2],a[aux*2+1]) ? 2 : 3;

	while(!compare(a[aux],a[aux2])){
		temp = a[aux];
		a[aux] = a[aux2];
		a[aux2] = temp;
		aux = aux2;
		aux2 = compare(a[aux*2],a[aux*2+1]) ? aux * 2 : aux * 2 + 1;
	}

	if(howMany - aux/2 == 1)
		a[aux/2] = a[aux/2+1];
	if(howMany - aux/2 == 2){
		a[aux/2] = a[aux/2+1];
		a[aux/2+1] = a[aux/2+2];
	}
	howMany--;
}

int Priority::top(){
	return a[1];
}

int Priority::size(){
	return howMany;
}

bool Priority::empty(){
	return howMany == 0;
}

void Priority::print(){
	for(int i=1; i<=howMany; i++)
		cout<<a[i]<<" ";
}






