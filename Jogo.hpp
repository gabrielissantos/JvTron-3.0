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
	Nave * nave;
	Lista<Tiro> tiros;
	unsigned short int municao;
public:
	Jogo();
	~Jogo();
	virtual int Executar(sf::RenderWindow&);
};

Jogo::Jogo(){
	municao = 3; // numero
	nave = new Nave("inimigo.png");
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
	Tiro tiroTemplate;
	Lista <Tiro> * aux = new Lista<Tiro>;
	// auxiliares pra posicao
/*	sf::RectangleShape linhaAux1;
	linhaAux1.setPosition(sf::Vector2f(0, altura/2));
    linhaAux1.setFillColor(sf::Color(0,255,255));
    linhaAux1.setSize(sf::Vector2f(largura, 1.0f ));
    
    sf::RectangleShape linhaAux2;
	linhaAux2.setPosition(sf::Vector2f(largura/2, 0));
    linhaAux2.setFillColor(sf::Color(0,255,255));
    linhaAux2.setSize(sf::Vector2f(1.0f, altura ));
*/
    // comecando no meio
	nave->setPosicao(sf::Vector2f(largura/2,altura/2));
	tiroTemplate.setPosition(nave->getFrente());

	// zerando iteradorTiros
//	for(int i; i<municao; i++)
//		iteradorTiros = 0;

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
						if(!atirou){
							tiroTemplate.setDirecao(nave->getDirecao());
							tiroTemplate.setPosition(nave->getFrente());
						}
						break;
					case sf::Keyboard::Right:
						nave->rodaHorario();
						if(!atirou){
							tiroTemplate.setDirecao(nave->getDirecao());
							tiroTemplate.setPosition(nave->getFrente());
						}
						break;
					case sf::Keyboard::End:
						App.close();
						return (-1);
						break;
					case sf::Keyboard::Space:
						if(contaTiros < 3){
							contaTiros++;
						}

						// aqui era pra setar quantos tiros estão prontos pra andar
						if(contaTiros > 0){
							while(tiros.getQuant()>0){ // zera a fila
								tiros.remove(tiroTemplate, deuCerto);
								aux->insere(tiroTemplate, deuCerto);
							}
							// aqui era pra setar
							for(int i=0; i<municao; i++){
								aux->remove(tiroTemplate, deuCerto);
								if(tiroTemplate.getIterador()==-1 && i < contaTiros){
									std::cout << "tadaima: "<< contaTiros << std::endl;
									tiroTemplate.comecaMover();
								}else tiroTemplate.paraNavegar();
								tiros.insere(tiroTemplate, deuCerto);
							}
						}
						//tiroTemplate->navega(10.0f);
						break;
				}
			}
		}


		// rotina para atirar:
		App.clear(sf::Color(32,32,32)); // limpa a tela

		// determinando quantos tiros vai dar.

		for(int i=0; i < municao; i++){
			tiros.remove(tiroTemplate, deuCerto);
			if(tiroTemplate.getIterador() != -11 && tiroTemplate.getIterador() < 400){ // n sei pq mas isso funciona no -11
				tiroTemplate.navega(10.0f);
				//std::cout<<tiroTemplate.getIterador()<<std::endl;
				App.draw(tiroTemplate.getForma());
				tiros.insere(tiroTemplate, deuCerto);
			}else if(tiroTemplate.getIterador() == 400){ // parar de andar no 400
				std::cout << "tadaima!!" << std::endl;
				tiroTemplate.setDirecao(nave->getDirecao());
				tiroTemplate.setPosition(nave->getFrente());
				tiroTemplate.paraNavegar();
				contaTiros--;
			}
		}

		// isso era pra exibir mesmo em que posição cada um tá
		for(int i = 0; i < municao; i++){
			tiros.remove(tiroTemplate, deuCerto);
			std::cout << tiroTemplate.getIterador() << " ";
			tiros.insere(tiroTemplate, deuCerto);
		}
		std::cout << contaTiros << std::endl;

		App.draw(nave->getSprite());
		App.display();
	//	std::cout << contaTiros << std::endl;
	}
};