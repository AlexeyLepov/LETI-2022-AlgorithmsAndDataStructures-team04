////////////////////////////////////////////
//                                        //
//    Выполнили студенты, гр. 1308:       //
//    Мельник Д. А.                       //
//    Лепов А. В.                         //
//                                        //
////////////////////////////////////////////
///////////////////////////////////
//                               //
//    Работа с массивом битов    //
//                               //
///////////////////////////////////

#include <iostream>
#include<bitset>
#include<iomanip>
#include<string.h>

using namespace std;

bitset<26> into_bitset(char A[]){
    bitset<26> bA=0;
    for (int i=0; i<strlen(A); i++){
        bA[A[i]-'a'] = 1;
    }
    return bA;
}

int main()
{
    bitset<26> bA=0;
    bitset<26> bB=0;
    bitset<26> bC=0;
    bitset<26> bD=0;
    bitset<26> bE=0;
    char U[] = "abcdefghijklmnopqrstuvwxyz";
    char A[10],B[10],C[10],D[10], E[10]="";
    int m = 26;
    cout << "Enter A B C D:" << endl;
    cin >> A >> B >> C >> D;

    bA=into_bitset(A);
    bB=into_bitset(B);
    bC=into_bitset(C);
    bD=into_bitset(D);

    cout << "bA = " <<  bA << endl;
    cout << "bB = " <<  bB << endl;
    cout << "bC = " <<  bC << endl;
    cout << "bD = " <<  bD << endl;

    //enh
    
    for (int i=0;i<m;i++){
        bE[i]=bA[i]*bB[i];
    }
    cout << "A and B = " << bE << endl;

    for (int i=0;i<m;i++){
        bE[i]=bE[i]&&~bC[i];
         if (bE[i]==(-1))
             bE[i]=0;
    }
    cout << "A and B without C = " << bE << endl;

    for (int i=0;i<m;i++){
        bE[i]=bE[i]|bD[i];
    }

    cout << "A and B without C or D = " << bE << endl;

    cout << "result: ";

    for (int i =0, k = 0;i<m;i++){
        if (bE[i]==1){
            E[k]=U[i];
            k++;
        }
    }
    cout << E << endl;
    return 0;
}