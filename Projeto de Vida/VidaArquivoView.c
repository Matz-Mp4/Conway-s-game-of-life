#include <time.h>
#include "Headers/Lista.h"
#include "Headers/VidaArquivoView.h"
#include "Headers/VidaView.h"
// desenha erro
void desenharErro(interface *a) {

  apagarJanela(a);
  lerFraseArquivoTxT("ASCII_Art/manutencao.txt", 1,
                     a->larg / 2 - COL_MANUTENCAO_TXT / 2, a, PRETO_BRANCO, 'J',
                     0.03);
  mostrarJanela(a, PADRAO);
  wattron(a->janela, COLOR_PAIR(PRETO_BRANCO));
  mvwprintw(a->janela, a->comp - 2, 2, "PRESSIONE QUALQUER TECLA PARA CONTINUAR");
  wattroff(a->janela, COLOR_PAIR(PRETO_BRANCO));
  wrefresh(a->janela);
  wgetch(a->janela);
}

void inicializarInterArq(arquivo *arq) {
  int comp, larg;
  getmaxyx(stdscr, comp, larg);
  int largArq;

  // Janela para base
  arq->menu[1].comp = 40;
  arq->menu[1].larg = 102;
  arq->menu[1].largComeca = larg / 2 - arq->menu[1].larg / 2;
  arq->menu[1].compComeca = comp / 2 - arq->menu[1].comp / 2;
  arq->menu[1].janela =
      newwin(arq->menu[1].comp, arq->menu[1].larg, arq->menu[1].compComeca,
             arq->menu[1].largComeca);

  // Janela para mostrar arquivo txt
  criarSubInter(&(arq->menu[1]), &(arq->menu[2]), 7, arq->menu[1].larg - 2, 1,
                1);
  arq->menu[2].janela =
      newwin(arq->menu[2].comp, arq->menu[2].larg, arq->menu[2].compComeca,
             arq->menu[2].largComeca);

  largArq = strlen("|Arquivo|");

  arq->menu[0].comp = 6;
  arq->menu[0].larg = 16;
  arq->menu[0].largComeca = larg - largArq - 9;
  arq->menu[0].compComeca = 1;
  arq->menu[0].janela =
      newwin(arq->menu[0].comp, arq->menu[0].larg, arq->menu[0].compComeca,
             arq->menu[0].largComeca);

  arq->menu[0].nI = 4;
  carregarItem(arq->menu[0].item, " CARREGAR ", "  SALVAR  ", "TRANSFERIR",
               "   SAIR   ", "", arq->menu[0].nI);

  keypad(arq->menu[0].janela, true);

  // Janela para mostrar a lista de arquivos tanto salvo ou transferido
  criarSubInter(&(arq->menu[1]), &(arq->submenu[3]), 30,
                arq->menu[1].larg / 5 + 1, arq->menu[2].comp + 2, 1);
  arq->submenu[3].janela =
      newwin(arq->submenu[3].comp, arq->submenu[3].larg,
             arq->submenu[3].compComeca, arq->submenu[3].largComeca);

  // Janela para entrada de dados de arquivo Binario
  criarSubInter(&(arq->menu[1]), &(arq->submenu[0]), 15,
                (arq->menu[1].larg * 2) / 5 - 1, arq->menu[2].comp + 2,
                arq->submenu[3].larg + 1);
  arq->submenu[0].janela =
      newwin(arq->submenu[0].comp, arq->submenu[0].larg,
             arq->submenu[0].compComeca, arq->submenu[0].largComeca);

  // Janela para entrada de dados de arquivo Txt
  criarSubInter(&(arq->menu[1]), &(arq->submenu[1]), 15,
                (arq->menu[1].larg * 2) / 5, arq->menu[2].comp + 2,
                arq->submenu[0].larg + 1 + arq->submenu[3].larg);
  arq->submenu[1].janela =
      newwin(arq->submenu[1].comp, arq->submenu[1].larg,
             arq->submenu[1].compComeca, arq->submenu[1].largComeca);

  // Janela para mostrar info de algum tipo de arquivo na janela da lista
  criarSubInter(&(arq->menu[1]), &(arq->submenu[2]), 15,
                ((arq->menu[1].larg * 2) / 5 - 2) * 2 + 3,
                arq->menu[2].comp + 2 + arq->submenu[1].comp,
                arq->submenu[3].larg + 1);
  arq->submenu[2].janela =
      newwin(arq->submenu[2].comp, arq->submenu[2].larg,
             arq->submenu[2].compComeca, arq->submenu[2].largComeca);
}

void desenharTransferir(arquivo *arq, int *destaqueH, int *destaqueV) {

  desenharTituloJanela(&(arq->submenu[3]), "LISTA", PRETO_BRANCO);
  desenharTituloJanela(&(arq->submenu[0]), "BINARIO", PRETO_BRANCO);

  mostrarJanela(&(arq->submenu[3]), PADRAO);
  mostrarJanela(&(arq->submenu[0]), PADRAO);
  mostrarJanela(&(arq->submenu[1]), PADRAO);
  mostrarJanela(&(arq->submenu[2]), PADRAO);

  desenharTituloJanela(&(arq->submenu[1]), "TEXTO", PRETO_BRANCO);

  lerCaracterArquivoTxT("ASCII_Art/transferir.txt",
                        arq->menu[2].comp / 2 - LIN_TRANSFERIR_TXT / 2,
                        arq->menu[2].larg / 2 - COL_TRANSFERIR_TXT / 2,
                        &(arq->menu[2]), PADRAO, 'J', 0.005);

  desenharListaArquivo(arq, destaqueH, destaqueV);

  selecionarJanelaArquivo(arq, destaqueH, destaqueV);
}

void desenharListaArquivo(arquivo *arq, int *destaqueH, int *destaqueV) {

  desenharTituloJanela(&(arq->submenu[3]), "LISTA", PRETO_BRANCO);

  wattron(arq->submenu[3].janela, COLOR_PAIR(PRETO_BRANCO));
  mvwprintw(arq->submenu[3].janela, 3, 8, "SAVES");

  mvwprintw(arq->submenu[3].janela, 15, 5, "TRANSFERIDOS");

  wattroff(arq->submenu[3].janela, COLOR_PAIR(PRETO_BRANCO));
  for (int i = 0; i < 10; i++) {

    if (i >= 0 && i <= 4) {
      mvwaddch(arq->submenu[3].janela, 1 + 4 + i * 2, 6, ACS_DIAMOND);

      if (arq->lista[i].status == -1) {
        mvwprintw(arq->submenu[3].janela, 1 + 4 + i * 2, 8, "Vazio");
      } else if (arq->lista[i].status == 0) {
        mvwprintw(arq->submenu[3].janela, 1 + 4 + i * 2, 8, "%s",
                  arq->lista[i].nomeExibicao);
      } else if (arq->lista[i].status == 1) {
        mvwprintw(arq->submenu[3].janela, 1 + 4 + i * 2, 8, "%s",
                  arq->lista[i].nomeExibicao);
      }
      atrasarTela(0.04);
      wrefresh(arq->submenu[3].janela);
    } else if (i >= 5) {
      mvwaddch(arq->submenu[3].janela, 4 + i * 2 + 3, 6, ACS_DIAMOND);
      if (arq->lista[i].status == -1) {
        mvwprintw(arq->submenu[3].janela, 4 + i * 2 + 3, 8, "Vazio");
      } else if (arq->lista[i].status == 2 || arq->lista[i].status == 3) {
        mvwprintw(arq->submenu[3].janela, 4 + i * 2 + 3, 8, "%s",
                  arq->lista[i].nomeExibicao);
      }
      atrasarTela(0.04);
      wrefresh(arq->submenu[3].janela);
    }
  }
}
void mostrarMensagemVazioArquivo(arquivo *arq){
  // Apagar mensagens
  for(int i = 0; i < 11; i++){
    apagarFrases(&(arq->submenu[2]), 3+i, 3, "                                     ");
  }
  wattron(arq->submenu[2].janela, COLOR_PAIR(PRETO_BRANCO));
  mvwprintw(arq->submenu[2].janela, 3, 4, "ESTE ESPACO ESTA VAZIO !!!");
  wattroff(arq->submenu[2].janela, COLOR_PAIR(PRETO_BRANCO));

}

void mostrarMensagemInfoArquivoBinario(arquivo *arq, mundo *mundoInfo){
    
    wattron(arq->submenu[2].janela, COLOR_PAIR(PRETO_BRANCO));
    mvwprintw(arq->submenu[2].janela, 3, 4, "Quandidade de seres:");
    mvwprintw(arq->submenu[2].janela, 5, 4, "Atraso de Geracao:");
    mvwprintw(arq->submenu[2].janela, 7, 4, "Cor da Celula:");
    mvwprintw(arq->submenu[2].janela, 9, 4, "Tamanho do Mundo:");    
    mvwprintw(arq->submenu[2].janela, 11, 4, "Data de criacao do mundo:");
    wattroff(arq->submenu[2].janela, COLOR_PAIR(PRETO_BRANCO));
    
    mvwprintw(arq->submenu[2].janela, 3, 24, "%d               ",mundoInfo->vivo.qtdItens);
    mvwprintw(arq->submenu[2].janela, 5, 24, "%0.3f  ",mundoInfo->mundoConfig.vel);
    mvwprintw(arq->submenu[2].janela, 9, 22, "%d    ",mundoInfo->infoMundo.tamMundo);
    mvwprintw(arq->submenu[2].janela, 11, 30, "%d / %d / %d   ", mundoInfo->infoMundo.dia, mundoInfo->infoMundo.mes, mundoInfo->infoMundo.ano);
    // 22 apenas para ter um identificação generica
    init_pair(22, mundoInfo->mundoConfig.corCelula1,mundoInfo->mundoConfig.corCelula2);
    wattron(arq->submenu[2].janela, COLOR_PAIR(22));
    mvwprintw(arq->submenu[2].janela, 7, 19, "O");
    wattroff(arq->submenu[2].janela, COLOR_PAIR(22));
  

}

void mostrarMensagemInfoArquivoTxt(arquivo *arq, mundo *mundoInfo){
  int colComeca = 4 * TERMINAL_COL + 2;
  int linComeca = 4;

  for (int i = 0; i < 11; i++) {
    apagarFrases(&(arq->submenu[2]), 3 + i, 3, "                                     ");
  }

  limparMatriz(mundoInfo->celula, 8);
  desenharEnum(&(arq->submenu[2]), 8, 4, 4 * TERMINAL_COL, 0, 1);

  for (int i = 0; i < 8; i++) {

    for (int j = 0; j < 8; j++) {
      desenharPadraoSave(linComeca + 1, colComeca, AZUL_BRANCO, i, j,
                         &(arq->submenu[2]), 'J', mundoInfo->celula);
    }
  }
}
void desenharInfoArquivo(arquivo *arq, int *destaqueH, int *destaqueV) {

  mundo mundoInfo;

  if (arq->lista[*destaqueV].status == -1) {

    mostrarMensagemVazioArquivo(arq);

  } else if (arq->lista[*destaqueV].status == 0 || arq->lista[*destaqueV].status == 2) {
    
    carregarArquivo(&(arq->lista[*destaqueV]), &mundoInfo, *destaqueV);  
    
    mostrarMensagemInfoArquivoBinario(arq, &mundoInfo);
     
  } else if (arq->lista[*destaqueV].status == 1 || arq->lista[*destaqueV].status == 3) {
    int colComeca = 4 * TERMINAL_COL + 2; 
    int linComeca = 4;
    
    for(int i = 0; i < 11; i++){
      apagarFrases(&(arq->submenu[2]), 3+i, 3, "                                     ");
    }

    limparMatriz(mundoInfo.celula, 8);
    desenharEnum(&(arq->submenu[2]), 8, 4, 4 * TERMINAL_COL, 0, 1);

    lerPadraoArquivoTxt(arq, mundoInfo.celula, *destaqueV);
    
    for (int i = 0; i < 8; i++) {

      for (int j = 0; j < 8; j++) {
        desenharPadraoSave(linComeca+1, colComeca,AZUL_BRANCO,i , j, &(arq->submenu[2]), 'J', mundoInfo.celula);
      }
    }
  }
  wrefresh(arq->submenu[2].janela);
}

void desenharCarregar(arquivo *arq, int *destaqueH, int *destaqueV) {

  bool sair = false;
  int opSeta = 0;

  mostrarJanela(&(arq->menu[1]), PRETO_BRANCO);
  lerCaracterArquivoTxT("ASCII_Art/carregar.txt",
                        arq->menu[2].comp / 2 - LIN_CARREGAR_TXT / 2,
                        arq->menu[2].larg / 2 - COL_CARREGAR_TXT / 2,
                        &(arq->menu[2]), PADRAO, 'J', 0.005);
  
  mostrarJanela(&(arq->submenu[2]), PADRAO);
  mostrarJanela(&(arq->submenu[3]), PADRAO);
  
  
  desenharListaArquivo(arq, destaqueH, destaqueV);

  while (sair == false) {

    opSeta = getch();
    sair = moverSeta(destaqueV, destaqueH, 1, 1, 8, 8, &opSeta);

    for (int i = 0; i < 10; i++) {

      if (i == *destaqueV) {
        wattron(arq->submenu[3].janela, COLOR_PAIR(AZUL_BRANCO));
      }
      if (i < 5) {

        if (arq->lista[i].status == -1) {
          mvwprintw(arq->submenu[3].janela, 1 + 4 + i * 2, 8, "Vazio");
        } else {
          mvwprintw(arq->submenu[3].janela, 1 + 4 + i * 2, 8, "%s", arq->lista[i].nomeExibicao);
        }
      } else if (i >= 5) {
        if (arq->lista[i].status == -1) {
          mvwprintw(arq->submenu[3].janela, 4 + i * 2 + 3, 8, "Vazio");
        } else {
          mvwprintw(arq->submenu[3].janela, 4 + i * 2 + 3, 8, "%s", arq->lista[i].nomeExibicao);
        }
      }
      wattroff(arq->submenu[3].janela, COLOR_PAIR(AZUL_BRANCO));
      wrefresh(arq->submenu[3].janela);
    }
    desenharInfoArquivo(arq, destaqueH, destaqueV);
  }

  apagarJanela(&(arq->submenu[3]));
  apagarJanela(&(arq->submenu[2]));
}

void selecionarJanelaArquivo(arquivo *arq, int *destaqueH, int *destaqueV) {

  bool sair;
  int opSeta;

  while (sair == false) {

    opSeta = getch();
    sair = moverSeta(destaqueV, destaqueH, 1, 0, 1, 1, &opSeta);

    if (*destaqueV == 0) {

      for (int i = 0; i < 3; i++) {

        if (i == *destaqueH) {
          mostrarJanela(&(arq->submenu[i]), AZUL_BRANCO);
        } else {
          mostrarJanela(&(arq->submenu[i]), PADRAO);
        }
      }
    } else if (*destaqueV == 1) {
      for (int i = 0; i < 4; i++) {

        if (i != 2) {
          mostrarJanela(&(arq->submenu[i]), PADRAO);
        } else {

          mostrarJanela(&(arq->submenu[i]), AZUL_BRANCO);
        }
      }
    } else {

      for (int i = 0; i < 4; i++) {

        mostrarJanela(&(arq->submenu[i]), PADRAO);
      }
    }
  }
}
void desenharSalvar(arquivo *arq, int *destaqueH, int *destaqueV) {

  int opSeta = 0;
  bool sair = false;

  mostrarJanela(&(arq->submenu[3]), PADRAO);
  mostrarJanela(&(arq->submenu[0]), PADRAO);
  mostrarJanela(&(arq->submenu[1]), PADRAO);
  mostrarJanela(&(arq->submenu[2]), PADRAO);


  desenharTituloJanela(&(arq->submenu[0]), "BINARIO", PRETO_BRANCO);
  desenharTituloJanela(&(arq->submenu[1]), "TEXTO", PRETO_BRANCO);

  lerCaracterArquivoTxT("ASCII_Art/salvar.txt",
                        arq->menu[2].comp / 2 - LIN_SALVAR_TXT / 2,
                        arq->menu[2].larg / 2 - COL_SALVAR_TXT / 2,
                        &(arq->menu[2]), PADRAO, 'J', 0.005);


  desenharListaArquivo(arq, destaqueH, destaqueV);

  selecionarJanelaArquivo(arq, destaqueH, destaqueV);
}

void desenharPadrao(arquivo *arq) {

  bool sair = false;
  int l = 0, c = 0;
  int opSeta = 0;
  int colComeca = 4, linComeca = 12 * TERMINAL_COL; individuo celula[100][100];
  limparMatriz(celula, 8);

  desenharTituloJanela(&(arq->submenu[2]), "PADRAO", PRETO_BRANCO);
  desenharEnum(&(arq->submenu[2]), 8, 4, 12 * TERMINAL_COL, 0.1, 1);

  while (sair == false) {

    sair = animarCursor(&l, &c, 8, 4, 12 * TERMINAL_COL, 1, &(arq->submenu[2]),&opSeta);
    definirCelViva(celula, l, c);

    wmove(arq->submenu[2].janela, linComeca + l + 1, colComeca + c * 3 + 2);
    wattron(arq->submenu[2].janela, COLOR_PAIR(AZUL_BRANCO));
    wprintw(arq->submenu[2].janela, "%c", celula[l][c].desenho);
    wattroff(arq->submenu[2].janela, COLOR_PAIR(AZUL_BRANCO));
    wrefresh(arq->submenu[2].janela);
  }

  arq->lista[arq->qS - 1].arq = fopen(arq->lista[arq->qS - 1].nomeArq, "w+");

  for (int l = 0; l < 9; l++) {

    for (int c = 0; c < 9; c++) {
      if (l < 8 && c < 8) {
        adicionarCaracterTxt(arq->lista[arq->qS - 1].arq,
                             arq->lista[arq->qS - 1].nomeArq,
                             celula[l][c].desenho, 0);
      } else if (c == 8) {
        adicionarCaracterTxt(arq->lista[arq->qS - 1].arq,
                             arq->lista[arq->qS - 1].nomeArq, '\n', 0);
      }
    }
  }
  fclose(arq->lista[arq->qS - 1].arq);

  getch();
  apagarJanela(&(arq->submenu[2]));
}

void mostrarMensagemBinarioSalvar(arquivo *arq){

    mostrarJanela(&(arq->submenu[0]), PADRAO);
    mvwaddch(arq->submenu[0].janela, 3, 1, ACS_DIAMOND);
    mvwprintw(arq->submenu[0].janela, 3, 3, "Digite o nome do arquivo");
    mvwaddch(arq->submenu[0].janela, 5, 1, ACS_DIAMOND);
    mvwprintw(arq->submenu[0].janela, 5, 3, "Recomendamos que voce coloque um");
    mvwprintw(arq->submenu[0].janela, 6, 3, " nome reconhecivel");
    wattron(arq->submenu[0].janela, COLOR_PAIR(AZUL_BRANCO));
    mvwprintw(arq->submenu[0].janela, 8, 1, "> ");
    wrefresh(arq->submenu[0].janela);
   
}

void mostrarMensagemTextoSalvar(arquivo *arq){

    mostrarJanela(&(arq->submenu[1]), PADRAO);
    mvwaddch(arq->submenu[1].janela, 3, 1, ACS_DIAMOND);
    mvwprintw(arq->submenu[1].janela, 3, 3,"Arquivo para guardar um padrao de");
    mvwprintw(arq->submenu[1].janela, 4, 3, "conjunto de individuos");
    mvwaddch(arq->submenu[1].janela, 6, 1, ACS_DIAMOND);
    mvwprintw(arq->submenu[1].janela, 6, 3, "Digite o nome do arquivo");
    mvwaddch(arq->submenu[1].janela, 8, 1, ACS_DIAMOND);
    mvwprintw(arq->submenu[1].janela, 8, 3, "Recomendamos que voce coloque um");
    mvwprintw(arq->submenu[1].janela, 9, 3, " nome reconhecivel");
    wattron(arq->submenu[1].janela, COLOR_PAIR(AZUL_BRANCO));
    mvwprintw(arq->submenu[1].janela, 11, 1, "> ");
    wattroff(arq->submenu[1].janela, AZUL_BRANCO);
    wrefresh(arq->submenu[1].janela);
 
}

void mostrarMensagemBinarioTransferir(arquivo *arq){
    
    mostrarJanela(&(arq->submenu[0]), PADRAO);
    mvwaddch(arq->submenu[0].janela, 3, 1, ACS_DIAMOND);
    mvwprintw(arq->submenu[0].janela, 3, 3, "Digite o nome do arquivo");
    mvwaddch(arq->submenu[0].janela, 5, 1, ACS_DIAMOND);
    mvwprintw(arq->submenu[0].janela, 5, 3, "Voce pode transferir ate");
    mvwprintw(arq->submenu[0].janela, 6, 3, " 5 arquivos");
    mvwaddch(arq->submenu[0].janela, 8, 1, ACS_DIAMOND);
    mvwprintw(arq->submenu[0].janela, 8, 3, "Nao precisa escrever a extensao");
    mvwprintw(arq->submenu[0].janela, 9, 3, "do arquivo");
    wattron(arq->submenu[0].janela, COLOR_PAIR(AZUL_BRANCO));
    mvwprintw(arq->submenu[0].janela, 10, 1, "> ");
    wattroff(arq->submenu[0].janela, AZUL_BRANCO);
    wrefresh(arq->submenu[0].janela);
 
}

void mostrarMensagemTextoTransferir(arquivo *arq){
    
    mostrarJanela(&(arq->submenu[1]), PADRAO);
    mvwaddch(arq->submenu[1].janela, 3, 1, ACS_DIAMOND);
    mvwprintw(arq->submenu[1].janela, 3, 3, "Digite o nome do arquivo");
    mvwaddch(arq->submenu[1].janela, 5, 1, ACS_DIAMOND);
    mvwprintw(arq->submenu[1].janela, 5, 3, "Voce pode transferir ate");
    mvwprintw(arq->submenu[1].janela, 6, 3, " 5 arquivos");
    mvwaddch(arq->submenu[1].janela, 8, 1, ACS_DIAMOND);
    mvwprintw(arq->submenu[1].janela, 8, 3, "Nao precisa escrever a extensao");
    mvwprintw(arq->submenu[1].janela, 9, 3, "do arquivo");
    wattron(arq->submenu[1].janela, COLOR_PAIR(AZUL_BRANCO));
    mvwprintw(arq->submenu[1].janela, 10, 1, "> ");
    wattroff(arq->submenu[1].janela, AZUL_BRANCO);
    wrefresh(arq->submenu[1].janela);
}

void obterNomeArq(arquivo *arq, int i) {

  char nome[100];

  switch (i) {
  case 0:
    mostrarMensagemBinarioSalvar(arq);
    mvwgetstr(arq->submenu[i].janela, 8, 3, nome);
    arq->lista[arq->qS].status = i;
    strcat(nome, ".dat");
    strcat(arq->lista[arq->qS].nomeArq, nome);
    strcpy(arq->lista[arq->qS].nomeExibicao, nome);
    arq->qS++;

    break;

  case 1:
    mostrarMensagemTextoSalvar(arq);
    mvwgetstr(arq->submenu[i].janela, 11, 3, nome);
    arq->lista[arq->qS].status = i;
    strcat(nome, ".txt");
    strcat(arq->lista[arq->qS].nomeArq, nome);
    strcpy(arq->lista[arq->qS].nomeExibicao, nome);
    arq->qS++;

    break;

  case 2:
    mostrarMensagemBinarioTransferir(arq);
    mvwgetstr(arq->submenu[0].janela, 10, 3, nome);
    arq->lista[arq->qT].status = i;
    strcat(nome, ".dat");
    strcat(arq->lista[arq->qT].nomeArq, nome);
    strcpy(arq->lista[arq->qT].nomeExibicao, nome);
    arq->qT++;

    break;

  case 3:
    mostrarMensagemTextoTransferir(arq);
    mvwgetstr(arq->submenu[1].janela, 10, 3, nome);
    arq->lista[arq->qT].status = i;
    strcat(nome, ".txt");
    strcat(arq->lista[arq->qT].nomeArq, nome);
    strcpy(arq->lista[arq->qT].nomeExibicao, nome);
    arq->qT++;

    break;
  }
}

void desenharPadraoSave(int linMover, int colMover,int cor, int lin, int col, interface *interfaceP, char temJanela, individuo padrao[100][100]){

  if (temJanela == 'J') {
    wmove(interfaceP->janela, linMover + lin, colMover + col*3);
    if (padrao[lin][col].status == 1) {
      wattron(interfaceP->janela, COLOR_PAIR(cor));
    }
    wprintw(interfaceP->janela, "%c", padrao[lin][col].desenho);
    wattroff(interfaceP->janela, COLOR_PAIR(cor));
    wrefresh(interfaceP->janela);

  } else {
    move(linMover + lin, colMover + col*3);
    if (padrao[lin][col].status == 1) {
      attron(COLOR_PAIR(cor));
    }
    printw("%c", padrao[lin][col].desenho);
    attroff(COLOR_PAIR(cor));
    refresh();
  }
}
int lerPadraoArquivoTxt(arquivo *arqP, individuo padrao[100][100], int posicao){

  char c;
  tipoItem aux;
  int maiorColuna = 0, maiorLinha = 0;

  arqP->lista[posicao].arq = fopen(arqP->lista[posicao].nomeArq, "rt");

  if (arqP->lista[posicao].arq == NULL) {
    printw("Problemas na abertura do arquivo\n");
    refresh();
    exit(1);
  }

  int i = 0;
  int j = 0;

  while (!feof(arqP->lista[posicao].arq)) {

    c = fgetc(arqP->lista[posicao].arq);

    if (c == 'O') {
      definirCelViva(padrao, i, j);
    }else{
      definirCelMorta(padrao, i, j);
    }
    j++;
    if (c == '\n') {
      i++;
      if(maiorColuna < j){
        maiorColuna = j;
      }
      j = 0;
    }
  }
  if (maiorColuna > maiorLinha) {
    return maiorColuna;
  } else {
    return maiorLinha;
  }
}
// faz  leitura do txt
void lerCaracterArquivoTxT(char *nomeArq, int x, int y, interface *a, int cor, char temJanela, float vel) {

  FILE *arq;
  char c;

  if (temJanela == 'J')
    wattron(a->janela, COLOR_PAIR(cor));
  else
    attron(COLOR_PAIR(cor));

  // Abre um arquivo TEXTO para LEITURA

  arq = fopen(nomeArq, "rt");
  if (arq == NULL) // Se houve erro na abertura
  {
    printw("Problemas na abertura do arquivo\n");
    exit(1);
  }
  
  int i = 0;
  int j = 0;
  while (!feof(arq)) {
    // Lê cada caracter
    c = fgetc(arq);
    if (temJanela == 'J') {
      mvwprintw(a->janela, x + i, y + j, "%c", c);
      atrasarTela(vel);
      wrefresh(a->janela);
    } else {
      mvprintw(x + i, y + j, "%c", c);
      atrasarTela(vel);
      refresh();
    }
    if (c == '\n') {
      i++;
      j = 0;
    }

    j++;
  }

  if (temJanela == 'J') {
    wattroff(a->janela, COLOR_PAIR(cor));
    mostrarJanela(a, cor);
  } else
    attroff(COLOR_PAIR(cor));

  fclose(arq);
}

// MODO = 'J' (JANELA)
void lerFraseArquivoTxT(char *nomeArq, int x, int y, interface *a, int cor, char temJanela, float vel) {

  FILE *arq;
  char Linha[200];

  if (temJanela == 'J')
    wattron(a->janela, COLOR_PAIR(cor));
  else
    attron(COLOR_PAIR(cor));

  // Abre um arquivo TEXTO para LEITURA

  arq = fopen(nomeArq, "rt");
  if (arq == NULL) // Se houve erro na abertura
  {
    printw("Problemas na abertura do arquivo\n");
    exit(1);
  }

  int i = 0;
  while (!feof(arq)) {
    // Lê uma linha (inclusive com o '\n')
    fgets(Linha, 100, arq); // o 'fgets' lê até 99 caracteres ou até o '\n'
    if (temJanela == 'J') {
      mvwprintw(a->janela, x + i, y, "%s", Linha);
      atrasarTela(vel);
      wrefresh(a->janela);
    } else {
      mvprintw(x + i, y, "%s", Linha);
      atrasarTela(vel);
      refresh();
    }
    i++;
  }

  if (temJanela == 'J') {
    wattroff(a->janela, COLOR_PAIR(cor));
    mostrarJanela(a, cor);
  } else
    attroff(COLOR_PAIR(cor));

  fclose(arq);
}

void colocarArquivoPadraoTxt(int tamMundo,int *lin, int *col,arquivo *arq, mundo *mundoPadrao, mundo *mundo){
  
  tipoItem aux;
  int opSeta;
  bool sair = false;
  int  colConst, linConst; 
  int tamMundoPadrao = mundoPadrao->infoMundo.tamMundo;
  clear();

  getmaxyx(stdscr, linConst ,colConst);
  linConst = linConst/2 - mundo->infoMundo.tamMundo/2;
  colConst = colConst/2 - mundo->infoMundo.tamMundo/2 * TERMINAL_COL;
  
  desenharMundoEnum(mundo, 0);
  while (sair == false) {
    
    clear();
    desenharMundoEnum(mundo, 0);
    desenharCel(mundo, 0, mundo->mundoConfig.corCelula, 0);

    attron(COLOR_PAIR(INVERTIDO_2));
    for (int i = 0; i < 8; i++) {
 
      for (int j = 0; j < 8; j++) {
        move(linConst + (*lin+i) + 1, colConst + (*col+j) * 3 + 2);
        if(mundoPadrao->celula[i][j].status == 1){
          printw("%c", mundoPadrao->celula[i][j].desenho);
        }
      }
    }
    attroff(COLOR_PAIR(INVERTIDO_2));
    refresh();
    opSeta = getch();
    sair = moverSeta(lin, col, 1, 1, tamMundo - 2 - 7, tamMundo - 2- 7, &opSeta);


  }

  for( int i = 0; i < 8; i++){

    for( int j = 0; j < 8; j++){
      if(mundoPadrao->celula[i][j].status == 1){
        definirCelViva(mundo->celula, i+(*lin), j+(*col));
        aux.linha = i+(*lin);
        aux.coluna = j+(*col);
        inserirItemLista(&(mundo->vivo), aux);
      }
    }
  }
}


