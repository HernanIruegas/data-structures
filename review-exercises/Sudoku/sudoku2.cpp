#include <iostream>
using namespace std;


int main() 
{
	int sudoku[9][9];
	int aux[9];
	int counter;

	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
			cin >> sudoku[j][i];

		aux[i] = 0;
	}		

	for (int i = 0; i<9; i++){

		for (int j = 0; j < 9; j++)
			aux[sudoku[j][i] - 1]++;
	}
			
	char chCond = 's';
	for (int i = 0; i < 9; i++){ //Primero revisa que hayan 9 de cada digito del 1 al 9 en toda la matriz de 9x9
		
		if (aux[i] != 9)
			chCond = 'n';
	}
		
	if (chCond == 's'){ //Luego revisa que la suma de todos los digitos de cada columna y de cada fila de 45
	
		int i = 0;

		while (i < 9 && chCond == 's'){

			counter = 0;

			for (int j = 0; j < 9; j++)
				counter+=sudoku[j][i];

			if (counter != 45)
				chCond = 'n';

			i++;
		}

		i = 0;
		while (i < 9 && chCond == 's'){

			counter = 0;

			for (int j = 0; j < 9; j++)
				counter+=sudoku[i][j];

			if (counter != 45)
				chCond = 'n';

			i++;
		}

		int n = 0;
		while (chCond == 's' && n < 9){ //Finalmente revisa que la suma de todos los numeros de cada submatriz 3x3 de 45
		
			int m = 0;	
			while (chCond == 's' && m < 9){

			int auxcum = 0;
			for (int x = 0; x < 3; x++){
				for (int w = m; w < m + 3; w++)
				auxcum+=sudoku[w][x];
			}
			
			if (auxcum != 45)
				chCond = 'n';

			m += 3;
			}
		n+=3;
		}
	}

	if (chCond == 's')
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	return 0;
}