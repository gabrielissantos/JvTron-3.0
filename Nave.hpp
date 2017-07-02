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
#include <string>
#include <math.h>
#include <SFML/Graphics.hpp>
using std::string;

class Nave{
	public:
		Nave(string=""); // inserir nome da imagem
		~Nave();
		void setPosicao(const sf::Vector2f &); // determina posição
		void rodaAntiHorario(); // faz a nave rodar no sentido anti-horário
		void rodaHorario(); // faz a nave rodar no sentido horário
		void andaFrente(const float &); // faz a nave andar pra frente
		sf::Sprite getSprite() const; // retorna a instancia de sprite
		sf::Vector2f getFrente() const; // retorna a frente da nave
		sf::Vector2f getDirecao() const;
		sf::Vector2f getPosicao() const; // retorna a posicao da nave
		float getAngulo() const;
	private:
		float x; // posicao (horizontal)
		float y; // posicao (vertical)
		float anguloAtual; // angulo atual relativo
		float posicaoAtual; //posicao atual relativa

		sf::Vector2f direcao; // direcao q a nave aponta
		sf::Vector2f frente; // parte de frente da nave
		sf::Vector2f posicao; //posicao que a nave ocupa
		sf::Sprite spriteNave; // instancia de sprite
		sf::Texture texture; // instancia de textura
		sf::Image imagem; // arquivo de iamgem
};

const float anguloRotacao = 1*3.14/18; // angulo de rotacao em radianos

Nave::Nave(string s){
	// importando a imagem de forma mais geral possível
	anguloAtual = 0;
	direcao = sf::Vector2f(0.0f,0.0f);
	imagem.loadFromFile(s);
	texture.loadFromImage(imagem);
	spriteNave.setTexture(texture);
	spriteNave.setOrigin(imagem.getSize().x/2, imagem.getSize().y/2);
	frente = sf::Vector2f(imagem.getSize().x/2, 0.0f);
};

Nave::~Nave(){
};

void Nave::setPosicao(const sf::Vector2f & v){
	spriteNave.setPosition(v);
	frente += v;
	x = v.x;
	y = v.y;
};

sf::Sprite Nave::getSprite() const{
	return spriteNave;
};

void Nave::rodaHorario(){
	spriteNave.rotate(10); // angulo de rotação em graus (discutivel)
	anguloAtual = anguloAtual + anguloRotacao; // acrescentando no angulo relativo atual
	if(anguloAtual >= 3.14*2 - anguloRotacao) anguloAtual = 0; // zera após uma volta
	frente = sf::Vector2f(x,y) + sf::Vector2f(cos(anguloAtual)*imagem.getSize().x/2, sin(anguloAtual)*imagem.getSize().x/2); //apos girar, mudar a posicao da frente 
	direcao= sf::Vector2f(cos(anguloAtual), sin(anguloAtual)); // apos girar, atualizar a direcao
};

// mesmo que o rodaHorario
void Nave::rodaAntiHorario(){
	spriteNave.rotate(-10);
	anguloAtual -= anguloRotacao;
	if(anguloAtual <= -3.14*2 + anguloRotacao) anguloAtual = 0;
	frente = sf::Vector2f(x,y) + sf::Vector2f(cos(anguloAtual)*imagem.getSize().x/2, sin(anguloAtual)*imagem.getSize().x/2);
	direcao= sf::Vector2f(cos(anguloAtual), sin(anguloAtual));
};

void Nave::andaFrente(const float & passo){
	spriteNave.move(direcao*passo);
	posicao = spriteNave.getPosition();
	x = posicao.x;
	y = posicao.y;
}

sf::Vector2f Nave::getFrente() const{
	return frente;
};

sf::Vector2f Nave::getDirecao() const{
	return direcao;
};

sf::Vector2f Nave::getPosicao() const{
	return posicao;
}

float Nave::getAngulo() const{
	return anguloAtual;
};