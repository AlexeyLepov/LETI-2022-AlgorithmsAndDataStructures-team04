#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Set
{
private:
    unsigned int wA;
public:
    Set() { wA=0;};
    Set(char A[]);
    void into_word(char A[]);
    void print_set();
    void print_set_bol();
    Set &operator &= (const Set&);
    Set operator & (const Set&) const;
    Set &operator |= (const Set &);
    Set operator| (const Set&) const;
    Set operator ~ () const;
    Set (const Set&);
    Set &operator= (const Set&);
};

void Set::print_set(){
    char U[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i=0, k=0; i<32; i++){
        if ((wA>>i)&1==1){
            cout << U[i];
        }
    }
}

void Set::into_word(char A[]){
    wA=0;
    for (int i=0; A[i]; ++i){
        wA|=(1<<(A[i]-'a'));
    }
}

Set :: Set(const Set&B){
    wA=B.wA;
}

Set :: Set(char A[]){
    into_word(A);
}

void Set::print_set_bol(){
    bool bA[32];
    unsigned int wwA = wA;
    for (int i =0; i< 32; i++) bA[i]=0;
    for (int i =0; i<32; i++) {bA[i] = wwA%2; wwA= wwA/2;}
    for (int i =31; i>=0; i--) cout << bA[i] << " ";
    cout << endl;
}

Set&Set :: operator= (const Set&B){
    wA=B.wA;
    return *this;
}

Set&Set :: operator&=(const Set &B){
    Set C(*this);
    wA=C.wA&B.wA;
    return *this;
}

Set Set :: operator & (const Set &B) const{
    Set C(*this);
    return (C&=B);
}

Set & Set :: operator|= (const Set&B){
    Set C(*this);
    wA=C.wA|B.wA;
    return *this;
}

Set Set :: operator| (const Set&B) const{
    Set C(*this);
    return (C|=B);
}

Set Set :: operator~() const{
    Set C;
    C.wA=~wA;
    return C;
}

void checking (char A[]){
    for (int i = 0; i< strlen(A); i++){
        if ((A[i]>'z') || (A[i]<'a')){
            cout << A << endl;
            while ((A[i]>'z') || (A[i]<'a')){
                cout << "simbol[" << i << "] = " << A[i] << " is not lat lowercase letter, please, enter new : ";
                cin >> A[i];
                cout << endl;
            }
        }
    }
}

char *delete_repet (char A[]){
    int rep[26];
    int s=0, k=0;
    char *B = nullptr;
    for (int i =0; i< strlen(A); i++) rep[A[i]-97]=0;
    for (int i =0; i< strlen(A); i++){
        rep[A[i]-97]++;
    }
    for (int i =0; i< strlen(A); i++){
        if (rep[A[i]-97]>1){
            rep[A[i]-97]--;
            A[i] = '*';
        }
    }
    A[strlen(A)] = 0;
    B=new char [26];
    for (int i=0; i<strlen(A); i++) if (A[i]!='*') B[k++] = A[i];
    B[k]=0;
    return B;
}

int main(){

    char *M1, *M2, *M3, *M4;
    M1 = new char[26];
    M2 = new char[26];
    M3 = new char[26];
    M4 = new char[26];

    cout << "enter M1: ";
    cin >> M1;
    checking(M1);
    M1 = delete_repet(M1);
    cout << "enter M2: ";
    cin >> M2;
    checking(M2);
    M2 = delete_repet(M2);
    cout << "enter M3: ";
    cin >> M3;
    checking(M3);
    M3 = delete_repet(M3);
    cout << "enter M4: ";
    cin >> M4;
    checking(M4);
    M4 = delete_repet(M4);
    cout << endl;

    Set S1(M1), S2(M2), S3(M3), S4(M4), E;
    cout << "\n-----\n";
    cout << "A and B = ";
    (S1&S2).print_set();
    cout << endl;
    cout << "A and B not C = ";
    ((S1&S2)&~S3).print_set();
    cout << endl;
    E = ((S1&S2)&~S3)|S4;
    E.print_set();
     delete [] M1;
     delete [] M2;
     delete [] M3;
     delete [] M4;
    return 0;
}
