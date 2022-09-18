#include <iostream>
#include <time.h>

using namespace std;

void print_word(unsigned int wA, char U[]){
    char A[26]="";
    int m=32;
    for (int i=0, k=0; i<m; i++){
        if ((wA>>i)&1==1){
            A[k++]=U[i];
        }
    }
    cout << A << endl;
}
int main(){
    srand(time(0));
    char U[] = "abcdefghijklmnopqrstuvwxyz";
    char E[26]="", A[26]="", B[26]="", C[26]="", D[26]="";
    unsigned int wA=0, wB=0, wC=0, wD=0, wE=0;
    int m=32;

    wA=(long)(rand()%16)|rand();
    wB=(long)(rand()%16)|rand();
    wC=(long)(rand()%16)|rand();
    wD=(long)(rand()%16)|rand();

    cout << "A = ";
    print_word(wA, U);
    cout << "B = ";
    print_word(wB, U);
    cout << "C = ";
    print_word(wC, U);
    cout << "D = ";
    print_word(wD, U);

    wE=((wA&wB)&~wC)|wD; // so small...
    print_word(wE,U);
}