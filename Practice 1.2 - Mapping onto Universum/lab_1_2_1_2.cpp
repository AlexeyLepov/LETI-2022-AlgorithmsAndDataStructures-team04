#include <iostream>

using namespace std;

unsigned int into_word (char A[]){
    unsigned int wA=0;
    for (int i=0; A[i]; ++i){
        wA|=(1<<(A[i]-'a'));
    }
    return wA;
}
int main(){
    char U[] = "abcdefghijklmnopqrstuvwxyz";
    char A[10], B[10], C[10]="", D[10], E[10]="";
    unsigned int wA=0, wB=0, wC=0, wD=0, wE=0;
    int m=32;
    cout << "Enter A B C D:" << endl;
    cin >> A >> B >> C >> D;
    wA=into_word(A);
    wB=into_word(B);
    wC=into_word(C);
    wD=into_word(D);
    wE=((wA&wB)&~wC)|wD; // so small...
    for (int i=0, k=0; i<m; i++){
        if ((wE>>i)&1==1){
            E[k++]=U[i];
        }
    }
    cout << E << endl;
}