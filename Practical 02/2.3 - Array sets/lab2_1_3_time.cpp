#include <iostream>
#include <cstring>

using namespace std;

class Set
{
private:
    bool bA[26];
public:
    Set(char A[]);
    Set() {for (int i=0; i<26; i++) bA[i]=0;};
    //~Set();
    void into_bitset(char A[]);
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

Set :: Set(char A[]){
    for (int i=0; i<26; i++) bA[i]=0;
    into_bitset(A);
}



void Set :: print_set (){
    char U[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i =0, k=0; i<26;i++) {if (bA[i]==1) cout<<U[i];};
    cout << endl;
}

void Set :: print_set_bol (){
    for (int i =0; i<26;i++) cout << bA[i] << " ";
    cout << endl;
}

void Set :: into_bitset(char A[]){
    for (int i=0; i<26; i++) bA[i]=0;
    for (int i=0; i<strlen(A); i++){
        bA[A[i]-'a'] = 1;
    }
}

Set :: Set(const Set&B){
    for (int i=0; i<26; i++) bA[i]=B.bA[i]; 
}

Set&Set :: operator= (const Set&B){
    for (int i=0; i<26;i++){
        bA[i]=B.bA[i];
    }
    return *this;
}

Set&Set :: operator&=(const Set &B){
    Set C(*this);
    for (int i=0; i<26; i++){
        if ((C.bA[i]==1)&&(B.bA[i]==1)) bA[i]=1;
        else bA[i]=0;
    }
    return *this;
}
Set Set :: operator & (const Set &B) const{
    Set C(*this);
    return (C&=B);
}

Set&Set :: operator|=(const Set &B){
    Set C(*this);
    for (int i=0; i<26; i++){
        if ((C.bA[i]==0)&&(B.bA[i]==1)) bA[i]=1;
        if ((C.bA[i]==1)&&(B.bA[i]==1)) bA[i]=1;
        if ((C.bA[i]==1)&&(B.bA[i]==0)) bA[i]=1;
        if ((C.bA[i]==0)&&(B.bA[i]==0)) bA[i]=0;

    }
    return *this;
}
Set Set :: operator | (const Set &B) const{
    Set C(*this);
    return (C|=B);
}

Set Set :: operator~() const{
    Set C;
    for (int i=0; i<26; i++){
        if (bA[i]==1) C.bA[i]=0;
        if (bA[i]==0) C.bA[i]=1;
    }
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

    char M1[]="abcde", M2[]="fcde", M3[]="ckm", M4[]="twd";
    clock_t t;
    float s=0;
    for (int i =0; i<100000; i++){
        t=0;
        t=clock(); 
        Set S1(M1), S2(M2), S3(M3), S4(M4), E;
        E = ((S1&S2)&~S3)|S4;
        t=clock()-t;
        s+=t;
    }
    cout << ((s/100000)*0.017) << endl;
    return 0;
}

