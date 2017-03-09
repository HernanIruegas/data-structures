#include <iostream>
using namespace std;

int main() {
	
	int T, P, S, iTiempo, iAux;
	char chEstado, chProblema;

	cin >> T >> P;

	int iWA[P][T];
	string sNombre, sAux, sArrNombres[T];

	for (int m = 0; m < T; m++){
		for (int n = 0; n < P; n++)
		iWA[n][m] = 0;	
	}

	int iArrTiempos[T], iArrAceptados[T];
	for (int i = 0; i < T; i++){
		cin >> sArrNombres[i];
		iArrTiempos[i] = 0;
		iArrAceptados[i] = 0;
	}	

	cin >> S; 
	for (int i = 0; i < S; i++){

		cin >> sNombre >>  chProblema >> iTiempo >> chEstado;
		int j = 0;

		while(sNombre != sArrNombres[j])
			j++;

		iAux = chProblema - 65;
		if (chEstado == 'A'){

			iArrTiempos[j] += (iTiempo + (iWA[iAux][j]*20)); 
			iArrAceptados[j]++;	
		}
		else
			iWA[iAux][j]++; 
	}

	bool Aux;
	for (int x = 0; x < T - 1; x++){
		for (int y = x+1; y < T; y++){  

			Aux = false;
			if(iArrAceptados[y] > iArrAceptados[x]) 
				Aux = true;		
			else{
			 if(iArrAceptados[x] == iArrAceptados[y]) 
				if(iArrTiempos[y] < iArrTiempos[x])
				 Aux = true;
			}

			if(Aux){
				iAux = iArrAceptados[x];
				iArrAceptados[x] = iArrAceptados[y];
				iArrAceptados[y] = iAux;
				iAux = iArrTiempos[x];
				iArrTiempos[x] = iArrTiempos[y];
				iArrTiempos[y] = iAux;
				sAux = sArrNombres[x];
				sArrNombres[x] = sArrNombres[y];
				sArrNombres[y] = sAux;
			}
		}
	}


	for (int h = 0; h < T; h++){
		cout << h+1 << " - " << sArrNombres[h] << " " << iArrAceptados[h] << " "; 
		if(iArrTiempos[h] == 0) 
			cout << '-' << endl; 
		else 
			cout << iArrTiempos[h] << endl;
	}

}









