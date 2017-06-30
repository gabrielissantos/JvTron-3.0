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
		sf::Sprite getSprite() const; // retorna a instancia de sprite
		sf::Vector2f getFrente() const; // retorna a frente da nave
		sf::Vector2f getDirecao() const;
		float getAngulo() const;
	private:
		float x; // posicao (horizontal)
		float y; // posicao (vertical)
		float anguloAtual;

		sf::Vector2f direcao; // direcao q a nave aponta
		sf::Vector2f frente; // parte de frente da nave
		sf::Sprite spriteNave; // instancia de sprite
		sf::Texture texture; // instancia de textura
		sf::Image imagem; // arquivo de iamgem
};

const float anguloRotacao = 1*3.14/18;

Nave::Nave(string s){
	// importando a imagem de forma mais geral possível
	anguloAtual = 0;
	direcao = sf::Vector2f(1.0f,0.0f);
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
	spriteNave.rotate(10);
	anguloAtual = anguloAtual + anguloRotacao;
	if(anguloAtual >= 3.14*2 - anguloRotacao) anguloAtual = 0;
	frente = sf::Vector2f(x,y) + sf::Vector2f(cos(anguloAtual)*imagem.getSize().x/2, sin(anguloAtual)*imagem.getSize().x/2);
	direcao= sf::Vector2f(cos(anguloAtual), sin(anguloAtual));
	//std::cout << "direcao: " << direcao.x << "; " << direcao.y << std::endl; 
};

void Nave::rodaAntiHorario(){
	spriteNave.rotate(-10);
	anguloAtual -= anguloRotacao;
	if(anguloAtual <= -3.14*2 + anguloRotacao) anguloAtual = 0;
	frente = sf::Vector2f(x,y) + sf::Vector2f(cos(anguloAtual)*imagem.getSize().x/2, sin(anguloAtual)*imagem.getSize().x/2);
	direcao= sf::Vector2f(cos(anguloAtual), sin(anguloAtual));
	//std::cout << "direcao: " << direcao.x << "; " << direcao.y << std::endl;
};

sf::Vector2f Nave::getFrente() const{
	return frente;
};

sf::Vector2f Nave::getDirecao() const{
	return direcao;
};

float Nave::getAngulo() const{
	return anguloAtual;
};