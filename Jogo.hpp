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
#include "Tiro.hpp"
#include "Nave.hpp"
#include "Lista.hpp"

class Jogo : public Tela{
private:
	Lista <Tiro> tiros;
	Nave * nave;
	unsigned short int municao;
public:
	Jogo();
	~Jogo();
	virtual int Executar(sf::RenderWindow&);
};

Jogo::Jogo(){
	municao = 1; // numero
	nave = new Nave("heroi-nave-jogo3.png");
};

Jogo::~Jogo(){
	delete nave;
};

int Jogo::Executar(sf::RenderWindow & App){
	// armazenando o tamanho atual da tela
	float altura = App.getSize().y;
	float largura = App.getSize().x;
	bool atirou = false;

	int contaTiros = 0;
	int iteradorTiros = 0;

	bool deuCerto;
	Tiro tAux;
	Lista <Tiro> * aux = new Lista<Tiro>;
	// auxiliares pra posicao
	sf::RectangleShape linhaAux1;
	linhaAux1.setPosition(sf::Vector2f(0, altura/2));
    linhaAux1.setFillColor(sf::Color(0,255,255));
    linhaAux1.setSize(sf::Vector2f(largura, 1.0f ));

    sf::RectangleShape linhaAux2;
	linhaAux2.setPosition(sf::Vector2f(largura/2, 0));
    linhaAux2.setFillColor(sf::Color(0,255,255));
    linhaAux2.setSize(sf::Vector2f(1.0f, altura ));

    // comecando no meio
	nave->setPosicao(sf::Vector2f(largura/2,altura/2));
	tAux.setPosition(nave->getFrente());
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
					//tecla de cima
					case sf::Keyboard::Up:
						nave->andaFrente();
						if(!atirou){
							tAux.setPosition(nave->getFrente());
							tAux.setDirecao(nave->getDirecao());
						}
						break;
					//tecla da esquerda
					case sf::Keyboard::Left:
						nave->rodaAntiHorario();
						if(!atirou){
							tAux.setDirecao(nave->getDirecao());
							tAux.setPosition(nave->getFrente());
							//std::cout << "direcao: " << nave->getDirecao().x << "; " << nave->getDirecao().y << std::endl; 
						}
						break;
					//tecla da direita
					case sf::Keyboard::Right:
						nave->rodaHorario();
						if(!atirou){
							tAux.setDirecao(nave->getDirecao());
							tAux.setPosition(nave->getFrente());
						}
						break;
					case sf::Keyboard::End:
						App.close();
						return (-1);
						break;
					case sf::Keyboard::D:
						if(!atirou){
							atirou = true;
							tAux.setPosition(nave->getFrente());
							tAux.setDirecao(nave->getDirecao());
						}
						break;
				}
			}
		}
//		std::cout << iteradorTiros << std::endl;
		// rotina para atirar:
		App.clear(sf::Color(32,32,32)); // limpa a tela

		if(atirou && iteradorTiros < 800){
			//tAux.setDirecao(nave->getDirecao());
			tAux.setPosition(nave->getFrente());
			tAux.navega(10.0f);
			App.draw(tAux.getForma());
			iteradorTiros += 10;
		}
		if(iteradorTiros == 800){
			iteradorTiros = 0;
			tAux.paraNavegar();
			//tAux.setDirecao(nave->getDirecao());
			//tAux.setPosition(nave->getFrente());
		//	std::cout << "atirou" << std::endl;
			atirou = false;
		}
		App.draw(nave->getSprite());
		App.display();
	}
};