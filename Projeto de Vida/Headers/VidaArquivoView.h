#ifndef  VIDAARQUIVOVIEW_H_
#define VIDAARQUIVOVIEW_H_


#include "VidaArquivoModel.h"
#include "VidaView.h"
//Constantes do tamanho da largura e comprimento dos arquivos Txt
#define COL_AUTOMATO_CEL_TXT 60
#define LIN_AUTOMATO_CEL_TXT 20

#define COL_BLIN_TXT 66
#define LIN_BLIN_TXT 18

#define COL_MANUTENCAO_TXT 47
#define LIN_MANUTENCAO_TXT 18

#define LIN_SALVAR_TXT 4
#define COL_SALVAR_TXT 37

#define LIN_TRANSFERIR_TXT 5
#define COL_TRANSFERIR_TXT 62

#define COL_CARREGAR_TXT 53
#define LIN_CARREGAR_TXT 5

typedef struct arquivo{
  
  arquivoInfo lista[10];
  int qS;
  int qT;

  interface menu[3];
  //Subjanelas do menu[1]
  interface submenu[4];


}arquivo;

void colocarArquivoPadraoTxt(int tamMundo,int *lin, int *col, arquivo *arq, mundo *mundoPadrao, mundo *mundo);
void selecionarJanelaArquivo(arquivo *arq, int *destaqueH, int *destaqueV);
void desenharTransferir(arquivo *arq, int *destaqueH, int *destaqueV);
void desenharCarregar(arquivo *arq, int *destaqueH, int *destaqueV);
void desenharSalvar(arquivo *arq, int *destaqueH, int *destaqueV);
void inicializarInterArq(arquivo *arq);
void lerCaracterArquivoTxT(char *nomeArq, int x, int y, interface *a, int cor, char temJanela, float vel);
void lerFraseArquivoTxT(char *nomeArq, int x, int y, interface *a,int cor, char temJanela, float vel);
void desenharErro(interface *a);
void obterNomeArq(arquivo *arq, int i);
void desenharPadrao(arquivo *arq);
void desenharListaArquivo(arquivo *arq, int *destaqueH, int *destaqueV);
void desenharInfoArquivo(arquivo *arq, int *destaqueH , int *destaqueV);
void mostrarMensagemTextoSalvar(arquivo *arq);
void mostrarMensagemBinarioSalvar(arquivo *arq);
void mostrarMensagemBinarioTransferir(arquivo *arq);
void mostrarMensagemTextoTransferir(arquivo *arq);
int lerPadraoArquivoTxt(arquivo *arqP, individuo padrao[100][100], int posicao);
void desenharPadraoSave(int linMover, int colMover, int cor, int lin, int col, interface *interfaceP, char temJanela, individuo padrao[100][100]);
void mostrarMensagemVazioArquivo(arquivo *arq);
void mostrarMensagemInfoArquivoBinario(arquivo *arq, mundo *mundoInfo);
void mostrarMensagemInfoArquivoTxt(arquivo *arq, mundo *mundoInfo);
#endif




