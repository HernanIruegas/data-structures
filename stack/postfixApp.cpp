#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <stack>


using namespace std;
int main(){

	string d,data;
 
	getline(cin, data);
	while (data != "#"){

		stack<int> myStack;
		queue<int> myQueue;
		priority_queue<int, vector<int>, greater<int> > mpq;
		int resp, respQueue, respStack, respmpq;

		stringstream ss;
  		ss<< data;
		while (ss >> d){
			if(d=="+" || d=="-"  || d=="*"  || d=="/" ){

				char Operator = d[0];

				int X = myStack.top();
				myStack.pop();
				int Y = myStack.top();
				myStack.pop();
				
				int xq = myQueue.front();
				myQueue.pop();
				int yq = myQueue.front();
				myQueue.pop();

				int xpq = mpq.top();
				mpq.pop();
				int ypq = mpq.top();
				mpq.pop();

				switch(Operator){

					case '+':
						respQueue = yq + xq;
						respStack = Y + X;
						respmpq = ypq + xpq;
						break;

					case '-':
						respQueue = yq - xq;
						respStack = Y - X;
						respmpq = ypq - xpq;
						break;

					case '*':
						respQueue = yq * xq;
						respStack = Y * X;
						respmpq = ypq * xpq;
						break;

					case '/':
						respQueue = yq / xq;
						respStack = Y / X;
						respmpq = ypq / xpq;
						break;
				}

				myStack.push(respStack);
				myQueue.push(respQueue);
				mpq.push(respmpq);

			}else{
				int intd = stoi(d);
				myStack.push(intd);
				myQueue.push(intd);
				mpq.push(intd);
			}
		}
	cout<<myStack.top()<<" "<<myQueue.front()<<" "<<mpq.top()<<endl;
  	getline(cin, data);	
	}
	return 0;
}


