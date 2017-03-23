#include <iostream>

using namespace std;

#include "BST.h"

int main(){

	BST miArbol;
	miArbol.add(14);
	miArbol.add(39);
	miArbol.add(20);
	miArbol.add(5);
	miArbol.add(10);
	miArbol.add(25);
	miArbol.add(28);
	miArbol.add(12);
	miArbol.add(11);
	miArbol.add(30);
	miArbol.add(18);

	if(miArbol.search(20))
		cout<<"si lo encontre"<<endl;
	else
		cout<<"no lo encontre"<<endl;

	if(miArbol.search(21))
		cout<<"si lo encontre"<<endl;
	else
		cout<<"no lo encontre"<<endl;

	miArbol.print(1);
	cout<<endl;
	miArbol.print(2);
	cout<<endl;
	miArbol.print(3);
	cout<<endl;
	miArbol.print(4);
	cout<<endl;
	cout<<"Mi arbol tiene: "<<miArbol.count()<<" nodos"<<endl;
	miArbol.erase(11);
	miArbol.print(4);
	cout<<endl;

	cout<<"la altura es: "<<endl;
	cout<<miArbol.height()<<endl;

	miArbol.ancestors(18);

	//miArbol.print(5);
	
	cout<<miArbol.nearstRelative(18,28);
	cout<<endl;

	return 0;
}