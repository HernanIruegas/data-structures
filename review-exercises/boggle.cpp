#include <iostream>
#include <utility>
#include <map>
#include <iomanip>
using namespace std;

bool adjacentCell(char matrix[4][4], int row, int column, int row2, int column2){

	if(row == row2 && column + 1 == column2) return true;
	if(row == row2 && column - 1 == column2) return true;
	if(row + 1 == row2 && column == column2) return true;
	if(row - 1 == row2 && column == column2) return true;
	if(row - 1 == row2 && column + 1 == column2) return true;
	if(row + 1 == row2 && column + 1 == column2) return true;
	if(row - 1 == row2 && column - 1 == column2) return true;
	if(row + 1 == row2 && column - 1 == column2) return true;

	return false;
}

bool acceptable(string word, char matrix[4][4]){

	int row, column, aux=0, row2, column2;

	while(aux <= word.length()){
		bool found = false;
		for(int i = 0; i<4; i++){
			for(int j = 0; j<4; j++){
				if(matrix[i][j] == word[0] && aux == 0){
					row = i;
					column = j;
					aux++;
					found = true;
				}
				if(matrix[i][j] == word[aux] && aux > 0){
					row2 = i;
					column2 = j;
					if(adjacentCell(matrix, row, column, row2, column2)){
						row = row2;
						column = column2;
						found = true;
						aux++;
					}
				}
			}
		}
		if(!found) break; //no encontro la letra
	}
	if(aux == word.length()) return true;
	return false;
}

int main(){

	int games, words, points, aux = 1, aux2, aux3 = 0;
	map<int,int> m;
	string word, row, validWords[20];
	char matrix[4][4];
	cin>>games;
	aux2 = games;
	
	while(games){
		for(int i = 0; i<4; i++){
			cin>>row;
			for(int j = 0; j<4; j++){
				matrix[i][j] = row[j];
			}
		}
		cin>>words;
		while(words){
			cin>>word;
			if(word.length() > 2 && acceptable(word, matrix)){
				bool repeated = false;
				for(int i = 0; i <= aux3; i++){
					if(validWords[i] == word)
						repeated = true;
				}
				if(!repeated){
					validWords[aux3] = word;
					aux3++;
					switch(word.length()){
						case 3: 
							points+= 1;
							break;
						case 4: 
							points+= 1;
							break;
						case 5: 
							points+= 2;
							break;
						case 6: 
							points+= 3;
							break;
						case 7: 
							points+= 5;
							break;
						default: 
							points+= 11;
							break;
					}
				}
			}
			words--;
		}
		for(int i = 0; i<=aux3; i++){
			validWords[i] = " ";
		}
		m[aux] = points;
		points = 0;
		aux++;
		games--;
		aux3 = 0;
	}

	for(int i = 1; i<=aux2; i++){
		cout<<"Game "<< i <<": "<<m[i]<<endl; 
	}
	
	return 0;
}


//cout<<"i0: "<<i<<"j0:"<<j<<endl;




