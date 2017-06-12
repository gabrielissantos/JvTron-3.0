#include "Pilha.h"

Pilha::Pilha()
{
    topo = 0;
}

Pilha::~Pilha()
{
    while(!Vazia()){
        int X;
        bool DeuCerto = true;
        Desempilha(X, DeuCerto);
    }
}

void Pilha::Empilha(int X, bool DeuCerto){
    if(Cheia()==true)
        DeuCerto = false;
    else{
        DeuCerto = true;
        topo++;
        elementos[topo] = X;
    }
}

void Pilha::Desempilha(int X, bool DeuCerto){
    if(Vazia()==true)
        DeuCerto = false;
    else{
        DeuCerto = true;
        X = elementos[topo];
        topo--;
    }
}

bool Pilha::Cheia(){
    if(topo == 2000)
        return true;
    else
        return false;
}

bool Pilha::Vazia(){
    if(topo == 0)
        return true;
    else
        return false;
}

int Pilha::getTopo(){
    return topo;
}
