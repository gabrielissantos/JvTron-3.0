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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

class Request{
    public:
        void enviarRanking(std::string&,std::string&);


};
void Request::enviarRanking(std::string &nome , std::string &score){
    CURL *curl;
  CURLcode res;
  std::string url = "http://linux1001.pythonanywhere.com/api/JvTron3/Jogo/Ranking/"+nome+"/"+score+"";
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
 
#ifdef SKIP_PEER_VERIFICATION

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 10L);
#endif
 
#ifdef SKIP_HOSTNAME_VERIFICATION

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 10L);
#endif
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    /* always cleanup */ 

   // curl_easy_cleanup(curl);
  }
 
  curl_global_cleanup();
}
