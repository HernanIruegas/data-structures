#include <iostream>
using namespace std;
#include "queue.h"

int main(){
		
	queue<int> myStack;
	myStack.push(20);
	myStack.push(30);
	cout<<"El tope es: "<<myStack.front()<<endl;
	myStack.push(50);
	myStack.push(10);
	cout<<"La pila tiene: "<<myStack.size()<<" elementos"<<endl;
	while(!myStack.empty()){
		cout<<"saco a: "<<myStack.front()<<endl;
		myStack.pop();
	}

	return 0;
}