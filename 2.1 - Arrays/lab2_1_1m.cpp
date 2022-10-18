#include <iostream>
#include <cstring>

using namespace std;

class Set
{
private:
    int n;
    char *M;
public:
    Set(char *A) {n=strlen(A);M=A;};
    Set() {n=0;M=new char[26];}
    ~Set(){};
    void print_set () {cout << M <<  endl;}
    Set &operator &= (const Set&);
    Set operator & (const Set&) const;
    Set &operator |= (const Set &);
    Set operator| (const Set&) const;
    Set operator ~ () const;
    Set (const Set&);
    Set &operator= (const Set&);

};

Set :: Set(const Set&B): n(B.n), M(new char[n+1]){
    char *dst(M), *src(B.M);
    while (*dst++ = *src++);
}

Set&Set :: operator= (const Set&B){
    n=B.n;
    char *M1=new char [strlen(B.M)];
    for (int i=0; i<strlen(B.M);i++){
        M1[i]=B.M[i];
    }
    M=M1;
    return *this;
}

Set&Set :: operator&=(const Set &B){
    Set C(*this);
    n=0;
    for (int i=0; i<C.n; i++){
        for (int j=0; j<B.n; j++)
            if (C.M[i]==B.M[j]) M[n++] = C.M[i];
    }
    M[n]=0;
    return *this;
}
Set Set :: operator & (const Set &B) const{
    Set C(*this);
    return (C&=B);
}

Set & Set :: operator|= (const Set&B){
    for (int i =0; i<B.n;i++){
        bool f= true;
        for (int j=0; j<n;j++)
            if (B.M[i]==M[j]) f =false;
        if (f) M[n++] = B.M[i];
    }
    M[n]=0;
    return *this;
}

Set Set :: operator| (const Set&B) const{
    Set C(*this);
    return (C|=B);
}

Set Set :: operator~ () const{
    Set C;

    for (char c='a'; c<= 'z'; ++c){
        bool f =true;
        for (int j=0; j<n;++j)
            if (c==M[j]) {f = false; break;}
        if (f) {
            C.M[C.n] = c;
            C.n++;
        }
    }
    C.M[C.n] = 0;
    return C;
}


void checking (char A[]){
    for (int i = 0; i< strlen(A); i++){
        if ((int(A[i])>int('z')) || (int(A[i])<int('a'))){
            cout << A << endl;
            while ((int(A[i])>int('z')) || (int(A[i])<int('a'))){
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
