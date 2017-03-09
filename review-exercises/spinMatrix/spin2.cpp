#include <iostream>
using namespace std;

const int N=4;

void spinMAtrix(int (&matA)[N][N], int  (&matB)[N][N], int rotations){
    
    int colA = 0;
    int rowA = 0;
    
    int colB = N-1;
    int rowB = 0;
    
    for(int aux = rotations; aux>0; aux--){
        
        for(int iA=0; iA<N; iA++){
            
            for(int iB=0; iB<N; iB++){
                
                matB[rowB][colB] = matA[rowA][colA];
            
                colA++;
                rowB++;   
            }

            colA=0;
            rowB=0;
            rowA++;
            colB--;
        }

        rowA = 0;
        colB = N-1;
        
        for(int i = 0; i<N;i++){
            
            for(int j=0; j<N;j++){
                
                matA[i][j] = matB[i][j];
            }
        }
    }
}

using namespace std;

int main() {
    
    int matA[N][N];
    int matB[N][N];
    int rotations;

    cin>>rotations;
    rotations = rotations%4;
    rotations = (rotations < 0) ? rotations + 4 : rotations;
    
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            cin>>matA[i][j];
        }
    }   
    
    if(rotations!=0)   
        spinMAtrix(matA, matB, rotations); 

    if(rotations!=0){
        for(int i = 0; i<N; i++){
            for(int j = 0; j<N; j++){
                cout<<matB[i][j];
                if(j<3)
                    cout<<" ";
            }
                cout<<endl;
        }
    }else{
        for(int i = 0; i<N; i++){
            for(int j = 0; j<N; j++){
                cout<<matA[i][j];
                if(j<3)
                    cout<<" ";
            }
                cout<<endl;
    }
}
       //1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
  
    return 0;
}
