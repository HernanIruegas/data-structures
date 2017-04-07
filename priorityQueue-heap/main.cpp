#include <iostream>
using namespace std;
#include "Priority.h"

int main(){

	Priority pqh;
	
	/*pqh.push(8);
	pqh.push(14);
	pqh.push(5);
	pqh.push(20);
	pqh.push(30);
	pqh.push(21);
	pqh.push(10);
	pqh.push(15);*/

	pqh.push(40);
	pqh.push(80);
	pqh.push(35);
	pqh.push(100);
	pqh.push(60);
	pqh.push(85);
	pqh.push(10);
	pqh.push(75);
	pqh.push(15);

	pqh.print();
	cout<<endl;
	pqh.pop();
	pqh.print();
	cout<<endl;
	pqh.push(50);
	pqh.print();
	return 0;
}


