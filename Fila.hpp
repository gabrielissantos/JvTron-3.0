#include <iostream>

struct Node{
  int Info;
  Node *Next;
};

typedef struct Node *NodePtr;

class Fila
{
    public:
        Fila(); //ok
        virtual ~Fila(); //ok
        void Insere(int X, bool DeuCerto); //ok
        void Retira(int X, bool DeuCerto);
        bool Vazia(); //ok
        bool Cheia(); //ok
        int getPrimeiro(); //ok
        int getUltimo();   //ok
    private:
        NodePtr F_Primeiro;
        NodePtr F_Ultimo;
};

Fila::Fila()
{
    F_Primeiro = NULL;
    F_Ultimo = NULL;
}

Fila::~Fila()
{
    int X;
    bool DeuCerto;
    while(!Vazia()){
        DeuCerto = true;
        Retira(X, DeuCerto);
    }
}

void Fila::Insere(int X, bool DeuCerto){
    NodePtr F_Aux;
    if(Cheia())
        DeuCerto = false;
    else{
        DeuCerto = true;
        F_Aux = new Node;
        F_Aux->Info = X;
        F_Aux->Next = NULL;
        if(Vazia())
            F_Primeiro = F_Aux;
        else
            F_Ultimo->Next = F_Aux;
        F_Ultimo = F_Aux;
    }
}

void Fila::Retira(int X, bool DeuCerto){
    NodePtr F_Aux;
    if(Vazia()==true)
        DeuCerto = false;
    else{
        DeuCerto = true;
        X = F_Primeiro->Info;
        F_Aux = F_Primeiro;
        F_Primeiro = F_Primeiro->Next;
        if(F_Primeiro == NULL)
            F_Ultimo == NULL;
        delete(F_Aux);
    }
}

bool Fila::Cheia(){
    return false;
}

bool Fila::Vazia(){
    if(F_Primeiro == NULL || F_Ultimo == NULL)
        return true;
    else
        return false;
}


int Fila::getPrimeiro(){
    return F_Primeiro->Info;
}

int Fila::getUltimo(){
    return F_Ultimo->Info;
}