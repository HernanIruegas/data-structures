#include <iostream>
#include <utility>
#include <map>
#include <iomanip>
using namespace std;


int main (){
	map <int, string> m;
	map <int, string>::iterator p;
	int queries, number;
	string verb, name;
	cin>>queries;
	while(queries > 0){
		cin>>verb;
		if(verb == "add"){
			cin>>number>>name;
			m[number] = name;
		}else if(verb == "find"){
			cin>>number;
			if(m.find(number) != m.end())
				cout<<m[number]<<endl;
			else
				cout<<"not found"<<endl;
		}else{
			cin>>number;
			if(m.find(number) != m.end())
       		 	m.erase(number);
		}
		queries--;
	}
	return 0;
}




