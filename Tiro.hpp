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
		void comecaMover();
		float getIterador() const;

		sf::Vector2f getPosition() const;
		sf::CircleShape getForma() const;
};

Tiro::Tiro(){
	forma.setFillColor(sf::Color(255,0,255));
	forma.setRadius(2.0f);
	forma.setOrigin(sf::Vector2f(forma.getRadius(),forma.getRadius()));
<<<<<<< HEAD
    direcao = sf::Vector2f(0.0f, 0.0f);
=======
    direcao = sf::Vector2f(1.0f, 0.0f);
    iMovimento = -1;
>>>>>>> 9510d34bae59c2f303e1ebd9c5ed9f347fd22757
};

Tiro::~Tiro(){};

void Tiro::navega(const float & passo){
	if(iMovimento != -1){
		forma.setPosition(posicao + direcao*iMovimento);
		iMovimento += passo;		
	}
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