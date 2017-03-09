#include <iostream>
using namespace std;

int const N = 9;

void display(int iMatA[][N])
{
    cout<<"    ";
    for(int iC=0; iC<N; iC++)
        cout << iC <<"\t";
    cout<<"\n";
    for(int iC=0; iC<N; iC++)
        cout << "_____";
    cout<<"\n";
    for (int iR=0; iR<N; iR++)
    {
        cout<<iR<<"|";
        for(int iC=0; iC<N; iC++)
            cout <<"\t"<< iMatA[iR][iC];
        cout<<"\n";
    }
}

bool rows(int mat[][N]){

	int auxCol = 0;
	int auxRow = 0;

	for(int reps=0; reps < N; reps++){

		for(int i = 0; i< N ; i ++){

			for(int j = auxCol+1; j<N; j++){
			
				if(mat[auxRow][auxCol] == mat[auxRow][j])
					return false;
			}
			auxCol++;
		}
		auxRow++;
		auxCol = 0;
	}

	return true;
}


bool columns(int mat[][N]){

	int auxCol = 0;
	int auxRow = 0;

	for(int reps=0; reps < N; reps++){

		for(int j = 0; j< N ; j ++){

			for(int i = auxRow+1; i<N; i++){
			
				if(mat[auxRow][auxCol] == mat[i][auxCol])
					return false;
			}
			auxRow++;
		}
		auxCol++;
		auxRow = 0;
	}

	return true;
}


bool miniMatrix(int mat[][N]){

int numbers[] = {0,0,0,0,0,0,0,0,0};
int miniIndex = 3;
int counter = 0;
int aux2 = 0;

int coordinates[] = {0,3,6};
int indexOnRow = 0;
int indexOnCol = 0;

int aux3=3;
int aux4=3;

/***to control coordinates on 9 X 9 matrix, in order to shift 3 X 3 matrix************************/
for(int i = 0; i < 3; i++){

	indexOnRow = coordinates[i];

	if(indexOnRow == 0)
			aux4=3;

	for(int aux = 0; aux < 3; aux++){

		indexOnCol = coordinates[aux];

		if(indexOnCol == 0)
			aux3=3;

		cout<<coordinates[aux]<<endl;
/***************************/

		//recorrido matriz 3X3
		for(int i=indexOnRow; i < aux4; i++){

			for(int j=indexOnCol; j<aux3; j++){

				cout<<i<<" "<<j<<endl;

				for(int aux=0; aux<9; aux++){

					if(mat[i][j] != numbers[aux])
						counter++;

				}

				if(counter == 9){
					numbers[aux2] = mat[i][j];
					aux2++;
				}
				else
					return false;

				counter = 0 ;
			}

		}
		//restart array in zeroes
		for(int i=0; i<9; i++){
			numbers[i] = 0;
		}
		aux3+=3;
	}
	aux4+=3;

}

return true;

}



int main(){

	int mat[N][N];
	int rowIndex = 0;
	int colIndex = 0;

	for(int i =0; i<N; i++){

		for(int j=0; j<N; j++){

			cin>>mat[i][j];			
		}
	}

	display(mat);

	/*
	if(rows(mat))
		cout<<"si jalo"<<endl;
	else
		cout<<"no jalo"<<endl;

	if(columns(mat))
		cout<<"si jalo"<<endl;
	else
		cout<<"no jalo"<<endl;

	if(miniMatrix(mat))
		cout<<"si jalo"<<endl;
	else
		cout<<"no jalo"<<endl;

	*/

	if(rows(mat) && columns(mat))
		cout<<"es aceptado"<<endl;
	else
		cout<<"no es aceptado"<<endl;
	


	
	
	return 0;
}