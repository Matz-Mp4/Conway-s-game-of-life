#ifndef VIDAVIEW_H_
#define VIDAVIEW_H_

#include "VidaModel.h"

//terminal nao é feito de pixels 
//o tamanho bloco de coluna é diferente do tamanho do bloco de linha
#define TERMINAL_COL 3.5

enum Cores {

  TESTE,
  ALERTA, 
  PADRAO, 
  DESTAQUE,  
  PRETO_BRANCO, 
  BRANCO, 
  CIANO,
  AZUL_BRANCO,
  AMARELO_ESCURO,
  INVERTIDO_1,
  INVERTIDO_2
        
};

//Configurações do usuario 
typedef struct config{

  float vel;
  int  corFundo;
  int corCelula;

  //Paletas de cor da "celula"
  int corCelula1, corCelula2;
  //Paletas de cor do "fundo"
  int corFundo1, corFundo2;
}config;

typedef struct Interface{  // <--- view
    
  int compComeca, largComeca; //posição na qual eles vao comecar a ser printados
  int comp, larg; //coluna linha
  int destaqueH;//Palvra destacada: highlight
  int destaqueV;
  WINDOW *janela;
  Item item[Q_ITEM];
  int nI;

}interface;


typedef struct mundo{ // <--- view

  config mundoConfig;
  individuo celula[100][100];
  info infoMundo;
  int tam;
  interface menu[5];
  
  tipoLista vivo;
  tipoLista possivelVivo;
  tipoLista mortoFuturo;
  tipoLista vivoFuturo;

  
}mundo;

void inicializarMundo(mundo *mundo);
void desenharCelVizinhos(mundo *mundo, int cor);
void obterCorFundo(interface *submenuP, int lin, int col, mundo *mundo);
void obterCorCelula(interface *submenuP, int lin, int col, mundo *mundo);
void desenharMundoEnum(mundo *mundo, float vel);
bool animarCursor(int *l, int *c, int tam, int lin, int col, int modo, interface *a, int *opSeta);
void inicializarInterMundo(mundo *mundo);
void selecionarBorda(mundo *mundo, int *destaqueH, int *destaqueV);
void inicializarCor(mundo *mundo);
void inicializarInter(interface *menuP);
void mostrarJanela(interface *a, int cor);
int obterTam(interface *submenuP);
void desenharTituloJanela(interface *a, char *titulo, int cor);
void desenharBorda();
void destacarItem(interface *a, int cor, int x, int y, int k, int modoSeta);
void desenharCel(mundo *mundo, float vel, int cor, int modo);
void destacarBorda(int destaqueH, int destaqueV);
void inicializarSubInter(interface submenuP[], interface *menuP);
void criarSubInter(interface *a, interface *aSub, int  linha, int coluna, int compComeca, int largComeca);
void desenharCelUnica(mundo *mundo, int cor, int lin, int col, int status, float vel);
void apagarJanela(interface *a);
void iniciarGeracao(mundo *mundo,  int tam);
char escolherModo(mundo *mundo );
void iniciarModoManual(mundo *mundo);
void iniciarModoAleatorio(mundo *mundo);
float obterVelocidade(interface *submenuP, int lin, int col, mundo *mundo);
bool moverSeta(int *escolhaH, int *escolhaV, int minH, int minV, int maxH, int maxV, int *opcao);
void desenharEnum(interface *a, int tam, int lin, int col, float vel, int modo);
void desenharGeracao(char op, int nG, mundo *mundo);
void apagarFrases(interface *interfaceP, int lin, int col, char *palavra);
#endif
