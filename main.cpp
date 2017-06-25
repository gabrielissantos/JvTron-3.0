/*
    JvTron: Trabalho 3
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
#include "todasTelas.hpp"

/* isso � o comando no terminal linux pra compilar o programa
    g++ -c main.cpp && g++ main.o todasTelas.hpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app 
*/

// main()
// Fun��o principal e gerenciadora de telas.
int main (){
    std::vector<Tela*> telas; // vetor que conter� as telas
    int numeroTela = 0; // tela de inicio da aplicacao (0) � o menu

    // Janela do aplicativo creation
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "JvTron", sf::Style::Titlebar | sf::Style::Close);

    // Esconder seta do mouse
    App.setMouseCursorVisible(false);

    // Preparacao das tela
    Menu * s0 = new Menu(App.getSize().x, App.getSize().y); // TELA 0: menu do jogo
    telas.push_back(s0);

    // loop principal
    while (numeroTela >= 0){
        if( (numeroTela = telas[numeroTela]->Run(App)) == 1 );// chamada do metodo que faz funcionar a tela atual
            //telas[1] = new Campo();
    } // fim loop principal

    return EXIT_SUCCESS; // fim do programa
}
// fim main