#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <cstring>


using namespace std;


class Node
{
    char d;
    Node *lft;
    Node *mdl;
    Node *rgt;

    public:
    Node():lft(NULL), rgt(NULL), mdl(NULL){}
    ~Node(){if(lft) delete lft; if (rgt) delete rgt; if(mdl) delete mdl;}
    friend class Tree;
};


class Tree
{
    Node * root;
    char num, maxnum;
    int maxrow, offset;
    int numel;
    char ** SCREEN;
    void clrscr( );
    Node* MakeNode(int depth);
    void OutNodes(Node * v, int r, int c);
    Tree (const Tree &);
    Tree (Tree &&);
    Tree operator = (const Tree &) const;
    Tree operator = (Tree &&) const;

    public:
    Tree(char num, char maxnum, int maxrow);
    ~Tree();
    void MakeTree()
    {
        root = MakeNode(0);
    }
    bool exist( )
    {
        return root != nullptr;
    }
    int DFS( );
    int BFS( );
    void OutTree( );//*
    int show_numel()
    {
        return numel;
    }
};


Tree ::   Tree(char nm, char mnm, int mxr): num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(nullptr), SCREEN(new char * [maxrow]), numel(0)
{
    for(int i = 0; i < maxrow; ++i) SCREEN[ i ] = new char[80];
}


Tree :: ~Tree( )
{
    for(int i = 0; i < maxrow; ++i)
        delete [ ]SCREEN[i];
    delete [ ] SCREEN; delete root;
}


Node * Tree :: MakeNode(int depth)
{
    Node * v = nullptr;
    int Y;
    cout << "Node (" << num << ',' << depth << ")1/0: "; cin >> Y;
    if (Y)
    {
        v = new Node;
        v->d = num++;
        v->lft = MakeNode(depth+1);
        v->mdl = MakeNode(depth+1);
        v->rgt = MakeNode(depth+1);
        numel++;
    }
    return v;
}


void Tree::OutTree()
{
    clrscr();
    OutNodes(root,1,40);
    for (int i=0; i<maxrow; i++)
    {
        SCREEN[i][79]=0;
        cout << '\n' <<SCREEN[i];
    }
    cout << '\n';
}


void Tree :: clrscr( )
{
    for(int i = 0; i < maxrow; ++i)
        memset(SCREEN[ i ], '_', 80);
}


void Tree::OutNodes(Node *v, int r, int c)
{
    int M[] = {40,20,10,5,0};
    if(r && c && (c<80)) SCREEN[r-1][c-1] = v->d;
    if (r < 4)
    {
        if(v->lft) OutNodes(v->lft, r+1, c - M[r]);
        if(v->mdl) OutNodes(v->mdl, r+1, c);
        if(v->rgt) OutNodes(v->rgt, r+1, c + M[r]);
    }
}


int Tree :: BFS( )
{
    int countHasParant = 0; // количество узлов, имеющих предка
    int countLeaves = 0; // количество листьев
    queue < Node * > Q;     // создание очереди указателей на узлы
    Q.push(root);           // поместить в очередь корень дерева
    while (!Q.empty( ))     // пока очередь не пуста
    {
        Node * v = Q.front( ); Q.pop( );    // взять из очереди,
        cout << v->d << '_'; ++countHasParant;       // выдать тег, счёт узлов
        if (v->lft) Q.push(v->lft); // Q <- (левый сын)
        if (v->mdl) Q.push(v->mdl); // Q <- (средний сын)
        if (v->rgt) Q.push(v->rgt); // Q <- (правый сын)
        if ((v->lft)==NULL && (v->mdl)==NULL && (v->rgt)==NULL) countLeaves++;
    }
    return countLeaves;
}


int main()
{
    int n=0;
    Tree Tr('a','z',4);
    Tr.MakeTree();
    if (Tr.exist())
    {
        Tr.OutTree();
        n=Tr.BFS();
        cout << '\n';
        cout << "Number of vertices from BFC: " << n << '\n';
        // cout << "Number of vertices that have ancestors: " << Tr.show_numel()-1 << '\n'; // вывод количества узлов, имеющих предка
        cout << "Number of leaves: " << Tr.show_numel()-1 << '\n'; // вывод количества листьев
    }
    return 0;
}

