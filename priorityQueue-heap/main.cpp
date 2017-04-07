#include <iostream>
using namespace std;
#include "PriorityQHeap.h"

int main(){

	PriorityQHeap pqh;
	
	pqh.push(8);
	pqh.push(14);
	pqh.push(5);
	pqh.push(20);
	pqh.push(30);
	pqh.push(21);
	pqh.push(10);
	pqh.push(15);

	pqh.print();
	cout<<endl;
	pqh.pop();
	pqh.print();
	return 0;
}


