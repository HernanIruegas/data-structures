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
			p = m.find(number);
			if(p->second != "")
				m.erase(number);
			m.insert(pair <int, string> (number, name));
		}else if(verb == "find"){
			cin>>number;
			p = m.find(number);
			if(p->second != ""){
				cout<<p->second<<endl;
			}else
				cout<<"not found"<<endl;
		}else{
			cin>>number;
			m.erase(number);
		}
		queries--;
	}
	return 0;
}
