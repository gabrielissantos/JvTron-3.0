#include <iostream>

struct Node{
  int Info;
  Node *Next;
};

typedef struct Node *NodePtr;

class Pilha
{
    public:
        Pilha();
        virtual ~Pilha();
        void Empilha(int X, bool DeuCerto);
        void Desempilha(int X, bool DeuCerto);
        bool Vazia();
        bool Cheia();
        int getTopo();
    private:
        NodePtr P_Topo;
};

Pilha::Pilha()
{
    P_Topo = NULL;
}

Pilha::~Pilha()
{
    int X;
    bool DeuCerto;
    while(!Vazia()){
        DeuCerto = true;
        Desempilha(X, DeuCerto);
    }
}

void Pilha::Empilha(int X, bool DeuCerto){
    NodePtr P_Aux;
    if(Cheia()==true)
        DeuCerto = false;
    else{
        DeuCerto = true;
        P_Aux = new Node;
        P_Aux->Info = X;
        P_Aux->Next = P_Topo;
        P_Topo = P_Aux;
    }
}

void Pilha::Desempilha(int X, bool DeuCerto){
    NodePtr P_Aux;
    if(Vazia()==true)
        DeuCerto = false;
    else{
        DeuCerto = true;
        X = P_Topo->Info;
        P_Aux = P_Topo;
        P_Topo = P_Topo->Next;
        delete(P_Aux);
    }
}

bool Pilha::Cheia(){
    return false;
}

bool Pilha::Vazia(){
    if(P_Topo == NULL)
        return true;
    else
        return false;
}


int Pilha::getTopo(){
    return P_Topo->Info;
}