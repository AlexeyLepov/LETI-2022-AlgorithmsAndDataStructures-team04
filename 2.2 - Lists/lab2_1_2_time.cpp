#include <iostream>
#include <cstring>

using namespace std;

struct Set_node{
    char A;
    Set_node *next;
    Set_node *prew;
};

class Set
{
private:
    int n;
    Set_node *first;
    Set_node *last;
public:
    Set_node *make_node(char simbol);
    Set(char M[]);
    void add_node(Set_node *neww, Set_node *node0);
    void make_list (char M[]);
    void add_first(Set_node *f);
    void print_set();
     Set &operator &= (const Set&);
     Set operator & (const Set&) const;
     Set();
     Set &operator |= (const Set &);
     Set operator| (const Set&) const;
     Set operator ~ () const;
     void deleeete (char g);
     Set (const Set&);
     Set &operator= (const Set&);
};

Set :: Set(){
    first = nullptr;
    last=nullptr;
    n=0;
}

Set :: Set(char M[]){
    n=strlen(M);
    make_list(M);
}

Set_node* Set :: make_node (char simbol){
    Set_node *neww;
    neww = new Set_node;

    neww->A = simbol;
    neww->next = nullptr;
    neww->prew = nullptr;
    return neww;
}

void Set::add_node(Set_node *neww, Set_node *node0){
    node0->next=neww;
    neww->prew=node0;
    last = neww;
}

void Set::add_first(Set_node *f){
    first = f;
    last = f;
}

void Set::make_list(char M[]){
    Set_node *node, *node0;
    n=0;
    node = make_node(M[0]);
    add_first(node);
    n++;
    node0 = first;
    for (int i=1; i<strlen(M);i++){
        node = make_node(M[i]);
        add_node(node,node0);
        node0=node;
        n++;
    }
}

void Set::print_set(){
    Set_node *node;
    if (n==0) cout << "\nlist is poor\n";
    else{
        node = first;
        while (node!=nullptr){
            cout << node->A << " ";
            node=node->next;
        }
    }
}

Set :: Set(const Set&B){
    n=B.n;
    char *M;
    M=new char [n];
    Set_node *p;
    p=B.first;
    int k=0;
    while (p!=nullptr){
        M[k]=p->A;
        k++;
        p=p->next;
    }
    M[k]=0;
    make_list(M);
    n=strlen(M);
}

Set&Set :: operator= (const Set&B){
    n=B.n;
    Set_node *p;
    p=B.first;
    char *M;
    int k=0;
    M= new char[n];
    while (p!=nullptr){
        M[k]=p->A;
        k++;
        p=p->next;
    }
    make_list(M);
    n=strlen(M);

    return *this;
}
Set&Set :: operator&=(const Set &B){
    Set C(*this);
    char *M0, *M, *M1;
    M0 = new char[20];
    M=new char[20];
    M1=new char[20];
    Set_node *p, *p0, *pp, *pp0;
    n=0;
    p = C.first;
    p0= B.first;
    int k=0, k0=0;
    while (p!=C.last->next)
    {
        M[k]=p->A;
        p=p->next;
        k++;
    }
    while (p0!=B.last->next)
    {
        M0[k0]=p0->A;
        p0=p0->next;
        k0++;
    }
    M0[k0]=0;
    M[k]=0;
    for (int i=0; i<k; i++){
        for (int j=0; j<k0; j++)
            if (M[i]==M0[j]) M1[n++] = M[i];
    }
    M1[n]=0;
    make_list(M1);
    this->n=strlen(M1);
    return *this;
}

Set Set :: operator & (const Set &B) const{
    Set C(*this);
    return (C&=B);
}

Set & Set :: operator|= (const Set&B){
    char *M, *M0, *M1;
    Set_node *p, *p0;
        M0 = new char[26];
        M = new char[26];
        int k0=0, k=0;
        p=this->first;
        p0=B.first;
        while (p!=this->last->next){
            M[k++]=p->A;
            p=p->next;
        }
        while (p0!=B.last->next){
            M0[k0++]=p0->A;
            p0=p0->next;
        }
        M0[k0]=0;
        n=k;
        if (k!=1){
            for (int i=0; i<k0;i++){
                bool f=true;
                for (int j=0; j<k;j++){
                    if (M0[i]==M[j]) f=false;
                }
                if (f) M[n++] = M0[i];
            }
            M[n]=0;
            make_list(M);
        }
        if (k==1){
            make_list(M0);
        }

    return *this;
}

Set Set :: operator| (const Set&B) const{
    Set C(*this);
    return (C|=B);
}

Set Set :: operator~ () const{
    Set C;
    Set_node *p, *pp;
    char *M, *M1;
    int k=0;
    M=new char[20];
    M1=new char[20];
    p=this->first;
    while (p!=this->last->next){
        M[k++]=(p->A);
        p=p->next;
    }
    M[k]=0;

    for (char c='a'; c<= 'z'; ++c){
        bool f =true;
        for (int j=0; j<k;++j){
            if (c==M[j]) {f = false; break;}
        }
        if (f) {
            M1[C.n++]=c;
        }
    }
    M1[C.n]=0;
    C.make_list(M1);
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
