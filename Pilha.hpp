#include <iostream>

template<class Gen> struct NodePilha{
  Gen Info;
  struct NodePilha<Gen> *Next;
};

template<class Gen>
class Pilha
{
    public:
        Pilha();
        virtual ~Pilha();
        void Empilha(const Gen & X, bool & DeuCerto);
        void Desempilha(Gen & X, bool & DeuCerto);
        bool Vazia();
        bool Cheia();
        Gen getTopo();
    private:
        struct NodePilha<Gen> *  P_Topo;
};

template<class Gen>
Pilha<Gen>::Pilha()
{
    P_Topo = NULL;
}

template<class Gen>
Pilha<Gen>::~Pilha()
{
    Gen X;
    bool DeuCerto;
    while(!Vazia()){
        DeuCerto = true;
        Desempilha(X, DeuCerto);
    }
}

template<class Gen>
void Pilha<Gen>::Empilha(const Gen & X, bool & DeuCerto){
    struct NodePilha<Gen> *  P_Aux;
    if(Cheia()==true)
        DeuCerto = false;
    else{
        DeuCerto = true;
        P_Aux = new NodePilha<Gen>;
        P_Aux->Info = X;
        P_Aux->Next = P_Topo;
        P_Topo = P_Aux;
    }
}

template<class Gen>
void Pilha<Gen>::Desempilha(Gen & X, bool & DeuCerto){
    struct NodePilha<Gen> *  P_Aux;
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

template<class Gen>
bool Pilha<Gen>::Cheia(){
    return false;
}

template<class Gen>
bool Pilha<Gen>::Vazia(){
    if(P_Topo == NULL)
        return true;
    else
        return false;
}

template <class Gen>
Gen Pilha<Gen>::getTopo(){
    return P_Topo->Info;
}