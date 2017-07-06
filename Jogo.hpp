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
#include "Pilha.hpp"
#include "Fila.hpp"

const short int maxNumeroVidas = 3; // constante de maximo numero de vidas

class Jogo : public Tela{
private:
	Fila <Tiro> tiros;
	Nave * nave;
	unsigned short int municao;
	sf::Sprite background;
	sf::Music tiro;
	sf::Music atinge;
	void obedecerToroide(Nave*, const float &, const float &);
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
	float iteradorVel = 0; // auxiliar para velocidade da nave
	bool inercia = false;

	float altura = App.getSize().y;
	float largura = App.getSize().x;
	bool atirou = false;

	Pilha<sf::Sprite> vidas;
	sf::Sprite auxVidas;
	int contaTiros = 0; // conta tiros do heroi
	bool deuCerto = true;
	Tiro tAux, tiroTemplate;

	// background
	sf::Texture texturaBackground;
	texturaBackground.loadFromFile("back-jogo3.jpg");
	background.setTexture(texturaBackground);

	// imagens pra vida
	sf::Image imagemVida[maxNumeroVidas];
	sf::Texture texturaVida[maxNumeroVidas];
	sf::Sprite templateSpriteVida[maxNumeroVidas];

	// carregando pilha de vidas
	if(vidas.Vazia()){
		for(int i=0; i<maxNumeroVidas; i++){
			imagemVida[i].loadFromFile(std::to_string(i+1)+"vidas.png");
			texturaVida[i].loadFromImage(imagemVida[i]);
			templateSpriteVida[i].setTexture(texturaVida[i]);
			templateSpriteVida[i].setPosition(sf::Vector2f(50.0f, 50.0f));
			vidas.Empilha(templateSpriteVida[i], deuCerto);
		}
	}

	// auxiliares pra posicao
	sf::Texture texturaInimigo;
	sf::Image imagemInimigo;
	sf::Sprite spriteInimigo;
	imagemInimigo.loadFromFile("inimiga-nave-jogo3.png");
	texturaInimigo.loadFromImage(imagemInimigo);
	spriteInimigo.setTexture(texturaInimigo);
	spriteInimigo.setOrigin(sf::Vector2f(imagemInimigo.getSize().x/2,imagemInimigo.getSize().y/2));
	spriteInimigo.rotate(180);
	spriteInimigo.setPosition(sf::Vector2f(500, 60.0f));

    // comecando no meio
	nave->setPosition(sf::Vector2f(largura/2,altura/2));
	tiroTemplate.setPosition(nave->getFrente());
	deuCerto = true;
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
						nave->andaFrente(2); // tem q ser inteiro pq, se nao, n da pra chegar a 0 com double (wtf, neh)
						if(!atirou){
							tiroTemplate.setPosition(nave->getFrente());
							tiroTemplate.setDirecao(nave->getDirecao());
						}
						// estrutura do toroide para a nave heroi
						obedecerToroide(nave, largura, altura);
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
							while(deuCerto) tiros.Retira(tAux, deuCerto);
							atirou = true;
							contaTiros = 0;
						}
						if(contaTiros < 3){
							contaTiros++;
							tiros.Insere(tiroTemplate, deuCerto);
						}
						break;
					case sf::Keyboard::D: // teste pra perder vida
						vidas.Desempilha(auxVidas, deuCerto);
						std::cout<<deuCerto<<std::endl;
						break;
				}
			}
			if(evento.type == sf::Event::KeyReleased){
				switch(evento.key.code){
					case sf::Keyboard::Up: // efeito de movimento do asteroids
						inercia = true;
						break;
				}
			}
		}

		App.clear(sf::Color(32,32,32)); // limpa a tela
		App.draw(background);
		// rotina para atirar:
		for(int i=0; i < contaTiros; i++){
			tiros.Retira(tAux, deuCerto);
			if(deuCerto){
				if(tAux.getForma().getGlobalBounds().intersects(spriteInimigo.getGlobalBounds())){ // quando acerta um inimigo
					std::cout << "acertou" << std::endl;
					tAux.paraNavegar();
					if(!atinge.openFromFile("atinge-inimigo.ogg")){
        					std::cout << "ERROR 1" << std::endl;
        					return 1; //retorna um se a leitura da musica não foi efetuada com sucesso
    					}
    				atinge.play(); //inicializa a musica
					contaTiros--;
					if(contaTiros == 0) atirou = false;
				}else{
					if(atirou && tAux.getIterador() < 400){
						tAux.navega(10.0f);
						App.draw(tAux.getForma());
						tiros.Insere(tAux, deuCerto);
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

		if(!vidas.Vazia()){
			App.draw(vidas.getTopo());
		}else return(-1); // sem vidas, fim de jogo

		App.draw(spriteInimigo);
		// efeito do asteroids
		if(inercia){
			nave->andaFrente(-1);
			if(nave->getVel()==0) inercia = false;
			if(!atirou){
				tiroTemplate.setPosition(nave->getFrente());
				tiroTemplate.setDirecao(nave->getDirecao());
			}
			obedecerToroide(nave, largura, altura);
		}
		App.draw(nave->getSprite());
		std::cout << nave->getVel() << std::endl;
		App.display();
	}
};

void Jogo::obedecerToroide(Nave * nave, const float & largura, const float & altura){
	if(nave->getPosition().x > largura)
		nave->setPosition(sf::Vector2f(0.0f,nave->getPosition().y)); // limite direito da tela
	if(nave->getPosition().x < 0)
		nave->setPosition(sf::Vector2f(largura,nave->getPosition().y)); // limite esquerdo da tela
	if(nave->getPosition().y > altura)
		nave->setPosition(sf::Vector2f(nave->getPosition().x, 0.0f)); // limite baixo da tela
	if(nave->getPosition().y < 0)
		nave->setPosition(sf::Vector2f(nave->getPosition().x, altura)); // limite alto da tela}
};