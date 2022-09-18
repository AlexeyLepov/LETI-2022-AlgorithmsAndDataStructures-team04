#include <iostream>
#include <string.h>

using namespace std;

int num_of_elements_and (char A[], char B[], int nA, int nB){
    int nAB=0, i, j;
    for (i=0;i<nA;i++){
        for(j=0;j<nB;j++){
            if (A[i]==B[j])
                nAB++;
        }
    }
    return nAB;
}

int num_of_elements_or (char A[], char B[], int nA, int nB){
    int nABCD=0, i, j;
    for (i=0;i<nA;i++){
        for (j=0;j<nB;j++){
            if (A[i]!=B[j])
                nABCD++;
        }
    }
    return nABCD;
}

int num_of_strelements (char A[]){
    int nE =0, i;
    while (A[i]!='\0'){
        nE++;
        i++;
    }
    return nE;
}

int main(){
    char A[80], B[80], C[80], D[80], *notC, *AandB, *AandBnotC, *AandBnotCorD;

    int i, j, nA, nB, nAB=0, m, nABC=0, nC, nD, nABCD = 0;


    cin >> A;
    cin >> B;
    cin >> C;
    cin >> D;

    nA = strlen(A);
    nB = strlen(B);
    nC = strlen(C);
    nD = strlen(D);

    

    cout << "A = " << nA << " B = " << nB << " nC = " << nC << " nD = " << nD;
    /*nAB = num_of_elements_and(A,B,nA,nB);
    AandB = new char [nAB];
    
    m=0;

    for (i=0;i<nA;i++){
        for(j=0;j<nB;j++){
            if (A[i]==B[j]){
                AandB[m]=A[i];
                m++;
            }     
        }
    }
    nABC=nAB;
    for (i=0;i<nAB;i++){
        for (j=0;j<nC;j++){
            if (AandB[i]==C[j])
                nABC--;
        }
    }
    AandBnotC = new char [nABC];
    for (i=0;i<nAB;i++){
        for (j=0;j<nC;j++){
            if (AandB[i]==C[j])
                AandB[i]='*';
        }
    }
    m=0;
    for (i=0;i<nAB;i++){
        if (AandB[i]!='*'){
            AandBnotC[m]=AandB[i];
            m++;
        }
    }
    nABCD = num_of_elements_or(AandBnotC,D,nABC,nD);
    nABCD+=nABC;
    AandBnotCorD = new char [nABCD];
    m=nABC;
    for (i=0;i<nABC;i++){
        AandBnotCorD[i]=AandBnotC[i];
    }
    for (i=0;i<nABC;i++){
        for (j=0;j<nD;j++){
            if (AandBnotC[i]!=D[j]){
                AandBnotCorD[m]=D[j];
                m++;
            }
        }
    }
    cout << nABCD << endl;
    for (i=0;i<nABCD;i++)
        cout << AandBnotCorD[i] << " ";
    delete []AandB;
    delete []AandBnotC;
    delete []AandBnotCorD;*/

    
    return 0;
}