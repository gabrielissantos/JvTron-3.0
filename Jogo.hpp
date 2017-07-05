
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
#include <SFML/Audio.hpp>
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
	sf::Music tiro;
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

	int contaTiros = 0; // conta tiros do heroi
	bool deuCerto = true;
	Tiro tAux, tiroTemplate;

	// auxiliares pra posicao
	sf::Texture inimigoTextura;
	sf::Image inimigoImagem;
	sf::Sprite inimigoSprite;
	inimigoImagem.loadFromFile("inimiga-nave-jogo3.png");
	inimigoTextura.loadFromImage(inimigoImagem);
	inimigoSprite.setTexture(inimigoTextura);
	inimigoSprite.setOrigin(sf::Vector2f(inimigoImagem.getSize().x/2,inimigoImagem.getSize().y/2));
	inimigoSprite.rotate(180);
	inimigoSprite.setPosition(sf::Vector2f(100, 60.0f));

    // comecando no meio
	nave->setPosition(sf::Vector2f(largura/2,altura/2));
	tiroTemplate.setPosition(nave->getFrente());
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
							tiroTemplate.setPosition(nave->getFrente());
							tiroTemplate.setDirecao(nave->getDirecao());
						}
						// estrutura do toroide
						if(nave->getPosition().x > largura)
							nave->setPosition(sf::Vector2f(0.0f,nave->getPosition().y)); // limite direito da tela
						if(nave->getPosition().x < 0)
							nave->setPosition(sf::Vector2f(largura,nave->getPosition().y)); // limite esquerdo da tela
						if(nave->getPosition().y > altura)
							nave->setPosition(sf::Vector2f(nave->getPosition().x, 0.0f)); // limite baixo da tela
						if(nave->getPosition().y < 0)
							nave->setPosition(sf::Vector2f(nave->getPosition().x, altura)); // limite alto da tela
						break;
					//tecla da esquerda
					case sf::Keyboard::Left:
						nave->rodaAntiHorario();
						if(!atirou){
							tiroTemplate.setDirecao(nave->getDirecao());
							tiroTemplate.setPosition(nave->getFrente());
							//std::cout << "direcao: " << nave->getDirecao().x << "; " << nave->getDirecao().y << std::endl; 
						}
						break;
					//tecla da direita
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
						tiroTemplate.comecaMover();
						tiroTemplate.setPosition(nave->getFrente());
						tiroTemplate.setDirecao(nave->getDirecao());
						if(!tiro.openFromFile("laser.ogg")){
        					std::cout << "ERROR 1" << std::endl;
        					return 1; //retorna um se a leitura da musica não foi efetuada com sucesso
    					}
    					tiro.play(); //inicializa a musica
						if(!atirou){ // 1a vez atirando
							while(deuCerto) tiros.remove(tAux, deuCerto);
							atirou = true;
							contaTiros = 0;
						}
						if(contaTiros < 3){
							contaTiros++;
							tiros.insere(tiroTemplate, deuCerto);
						}
						break;
				}
			}
		}

		App.clear(sf::Color(32,32,32)); // limpa a tela

		// rotina para atirar:
		for(int i=0; i < contaTiros; i++){
			tiros.remove(tAux, deuCerto);
			if(deuCerto){
				if(tAux.getForma().getGlobalBounds().intersects(inimigoSprite.getGlobalBounds())){ // quando acerta um inimigo
					std::cout<<"tadaima"<<std::endl;
					tAux.paraNavegar();
					contaTiros--;
					if(contaTiros == 0) atirou = false;
				}else{
					if(atirou && tAux.getIterador() < 400){
						tAux.setPosition(nave->getFrente());
						tAux.navega(10.0f);
						App.draw(tAux.getForma());
						tiros.insere(tAux, deuCerto);
					}else{ 
						if(tAux.getIterador() == 400){
							tAux.paraNavegar();
							contaTiros--;
							if(contaTiros == 0)	atirou = false;
						}
					}
				}
			}
		}

		App.draw(inimigoSprite);
		App.draw(nave->getSprite());
		App.display();
	}
};