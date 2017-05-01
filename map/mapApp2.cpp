#include <iostream>
using namespace std;
 
int main(){
    int N, iNum;
    string op;
    cin >> N;
    map<int,string> Book;
    while(N)
	{
        cin >> op >> iNum;
        if(op == "add")
		{
            cin >> op;
            Book[iNum] = op;
        } 
		else if(op == "find")
			 (Book.find(iNum) != Book.end())? cout << Book[iNum] << endl : cout << "not found" << endl;
        else
			if(Book.find(iNum) != Book.end())
       		 Book.erase(iNum);
        
        N--;
    }
    return 0;
}