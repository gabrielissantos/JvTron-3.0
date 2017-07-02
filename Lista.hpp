#ifndef LISTA_H
#define LISTA_H
#include <SFML/Graphics.hpp>
#include <iostream>

// Estrutura da Lista
template <class Gen> struct Node{
    Gen info;
    struct Node<Gen> *dir;
    struct Node<Gen> *esq;
};

template<class Gen>
class Lista{
    private:
        int quant;
    public:
        Lista();
        ~Lista();
        struct Node<Gen> *header;
        int getQuant();
        void insere(Gen&,bool&);
        bool estaNaLista(Gen& x);
        void insereAEsquerdaDeP(struct Node <Gen> *N,Gen&,bool&);
        void removeP(struct Node <Gen> &N,Gen&,bool&);
        void remove(Gen& x,bool& deuCerto);
};

template<class Gen>
Lista<Gen>::Lista(){   
    quant=0;
    struct Node<Gen> *Paux = new Node<Gen>();
    header=Paux;
    header->esq=header;
    header->dir=header;
    Paux=NULL;
    delete Paux;
};

template<class Gen>
Lista<Gen>::~Lista(){
    bool deuCerto;
    Gen x;
    while(header->dir!=header) remove(x, deuCerto);
};

template<class Gen>
int Lista<Gen>::getQuant(){
    return quant;
};

template<class Gen>
void Lista<Gen>::insere(Gen& x,bool& deuCerto){
    quant++;
    insereAEsquerdaDeP(header,x,deuCerto);
};

template<class Gen>
void Lista<Gen>::insereAEsquerdaDeP(struct Node <Gen> *N,Gen& x,bool& deuCerto){
    struct  Node<Gen> *Paux = new struct Node<Gen>();
    Paux->info=x;
    Paux->esq=N->esq;
    Paux->dir=N;
    N->esq->dir=Paux;
    N->esq=Paux;
    Paux=NULL;
    deuCerto=true;
    delete Paux;    
};

template<class Gen>
void Lista<Gen>::removeP(struct Node <Gen> &N,Gen& x,bool& deuCerto){
    quant--;
    struct Node <Gen> *Paux = N;
    header->info=x;
    while(Paux->info != x)
        Paux=Paux->esq;    
    if(Paux != header){
        deuCerto=true;
        Paux->esq->dir=Paux->dir;
        Paux->dir->esq=Paux->esq;
        delete Paux;
    }else{
        deuCerto=false;
    }   
};

template <class Gen>
void Lista<Gen>::remove(Gen& x,bool& deuCerto){
    struct Node <Gen> *Paux;
    if(header->dir != header){
        quant--;
        deuCerto=true;
        Paux=header->dir;
        x=Paux->info;
        header->dir=Paux->dir;
        Paux->dir->esq=header;
        delete Paux;
    }else{
        deuCerto=false;
        
    }
};

template <class Gen>
bool Lista<Gen>::estaNaLista(Gen& x){
    struct Node <Gen>  *Paux;
    Paux=header->esq;
    while(Paux != header){
        if(Paux->info == x)
            return true;
    }
    return false;
};
// inline bool operator==(const Item &lhs, const Item & rhs){ 
//     if(lhs.getId() == rhs.getId())
//         return true;
//     return false;
// }
#endif
