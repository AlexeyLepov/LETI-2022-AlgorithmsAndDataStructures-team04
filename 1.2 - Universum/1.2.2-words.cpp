//////////////////////////////////////
//                                  //
//    //////////////////////////    //
//    //                      //    //
//    //    Машинные слова    //    //
//    //                      //    //
//    //////////////////////////    //
//                                  //
//////////////////////////////////////

#include <iostream>

using namespace std;

unsigned int into_word (char A[]){
    unsigned int wA=0;
    for (int i=0; A[i]; ++i){
        wA|=(1<<(A[i]-'a'));
    }
    return wA;
}

void bin_print(unsigned int wA){
    int binstr[32];
    for (int i=0; i<32; i++){
            binstr[i]=0;
            binstr[i]=wA%2;
            wA=wA/2;
    }
    for (int i =31; i>-1; i--)
        cout << binstr[i];
    cout << endl;
}

int main(){
    char U[] = "abcdefghijklmnopqrstuvwxyz";
    char A[10], B[10], C[10]="", D[10], E[10]="" ;
    unsigned int wA=0, wB=0, wC=0, wD=0, wE=0, wW=0, wE1;
    int m=32;
    cout << "Enter A B C D:" << endl;
    cin >> A >> B >> C >> D;
    wA=into_word(A);
    wB=into_word(B);
    wC=into_word(C);
    wD=into_word(D);

    cout << "A            = ";
    bin_print(wA);
    cout << "B            = ";
    bin_print(wB);
    cout << "C            = ";
    bin_print(wC);
    cout << "D            = ";
    bin_print(wD);
    cout << "AandB        = ";
    bin_print(wA&wB);
    cout << "AandBnotC    = ";
    bin_print ((wA&wB)&~wC);
    cout << "AandBnotCorD = ";
    bin_print (((wA&wB)&~wC)|wD);

    wE=((wA&wB)&~wC)|wD;

    for (int i=0, k=0; i<m; i++){
        if ((wE>>i)&1==1){
            E[k++]=U[i];
        }
    }
    cout << "result = " << E << endl;
}