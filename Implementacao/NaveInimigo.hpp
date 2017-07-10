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
#ifndef NAVEINIMIGO_H
#define NAVEINIMIGO_H
#include <iostream>
#include <string>
#include <math.h>
#include <SFML/Graphics.hpp>
using std::string;

class NaveInimigo{
	public:
		void setPosition(const sf::Vector2f &); // determina posição
		void rodaAntiHorario(); // faz a nave rodar no sentido anti-horário
		void rodaHorario(); // faz a nave rodar no sentido horário
		void andaFrente(const float &); // faz a nave andar pra frente
		float getAngulo() const;
		sf::Sprite getSprite() const; // retorna a instancia de sprite
		sf::Vector2f getPosition() const; // retorna a posicao da nave
		sf::RectangleShape visao(sf::Sprite heroi);   //visao da nave inimiga
        bool getAtirou();   //verifica se a nave atirou
        void resetAtirou(); //deixa que a nave não atirou
        sf::Vector2f getLocalTiro(); // pega o posicao do tiro
        void setId(int);    //set o id da nave
        int getId();        //pega o id da nave
        void criarNave();   //cria a nave
        sf::Sprite spriteNave; // instancia de sprite
		sf::Texture texture; // instancia de textura
		sf::Image imagem; 
	private:
        int id;     //id da nave
		float anguloAtual; // angulo atual relativo
		float posicaoAtual; //posicao atual relativa
        sf::Vector2f posicaoT; // posicao do inicio do tiro
		sf::Vector2f direcaoT; // para onde aponta o tiro
		int vidas;    //int de vida
        sf::Vector2f posicaoHeroi; //posicao do heroi
		sf::Vector2f direcao; // direcao q a nave aponta
		sf::Vector2f frente; // parte de frente da nave
		sf::Vector2f posicao; //posicao que a nave ocupa// arquivo de iamgem		
        float speed;
        void setPositionTiro(const sf::Vector2f &); //seta a posicao do tiro
		void setDirecaoTiro(const sf::Vector2f &); //seta a direcao do tiro
        bool achou; //achou o inimigo
        sf::Clock movimentoClock; //clock do movimento
        sf::Time movimentoTempo; // tempo para o movimento
        sf::Clock atacarClock; //clock do ataque
        sf::Time atacarTempo; //tempo do ataque
        void Mover(sf::Vector2f heroi,float); // move a nave
        bool atirou;    //bool do tiro
        sf::Vector2f localTiro; //local do tiro
}; // angulo de rotacao em radianos
sf::Vector2f NaveInimigo::getLocalTiro(){
    return localTiro;
}
//cria a nave
void NaveInimigo::criarNave(){
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
//visao da nave inimiga - verifica onde o heroi esta , gira para ele e comeca a ir na sua direcao
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

//move a nave inimiga
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

#endif
