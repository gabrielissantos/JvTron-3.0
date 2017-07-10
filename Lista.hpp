#ifndef LISTA_H
#define LISTA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tiro.hpp"
#include "NaveInimigo.hpp"
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
        struct Node<Gen> *Primeiro; 
        struct Node<Gen> *Atual;
        struct Node<Gen> *header;
    public:
        Lista();
        ~Lista();
        void PegaOProximo(Gen&,bool&);
        void PegaOPrimeiro(Gen&,bool&);
        void cria();
        int getQuant();
        void insere(Gen&,bool&);
        bool estaNaLista(Gen& x);
        void insereAEsquerdaDeP(Gen&,bool&);
        void removeP(Gen&,bool&);
        void remove(Gen& x,bool& deuCerto);
        void atualizaP(Gen& x,bool& deuCerto);
};

template<class Gen>
Lista<Gen>::~Lista(){
    struct Node <Gen> *Paux;
    Paux= header->esq;
    quant=0;
    while(Paux != header){
        
        Paux->esq->dir=Paux->dir;
        Paux->dir->esq=Paux->esq;
        delete Paux;
        Paux= header->esq;
    }
    delete Paux;
    
}
template<class Gen>
Lista<Gen>::Lista(){
    
    quant=0;
}
template<class Gen>
int Lista<Gen>::getQuant(){
    
    return quant;
};
template<class Gen>
void Lista<Gen>::cria(){
    quant=0;
    struct Node<Gen> *Paux = new Node<Gen>();
    header=Paux;
    header->esq=header;
    header->dir=header;
    Paux=NULL;
}
template<class Gen>
void Lista<Gen>::PegaOPrimeiro(Gen& x,bool& deuCerto){
    if(header->dir != header){
        Atual=header->dir;
        Primeiro=Atual;
        if(Primeiro == NULL){
            deuCerto= false;
        }else{
            x=Primeiro->info;
            deuCerto= true;
        }
    }else{
        deuCerto= false;
    }
};
template<class Gen>
void Lista<Gen>::PegaOProximo(Gen& x,bool& deuCerto){
    if(Atual != header){
        Atual=Atual->dir;
    }else{
        deuCerto=false;
    }
    if(Atual == header){
        deuCerto=false;
    }else{
        deuCerto=true;
        x=Atual->info;
    }
};
template<class Gen>
void Lista<Gen>::insere(Gen& x,bool& deuCerto){
    quant++;
    insereAEsquerdaDeP(x,deuCerto);
}
template<class Gen>
void Lista<Gen>::insereAEsquerdaDeP(Gen& x,bool& deuCerto){
    struct  Node<Gen> *Paux = new struct Node<Gen>();
    if(Paux !=NULL){
        Paux->info=x;
        Paux->dir = header->dir;
        Paux->esq=header;
        header->dir->esq=Paux;
        header->dir=Paux;
        deuCerto=true;
        Paux=NULL;
        delete Paux;
    }else{
        deuCerto=false;
        delete Paux;
    }
}

template<class Gen>
void Lista<Gen>::removeP(Gen& x,bool& deuCerto){
    struct Node <Gen> *Paux;
    Paux= header->dir;
    header->info=x;
    while(Paux->info.getId() != x.getId())
        Paux=Paux->dir;
    
    if(Paux != header){
        
        x=Paux->info;
        deuCerto=true;
        Paux->dir->esq=Paux->esq;
        Paux->esq->dir=Paux->dir;
        delete Paux;
        Paux=NULL;
        Atual=header->dir;
        quant--;
    }else{
        deuCerto=false;
    }
    
}

template<class Gen>
void Lista<Gen>::atualizaP(Gen& x,bool& deuCerto){
    struct Node <Gen> *Paux;
    Paux= header->dir;
    header->info=x;
    while(Paux->info.getId() != x.getId() )
        Paux=Paux->dir;
    
    if(Paux != header){
        Paux->info=x;
        deuCerto=true;
        
        Paux=NULL;
        delete Paux;
    }else{
        
        Paux=NULL;
        deuCerto=false;
    }
    
}
// 





#endif
