#include <iostream>
using namespace std;


int findName(string team, string teamNames[5], int numTeams){

	for(int i=0; i<numTeams; i++){

		if(team == teamNames[i])
			return i;
	}

	return 0;
}

int findProblem(string problem, string problems[2], int numProblems){

	for(int i=0; i<numProblems; i++){

		if(problem == problems[i])
			return i;
	}

	return 0;
}

void burbuja(int (&a)[5], int n)  {
     bool interruptor = true;
for (int pasada=0; pasada<n-1 && interruptor; pasada++) { 
      interruptor = false;   // no se han hecho intercambios
      for (int j=0; j<n-1-pasada; j++) 
          if (a[j+1] < a[j]) {  
              int tmp = a[j]; 
              a[j] = a[j+1]; 
              a[j+1] = tmp; 
			interruptor = true;
          } 
     } 
  }

void displayWinners(string teamNames[5], int score[5], int problemsSolved[5], int winners[5], int numTeams){

	for(int i=0; i<numTeams; i++){

		cout<<i+1<<" - "<<teamNames[winners[i]]<<" "<<problemsSolved[winners[i]]<<" ";
		if(score[winners[i]]==0)
			cout<<"-";
		else
			cout<<score[winners[i]];
		
		if(i!=numTeams)cout <<endl;
	
	}
}

int findWinners(string teamNames[5], int score[5], int numTeams, int problemsSolved[5],  int (&auxTimes)[5]){

	int counter = 0, counter2 = 0, repetitiveScores[5], winners[5], sortedProblemsSolved[5], aux = numTeams-1, indexWinners = 0, aux4 = 0;

	//making a copy of the problems solved array, because later on we are going to sort it
	for(int i=0; i<numTeams; i++){

		sortedProblemsSolved[i] = problemsSolved[i];
	}
	burbuja(sortedProblemsSolved, numTeams);

	char usedNumbers[5];
	for(int i=0; i<5; i++){
		usedNumbers[i] = 'N';
	}

	for(int iB=0; iB<numTeams; iB = iB+counter2){

		//this builds the repetitiveScores array with the index numbers of the teams with the same number of problems solved
		for(int i=numTeams-1, aux2=0; i>=0; i--){

			if(sortedProblemsSolved[aux] == problemsSolved[i]){

				if(sortedProblemsSolved[aux] == 0){

					for(int iC= 0; aux>=0; iC++){

						if(sortedProblemsSolved[aux] == problemsSolved[iC] && usedNumbers[iC] == 'N'){
							winners[indexWinners] = iC;
							usedNumbers[iC] = 'Y';
							aux--;
							iC=0;
							indexWinners++;
						}
					}
				}else{

					repetitiveScores[aux2] = i;
					aux2++;
					counter++;
				}
			}
		}	

		if(aux>0){

			counter2 = counter;
			aux = aux - counter;

			if(counter>1){

				//we create the times (scores) of all the teams with same # of problems solved, then we sort the array
				for(int i=0; i<counter; i++){
					auxTimes[i] = score[repetitiveScores[i]];
				}
				burbuja(auxTimes, counter);

				//we find the team for which the lowest times correspond, and we add them to the winners array
				for(int i=0, iA = 0; iA<counter; i++){

					if(auxTimes[iA] == score[repetitiveScores[aux4]]){

						if(usedNumbers[aux4] == 'N'){

							winners[indexWinners] = repetitiveScores[aux4];
							usedNumbers[repetitiveScores[aux4]] = 'Y';
							aux4 = 0;
							iA++;
							indexWinners++;

						}else
							aux4++;
					}else
						aux4++;
				}

			}else{
				winners[indexWinners] = repetitiveScores[0];
				indexWinners++;
			}

			counter = 0;

		}else
			iB = numTeams;
	}

	displayWinners(teamNames, score, problemsSolved, winners, numTeams);

	return 0;	
}

int main(){
	
	int numTeams, numProblems;

	cin>>numTeams>>numProblems;

	string teamNames[5], problems[2];
	int score[5], problemsSolved[5], numberTries[5][2], problemsAccepted, winners[5], auxTimes[5];

	//read all the team's names
	for(int aux=0; aux<numTeams; aux++){
		cin>>teamNames[aux];
	}

	cin>>problemsAccepted;

	for(int aux=0; aux < problemsAccepted; aux++){

		string team, problem;
		int timeTaken, nameIndex, problemIndex;
		char accepted;

		cin>>team>>problem>>timeTaken>>accepted;

		if(accepted == 'A'){

			//I find the team's name of the given solution in the teamNames array, 
			//the same with which problem they actually solved  

			nameIndex = findName(team, teamNames, numTeams);
			problemIndex = findProblem(problem, problems, numProblems);

			//now that I know the team's name and the problem solved
			//I add the time they took to solve the problem (plus any penalties if necessary)
			//finally, I increment the number of problems solved by the given team

			score[nameIndex] = score[nameIndex] + timeTaken + (numberTries[nameIndex][problemIndex] * 20);
			problemsSolved[nameIndex]++;
		}
		else{

			//we just need to increment the number of tries the given team has tried to solve the given problem

			nameIndex = findName(team, teamNames, numTeams);
			problemIndex = findProblem(problem, problems, numProblems);
			numberTries[nameIndex][problemIndex]++;
		}

	}

	findWinners(teamNames, score, numTeams, problemsSolved, auxTimes);

	return 0;
}