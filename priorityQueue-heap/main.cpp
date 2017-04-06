#include <iostream>
using namespace std;
#include "PriorityQHeap.h"

int main(){

	PriorityQHeap pqh;
	
	pqh.push(19);
	pqh.push(29);
	pqh.push(5);
	pqh.push(10);
	pqh.push(70);

	cout<<pqh.top()<<endl;
	pqh.print();
	cout<<endl;
	pqh.pop();
	pqh.print();
	return 0;
}


