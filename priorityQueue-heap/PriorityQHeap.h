class PriorityQHeap{

	public:
		PriorityQHeap();
		PriorityQHeap(bool priority);
		void push(int num);
		void pop();
		void top();
		int size();
		bool empty();

	private:
		vector<int> v;
		bool priority;
		int howMany;
};

PriorityQHeap::PriorityQHeap(){
	vector<int> v(101);
	priority = true;
	howMany = 0;
}

PriorityQHeap::PriorityQHeap(bool priority){
	vector<int> v(101);
	this->priority = priority;
	howMany = 0;
}

void PriorityQHeap::push(int num){
	
}

void PriorityQHeap::pop(){
	
}

void PriorityQHeap::top(){
	
}

int PriorityQHeap::size(){
	return howMany;
}

bool PriorityQHeap::empty(){
	return howMany == 0;
}






