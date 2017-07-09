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
#ifndef NAVEINIMIGO_H
#define NAVEINIMIGO_H
#include <iostream>
#include <string>
#include <math.h>
#include <SFML/Graphics.hpp>
using std::string;

class NaveInimigo{
	public:
		NaveInimigo(string=""); // inserir nome da imagem
		~NaveInimigo();
		void setPosition(const sf::Vector2f &); // determina posição
		void rodaAntiHorario(); // faz a nave rodar no sentido anti-horário
		void rodaHorario(); // faz a nave rodar no sentido horário
		void andaFrente(const float &); // faz a nave andar pra frente
		float getAngulo() const;
		float getVel() const;
		sf::Sprite getSprite() const; // retorna a instancia de sprite
		sf::Vector2f getPosition() const; // retorna a posicao da nave
		sf::RectangleShape visao(sf::Sprite heroi);
        bool getAtirou();
        void resetAtirou();
        sf::Vector2f getLocalTiro();
        void setId(int);
        int getId();
        void criarNave();
        sf::Sprite spriteNave; // instancia de sprite
		sf::Texture texture; // instancia de textura
		sf::Image imagem; 
	private:
        int id;
		float anguloAtual; // angulo atual relativo
		float posicaoAtual; //posicao atual relativa
        sf::Vector2f posicaoT; // posicao do inicio do tiro
		sf::Vector2f direcaoT; // para onde aponta o tiro
		int vidas;
		float vel; // velocidade da nave
        sf::Vector2f posicaoHeroi;
		sf::Vector2f direcaoVel;
		sf::Vector2f direcao; // direcao q a nave aponta
		sf::Vector2f frente; // parte de frente da nave
		sf::Vector2f posicao; //posicao que a nave ocupa// arquivo de iamgem		
        float speed,speedT;
        void setPositionTiro(const sf::Vector2f &);
		void setDirecaoTiro(const sf::Vector2f &);
        bool achou;
        sf::Clock movimentoClock;
        sf::Time movimentoTempo;
        sf::Clock atacarClock;
        sf::Time atacarTempo;
        void Mover(sf::Vector2f heroi,float);
        bool atirou;
        sf::Vector2f localTiro;
}; // angulo de rotacao em radianos
sf::Vector2f NaveInimigo::getLocalTiro(){
    return localTiro;
}
void NaveInimigo::criarNave(){
    vel=0;
    speedT=0;
    achou=false;
	anguloAtual = 0;
	direcao = sf::Vector2f(1.0f,0.0f);
	frente = sf::Vector2f(imagem.getSize().x/2, 0.0f);
	// importando a imagem de forma mais geral possível
	imagem.loadFromFile("inimiga-nave-jogo3.png");
    speed=1;
    movimentoTempo = sf::seconds(0);
    atacarTempo = sf::seconds(0);
    movimentoClock.restart();
    atacarClock.restart();
	texture.loadFromImage(imagem);
	spriteNave.setTexture(texture);
    spriteNave.setPosition(sf::Vector2f(300,300));
    posicaoHeroi=sf::Vector2f(0,0);
	spriteNave.setOrigin(imagem.getSize().x/2, imagem.getSize().y/2);
    setPositionTiro(sf::Vector2f(1,0));
    spriteNave.setScale(sf::Vector2f(spriteNave.getScale().x/1.4,spriteNave.getScale().y/1.4));
}
void NaveInimigo::setId(int x){
    id=x;
};
int NaveInimigo::getId(){
    
    return id;
};
bool NaveInimigo::getAtirou(){
	return atirou;
};
void NaveInimigo::resetAtirou(){
	 atirou=false;
};
void NaveInimigo::setPositionTiro(const sf::Vector2f & posicao){
	this->posicaoT = posicao;
};

void NaveInimigo::setDirecaoTiro(const sf::Vector2f & direcao){
	this->direcaoT = direcao;
};
NaveInimigo::NaveInimigo(string s){
// 	vel=0;
//     speedT=0;
//     achou=false;
// 	anguloAtual = 0;
// 	direcao = sf::Vector2f(1.0f,0.0f);
// 	frente = sf::Vector2f(imagem.getSize().x/2, 0.0f);
// 	// importando a imagem de forma mais geral possível
// 	imagem.loadFromFile(s);
//     speed=1;
//     movimentoTempo = sf::seconds(0);
//     atacarTempo = sf::seconds(0);
//     movimentoClock.restart();
//     atacarClock.restart();
// 	texture.loadFromImage(imagem);
// 	spriteNave.setTexture(texture);
//     spriteNave.setPosition(sf::Vector2f(300,300));
//     posicaoHeroi=sf::Vector2f(0,0);
// 	spriteNave.setOrigin(imagem.getSize().x/2, imagem.getSize().y/2);
//     setPositionTiro(sf::Vector2f(1,0));
};

NaveInimigo::~NaveInimigo(){
};
sf::RectangleShape NaveInimigo::visao(sf::Sprite heroi){
    sf::RectangleShape raio;
    sf::RectangleShape nave;
    sf::RectangleShape retanguloHeroi;
    raio.setFillColor(sf::Color(255,0,0));
    raio.setSize(sf::Vector2f(600,1));
    nave.setSize(sf::Vector2f(20,20));
    nave.setFillColor(sf::Color(255,0,255));
    nave.setPosition(sf::Vector2f(heroi.getPosition().x - 10 ,heroi.getPosition().y - 10));
    retanguloHeroi.setSize(sf::Vector2f(200,200));
    retanguloHeroi.setFillColor(sf::Color(0,255,0));
    retanguloHeroi.setPosition(sf::Vector2f(heroi.getPosition().x - 100 ,heroi.getPosition().y - 100));
    raio.setPosition(spriteNave.getPosition());
    localTiro = raio.getPosition();
//     direcaoT = heroi.getPosition() - 
    float norma = sqrt((heroi.getPosition().x -  spriteNave.getPosition().x)*(heroi.getPosition().x -  spriteNave.getPosition().x) + (heroi.getPosition().y -  spriteNave.getPosition().y)*(heroi.getPosition().y -  spriteNave.getPosition().y));
    float graus = asin((spriteNave.getPosition().y - heroi.getPosition().y) / norma);
    graus =  -(graus * 180)/3.14;
    if(heroi.getPosition().x - spriteNave.getPosition().x < 0 )
        graus=180 - graus;
    raio.setRotation(graus);
    spriteNave.setRotation(graus);
        if(raio.getGlobalBounds().intersects(nave.getGlobalBounds()) ){
            if(!spriteNave.getGlobalBounds().intersects(retanguloHeroi.getGlobalBounds())){
                Mover(heroi.getPosition(),norma);
            }else{
                atacarTempo= atacarClock.getElapsedTime();
                if(atacarTempo > sf::seconds(2.5)){
                    atirou = true;
                    atacarClock.restart();
                }
            }
        }
    return raio;
}
void NaveInimigo::Mover(sf::Vector2f heroi,float norma){
    
    movimentoTempo= movimentoClock.getElapsedTime();
     if(movimentoTempo > sf::seconds(0.05)){
        movimentoClock.restart();
        if(heroi != posicaoHeroi){
            achou=false;
            speed=0;
            spriteNave.setPosition(sf::Vector2f(speed* (heroi.x -  spriteNave.getPosition().x)/norma + spriteNave.getPosition().x,
                speed*(heroi.y -  spriteNave.getPosition().y)/norma + spriteNave.getPosition().y
            ));
            posicaoHeroi=heroi;
        }else{
            speed= speed + 0.5;
            spriteNave.setPosition(sf::Vector2f(speed*(heroi.x -  spriteNave.getPosition().x)/norma + spriteNave.getPosition().x,
                speed*(heroi.y -  spriteNave.getPosition().y)/norma + spriteNave.getPosition().y
            ));
        }
        
    }
}

void NaveInimigo::setPosition(const sf::Vector2f & v){
	spriteNave.setPosition(v);
};

sf::Sprite NaveInimigo::getSprite() const{
	return spriteNave;
};

float NaveInimigo::getAngulo() const{
	return anguloAtual;
};

float NaveInimigo::getVel() const{
	return vel;
}
#endif
