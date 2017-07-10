/*
    JvAsteroids: Trabalho 3
    Departamento de Computação
    UFSCar Universidade Federal de São Carlos
    Disciplina: Estrutura de Dados
    Professor: Roberto Ferrari
    Aluno(a):                               RA:
        João Gabriel Melo Barbirato         726546
        Leonardo de Oliveira Peralta        726556
        Gabrieli Santos                     726523
    
    Controle de Versão: https://github.com/gabrielissantos/JvTron-3.0
*/

#ifndef TELA_H
#define TELA_H

#include <SFML/Graphics.hpp>

class Tela{
public:
    
	virtual int Executar(sf::RenderWindow & app,int &score) = 0;
};

#endif
