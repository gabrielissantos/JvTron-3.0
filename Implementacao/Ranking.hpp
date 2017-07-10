/*
    JvAsteroids: Trabalho 3
    Departamento de Computação
    UFSCar Universidade Federal de São Carlos
    Disciplina: Estrutura de Dados
    Professor: Roberto Ferrari
    Aluno(a):                               RA:
        João Gabriel Melo Barbirato         726546
        Leonardo de Oliveira Peralta        726556
        Gabrieli Santos                     726523
    
    Controle de Versão: https://github.com/gabrielissantos/JvTron-3.0
*/

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Tela.hpp"
#include "Request.hpp"
// Estrutura do Menu
class Ranking : public Tela{
private:
    const int maxNumeroTeclas; // numero de teclas
	const int maxNumeroBotoes;
	float largura, altura, centrox, centroy; // variáveis pra guardar medidas da tela utilizada
	int numeroItem;
	sf::Text titulo;
	sf::Font fonte;
	sf::Text *botao;
    sf::Text scoreText;
    char nome[3];
    std::string nomeString;
    std::string scoreString;
    int quantNome;
    sf::Text digitaNome;   
    sf::Text Nome;
    
void desenha(sf::RenderWindow &) const;
public: // métodos privados
	Ranking(float larg, float alt);
	~Ranking();
    void MovaParaEsquerda();
	void MovaParaDireita();
	int ItemApertado();
	virtual int Executar(sf::RenderWindow& App,int &score);
};

// Implementação dos métodos do menu

// Construtor
// Recebe como parâmetro a largura e altura (utiliza-se as medidas da janela principal da aplicação)
// Configuração inicial de atributos
Ranking::Ranking(float larg, float alt): maxNumeroTeclas(4), maxNumeroBotoes(2){
std::string textoBotao[maxNumeroBotoes] = { "Enviar", "Voltar"}; // textoBotao do botão

	numeroItem = 0;
	botao = new sf::Text[maxNumeroBotoes]; // vetor de botoes

	// variaveis das medidas
	largura = larg;
	altura = alt;
	centrox = largura/2;
	centroy = altura/2;
    nome[0]=' ';
    nome[1]=' ';
    nome[2]=' ';
    quantNome=0;
	if (!fonte.loadFromFile("Tr2n.ttf")){} // fonte das letras

	// inicializando titulo
	titulo.setCharacterSize(50);
	titulo.setString("Enviar Score");
	titulo.setFont(fonte);
	titulo.setPosition(sf::Vector2f(centrox - titulo.getCharacterSize()*3.5, centroy-altura*1/3 + titulo.getCharacterSize() - 150));
	titulo.setColor(sf::Color(0,255,255));
    
    digitaNome.setCharacterSize(30);
	digitaNome.setString("Digite o seu nome :");
	digitaNome.setFont(fonte);
	digitaNome.setPosition(sf::Vector2f(100,100));
	digitaNome.setColor(sf::Color(255,255,255));
    Nome.setCharacterSize(30);
	Nome.setFont(fonte);
	Nome.setPosition(sf::Vector2f(100, 150));
	Nome.setColor(sf::Color(255,255,255));
    scoreText.setCharacterSize(30);
	scoreText.setFont(fonte);
	scoreText.setPosition(sf::Vector2f(100, 200));
	scoreText.setColor(sf::Color(255,255,255));

	// inicializando botoes
	for(int i=0; i < maxNumeroBotoes; i++){
		botao[i].setFont(fonte);
		botao[i].setCharacterSize(40);
		if(i == 0)
			botao[i].setColor(sf::Color(0,255,255));
		else
			botao[i].setColor(sf::Color::White);
		botao[i].setString(textoBotao[i]);
		botao[i].setPosition(sf::Vector2f(centrox + ((i-1)*largura/(maxNumeroBotoes+1) + botao[i].getCharacterSize()*1.95), altura-100));
	}



}
// fim Construtor

// Destrutor
// Deleta vetor de botões
Ranking::~Ranking(){ 
	delete botao;
}; // fim Destrutor

// Executar
// Recebe por referência a janela da biblioteca gráfica
int Ranking::Executar(sf::RenderWindow &App, int &score){
// declaracao de variaveis
	sf::Event Event; // eventos de jogo
	bool executando = true;
	while (executando){ // loop da tela
		// Verificação de eventos
		while (App.pollEvent(Event)){ // loop de eventos
			if (Event.type == sf::Event::Closed){ // se fechar a tela
				return (-1); // fim jogo
			}
			// ao pressionar botões
			if (Event.type == sf::Event::KeyPressed){
				switch (Event.key.code){
                    //cases para cada tecla
					case sf::Keyboard::Right:
						MovaParaDireita();
						break;
					case sf::Keyboard::Left:
						MovaParaEsquerda();
						break;
                    case sf::Keyboard::A:
						nome[quantNome]= 'A';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::B:
						nome[quantNome]= 'B';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::C:
						nome[quantNome]= 'C';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::D:
						nome[quantNome]= 'D';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::E:
						nome[quantNome]= 'E';
                        if(!(quantNome == 2))
                            quantNome++;;
						break;
                    case sf::Keyboard::F:
						nome[quantNome]= 'F';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::G:
						nome[quantNome]= 'G';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::H:
						nome[quantNome]= 'H';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                     case sf::Keyboard::I:
						nome[quantNome]= 'I';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::J:
						nome[quantNome]= 'J';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::K:
						nome[quantNome]= 'K';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::L:
						nome[quantNome]= 'L';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::M:
						nome[quantNome]= 'M';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::N:
						nome[quantNome]= 'N';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::O:
						nome[quantNome]= 'O';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::P:
						nome[quantNome]= 'P';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::Q:
						nome[quantNome]= 'Q';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::R:
						nome[quantNome]= 'R';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::S:
						nome[quantNome]= 'S';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::T:
						nome[quantNome]= 'T';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::U:
						nome[quantNome]= 'U';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::V:
						nome[quantNome]= 'V';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::W:
						nome[quantNome]= 'W';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::X:
						nome[quantNome]= 'X';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::Y:
						nome[quantNome]= 'Y';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::Z:
						nome[quantNome]= 'Z';
                        if(!(quantNome == 2))
                            quantNome++;
						break;
                    case sf::Keyboard::BackSpace:
						nome[quantNome]= ' ';
                        if(!(quantNome == 0)){
                            quantNome--;
                        }
						break;
					case sf::Keyboard::Return:
						switch(ItemApertado()){
							case 0: // menu
                                //adiciona o score do jogador no banco
                                Request request;
                                request.enviarRanking(nomeString,scoreString);
								return 0;
								break;
							case 1: // proxima pagina
								return 0;
								break;
						}
					default:
						break;
				}
			}
		}// fim loop de eventos
        std::string n1(1,nome[0]);
        std::string n2(1,nome[1]);
        std::string n3(1,nome[2]);
        nomeString = n1+n2+n3;
		// desenhar coisas na tela
		App.clear();
		desenha(App); // chamada de método desenha
        App.draw(digitaNome);
        Nome.setString(nomeString);
        scoreString= std::to_string(score);
        scoreText.setString("Score : " + scoreString);
        App.draw(scoreText);
        App.draw(Nome);
        App.display();
	} // fim loop da tela

	// não há como chegar até aqui mas, se acontecer, termine o programa.
	return (-1);
}

// Desenha
// Método que desenha na tela alguns atributos
void Ranking::desenha(sf::RenderWindow & App) const{
	sf::RectangleShape linhas; // retângulo para linhas
	// configuração do retangulo
    linhas.setPosition(sf::Vector2f(50, 50));
    linhas.setFillColor(sf::Color(32,32,32));
    linhas.setOutlineThickness(1);
    linhas.setOutlineColor(sf::Color(0,255,255));
    linhas.setSize(sf::Vector2f(largura-100, altura -100));

    // desenha na janela
    App.clear(sf::Color(32,32,32));
	App.draw(linhas);
	App.draw(titulo);
	for(int i=0; i < maxNumeroBotoes; i++){
		App.draw(botao[i]);
	}

};
// fim desenha

// MovaParaCima
// Move a seleção de botão para cima
void Ranking::MovaParaEsquerda(){
	if(numeroItem - 1 >= 0){
		botao[numeroItem].setColor(sf::Color(255,255,255));
		numeroItem--;
		botao[numeroItem].setColor(sf::Color(0,255,255));
	}
};
// fim MovaParaCima

// MovaParaBaixo
// Move a seleção de botão para baixo
void Ranking::MovaParaDireita(){
	if(numeroItem + 1 < maxNumeroBotoes){
		botao[numeroItem].setColor(sf::Color(255,255,255));
		numeroItem++;
		botao[numeroItem].setColor(sf::Color(0,255,255));
	}
};
// fim MovaParaBaixo
int Ranking::ItemApertado(){ return numeroItem; };

// fim Executar

// Desenha
// Método que desenha na tela alguns atributos
