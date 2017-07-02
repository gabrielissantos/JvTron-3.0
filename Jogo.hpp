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
	Tiro tAux;
	Lista <Tiro> * aux = new Lista<Tiro>;
	// auxiliares pra posicao
/*	sf::RectangleShape linhaAux1;
	linhaAux1.setPosition(sf::Vector2f(0, altura/2));
    linhaAux1.setFillColor(sf::Color(0,255,255));
    linhaAux1.setSize(sf::Vector2f(largura, 1.0f ));
<<<<<<< HEAD
=======

>>>>>>> ea5482e62a693241b7081c208700f798e0f6b121
    sf::RectangleShape linhaAux2;
	linhaAux2.setPosition(sf::Vector2f(largura/2, 0));
    linhaAux2.setFillColor(sf::Color(0,255,255));
    linhaAux2.setSize(sf::Vector2f(1.0f, altura ));
*/
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
					case sf::Keyboard::Up:
						nave->andaFrente();
						if(!atirou){
							tAux.setPosition(nave->getFrente());
							tAux.setDirecao(nave->getDirecao());
						}
						break;
					case sf::Keyboard::Left:
						nave->rodaAntiHorario();
						if(!atirou){
							tAux.setDirecao(nave->getDirecao());
							tAux.setPosition(nave->getFrente());
							//std::cout << "direcao: " << nave->getDirecao().x << "; " << nave->getDirecao().y << std::endl; 
						}

						break;
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
					case sf::Keyboard::Space:
						if(!atirou){
							atirou = true;
							tAux.setPosition(nave->getDirecao());
						}
						if(contaTiros < 3){
							tiros.insere(tAux, deuCerto);
							tiros.insere(tAux, deuCerto);
							tiros.insere(tAux, deuCerto);
							contaTiros++;
						}

						// aqui era pra setar quantos tiros estão prontos pra andar
						if(contaTiros > 0){
							while(tiros.getQuant()>0){ // zera a fila
								tiros.remove(tAux, deuCerto);
								aux->insere(tAux, deuCerto);
							}
							// aqui era pra setar
							for(int i=0; i<municao; i++){
								aux->remove(tAux, deuCerto);
								if(tAux.getIterador()==-1 && i < contaTiros){
									std::cout << "tadaima: "<< contaTiros << std::endl;
									tAux.comecaMover();
								}else tAux.paraNavegar();
								tiros.insere(tAux, deuCerto);
							}
						}
						//tAux->navega(10.0f);
						break;
				}
			}
		}
//		std::cout << iteradorTiros << std::endl;
		// rotina para atirar:
		App.clear(sf::Color(32,32,32)); // limpa a tela

		// determinando quantos tiros vai dar.

		for(int i=0; i < municao; i++){
			tiros.remove(tAux, deuCerto);
			if(tAux.getIterador() != -1 && tAux.getIterador() < 400){ // n sei pq mas isso funciona no -11
				tAux.navega(10.0f);
				//std::cout<<tAux.getIterador()<<std::endl;
				App.draw(tAux.getForma());
				tiros.insere(tAux, deuCerto);
			}else if(tAux.getIterador() == 400){ // parar de andar no 400
				std::cout << "tadaima!!" << std::endl;
				tAux.setDirecao(nave->getDirecao());
				tAux.setPosition(nave->getFrente());
				tAux.paraNavegar();
				contaTiros--;
			}
		}

		// isso era pra exibir mesmo em que posição cada um tá
		for(int i = 0; i < municao; i++){
			tiros.remove(tAux, deuCerto);
			//std::cout << tAux.getIterador() << " ";
			tiros.insere(tAux, deuCerto);
		}
		//std::cout << contaTiros << std::endl;

		App.draw(nave->getSprite());
		App.display();
	}
};