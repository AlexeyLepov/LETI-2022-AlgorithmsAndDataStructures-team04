////////////////////////////////////////////
//                                        //
//    Выполнили студенты, гр. 1308:       //
//    Мельник Д. А.                       //
//    Лепов А. В.                         //
//                                        //
////////////////////////////////////////////
//////////////////////////////
//                          //
//    Работа со списками    //
//                          //
//////////////////////////////
#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

struct Set_node{
    char A;
    Set_node *next;
    Set_node *prew;
};
struct Set_head{
    Set_node *first;
    Set_node *last;
};
Set_head *make_head(){
    Set_head *hed;
    hed = new Set_head;
    hed->first=nullptr;
    hed->last=nullptr;
    return hed;
}
Set_node *make_node(char Arr){
    Set_node *neww;
    neww = new Set_node;

    neww->A = Arr;
    neww->next = nullptr;
    neww->prew = nullptr;
    return neww;
}
void add_node (Set_head *hed, Set_node *neww, Set_node *node0){
    node0->next=neww;
    neww->prew=node0;
    hed->last = neww;
}
void delete_node (Set_node*node1, Set_head *hed){
    Set_node *node0, *node2;
    if ((node1 == hed->first)&&(node1 != hed->last)){
        node2=node1->next;
        hed->first = node2;
    }
    if ((node1 == hed->last)&&(node1 != hed->first)){
        node0=node1->prew;
        hed->last = node0;
    }
    if ((node1 != hed->last)&&(node1 != hed->first)){
        node0=node1->prew;
        node2=node1->next;
        node0->next = node2;
    }
        
    if ((node1 == hed->last)&&(node1 == hed->first)){
        hed->first = nullptr;
        hed->last = nullptr;
    }
    delete node1;
}

void print_list (Set_head *hed){
    Set_node *node;
    node = hed->first;

    while (node!=hed->last->next){
        cout << node->A << " ";
        node=node->next;
    }
}

void init_list(Set_head *hed, char *C, int n){
    Set_node *neww, *node0;
    int i;
    neww=make_node(C[0]);
    hed->first=neww;
    hed->last=neww;
    node0=hed->last;
    for (i=1;i<n;i++){
        neww = make_node(C[i]);
        add_node(hed,neww,node0);
        node0=neww;
    }
}

void A_and_B(Set_head *W, Set_head *A, Set_head *B){
    Set_node *work1, *work2, *node0, *neww;
    work1 = A->first;
    work2 = B->first;
    neww = make_node('*');
    W->first=neww;
    W->last=neww;
    node0=W->last;
    while (work1!=A->last->next){
        work2 = B->first;
        while (work2!=B->last->next){
            if (work1->A==work2->A){
                neww=make_node(work1->A);
                add_node(W,neww,node0);
                node0=neww;
            }
            work2=work2->next;
        }
        work1=work1->next;
    }
}
void A_and_B_not_C (Set_head *C, Set_head *W){
    Set_node *work1, *work2, *work0;
    int d;
    work1=C->first;
    work2=W->first;

    while (work1!=C->last->next){
        work2=W->first;
        while (work2!=W->last->next){
            d=1;
            if (work1->A == work2->A){
                work0=work2->next;
                delete_node(work2,W);
                work2=work0;
                d=0;
            }
            if (d==1)
                work2=work2->next;
        }
        work1=work1->next;
    }
}

int main(){
    char *notC, *AandB, *AandBnotC, *AandBnotCorD, *Ar, *Cr, *Br, *Dr;
    int i, j, nA, nB, nAB=0, m, nABC=0, nC, nD, nABCD = 0, k=0, d;
    bool kond1, kond2;
    Set_node  *neww, *node0, *work1, *work2, *work0, *node1, *node2;;
    Set_head *A, *B, *C, *D, *W;

    A=make_head();
    B=make_head();
    C=make_head();
    D=make_head();

    cout << "input A : ";
    Ar=new char [10];
    cin >> Ar;
    cout << "input B : ";
    Br=new char [10];
    cin >> Br;
    cout << "input C : ";
    Cr=new char [10];
    cin >> Cr;
    cout << "input D : ";
    Dr=new char [10];
    cin >> Dr;

    nA = strlen(Ar);
    nB = strlen(Br);
    nC = strlen(Cr);
    nD = strlen(Dr);

    init_list(A,Ar,nA);
    init_list(B,Br,nB);
    init_list(C,Cr,nC);
    init_list(D,Dr,nD);

    //A and B
    W=make_head();
    A_and_B(W,A,B);
    
    cout << "AandB = ";
    print_list(W);
    cout<<endl;

    //A anb B without C

    A_and_B_not_C(C,W);

    cout<<"AandBnotC = ";
    print_list(W);
    cout << endl;

    //A anb B without C or D

    work1=W->first;
    work2=D->first;

    while (work1!=W->last->next){
        work2=D->first;
        while (work2!=D->last->next){
            if (work1->A == work2->A){
                k++;
            }
            work2=work2->next;
        }
        work1=work1->next;
    }

    work1=W->first;
    work2=D->first;

    if (k!=0){
        while (work1!=W->last->next){
            work2=D->first;
            while (work2!=D->last->next){
                d=1;
                if (work1->A == work2->A){
                    work0=work2->next;
                    delete_node(work2,D);
                    work2=work0;
                    d=0;
                }
                if (d==1)
                    work2=work2->next;
            }
            work1=work1->next;
        }
    }

    node0=W->last;
    work2=D->first;

    while (work2!=D->last->next){
        add_node(W,work2,node0);
        node0 = work2;
        work2=work2->next;
    }
    cout<<"AandBnotCorD = ";
    print_list(W);
    return 0;
    work1=W->first;
    work2=W->first;
    while (work1!=nullptr){
        work1=work2;
        work2 = work1->next;
        delete work1;
    }
    delete []Ar;
    delete []Br;
    delete []Cr;
    delete []Dr;
}