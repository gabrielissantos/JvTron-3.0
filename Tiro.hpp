/*
	JvTron: Trabalho 3
	Departamento de Computação
	UFSCar Universidade Federal de São Carlos
	Disciplina: Estrutura de Dados
	Professor: Roberto Ferrari
	Aluno(a):								RA:
		João Gabriel Melo Barbirato			726546
		Leonardo de Oliveira Peralta		726556
		Gabrieli Santos						726523
    
	Controle de Versão: https://github.com/gabrielissantos/JvTron-3.0
*/

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

	public:
		Tiro();
		~Tiro();
		void navega(const float & d); // faz o tiro se mover
		void setPosition(const sf::Vector2f &);
		void setDirecao(const sf::Vector2f &);
		void paraNavegar(); // faz o tiro parar de se mover

		sf::CircleShape getForma() const;
};

Tiro::Tiro(){
	forma.setFillColor(sf::Color(255,0,255));
	forma.setRadius(2.0f);
	forma.setOrigin(sf::Vector2f(forma.getRadius(),forma.getRadius()));
    direcao = sf::Vector2f(1.0f, 0.0f);
};

Tiro::~Tiro(){};

void Tiro::navega(const float & passo){
	forma.setPosition(posicao + direcao*iMovimento/*sf::Vector2f((float)iMovimento, 0.0f)*/);
	//posicao = posicao*(1+iMovimento);
	iMovimento += passo;
};

void Tiro::setPosition(const sf::Vector2f & posicao){
	this->posicao = posicao;
	forma.setPosition(posicao);
};

void Tiro::setDirecao(const sf::Vector2f & direcao){
	this->direcao = direcao;
};

void Tiro::paraNavegar(){
	forma.setPosition(posicao);
	iMovimento = 0;
}

sf::CircleShape Tiro::getForma() const { return forma; };