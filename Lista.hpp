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

template<class Gen> // LEMBRAR Q ISSO É UMA LISTA BURRA
class Lista{
    private:
        int quant;
        struct Node<Gen> *header;
        struct Node<Gen> *Atual;
        struct Node<Gen> *Primeiro;
    public:
        Lista();
        ~Lista();
        // metodos gerais
        int getQuant();
        bool vazia();
        void PegaOPrimeiro(Gen&, bool &);
        void PegaOProximo(Gen&, bool&);
        bool estaNaLista(Gen& x);
        void insereAEsquerdaDeP(struct Node <Gen> *N,Gen&,bool&);
        void removeP(struct Node <Gen> *N,Gen&,bool&);
        void setAtual(const Gen &, bool &);
        Gen getAtual() const;
        void resetAtual();

        // métodos para Fila
        void insereFila(Gen&,bool&);
        void removeFila(Gen& x,bool&);

        // métodos para lista
        void empilha(Gen x, bool &);
        void desempilha(Gen& x, bool&);
};
template<class Gen>
bool Lista<Gen>::vazia(){
    if(quant==0) return true;
    return false;
}

template<class Gen>
void Lista<Gen>::PegaOPrimeiro(Gen& x,bool& deuCerto){
    Atual=header->esq;
    Primeiro=Atual;
    if(Primeiro == NULL){
        deuCerto= false;
    }else{
        x=Primeiro->info;
        deuCerto= true;
    }
};

template<class Gen>
void Lista<Gen>::PegaOProximo(Gen& x,bool& deuCerto){
    if(Atual != NULL)
        Atual=Atual->esq;
    if(Atual == NULL){
        deuCerto=false;
    }else{
        deuCerto=true;
        x=Atual->info;
    }
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
    while(header->dir!=header) removeP(header->dir,x, deuCerto);
};

template<class Gen>
int Lista<Gen>::getQuant(){
    return quant;
};

template<class Gen>
void Lista<Gen>::insereFila(Gen& x,bool& deuCerto){
    insereAEsquerdaDeP(header,x,deuCerto);
    if(deuCerto){ 
        quant++;
        Primeiro = header->dir;
    }
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
    quant++;
    delete Paux;    
};

template<class Gen>
void Lista<Gen>::removeP(struct Node <Gen> *N,Gen& x,bool& deuCerto){
    struct Node <Gen> *Paux = N;
    if(Paux != header){
        quant--;
        deuCerto=true;
        x = Paux->info;
        Paux->esq->dir=Paux->dir;
        Paux->dir->esq=Paux->esq;
        delete Paux;
    }else{
        deuCerto=false;
    }  
};

template <class Gen>
void Lista<Gen>::removeFila(Gen& x,bool& deuCerto){
    removeP(header->dir, x, deuCerto);
    if(deuCerto) quant--;
};

template <class Gen>
void Lista<Gen>::desempilha(Gen& x, bool& deuCerto){
    removeP(header->esq, x, deuCerto);
};

template <class Gen>
void Lista<Gen>::empilha(Gen x, bool & deuCerto){
    insereAEsquerdaDeP(header, x, deuCerto);
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

template <class Gen>
Gen Lista<Gen>::getAtual() const {
    return Atual;
};

template <class Gen>
void Lista<Gen>::setAtual(const Gen & x, bool & deuCerto){
    if(getQuant()>0){
        Atual->info = x;
        deuCerto = true;
    }
    deuCerto = false;
};

template <class Gen>
void Lista<Gen>::resetAtual(){
    Atual = Primeiro;
};
// inline bool operator==(const Item &lhs, const Item & rhs){ 
//     if(lhs.getId() == rhs.getId())
//         return true;
//     return false;
// }
#endif
