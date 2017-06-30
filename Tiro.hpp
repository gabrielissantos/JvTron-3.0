#include <iostream>
#include <SFML/Graphics.hpp>
class Tiro{
	public:
		Tiro();
		~Tiro();
		void navega(const float & d);
		void setPosition(const sf::Vector2f &);
		void setDirecao(const sf::Vector2f &, const float &);
		void paraNavegar();

		sf::RectangleShape getForma() const;
	private:
		float iMovimento; // iterador pra movimento
		sf::Vector2f posicao;
		sf::Vector2f direcao;
		sf::RectangleShape forma;
};

Tiro::Tiro(){
	forma.setFillColor(sf::Color(255,0,255));
    forma.setSize(sf::Vector2f(20.0f, 1.0f ));
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

void Tiro::setDirecao(const sf::Vector2f & direcao, const float & angulo){
	this->direcao = direcao;
	forma.rotate(angulo);
	std::cout << angulo << std::endl;
};

void Tiro::paraNavegar(){
	forma.setPosition(posicao);
	iMovimento = 0;
}

sf::RectangleShape Tiro::getForma() const { return forma; };