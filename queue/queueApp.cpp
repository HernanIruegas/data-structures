#include <iostream>
using namespace std;
#include "queue.h"

int main(){
		
	queue<int> myQueue;
	myQueue.push(20);
	myQueue.push(30);
	cout<<"El tope es: "<<myQueue.front()<<endl;
	myQueue.push(50);
	myQueue.push(10);
	cout<<"La pila tiene: "<<myQueue.size()<<" elementos"<<endl;
	while(!myQueue.empty()){
		cout<<"saco a: "<<myQueue.front()<<endl;
		myQueue.pop();
	}

	return 0;
}