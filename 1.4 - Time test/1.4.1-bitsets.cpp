#include <iostream>
#include<bitset>
#include<iomanip>
#include<string.h>

using namespace std;

bitset<26> random_array (int n){
    bitset<26> bA=0;
    int i;
    for (int m=0; m<n; m++){
        i = rand()%26;
        bA[i]=1;
    }
    return bA;
}

void print_word (bitset<26> bE, char U[]){
    char E[26];
    int m=26;
    for (int i =0, k = 0;i<m;i++){
        if (bE[i]==1){
            E[k]=U[i];
            k++;
        }
    }
    cout << E << endl;
}

int main()
{
    bitset<26> bA=0;
    bitset<26> bB=0;
    bitset<26> bC=0;
    bitset<26> bD=0;
    bitset<26> bE=0;
    char U[] = "abcdefghijklmnopqrstuvwxyz";
    int m = 26;

    clock_t t;
    float s=0;

    for (int k=0;k<1000000;k++){

        t=0;
        t=clock();

        bA=random_array(5);
        bB=random_array(8);
        bC=random_array(5);
        bD=random_array(2);
        
    // cout << "bA = ";
    // print_word(bA,U);
        //cout << "bB = ";
        //print_word(bB,U);
        //cout << "bC = ";
        //print_word(bC,U);
        //cout << "bD = ";
        //print_word(bD,U);

        for (int i=0;i<m;i++){
            bE[i]=bA[i]*bB[i];
        }
        //cout << "A and B = ";
        //print_word(bE,U);

        for (int i=0;i<m;i++){
            bE[i]=bE[i]&&~bC[i];
            if (bE[i]==(-1))
                bE[i]=0;
        }
        //cout << "A and B without C = ";
        //print_word(bE,U);
        for (int i=0;i<m;i++){
            bE[i]=bE[i]|bD[i];
        }
        //cout << "A and B without C or D = ";
        //print_word(bE,U);
        t=clock()-t;
        s+=t;
        cout<<endl;
    }
    cout<<"=="<<(s/1000000)*0.017 << endl;
    return 0;
}