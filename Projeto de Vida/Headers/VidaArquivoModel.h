#ifndef VIDAARQUIVOMODEL_H_
#define VIDAARQUIVOMODEL_H_

#include "VidaView.h"

/*
____________________________________________
STATUS:
 0 → Arquivo binario salvo
 1 → Arquivo texto salvo
 2 → Arquivo binario transferido
 3 → Arquivo texto transferido
____________________________________________

 nomeExibicao → nome de escolha do usuário;
 nomeArq → caminho onde o arquivo será salvo

____________________________________________
  
*/
typedef struct arquivoInfo{
  
  FILE *arq;
  char status;
  char nomeArq[100];
  char nomeExibicao[100];

}arquivoInfo;


void salvarArquivo(arquivoInfo *lista, mundo *mundoSalvar, int i);
void carregarArquivo(arquivoInfo *lista, mundo *mundoCarregar, int i);
void adicionarCaracterTxt(FILE *arq, char *arqNome, char caracter, int modo);
void inicializarArqInfo(arquivoInfo lista[]);
#endif


