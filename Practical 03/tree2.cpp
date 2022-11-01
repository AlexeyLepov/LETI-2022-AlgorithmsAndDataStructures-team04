#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>

using namespace std;

class Node{
private:
    int d;
    Node *lft;
    Node *mdl;
    Node *rgt;
public:
    Node(){d=0;lft=NULL;mdl=NULL;rgt=NULL;}
    void print_node(){cout << "node: " << d << endl;}
    Node *make_node();
    void set_node (int n){d=n;lft=NULL;mdl=NULL;rgt=NULL;}
    friend class Tree;
};

class Tree{
    private:
        Node *N1;
        int *left;
        int *middle;
        int *right;
        int nv;
        Node *root;
        char **SCREEN;
        int offset;
        
    public:
        Tree ();
        void set_right(); //установка правых
        void set_left();//установка левых
        void set_middle();//установка средних
        void print_graph();//печать графа
        void set_SCREEN();//установка пустого графа
        void OutTree();//печать дерева
        void OutNodes(Node *v, int r, int c);//заполнение рекурсией памяти
        int BFS();//поиск в ширину
        int find_tz();//поиск количества вершин без предков
        void show_tz();//показ количества вершин без предков
};

void Tree::show_tz(){
    cout << this->find_tz() << endl;
}

int Tree::find_tz(){
    int tz=0;
    bool *pom;
    pom = new bool [nv];
    for (int i=0; i<nv; i++) pom[i]=0;
    for (int i=0; i<nv; i++){
        if(N1[i].lft) pom[N1[i].lft->d] = 1;//пометки соответсвенных вершин существования
        if(N1[i].rgt) pom[N1[i].rgt->d] = 1;
        if(N1[i].mdl) pom[N1[i].mdl->d] = 1;
        
    }
    for (int i=0; i<nv; i++) tz+=pom[i];//подсчёт верных вершин
    return tz;
}

int Tree::BFS(){
    int count = 0;
    queue <Node*> Q;
    Q.push(root);//впихиваем первый
    while (!Q.empty()){//пока не пустой список
        Node *v = Q.front(); Q.pop(); //выбираем первый в очереди
        cout << v->d << ' '; ++count; //печать выбранного элемента
        if (v->lft) Q.push(v->lft); //вставка в очередь сыновей
        if (v->mdl) Q.push(v->mdl);
        if (v->rgt) Q.push(v->rgt);
    }
    return count; // вывод колва обработанных элементов
}

void Tree::set_SCREEN(){ //уставновка начальной памяти в определённый символ
    SCREEN = new char *[4];
    int i, j;
    for (i=0; i<4; i++){
        SCREEN[i]=new char [80];
    }
    for (i=0; i<4; i++){
        for (j=0; j<80; j++){
            SCREEN[i][j]='_';
        }
    }
}

void Tree::OutNodes(Node *v, int r, int c){
    int M[] = {40,20,10,5,0};
    if(r && c && (c<80)) SCREEN[r-1][c-1] = char(v->d+'0');
    if (r < 4){
        if(v->lft) OutNodes(v->lft, r+1, c - M[r]);
        if(v->mdl) OutNodes(v->mdl, r+1, c);
        if(v->rgt) OutNodes(v->rgt, r+1, c + M[r]);
    }
}

void Tree::OutTree(){
    OutNodes(root,1,40);
    for (int i=0; i<4; i++){
        SCREEN[i][79]=0;
        cout << '\n' <<SCREEN[i];
    }
    cout << '\n';
}
 

void Tree::set_left(){
    ifstream file2;
    left = new int [nv];
    file2.open("left.txt");
    for (int i=0; i<nv;i++){
        left[i]=0;
        file2 >> left[i];
    }
    file2.close();
}

void Tree::set_right(){
    ifstream file2;
    right = new int [nv];
    file2.open("right.txt");
    for (int i=0; i<nv;i++){
        right[i]=0;
        file2 >> right[i];
    }
    file2.close();
}


void Tree::set_middle(){
    ifstream file2;
    middle = new int [nv];
    file2.open("middle.txt");
    for (int i=0; i<nv;i++){
        middle[i]=0;
        file2 >> middle[i];
    }
    file2.close();
}

Tree::Tree(){//главный конструктор дерева
    ifstream file1;
    int k;
    file1.open("tags.txt");
    file1 >> nv;//установка количества вершин
    N1 = new Node [nv];//памято по вершины
    for (int i=0; i<nv;i++){
        file1 >> k;
        N1[i].set_node(k);//создание вершины
        N1[i].lft=NULL;
        N1[i].rgt=NULL;
        N1[i].mdl=NULL;
    }
    this->set_left();//установка массива левых индексов
    this->set_right();
    this->set_middle();
    file1.close();
    for (int i=0; i<nv; i++){//склейка вершин в дерево
        if (this->left[i]!=0) N1[i].lft = &N1[this->left[i]];
        if (this->right[i]!=0) N1[i].rgt = &N1[this->right[i]];
        if (this->middle[i]!=0) N1[i].mdl = &N1[this->middle[i]];
    }
    set_SCREEN();//установка памяти для печати
    offset = 79;
    root = &N1[0];
}

int main(){
    Tree T1;//создание дерева
    T1.OutTree();//печать дерева
    cout << endl;
    cout << "bypass in breadth: ";
    T1.BFS();//поиск в ширину с соответствующим выводом
    cout << endl;
    cout << "Answer: ";
    T1.show_tz();
    cout << endl;
    return 0;
}