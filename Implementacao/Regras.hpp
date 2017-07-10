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
#include "Tela.hpp"
#include <string.h>

#include <SFML/Graphics.hpp>

class Regras : public Tela{
private: 
	// atributos privados
	const int maxNumeroTeclas; // numero de teclas
	const int maxNumeroBotoes;
	float largura, altura, centrox, centroy; // variáveis pra guardar medidas da tela utilizada
	int numeroItem;
	sf::Text titulo;
	sf::Font fonte;
	sf::Text botao;
	sf::Text *infos; // vetor de textoBotao para teclas
	sf::Text *descricaoTeclas; // descricao das teclas
	sf::RectangleShape *tecla; // vetor de teclas

	// métodos privados
	void desenha(sf::RenderWindow &) const;
public: // métodos públicos
	Regras(float larg, float alt);
	~Regras();
	virtual int Executar(sf::RenderWindow &App, int & score);
};

// Implementação dos métodos

// Construtor
// Inicializa e configura os atributos
Regras::Regras(float larg, float alt):  maxNumeroTeclas(4), maxNumeroBotoes(1){
	std::string textoBotao = "Menu"; // textoBotao do botão
	std::string instrucoes[maxNumeroTeclas] = { // informacoes sobre as teclas
		"^", "<", ">", "space"
	};
	std::string descricao[maxNumeroTeclas] = { "Mover o personagem", "Rodar anti-horario", "Rodar horario", "atirar" };
	numeroItem = 0;

	// alocação de posições
	descricaoTeclas = new sf::Text[maxNumeroTeclas]; // veteor para descricao das teclas
	tecla = new sf::RectangleShape[maxNumeroTeclas]; // vetor de teclas
	infos = new sf::Text[maxNumeroTeclas]; // vetor de informações

	// variaveis das medidas
	largura = larg;
	altura = alt;
	centrox = largura/2;
	centroy = altura/2;

	if (!fonte.loadFromFile("Tr2n.ttf")){} // fonte das letras

	// inicializando titulo
	titulo.setCharacterSize(50);
	titulo.setString("REGRAS");
	titulo.setFont(fonte);
	titulo.setPosition(sf::Vector2f(centrox - titulo.getCharacterSize()*2, centroy-altura*1/3 + titulo.getCharacterSize() - 150));
	titulo.setColor(sf::Color(0,255,255));

	// inicializando botoes
	botao.setFont(fonte);
	botao.setCharacterSize(30);
	botao.setColor(sf::Color(0,255,255));
	botao.setString(textoBotao);
	botao.setPosition(sf::Vector2f(centrox - botao.getCharacterSize()*1.25, altura-100));

	// inicializando descricoes dos botoes
	for(int i=0; i < maxNumeroTeclas; i++){
		descricaoTeclas[i].setString(descricao[i]);
		descricaoTeclas[i].setFont(fonte);
		descricaoTeclas[i].setCharacterSize(30);
		descricaoTeclas[i].setColor(sf::Color::White);
		if(i == maxNumeroTeclas-1)
			descricaoTeclas[i].setPosition(sf::Vector2f(40+largura/(maxNumeroTeclas), (titulo.getCharacterSize() + 60) + i*altura/(maxNumeroTeclas+3)));
		else
			descricaoTeclas[i].setPosition(sf::Vector2f(largura/(maxNumeroTeclas), (titulo.getCharacterSize() + 60) + i*altura/(maxNumeroTeclas+3)));
	}

	// inicializando as infos
	for(int i=0; i < maxNumeroTeclas; i++){
		infos[i].setString(instrucoes[i]);
		infos[i].setFont(fonte);
		infos[i].setCharacterSize(30);
		infos[i].setColor(sf::Color(0,255,255));

		if(i == maxNumeroTeclas-1){
			tecla[i].setSize(sf::Vector2f(120,40));
			infos[i].setPosition(sf::Vector2f(60 + largura/(maxNumeroTeclas+10), (titulo.getCharacterSize()+60) + i*altura/(maxNumeroTeclas+3)));
			tecla[i].setPosition(sf::Vector2f(50 + largura/(maxNumeroTeclas+10), (titulo.getCharacterSize()+60) + i*altura/(maxNumeroTeclas+3)));
		}else{
			tecla[i].setSize(sf::Vector2f(40,40));
			infos[i].setPosition(sf::Vector2f(100 + largura/(maxNumeroTeclas+10), (titulo.getCharacterSize()+60) + i*altura/(maxNumeroTeclas+3)));
			tecla[i].setPosition(sf::Vector2f(90 + largura/(maxNumeroTeclas+10), (titulo.getCharacterSize()+60) + i*altura/(maxNumeroTeclas+3)));
		}
		tecla[i].setFillColor(sf::Color(32,32,32));
		tecla[i].setOutlineThickness(1);
		tecla[i].setOutlineColor(sf::Color(0,255,255));
	}
}
// fim construtor

// Destrutor
// Deleta o vetor de teclas
Regras::~Regras(){ 
	delete infos;
	delete tecla;
	delete descricaoTeclas;
};

// Executar
// Recebe por referência a janela da biblioteca gráfica
int Regras::Executar(sf::RenderWindow &App, int & score){
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
					case sf::Keyboard::Return:
						return(0);
						break;
					default:
						break;
				}
			}
		}// fim loop de eventos

		// desenhar coisas na tela
		App.clear();
		desenha(App); // chamada de método desenha
        App.display();
	} // fim loop da tela

	// não há como chegar até aqui mas, se acontecer, termine o programa.
	return (-1);
}
// fim Executar

// Desenha
// Método que desenha na tela alguns atributos
void Regras::desenha(sf::RenderWindow & App) const{
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
	App.draw(botao);
	for(int i = 0; i < maxNumeroTeclas; i++){
		App.draw(tecla[i]);
		App.draw(infos[i]);
		App.draw(descricaoTeclas[i]);
	}
};
// fim desenha