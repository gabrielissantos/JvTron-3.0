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

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tela.hpp"
#include "Nave.hpp"

class Jogo : public Tela{
private:
	Nave * nave;
public:
	Jogo();
	~Jogo();
	virtual int Executar(sf::RenderWindow&);
};

Jogo::Jogo(){
	nave = new Nave("inimigo.png");
};

Jogo::~Jogo(){
	delete nave;
};

int Jogo::Executar(sf::RenderWindow & App){
	float altura = App.getSize().y;
	float largura = App.getSize().x;
	sf::RectangleShape linhaAux1;
	linhaAux1.setPosition(sf::Vector2f(0, altura/2));
    linhaAux1.setFillColor(sf::Color(0,255,255));
    linhaAux1.setSize(sf::Vector2f(largura, 1.0f ));

    sf::RectangleShape linhaAux2;
	linhaAux2.setPosition(sf::Vector2f(largura/2, 0));
    linhaAux2.setFillColor(sf::Color(0,255,255));
    linhaAux2.setSize(sf::Vector2f(1.0f, altura ));

	nave->setPosicao(sf::Vector2f(largura/2,altura/2));
	//  Aqui q vai tudo do jogo. 
	sf::Event evento; // eventos de jogo
	bool executando = true;
	while (executando){ // loop da tela
		// Verificação de eventos
		while (App.pollEvent(evento)){ // loop de eventos
			if (evento.type == sf::Event::Closed){
				return (-1);
			}
			if (evento.type == sf::Event::KeyPressed){
				switch(evento.key.code){
					case sf::Keyboard::Left:
						nave->rodaAntiHorario();
						break;
					case sf::Keyboard::Right:
						nave->rodaHorario();
						break;
					case sf::Keyboard::End:
						App.close();
						return (-1);
						break;
				}
			}
		}
		App.clear(sf::Color(32,32,32));
		App.draw(linhaAux1);
		App.draw(linhaAux2);
		App.draw(nave->getSprite());
		App.display();
	}
};