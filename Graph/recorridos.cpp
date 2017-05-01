#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

void anchura(bool mat[20][20], int n){
	queue <int> q;
	q.push(0);
	vector <bool> v(n,0); //para incializar en zeros
	v[0] = true;
	int out;

	while(!q.empty()){
		out = q.front();
		q.pop();
		for(int i=0; i<n; i++){
			if(mat[out][i] && !v[i]){
				q.push(i);
				v[i] = true;
			}
		}
	}
	cout<<endl;
}

void profundidad(bool mat[20][20], int n){
	stack <int> s;
	s.push(0);
	vector<bool> v(n,0);
	int out;

	while(!s.empty()){
		out = s.top();
		s.pop();
		if(!v[out]){
			cout<<(out+1)<<" ";
			v[out] = true;
			for(int i = n-1; i>=0; i--){
				if(!v[i] && mat[out][i]){
					s.push(i);
				}
			}
		}
	}
	cout<<endl;
}

int main(){

	bool mat[20][20];
	int n;
	cin>>n;

	for(int i =0; i<n; i++){
		for(int j=0; j<n; j++){
			cin>>mat[i][j];
		}
	}

	for(int i =0; i<n; i++){
		for(int j=0; j<n; j++){
			cout<<mat[i][j];
		}
		cout<<endl;
	}

	profundidad(mat,n);
	return 0;
}