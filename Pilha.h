#ifndef PILHA_H
#define PILHA_H

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
        int topo;
        int elementos[2000];
};

#endif // PILHA_H
