#include "Headers/VidaController.h" 
#include "Headers/VidaArquivoModel.h"
#include "Headers/VidaView.h"
#include <curses.h>

//anima a janela
void animarJanela(interface *a, int cor, int x, int y, int k, int *opcao, int modoSeta){

    bool sair = false;
    a->destaqueH = 0;
    a->destaqueV = 0;
    
    while(sair == false){

        destacarItem(a , cor, x, y, k, modoSeta);
        destacarBorda(a->destaqueH, a->destaqueV);        
        *opcao = wgetch(a->janela);
        sair = moverSeta(&(a->destaqueH), &(a->destaqueV), 0, 0, a->nI-1, 3, opcao);
   }
}


void controller(){
    
    initscr();
    start_color();
    keypad(stdscr, true);
        
    arquivo arq;    
    interface menuP;
    interface submenuP[3];
    mundo mundo;
    
    mundo.mundoConfig.corFundo = 21;
    mundo.mundoConfig.corCelula = 20;

    //Inicializacoes das variaveis 
    inicializarMundo(&mundo);
    inicializarCor(&mundo);
    inicializarInter(&menuP);
    inicializarSubInter(submenuP, &menuP);
    inicializarInterArq(&arq);
    inicializarArqInfo(arq.lista);
    
    arq.qS = 0;
    arq.qT = 5;

    keypad(submenuP[0].janela, true);

    int comp, larg;
    //pega o tamanho maximo do terminal
    getmaxyx(stdscr,comp, larg);

    //carrega um arquivo txt (tela inicial)     
    lerCaracterArquivoTxT("ASCII_Art/automato_celular.txt", comp/2 - LIN_AUTOMATO_CEL_TXT, larg/2 - COL_AUTOMATO_CEL_TXT/2, NULL, PADRAO, 'N', 0.003);
    

    refresh();
    getch();
    clear();
    

    desenharBorda();                                                      
    mostrarJanela(&menuP, PRETO_BRANCO);

    mostrarJanela(&submenuP[0], PADRAO);
    mostrarJanela(&submenuP[1], PADRAO);  
    
    gerenciarMenu(&menuP,  DESTAQUE, 4,  submenuP[0].larg/2-submenuP[0].item[0].nS/2, 8, &mundo, submenuP, &arq);

    endwin();
}
//menu das opções
void gerenciarMenuOpcao(interface *submenu, mundo *mundo){
  
  bool sair = false;   
  int opcao;
  
  apagarJanela(submenu);
  desenharTituloJanela(submenu,"CONFIGURACOES", PRETO_BRANCO);

  keypad(submenu->janela, true);

   while(sair == false){
     mostrarJanela(submenu, PADRAO);
     animarJanela(submenu, DESTAQUE, 4, 3, 5, &opcao, 0);
       
     switch(submenu->destaqueH){
        
        case 0:
          obterVelocidade(submenu, 5, 4, mundo);
        break;
          
        case 1:
          obterCorCelula(submenu, 9, 9, mundo);
        break;

        case 2:
          obterCorFundo(submenu, 13, 7, mundo);
        break;
       
        case 3:
          sair = true;
        break;
     }
   }

  apagarJanela(submenu);
}

//menu dos arquivos
void gerenciarMenuArquivo(arquivo *arq, mundo *mundoP){ 
  int opcaoArq;
  bool sair = false;   
  mundo mundoPadrao;
  mundoPadrao.infoMundo.tamMundo = 8;
  int destaqueH = 0, destaqueV = 0;     
  int lin = 0, col = 0;
   while(sair == false){
     mostrarJanela(&(arq->menu[0]), PADRAO);
     animarJanela(&(arq->menu[0]), AZUL_BRANCO, 1, 3, 1, &opcaoArq, 0);
     mostrarJanela(&(arq->menu[1]), PRETO_BRANCO);
       
     switch(arq->menu[0].destaqueH){
        
        case 0:
        //carrega um arquivo salvo
          desenharCarregar(arq,  &destaqueH,  &destaqueV);

          if(arq->lista[destaqueV].status == 0 || arq->lista[destaqueV].status == 2){
            carregarArquivo(&(arq->lista[destaqueV]), mundoP, destaqueV);  
            init_pair(mundoP->mundoConfig.corCelula, mundoP->mundoConfig.corCelula1, mundoP->mundoConfig.corCelula2);
            init_pair(mundoP->mundoConfig.corFundo, mundoP->mundoConfig.corFundo1, mundoP->mundoConfig.corFundo2);
          }
          if(arq->lista[destaqueV].status == 1 || arq->lista[destaqueV].status == 3){
            mundoPadrao.infoMundo.tamMundo = lerPadraoArquivoTxt(arq, mundoPadrao.celula, destaqueV);
            colocarArquivoPadraoTxt(mundoP->infoMundo.tamMundo, &lin, &col, arq, &mundoPadrao, mundoP);

          }
        break;
          
        case 1:
        //salva um arquivo
          desenharSalvar(arq, &destaqueH,  &destaqueV);
          if(destaqueH == 1 && destaqueV == 0){
            obterNomeArq(arq, 1);
            desenharPadrao(arq);
          }else if(destaqueH == 0 && destaqueV == 0){
            obterNomeArq(arq, 0);
            salvarArquivo(&(arq->lista[arq->qS-1]), mundoP, arq->qS-1);
          }
        break;

        case 2:
        //transfere um arquivo
          desenharTransferir(arq, &destaqueH,  &destaqueV);
          if (destaqueH == 1 && destaqueV == 0) {
            obterNomeArq(arq, 3);
          } else if (destaqueH == 0 && destaqueV == 0) {
            obterNomeArq(arq, 2);
          }

          break;

        case 3:
          sair = true;
        break;
      }
    apagarJanela(&(arq->menu[2]));
    apagarJanela(&(arq->submenu[3]));
    apagarJanela(&(arq->submenu[0]));
    apagarJanela(&(arq->submenu[1]));
   }

  clear(); 
}
//menu do jogo
void gerenciarMenu(interface *menuP, int cor, int x, int y, int k, mundo *mundo, interface submenuP[], arquivo *arq){

  bool sair = false;
  int opcao;
  int opcaoArq;
  int larg;
  int comp;
  getmaxyx(stdscr, comp, larg);

  while(sair == false){
  
    apagarJanela(&submenuP[1]);
    mostrarJanela(menuP, BRANCO);
    mostrarJanela(&submenuP[1], PADRAO);   
    lerFraseArquivoTxT("ASCII_Art/blin.txt", submenuP[1].comp/2 - LIN_BLIN_TXT/2 , submenuP[1].larg/2 - COL_BLIN_TXT/2, &submenuP[1], PADRAO, 'J', 0.03);
    
    desenharTituloJanela(&submenuP[0], "MENU", PRETO_BRANCO);
    mostrarJanela(&submenuP[0], PADRAO);
    animarJanela(&submenuP[0], cor, x, y, k, &opcao, 1);
    

    if((submenuP[0].destaqueH == submenuP[0].nI) && opcao == '\n'){
     desenharErro(&submenuP[1]); 
    }

    //invertido
    switch(submenuP[0].destaqueH){
     
      case -1:
        switch(submenuP[0].destaqueV){
        
          case 0:
            gerenciarMenuArquivo(arq, mundo);
          break;  
        }
      break;

      case 0:
        if(menuP[0].destaqueV != -1){
          mundo->infoMundo.tamMundo = obterTam(&submenuP[2]);
          limparMatriz(mundo->celula, mundo->infoMundo.tamMundo);
          clear();
          desenharMundoEnum(mundo, 0.01);
          gerenciarMundo(mundo,arq , mundo->mundoConfig.corFundo, PADRAO, 0.005);

          clear();
          mostrarJanela(menuP, BRANCO);
        }
      break;

      case 1:
        //desenharErro(&submenuP[1]); 
        gerenciarMenuOpcao(&submenuP[1], mundo);
      break;

      case 2:
        sair = true;
      break;
    }
    
    
  }

}

//gerencia o mundo 
void gerenciarMundo(mundo *mundo, arquivo *arq, int cor, int corJan, float vel){ //
  
  char opcao;
  inicializarLista(&(mundo->vivo));
  inicializarLista(&(mundo->possivelVivo));
  inicializarLista(&(mundo->vivoFuturo));
  inicializarLista(&(mundo->mortoFuturo));
  
  obterDataCriacaoMundo(&(mundo->infoMundo));
  
  wbkgd(stdscr, COLOR_PAIR(mundo->mundoConfig.corFundo));
  refresh();
  opcao = adicionarCelula(corJan , mundo, arq);
  
  while(opcao != 'S'){ 
    
    desenharMundoEnum(mundo, 0);
     
    wbkgd(stdscr, COLOR_PAIR(mundo->mundoConfig.corFundo));
    
    refresh();
    desenharCel(mundo, vel, cor, 0);
    desenharBorda();
    opcao = adicionarCelula(corJan , mundo, arq);
    
  }

  wbkgd(stdscr, COLOR_PAIR(PADRAO));
}

//adiciona celula
char adicionarCelula(int cor, mundo *mundo, arquivo *arq){
  
  echo();
  int  op; 
  int opSeta;
  op = escolherModo(mundo);
  int destaqueH = -1, destaqueV = -1;
  bool sair = true;

  mostrarJanela(&(mundo->menu[1]), mundo->mundoConfig.corFundo); //SDDS SUPERMAN
  desenharTituloJanela(&(mundo->menu[1]), "Celula", INVERTIDO_2);
  
  wbkgd(stdscr, COLOR_PAIR(mundo->mundoConfig.corFundo));
  
  switch(op){
    case 'A': //modo Aleatório
    iniciarModoAleatorio(mundo);

    break; 
    case 'M': //modo Manual
      iniciarModoManual(mundo);
      
    break;

    case 'L': //Limpar Mundo
      limparMatriz(mundo->celula, mundo->infoMundo.tamMundo);
      limparLista(&(mundo->vivo));
      
    break;

    case 'I': //iniciar o mundo
      apagarJanela(&(mundo->menu[0]));
      apagarJanela(&(mundo->menu[1]));
      apagarJanela(&(mundo->menu[2]));
      iniciarGeracao(mundo, mundo->infoMundo.tamMundo);
    break;
    
    case 'B':
      selecionarBorda(mundo, &destaqueH, &destaqueV);
      if(destaqueV == 0){
        gerenciarMenuArquivo(arq, mundo);
      }

    break;

    case 'V':
      apagarJanela(&(mundo->menu[1]));
      desenharMundoEnum(mundo, 0);
      desenharCelVizinhos(mundo, AMARELO_ESCURO);
      getch();
    break;
  }
  
  clear();
  apagarJanela(&(mundo->menu[1]));

  return op;
}
