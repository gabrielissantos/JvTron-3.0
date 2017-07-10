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
#include "NaveInimigo.hpp"
#include "Lista.hpp"
#include "Pilha.hpp"
#include "Fila.hpp"

const short int maxNumeroVidas = 3; // constante de maximo numero de vidas

class Jogo : public Tela{
private:
    //listas de tiro
	Lista <Tiro> tiros;
    Lista <Tiro> tirosInimigo;
    
    //lista de inimigos
    Lista <NaveInimigo> navesInimigas;
    
    //nave do heroi
	Nave * nave;
	sf::Sprite background;
    //quantidade de tiros do heori e do inimigo
    int quantTirosHeroi;
    int quantTirosInimigo;
    //quantidade de inimigos
    int quantInimigo;
    //musicas
	sf::Music tiro;
	sf::Music atinge;
    sf::Font fonte;
    //texto do score
    sf::Text scoreText;
    NaveInimigo naveInimigo;
	void obedecerToroide(Nave*, const float &, const float &);
public:
	Jogo();
	~Jogo();
    void gerarInimigos();
	virtual int Executar(sf::RenderWindow&,int &score);
};

Jogo::Jogo(){
	quantInimigo=0;
	nave = new Nave("heroi-nave-jogo3.png");
    
    //cria a lista inimigos
    navesInimigas.cria();
    
    //set os valores da nave
    naveInimigo.criarNave();
    naveInimigo.resetAtirou();
    naveInimigo.texture.loadFromFile("inimiga-nave-jogo3.png");
    naveInimigo.spriteNave.setTexture(naveInimigo.texture);
    
    fonte.loadFromFile("Tr2n.ttf");
    scoreText.setCharacterSize(30);
	scoreText.setFont(fonte);
	scoreText.setColor(sf::Color(255,255,255));
};

Jogo::~Jogo(){
	delete nave;
};
void Jogo::gerarInimigos(){
    bool deuCerto;
    int i;
    //decide qual canto as naves irão nascer
    int canto;
    
    if(navesInimigas.getQuant()  == 0 ){
        
        for(i =0 ; i<4;i++){
            naveInimigo.setId(quantInimigo);
            quantInimigo++;
            canto = rand() % 4;
            switch(canto){
                case 0:
                    naveInimigo.setPosition(sf::Vector2f(0 , rand() %  600 ));
                    break;
                case 1:
                    naveInimigo.setPosition(sf::Vector2f(800 , rand() %  600 ));
                    break;
                case 2:
                    naveInimigo.setPosition(sf::Vector2f(rand() % 800 ,   0 ));
                    break;
                case 3:
                    naveInimigo.setPosition(sf::Vector2f(rand() % 800 ,   600 ));
                    break;
            }
            //insere a nave gerada na lista def inimigos
            navesInimigas.insere(naveInimigo,deuCerto);
        }
    }
};
int Jogo::Executar(sf::RenderWindow & App,int &score){
	// armazenando o tamanho atual da tela
	float iteradorVel = 0; // auxiliar para velocidade da nave
	bool inercia = false;
    quantTirosHeroi = 0;
    quantTirosInimigo =0;
	float altura = App.getSize().y;
	float largura = App.getSize().x;
	bool atirou = false;
    
    //pega os arquivos de som
    tiro.openFromFile("atinge-inimigo.ogg");
    atinge.openFromFile("mata-inimigo.ogg");
    
    //pilha de sprites para a vida
	Pilha<sf::Sprite> vidas;
	sf::Sprite auxVidas;
    
	bool deuCerto = true;
    
    //bool para verificar se adi
    bool adicionarTiro =false;
    
    Tiro tiroAuxSpace;
    //cria as listas de tiro
    tiros.cria();
    tirosInimigo.cria();
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
            templateSpriteVida[i].setScale(sf::Vector2f(templateSpriteVida[i].getScale().x/1.3,templateSpriteVida[i].getScale().y/1.3));
			templateSpriteVida[i].setPosition(sf::Vector2f(10.0f, 590.0f - texturaVida[i].getSize().y ));
			vidas.Empilha(templateSpriteVida[i], deuCerto);
		}
	}
	// auxiliares pra posicao
	sf::Texture texturaInimigo;
    sf::RectangleShape olha;
    

    // comecando no meio
	nave->setPosition(sf::Vector2f(largura/2,altura/2));
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
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                nave->andaFrente(2);
                if(!atirou){
                    tiroAuxSpace.setPosition(nave->getFrente());
                    tiroAuxSpace.setDirecao(nave->getDirecao());
				}
						// estrutura do toroide para a nave heroi
                obedecerToroide(nave, largura, altura);
            }else{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
					
						nave->rodaAntiHorario();
						if(!atirou){
							tiroAuxSpace.setPosition(nave->getFrente());
                            tiroAuxSpace.setDirecao(nave->getDirecao());
						}
                }else{
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ 
						nave->rodaHorario();
						if(!atirou){
							tiroAuxSpace.setPosition(nave->getFrente());
                            tiroAuxSpace.setDirecao(nave->getDirecao());
						}
                    }else{
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                            adicionarTiro = true;
                            tiroAuxSpace.setPosition(nave->getFrente());
                            tiroAuxSpace.setDirecao(nave->getDirecao());
                        }
                    }
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

		if(!vidas.Vazia()){
			App.draw(vidas.getTopo());
		}else{ 
            return(2); // sem vidas, fim de jogo
        }
		// efeito do asteroids
		if(inercia){
			nave->andaFrente(-1);
			if(nave->getVel()==0) inercia = false;
            
			obedecerToroide(nave, largura, altura);
			
				tiroAuxSpace.setPosition(nave->getFrente());
                tiroAuxSpace.setDirecao(nave->getDirecao());
			
		}
		//adiciona um novo tiro na lista de tiros do heroi
        if(adicionarTiro){
            tiro.play();
            tiroAuxSpace.setId(quantTirosHeroi);
            quantTirosHeroi++;
            tiroAuxSpace.comecaMover();
            tiros.insere(tiroAuxSpace, deuCerto);
            adicionarTiro = false;
        }
        //percorre a lista de inimigos
        Tiro auxTiroInimigo;
        tirosInimigo.PegaOPrimeiro(auxTiroInimigo,deuCerto);
         while(deuCerto){
            App.draw(auxTiroInimigo.getForma());
            if(auxTiroInimigo.getForma().getGlobalBounds().intersects(nave->getSprite().getGlobalBounds())){
                tirosInimigo.removeP(auxTiroInimigo,deuCerto);
                vidas.Desempilha(auxVidas, deuCerto);
                atinge.play();
            }else{
                auxTiroInimigo.navega(0.03f);
                tirosInimigo.atualizaP(auxTiroInimigo,deuCerto);
            }
            tirosInimigo.PegaOProximo(auxTiroInimigo,deuCerto);
        }
        NaveInimigo auxNaveInimiga;
        auxNaveInimiga.criarNave();
        navesInimigas.PegaOPrimeiro(auxNaveInimiga,deuCerto);
        bool morreu=false;
        int movimentaTiros = 0;
        while(deuCerto){
            App.draw(auxNaveInimiga.spriteNave);
            Tiro auxTiro;
            tiros.PegaOPrimeiro(auxTiro,deuCerto);
            while(deuCerto){
                App.draw(auxTiro.getForma());
            
                if(auxTiro.getForma().getGlobalBounds().intersects(auxNaveInimiga.getSprite().getGlobalBounds())){
                    tiros.removeP(auxTiro,deuCerto);
                    score+=10;
                    atinge.play();
                    navesInimigas.removeP(auxNaveInimiga,deuCerto);
                    morreu=true;
                }else{
                    if(movimentaTiros == 0){
                        auxTiro.navega(10.0f);
                        tiros.atualizaP(auxTiro,deuCerto);
                        movimentaTiros;
                    }
                }
                tiros.PegaOProximo(auxTiro,deuCerto);
            }
            movimentaTiros++;
            if(!morreu){
                auxNaveInimiga.visao(nave->getSprite());
                if(auxNaveInimiga.getAtirou()){
                    tiro.play();
                    Tiro tiroAuxInimigo;
                    tiroAuxInimigo.setId(quantTirosInimigo);
                    quantTirosInimigo++;
                    tiroAuxInimigo.comecaMover();
                    tiroAuxInimigo.setPosition(auxNaveInimiga.getLocalTiro());
                    tiroAuxInimigo.setDirecao( nave->getSprite().getPosition() - auxNaveInimiga.getSprite().getPosition());
                    tirosInimigo.insere(tiroAuxInimigo, deuCerto);
                    auxNaveInimiga.resetAtirou();
                }
                navesInimigas.atualizaP(auxNaveInimiga,deuCerto);
                morreu = false;
            }
            navesInimigas.PegaOProximo(auxNaveInimiga,deuCerto);
        }
        App.draw(nave->getSprite());
        
		std::cout << nave->getVel() << std::endl;
        std::string strgScore= std::to_string(score);
        scoreText.setString("Score : " +  strgScore);
        scoreText.setPosition(sf::Vector2f(700 - scoreText.getCharacterSize()*3.5, 550.f));
        App.draw(scoreText);
		App.display();
        
        gerarInimigos();
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
        
    nave->resetFrente();
};
