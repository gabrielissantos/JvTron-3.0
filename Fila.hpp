#include <iostream>

template <class Gen> struct NodeFila{
  Gen Info;
  NodeFila<Gen> *Next;
};

template <class Gen>
class Fila
{
    public:
        Fila(); //ok
        virtual ~Fila(); //ok
        void Insere(const Gen & X, bool & DeuCerto); //ok
        void Retira(Gen & X, bool & DeuCerto);
        bool Vazia(); //ok
        bool Cheia(); //ok
        Gen getPrimeiro(); //ok
        Gen getUltimo();   //ok
    private:
        NodeFila<Gen> * F_Primeiro;
        NodeFila<Gen> * F_Ultimo;
};
template <class Gen>
Fila<Gen>::Fila()
{
    F_Primeiro = NULL;
    F_Ultimo = NULL;
}
template <class Gen>
Fila<Gen>::~Fila()
{
    Gen X;
    bool DeuCerto;
    while(!Vazia()){
        DeuCerto = true;
        Retira(X, DeuCerto);
    }
}
template <class Gen>
void Fila<Gen>::Insere(const Gen & X, bool & DeuCerto){
    NodeFila<Gen> * F_Aux;
    if(Cheia())
        DeuCerto = false;
    else{
        DeuCerto = true;
        F_Aux = new NodeFila<Gen>;
        F_Aux->Info = X;
        F_Aux->Next = NULL;
        if(Vazia())
            F_Primeiro = F_Aux;
        else
            F_Ultimo->Next = F_Aux;
        F_Ultimo = F_Aux;
    }
}
template <class Gen>
void Fila<Gen>::Retira(Gen & X, bool & DeuCerto){
    NodeFila<Gen> * F_Aux;
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
template <class Gen>
bool Fila<Gen>::Cheia(){
    return false;
}
template <class Gen>
bool Fila<Gen>::Vazia(){
    if(F_Primeiro == NULL || F_Ultimo == NULL)
        return true;
    else
        return false;
}

template <class Gen>
Gen Fila<Gen>::getPrimeiro(){
    return F_Primeiro->Info;
}
template <class Gen>
Gen Fila<Gen>::getUltimo(){
    return F_Ultimo->Info;
}