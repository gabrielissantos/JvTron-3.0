#include <iostream>
#include <string>
#include <math.h>
#include <SFML/Graphics.hpp>
using std::string;

class Nave{
	public:
		Nave(string="");
		~Nave();
		void setPosicao(const sf::Vector2f &);
		void rodaAntiHorario();
		void rodaHorario();
		sf::Sprite getSprite() const;
	private:
		float x;
		float y;
		float anguloAtual;
		sf::Vector2f direcao;
		sf::Vector2f frente;
		sf::Sprite spriteNave;
		sf::Texture texture;
		sf::Image imagem;
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
//	std::cout << anguloRotacao << std::endl;
};

Nave::~Nave(){
};

void Nave::setPosicao(const sf::Vector2f & v){
	spriteNave.setPosition(v);
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
	frente = sf::Vector2f(cos(anguloAtual)*imagem.getSize().x/2, sin(anguloAtual)*imagem.getSize().x/2);
	std::cout << std::endl;
	std::cout << anguloAtual << "rad" << std::endl;
	std::cout << frente.x << "; " << frente.y << std::endl;
};

void Nave::rodaAntiHorario(){
	spriteNave.rotate(-10);
	anguloAtual -= anguloRotacao;
	if(anguloAtual <= -3.14*2 + anguloRotacao) anguloAtual = 0;
	frente = sf::Vector2f(cos(anguloAtual)*imagem.getSize().x/2, sin(anguloAtual)*imagem.getSize().x/2);
	//if(anguloAtual >= 3.14*2) anguloAtual = 0;
	std::cout << std::endl;
	std::cout << anguloAtual << "rad" << std::endl;
	std::cout << frente.x << "; " << frente.y << std::endl;
};