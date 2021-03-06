/*
    JvAsteroids: Trabalho 3
    Departamento de Computa��o
    UFSCar Universidade Federal de S�o Carlos
    Disciplina: Estrutura de Dados
    Professor: Roberto Ferrari
    Aluno(a):                               RA:
        Jo�o Gabriel Melo Barbirato         726546
        Leonardo de Oliveira Peralta        726556
        Gabrieli Santos                     726523
    
    Controle de Vers�o: https://github.com/gabrielissantos/JvTron-3.0
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "TodasTelas.hpp"
/* isso � o comando no terminal linux pra compilar o programa
    g++ -c main.cpp && g++ main.o TodasTelas.hpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system - lcurl && ./sfml-app 
*/

// main()
// Fun��o principal e gerenciadora de telas.
int main (){
    std::vector<Tela*> telas; // vetor que conter� as telas
    int numeroTela = 0; // tela de inicio da aplicacao (0) � o menu
    
    // Janela do aplicativo creation
    sf::RenderWindow App(sf::VideoMode(800, 600), "JvAsteroids", sf::Style::Titlebar | sf::Style::Close);
    App.setFramerateLimit(32);
    // Esconder seta do mouse
    App.setMouseCursorVisible(false);

    sf::Music musica; // declara��o do objeto sonoro

    // Preparacao das tela
    Menu * s0 = new Menu(App.getSize().x, App.getSize().y); // TELA 0: menu do jogo
    telas.push_back(s0);
    Jogo * s1 = new Jogo();
    telas.push_back(s1);
    Ranking * s2 = new Ranking(App.getSize().x, App.getSize().y);
    telas.push_back(s2);
    Regras * s3 = new Regras(App.getSize().x, App.getSize().y);
    telas.push_back(s3);

    //inicializa��o da musica
    if(!musica.openFromFile("sweet-dreams.ogg")){
        std::cout << "ERROR 1" << std::endl;
        return 1; //retorna um se a leitura da musica n�o foi efetuada com sucesso
    }
    musica.setLoop(true); //music e entra num loop para que a musica reinicie quando ela acabar
    musica.play(); //inicializa a musica
    int score = 0;
    // loop principal
    while (numeroTela >= 0){
       // std::cout <<"Tela: "<< numeroTela << std::endl;
        if( (numeroTela = telas[numeroTela]->Executar(App,score)) == 1 );// chamada do metodo que faz funcionar a tela atual
            if(numeroTela == 1 ){
                telas[1] = new Jogo();
                score = 0;
            }
        
        
    } // fim loop principal

    return EXIT_SUCCESS; // fim do programa
}
// fim main
