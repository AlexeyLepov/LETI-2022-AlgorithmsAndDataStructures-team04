///////////////////////////////
//                           //
//    ///////////////////    //
//    //               //    //
//    //    Массивы    //    //
//    //               //    //
//    ///////////////////    //
//                           //
///////////////////////////////

#include <iostream>
#include <string.h>
#include <algorithm>

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


int main(){
    char A[26], B[26], C[26], D[26], *notC, *AandB, *AandBnotC, *AandBnotCorD;


    int i, j, nA, nB, nAB=0, m, nABC=0, nC, nD, nABCD = 0;

    bool kond1, kond2;


    cout << "input A : ";
    cin >> A;
    cout << "\ninput B : ";
    cin >> B;
    cout << "\ninput C : ";
    cin >> C;
    cout << "\ninput D : ";
    cin >> D;

    nA = strlen(A);
    nB = strlen(B);
    nC = strlen(C);
    nD = strlen(D);

    
    nAB = num_of_elements_and(A,B,nA,nB);

    //cout << "nAB = " << nAB << endl;

    nAB == 0 ? kond1 = false : kond1 =true;

    //cout << "nAB = " << nAB << endl;

    if (kond1){
        AandB = new char [nAB];
        
        m=0;

        for (i=0;i<nA;i++)
        {
            for(j=0;j<nB;j++)
            {
                if (A[i]==B[j])
                {
                    AandB[m]=A[i];
                    m++;
                }     
            }
        }

        cout << "AandB = " << AandB << endl;

        nABC=nAB;

        //cout << "nABC1 = " << nABC << endl;

        for (i=0;i<nAB;i++)
        {
            for (j=0;j<nC;j++)
            {
                if (AandB[i]==C[j])
                    nABC--;
            }
        }

        //cout << "nABC2 = " << nABC << endl;

        nABC == 0 ? kond2 = false : kond2 = true;

        if (kond2){

            AandBnotC = new char [nABC];
            for (i=0;i<nAB;i++)
            {
                for (j=0;j<nC;j++)
                {
                    if (AandB[i]==C[j])
                        AandB[i]='*';
                }
            }
            m=0;
            for (i=0;i<nAB;i++)
            {
                if (AandB[i]!='*')
                {
                    AandBnotC[m]=AandB[i];
                    m++;
                }
            }

            cout << "AandBnotC = " << AandBnotC << endl;
        }
    } else nABC = nAB;
    
    m=nABC;
    nABCD=nABC+nD;

    //cout << "nABCD = " << nABCD <<  endl;
    
    for (i=0;i<nABC;i++){
        for (j=0;j<nD;j++){
            if (AandBnotC[i]==D[j]){
                D[j]='*';
                nABCD--;
            }
                
        }
    }

    //cout << "nABCD = " << nABCD <<  endl;

    AandBnotCorD = new char [nABCD];

    for (i=0;i<nABC;i++)
    {
        AandBnotCorD[i]=AandBnotC[i];
    }

    for (i=0;i<nD;i++)
    {
        if (D[i]!='*'){
            AandBnotCorD[m]=D[i];
            m++;
        }
    }
    //cout << nABC << endl;
    //cout << nABCD << endl;

    cout << "AandBnotCorD = ";
    for (i=0;i<nABCD;i++)
        cout << AandBnotCorD[i] << " ";
    
    // sort(AandBnotCorD, AandBnotCorD+nABCD);
    // for (i=0;i<nABCD;i++)
    //     cout << AandBnotCorD[i] << " ";

    if (kond1){
        delete []AandB;
        if (kond2)
            delete []AandBnotC;
    }
    delete []AandBnotCorD;

    return 0;
}