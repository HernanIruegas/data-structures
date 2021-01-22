#include <iostream>
using namespace std;
#include "LinkedList.h"

// Combinar dos LL un elemento por un elemento de cada una en una nueva LL
// Tienes que encontrar la LL de menor tamaño y empezar a combinar
// Acabas de combinar y solo falta append de los elementos que sobraron
LinkedList<char> une(LinkedList<char> &FirstList, LinkedList<char> &otherList){

		LinkedList<char> newList;
		int size1 = FirstList.getSize();
		int size2 = otherList.getSize();
		int menor;

		size1<size2 ? menor = size1 : menor = size2;
	
		for(int i=0; i<menor; i++){

			if(size1==menor){

				newList.addLast(FirstList.getInfoAnyPosition(i));
				newList.addLast(otherList.getInfoAnyPosition(i));
			}else{

				newList.addLast(otherList.getInfoAnyPosition(i));
				newList.addLast(FirstList.getInfoAnyPosition(i));
			}
		}

		size1==menor ? size1 = 0, size2 -= menor : size2 = 0, size1 -= menor;

		if(size2>0){
			for(int i=menor; i<size2+menor; i++){
				newList.addLast(otherList.getInfoAnyPosition(menor));
			}
		}

		if(size1>0){
			for(int i=menor; i<size1+menor; i++){
				newList.addLast(FirstList.getInfoAnyPosition(menor));
			}
		}
		
	return newList;
}



int main(){
	
	LinkedList<string> miLista;
	LinkedList<string> otherLista;

	miLista.addFirst("hola");
	miLista.addFirst("como");
	miLista.addFirst("te");
	miLista.addFirst("va?");
	miLista.print();
	otherLista.addFirst("vaca");
	otherLista.addFirst("leche");
	otherLista.addFirst("leon");
	otherLista.addFirst("tigre?");
	otherLista.print();

	cout<<"shift:"<<endl;
	miLista.shift(3);
	miLista.print();

	cout<<"spin:"<<endl;
	miLista.spin(2);
	miLista.print();

	/* FUNCION UNE
	LinkedList<char> FirstList;
	LinkedList<char> otherList;

	FirstList.addLast('A');
	FirstList.addLast('B');
	FirstList.addLast('C');
	FirstList.addLast('D');
	

	otherList.addLast('E');
	otherList.addLast('F');
	otherList.addLast('G');
	otherList.addLast('H');

	LinkedList<char> newList = une(FirstList, otherList);
	newList.print(); 

	*/

	

	/*cout<<"reverse:"<<endl;
	miLista.reverse();
	miLista.print();

	cout<<"shift:"<<endl;
	miLista.shift(3);
	miLista.print();

	cout<<"spin:"<<endl;
	miLista.spin(2);
	miLista.print();

	cout<<"operator =="<<endl;
	if(miLista==otherLista){
		cout<<"mis dos listas son iguales"<<endl;
	}
	else
		cout<<"mis dos listas son diferentes"<<endl;

	cout<<"operator += de información "<<endl;
	miLista += "nuevaInformación";
	miLista.print();

	cout<<"operator += de linked list "<<endl;
	miLista += otherLista;
	miLista.print();

	cout<<"copy constructor "<<endl;
	LinkedList<string> nuevaLista(miLista);
	nuevaLista.print();

	cout<<"operator = "<<endl;
	miLista = otherLista;
	miLista.print();
	otherLista.print();*/

	return 0;
}