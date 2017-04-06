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

void PriorityQHeap::push(int num){
	if(howMany==0){
		a[howMany+1] = num;
		howMany++;
		return;
	}
	if(a[(howMany+1)/2] > num){
		a[howMany+1] = num;
		howMany++;
		return;
	}else{
		//hacemos el intercambio de los valores en el arreglo
		int temp = a[(howMany+1)/2];
		a[(howMany+1)/2] = num;
		a[howMany+1] = temp;

		int position = (howMany+1)/2; //lugar en donde está el # que cambio de casilla
		for(int i = position; i>1; i/=2){
			if(a[position] < a[position/2])
				return;
			else{
				//hacemos el intercambio de los valores en el arreglo
				temp = a[position/2];
				a[position/2] = a[position];
				a[position] = temp;
				position = position/2;
			}
		}
		howMany++;
	}
}

void PriorityQHeap::pop(){
	//pones al hijo mayor como el sucesor y recorres todo el arreglo haciendo esto

	int aux = 1;
	howMany--;

	if(a[aux*2] > a[(aux*2)+1]){
		a[aux] = a[aux*2];
		aux = aux*2;
	}else{
		a[aux] = a[(aux*2)+1];
		aux = (aux*2)+1;
	}

	for(int i=aux; i<howMany; i*=aux){
		cout<<"hola"<<endl;
		if(a[aux*2] > a[(aux*2)+1]){
			a[aux] = a[aux*2];
			aux = aux*2;
		}else{
			a[aux] = a[(aux*2)+1];
			aux = (aux*2)+1;
		}
	}
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






