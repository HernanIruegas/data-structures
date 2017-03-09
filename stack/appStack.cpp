#include <iostream>
using namespace std;
#include "stack.h"

int main(){
		
	stack<int> miPila;
	miPila.push(20);
	miPila.push(30);
	cout<<"El tope es: "<<miPila.top()<<endl;
	miPila.push(50);
	miPila.push(10);
	cout<<"La pila tiene: "<<miPila.size()<<" elementos"<<endl;
	while(!miPila.empty()){
		cout<<"saco a: "<<miPila.top()<<endl;
		miPila.pop();
	}

	return 0;
}