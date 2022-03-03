#ifndef VIDAMODEL_H_
#define VIDAMODEL_H_
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include "Lista.h"

#define Q_ITEM 5
#define Q_CARAC 60



//Definindo paletas de cor

//struct da celula

typedef struct individuo{
  
  char desenho;
  int status; 
  int vizinho;

}individuo;

typedef struct info{

  int quantVivo;
  int quantMorto;
  int geracao;
  int tamMundo;
  
  //Quando o mundo foi criado
  int dia, mes, ano;

}info;

typedef struct Item{

  char str[Q_CARAC];
  int nS;

}Item;


/*----------------------------------------------------------------

*LEGENDA*

Status
status=0 <----- Morto
status=1 <----- Vivo
status=2 <----- Vivo ja printado na tela (diminui o tempo de print)

Desenho
Célula morta ----> " "
Célula Viva  ----> "0"

Método de locomoção no programa
↑ - seta para cima
↓ - seta para baixo
→ - seta para direita
← - seta para esquerda 
↵ - enter

-------------------------------------------------------------------*/
void criarGeracao(individuo celula[100][100], int tam, tipoLista *vivo, tipoLista *possivelVivo, tipoLista *mortoFuturo, tipoLista *vivoFuturo);
void limparVizinhos(individuo celula[100][100], int tam, tipoLista *lista);
void transformarMaius(char *str); 
void transformarMinus(char *str); 
void atrasarTela(float tempo);
void delay(float delay1);
void carregarItem(Item a[], char *str1, char *str2, char *str3, char *str4, char *str5, int nA); 
void definirCelMorta(individuo celula[100][100], int lin, int col);
void definirCelViva(individuo celula[100][100], int lin, int col);
void limparMatriz(individuo celula[100][100], int tam);
void criarCelula(individuo celula[100][100], int tam, tipoLista *vivo, tipoLista *possivelVivo, tipoLista *mortoFuturo, tipoLista *vivoFuturo);
void listaCriarCelula(individuo celula[100][100], int tam, int lin, int col, int quant);
void seraCelVivo(tipoLista *a, tipoLista *iraViver,  individuo celula[100][100]);
void estadoCelula(tipoLista a[], int lin, int col, int contVizinhos);
void contarVizinho(int modo, tipoLista *compLista, tipoLista *vivoFuturo, tipoLista *mortoFuturo,  individuo celula[100][100], int tam);
void estimarCelFuturas(tipoLista *vivo, tipoLista *possivelVivo,  int tam, individuo celula[100][100]);
void definirCelPresentes(int modo ,tipoLista *vivoFuturo, tipoLista *mortoFuturo, int lin, int col, int contVizinhos, individuo celula[100][100]);
void obterDataCriacaoMundo(info *infoMundo);


#endif
