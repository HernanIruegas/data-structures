class PriorityQHeap{

	public:
		PriorityQHeap();
		PriorityQHeap(bool priority);
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
};

PriorityQHeap::PriorityQHeap(){
	priority = true;
	howMany = 0;
}

PriorityQHeap::PriorityQHeap(bool priority){
	this->priority = priority;
	howMany = 0;
}

void PriorityQHeap::push(int num){//recorrido de derecha a izquierda en el arreglo
	int aux = howMany+1;
	a[aux] = num;

	if(priority){
		//mientras que el # que va a entrar sea mayor que su padre
		while(a[aux] > a[aux/2] && howMany>0 && aux>1){
			int temp = a[aux/2];
			a[aux/2] = a[aux];
			a[aux] = temp;
			aux = aux/2;
		}
	}else{
		while(a[aux] < a[aux/2] && howMany>0 && aux>1){
			int temp = a[aux/2];
			a[aux/2] = a[aux];
			a[aux] = temp;
			aux = aux/2;
		}
	}
	howMany++;
}

void PriorityQHeap::pop(){//recorrido de izquierda a derecha en el arreglo
	int aux = 1;
	a[aux] = a[howMany];
	int temp;

	if(priority){
		while(a[aux] < a[aux*2] || a[aux] < a[aux*2+1]){
			temp = a[aux];
			if(a[aux*2] > a[aux*2+1]){
				a[aux] = a[aux*2];
				a[aux*2] = temp;
				aux = aux*2;
			}else{
				a[aux] = a[aux*2+1];
				a[aux*2+1] = temp;
				aux = aux*2+1;
			}
		}
	}else{
		while(a[aux] > a[aux*2] || a[aux] > a[aux*2+1]){
			temp = a[aux];
			if(a[aux*2] < a[aux*2+1]){
				a[aux] = a[aux*2];
				a[aux*2] = temp;
				aux = aux*2;
			}else{
				a[aux] = a[aux*2+1];
				a[aux*2+1] = temp;
				aux = aux*2+1;
			}
		}
	}

	if(howMany - aux/2 == 1)
		a[aux/2] = a[aux/2+1];
	if(howMany - aux/2 == 2){
		a[aux/2] = a[aux/2+1];
		a[aux/2+1] = a[aux/2+2];
	}
	howMany--;
}

int PriorityQHeap::top(){
	return a[1];
}

int PriorityQHeap::size(){
	return howMany;
}

bool PriorityQHeap::empty(){
	return howMany == 0;
}

void PriorityQHeap::print(){
	for(int i=1; i<=howMany; i++)
		cout<<a[i]<<" ";
}






