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
#ifndef TIRO_H
#define TIRO_H
#include <iostream>
#include <SFML/Graphics.hpp>

// Estrutura do tiro

class Tiro{
	// atributos privados
	private:
		float iMovimento; // iterador pra movimento
		sf::Vector2f posicao; // posicao do inicio do tiro
		sf::Vector2f direcao; // para onde aponta o tiro
		sf::CircleShape forma; // forma desenhável do tiro
        int id;
	public:
		Tiro();
		~Tiro();
        
        void setColor(sf::Color);//seta o cor do tiro
        void setId(int);    //seta o id do tiro
        int getId();    //pega o id do tiro
		void navega(const float & d); // faz o tiro se mover
		void comecaMover(); //comeca a mover o tiro
		void setPosition(const sf::Vector2f &);
        sf::Vector2f getPosition(); //pega a posicao inicial do tiro
        sf::Vector2f getDirecao();  //pega a direcao do tiro
		void setDirecao(const sf::Vector2f &); //seta a direcao do tiro
		void paraNavegar(); // faz o tiro parar de se mover
		float getIterador() const;
		int numeroTiro;
        
		sf::Vector2f getPosition() const;
		sf::CircleShape getForma() const;
};

Tiro::Tiro(){
	forma.setFillColor(sf::Color(0,255,255));
	forma.setRadius(2.0f);
	forma.setOrigin(sf::Vector2f(forma.getRadius(),forma.getRadius()));
    direcao = sf::Vector2f(1.0f, 0.0f);
    iMovimento = -1;
};
void Tiro::setColor(sf::Color cor){
    forma.setFillColor(cor);
};
Tiro::~Tiro(){};
void Tiro::setId(int x){
    id=x;
};
int Tiro::getId(){
    
    return id;
};
void Tiro::navega(const float & passo){
	if(iMovimento != -1){
		forma.setPosition(posicao + direcao*iMovimento);
		iMovimento += passo;		
	}
};
sf::Vector2f Tiro::getPosition(){
    return posicao;
};
sf::Vector2f Tiro::getDirecao(){
    return direcao;
};
void Tiro::comecaMover(){ if(iMovimento == -1) iMovimento = 0; };

void Tiro::setPosition(const sf::Vector2f & posicao){
	this->posicao = posicao;
	forma.setPosition(posicao);
};

void Tiro::setDirecao(const sf::Vector2f & direcao){
	this->direcao = direcao;
};

void Tiro::paraNavegar(){
	forma.setPosition(posicao);
	iMovimento = -1;
}

sf::CircleShape Tiro::getForma() const { return forma; };

sf::Vector2f Tiro::getPosition() const { return posicao; };

float Tiro::getIterador() const {return iMovimento;};
#endif
