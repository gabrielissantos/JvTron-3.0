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
	Lista <Tiro> tiros;
    Lista <Tiro> tirosInimigo;
    Lista <NaveInimigo> navesInimigas;
    sf::RectangleShape a;
	Nave * nave;
	unsigned short int municao;
	sf::Sprite background;
    int quantTirosHeroi;
    int quantTirosInimigo;
    int quantInimigo;
	sf::Music tiro;
	sf::Music atinge;
    sf::Font fonte;
    sf::Text scoreText;
    int score;
    NaveInimigo naveInimigo;
	void obedecerToroide(Nave*, const float &, const float &);
public:
	Jogo();
	~Jogo();
    void gerarInimigos();
	virtual int Executar(sf::RenderWindow&);
};

Jogo::Jogo(){
	municao = 1; // numero
	quantInimigo=0;
	nave = new Nave("heroi-nave-jogo3.png");
    
    navesInimigas.cria();
    
    naveInimigo.criarNave();
    score=0;
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
    
    if(navesInimigas.getQuant()  == 0 ){
        
        for(i =0 ; i<4;i++){
            naveInimigo.setId(quantInimigo);
            quantInimigo++;
            naveInimigo.setPosition(sf::Vector2f(rand() %  500 + 100 , rand() %  300 + 100 ));
            navesInimigas.insere(naveInimigo,deuCerto);
        }
    }
};
int Jogo::Executar(sf::RenderWindow & App){
	// armazenando o tamanho atual da tela
	float iteradorVel = 0; // auxiliar para velocidade da nave
	bool inercia = false;
    quantTirosHeroi = 0;
    quantTirosInimigo =0;
	float altura = App.getSize().y;
	float largura = App.getSize().x;
	bool atirou = false;

	Pilha<sf::Sprite> vidas;
	sf::Sprite auxVidas;
	int contaTiros = 0; // conta tiros do heroi
	bool deuCerto = true;
	Tiro  tiroTemplate;
    bool adicionarTiro =false;
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
                        adicionarTiro = true;
// 						if(!tiro.openFromFile("laser.ogg")){
//         					std::cout << "ERROR 1" << std::endl;
//         					return 1; //retorna um se a leitura da musica não foi efetuada com sucesso
//     					}
//     					tiro.play(); //inicializa a musica
// 						if(!atirou){ // 1a vez atirando
// 							while(deuCerto) tiros.Retira(tAux, deuCerto);
// 							atirou = true;
// 							contaTiros = 0;
// 						}
// 						if(contaTiros < 3){
// 							contaTiros++;
//                             tiros.Insere(tiroTemplate, deuCerto);
// 							tiros.Insere(tiroTemplate, deuCerto);
// 						}
// 						
                        break;
					case sf::Keyboard::D: // teste pra perder vida
						//vidas.Desempilha(auxVidas, deuCerto);
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
        if(adicionarTiro){
            Tiro tiroAuxSpace;
            tiroAuxSpace.setId(quantTirosHeroi);
            quantTirosHeroi++;
            tiroAuxSpace.comecaMover();
            tiroAuxSpace.setPosition(nave->getFrente());
            tiroAuxSpace.setDirecao(nave->getDirecao());
            tiros.insere(tiroAuxSpace, deuCerto);
            adicionarTiro = false;
        }
		App.clear(sf::Color(32,32,32)); // limpa a tela
		App.draw(background);

		if(!vidas.Vazia()){
			App.draw(vidas.getTopo());
		}else return(-1); // sem vidas, fim de jogo

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
        Tiro auxTiroInimigo;
        tirosInimigo.PegaOPrimeiro(auxTiroInimigo,deuCerto);
         while(deuCerto){
            App.draw(auxTiroInimigo.getForma());
            if(auxTiroInimigo.getForma().getGlobalBounds().intersects(nave->getSprite().getGlobalBounds())){
                tirosInimigo.removeP(auxTiroInimigo,deuCerto);
                vidas.Desempilha(auxVidas, deuCerto);
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
};
// 		// rotina para atirar:
// 		for(int i=0; i < contaTiros; i++){
// 			tiros.Retira(tAux, deuCerto);
// 			if(deuCerto){
// 				if(tAux.getForma().getGlobalBounds().intersects(spriteInimigo.getGlobalBounds())){ // quando acerta um inimigo
// 					std::cout << "acertou" << std::endl;
// 					tAux.paraNavegar();
// 					if(!atinge.openFromFile("atinge-inimigo.ogg")){
//         					std::cout << "ERROR 1" << std::endl;
//         					return 1; //retorna um se a leitura da musica não foi efetuada com sucesso
//     					}
//     				atinge.play(); //inicializa a musica
// 					contaTiros--;
// 					if(contaTiros == 0) atirou = false;
// 				}else{
// 					if(atirou && tAux.getIterador() < 400){
// 						tAux.navega(10.0f);
// 						App.draw(tAux.getForma());
// 						tiros.Insere(tAux, deuCerto);
// 					}else{ 
// 						if(tAux.getIterador() == 400){
// 							tAux.paraNavegar();
// 							contaTiros--;
// 							if(contaTiros == 0)	atirou = false;
// 						}
// 					}
// 				}
// 			}
// 		}

