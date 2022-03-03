#include "Headers/VidaView.h"
#include "Headers/VidaModel.h"
#include <curses.h>

void inicializarMundo(mundo *mundo){

  inicializarInterMundo(mundo);
  mundo->mundoConfig.corFundo = 21;
  mundo->mundoConfig.corCelula = 20;
  mundo->mundoConfig.vel = 0;
  mundo->infoMundo.tamMundo = 0;
  mundo->infoMundo.quantVivo = 0;
  mundo->infoMundo.quantMorto = 0;
  mundo->infoMundo.quantMorto = 0;


  mundo->mundoConfig.corCelula1 = COLOR_RED;
  mundo->mundoConfig.corCelula2 = COLOR_BLACK;
  mundo->mundoConfig.corFundo1 = COLOR_WHITE;  
  mundo->mundoConfig.corFundo2 = COLOR_BLACK;

}

void selecionarBorda(mundo *mundo, int *destaqueH, int *destaqueV) {

  int opSeta;
  *destaqueH = -1;
  *destaqueV = -1;
  bool sair = true;

  desenharBorda();
  apagarJanela(&(mundo->menu[1]));
  destacarBorda(*destaqueH, *destaqueV);
  desenharMundoEnum(mundo, 0);

  do {

    destacarBorda(*destaqueH, *destaqueV);
    opSeta = mvgetch(7, 24);
    sair = moverSeta(destaqueH, destaqueV, 0, 0, -2, -1, &opSeta);

  } while (sair != true);
}

void inicializarInterMundo(mundo *mundo){  

  int comp, larg;
  getmaxyx(stdscr, comp, larg);
  
  mundo->menu[1].larg = 80;
  mundo->menu[1].comp = 8;
  mundo->menu[1].largComeca = larg/2 - 40;
  mundo->menu[1].compComeca = comp/2 - 4; 
  mundo->menu[1].janela = newwin(mundo->menu[1].comp, mundo->menu[1].larg, mundo->menu[1].compComeca, mundo->menu[1].largComeca);
  
  mundo->menu[0].comp = 9;
  mundo->menu[0].larg = 40;
  mundo->menu[0].compComeca = 1;
  mundo->menu[0].largComeca = 1;
  mundo->menu[0].janela = newwin(mundo->menu[0].comp, mundo->menu[0].larg, mundo->menu[0].compComeca, mundo->menu[0].largComeca);
    
  mundo->menu[2].larg = 48;
  mundo->menu[2].comp = 6;
  mundo->menu[2].largComeca = 0;
  mundo->menu[2].compComeca = 1;
  mundo->menu[2].janela = newwin(mundo->menu[2].comp, mundo->menu[2].larg, mundo->menu[2].compComeca, mundo->menu[2].largComeca);
  
 
}

void desenharMundoEnum(mundo *mundo, float vel){
  int larg, comp;

  getmaxyx(stdscr, comp, larg);
  comp = comp/2 - mundo->infoMundo.tamMundo/2;
  larg = larg/2 - mundo->infoMundo.tamMundo/2 * TERMINAL_COL;

  desenharEnum(NULL, mundo->infoMundo.tamMundo, comp, larg, vel, 0);

}
//enumeração do mundo
void desenharEnum(interface *a, int tam, int lin, int col, float vel, int modo){
  
  int c, l;
  //Modo janela
  if(modo == 1){
     
    mvwhline(a->janela,lin, col-1, ACS_HLINE, tam*3+1);
    mvwvline(a->janela,lin, col, ACS_VLINE, tam+1);
     
    wmove(a->janela, lin-1, col);    
     
    for(c = 1; c <= tam; c++) { 
      
      if(c<10){ 
        wprintw(a->janela,"  %d", c);
        atrasarTela(vel);
        wrefresh(a->janela);  
      }else{      
        wprintw(a->janela," %d", c);
        atrasarTela(vel);
        wrefresh(a->janela);
      }
    }
     
    for(l = 1 ; l<= tam; l++) {
        
      if(l < 10){
        wmove(a->janela,l+lin, col-2);
        wprintw(a->janela," %d", l);
        atrasarTela(vel);
        wrefresh(a->janela);

      }else{
        wmove(a->janela,l+lin, col-2);
        wprintw(a->janela,"%d", l);
        atrasarTela(vel);
        wrefresh(a->janela);
          
      }
    }
  }
  //Modo padrao
  if(modo == 0){
     
    mvhline( lin, col-1, ACS_HLINE, tam*3+1);
    mvvline(lin, col, ACS_VLINE, tam+1);
    
    //move algo desejado no terminal
    move(lin-1, col);    
    for(c = 1; c <= tam; c++) { 
      if(c<10){ 
        printw("  %d", c);
        atrasarTela(vel);
        refresh();  
      }else{      
        printw(" %d", c);
        atrasarTela(vel);
        refresh();
      }
    }
    
    for(l = 1 ; l <= tam; l++) {
        
      if(l < 10){
        move(l+lin, col-2);
        printw(" %d", l);
        atrasarTela(vel);
        refresh();

      } else{
        move(l+lin, col-2);
        printw("%d", l);
        atrasarTela(vel);
        refresh();
          
      }
    }
  }
}

//Mostra uma janela (literalmente)
void mostrarJanela(interface *a, int cor){ 
  
    //seta a cor da janela
    wbkgd(a->janela, COLOR_PAIR(cor)); 
    //printa a janela desejada
    box(a->janela, 0, 0);
    refresh();
    wrefresh(a->janela);
}

//personaliza a cor do fundo
void obterCorFundo(interface *submenuP, int lin, int col, mundo *mundo){
  
  //Mostrar uma janela com as configurações e um mundo para visualizar
  //Apenas uma simulação
    interface config;
    int aux =  submenuP->comp/2+2, aux2 = submenuP->comp, aux3 = submenuP->larg,  tamMundo;
    criarSubInter(submenuP, &config, aux, aux*TERMINAL_COL, aux2 - aux-1  ,aux3 - aux*TERMINAL_COL-1);
    individuo celula;
 
    mostrarJanela(&config, mundo->mundoConfig.corFundo);
    tamMundo = config.comp-4;
    desenharEnum(&config, tamMundo , 2, config.larg/4+2 - config.comp/2, 0.001, 1);
    
    int l, c, linComeca = 3, colComeca = config.larg/4+2 - config.comp/2 +1;
     
    srand(time(NULL));
    
    for(int i = 0; i < tamMundo - tamMundo/4; i++){
      l = rand() % tamMundo;
      c = rand() % tamMundo; 
      wmove(config.janela, linComeca+l, colComeca+c*3+2); 
      wattron(config.janela, COLOR_PAIR(mundo->mundoConfig.corCelula));
      wprintw(config.janela, "O");
      wattroff(config.janela, COLOR_PAIR(mundo->mundoConfig.corFundo));
      wrefresh(config.janela);
    
    }

    int opcao;
    bool sair = false;
    col = submenuP->item[1].nS + col;
    //Vertical    Horizontal
    int corFundo = 0, corCelula = 0;
    short cor1, cor2;
    int corLetra;
    

    while(sair != true){
        opcao = mvwgetch(submenuP->janela,0,0);
        sair = moverSeta(&(mundo->mundoConfig.corFundo1), &(mundo->mundoConfig.corFundo2), 0, 0, 9, 9, &opcao);
        
        //Existe apenas 7 cores definidas no curses
        if(mundo->mundoConfig.corFundo2 >= 8 ){
          mundo->mundoConfig.corFundo2 = 0;

        }
        if(mundo->mundoConfig.corFundo2 <= -1 ){
          mundo->mundoConfig.corFundo2 =  7;
        }
        
          if(mundo->mundoConfig.corFundo1 >= 8 ){
          mundo->mundoConfig.corFundo1 = 0;

        }
        if(mundo->mundoConfig.corFundo1 <= -1 ){
          mundo->mundoConfig.corFundo1 = 7;
        }
        cor1 = mundo->mundoConfig.corFundo1;
        cor2 = mundo->mundoConfig.corFundo2;

        init_pair(mundo->mundoConfig.corFundo, cor1, cor2);
       
        wrefresh(submenuP->janela);
    }


    init_pair(mundo->mundoConfig.corFundo, cor1, cor2);
    init_pair(INVERTIDO_2, cor2, cor1);

}

//dá para personalizar a cor e o fundo da celula
void obterCorCelula(interface *submenuP, int lin, int col, mundo *mundo){

    int opcao;
    bool sair = false;
    col = submenuP->item[1].nS + col;
    //Vertical    Horizontal
    int corFundo = 0, corCelula = 0;
    short cor1, cor2;
  //Mostrar uma janela com as configurações e um mundo para visualizar
  //Apenas uma simulação
    interface config;
    int aux =  submenuP->comp/2+2, aux2 = submenuP->comp, aux3 = submenuP->larg,  tamMundo;
    criarSubInter(submenuP, &config, aux, aux*TERMINAL_COL, aux2 - aux-1  ,aux3 - aux*TERMINAL_COL-1);
    individuo celula[100][100];
 
    mostrarJanela(&config, mundo->mundoConfig.corFundo);
    tamMundo = config.comp-4;
    desenharEnum(&config, tamMundo , 2, config.larg/4+2 - config.comp/2, 0.001, 1);
    
    int l, c, linComeca = 3, colComeca = config.larg/4+2 - config.comp/2 +1;
     
    srand(time(NULL));
    
    for(int i = 0; i < tamMundo - tamMundo/4; i++){
      l = rand() % tamMundo;
      c = rand() % tamMundo; 
      definirCelViva(celula, l, c);

 
    }

    while(sair != true){
        opcao = mvwgetch(submenuP->janela,0,0);
        sair = moverSeta(&(mundo->mundoConfig.corCelula1), &(mundo->mundoConfig.corCelula2), 0,0, 9, 9, &opcao);
        
        //Existe apenas 7 cores definidas no curses
        if(mundo->mundoConfig.corCelula2 >= 8 ){
          mundo->mundoConfig.corCelula2 = 0;
      
        }
        if(mundo->mundoConfig.corCelula2 <= -1 ){
          mundo->mundoConfig.corCelula2 = 7;
          
        }if(mundo->mundoConfig.corCelula1 <= -1){
          mundo->mundoConfig.corCelula1 = 7;
        } 
        if(mundo->mundoConfig.corCelula1 >= 8){
          mundo->mundoConfig.corCelula1 = 0;
          
        }
        //Celula 
        cor1 = mundo->mundoConfig.corCelula1;
        //Fundo
        cor2 = mundo->mundoConfig.corCelula2;
        
        init_pair(mundo->mundoConfig.corCelula, cor1, cor2);
      

      for(int l = 0; l < tamMundo - tamMundo/4; l++){
        
        for(int c = 0; c < tamMundo - tamMundo/4; c++){

          wmove(config.janela, linComeca+l, colComeca+c*3+2); 
          wattron(config.janela, COLOR_PAIR(mundo->mundoConfig.corCelula));
          
          if(celula[l][c].status == 1 || celula[lin][col].status == 2)
            wprintw(config.janela, "O");
          
          wattroff(config.janela, COLOR_PAIR(mundo->mundoConfig.corCelula));
          wrefresh(config.janela);
        }
    
      }
      wrefresh(submenuP->janela);
    }

    init_pair(INVERTIDO_1, cor2, cor1);


}
//seta a velocidade que irá transitar de uma geração para a outra
float obterVelocidade(interface *submenuP, int lin, int col, mundo *mundo){

    int opcao;
    bool sair = false;
    int vazio = 0;
    int quantLinha = 0;
    float vel = 0;
    float aux, aux2 = 0.2;
    
    //tamanho da palavra "velocidad"
    col = submenuP->item[0].nS + 5;
    
    mvwaddch(submenuP->janela, lin, col, ACS_VLINE);
    mvwaddch(submenuP->janela, lin, col+52, ACS_VLINE);
    mvwhline(submenuP->janela, lin-1, col+1, ACS_S9, 51);
    mvwhline(submenuP->janela, lin+1, col+1, ACS_S1, 51);
    wrefresh(submenuP->janela);
    
    while(sair != true){

       aux = quantLinha;
       vel = 0.2*aux;
       mvwprintw(submenuP->janela, lin+2, 3, "Atraso: %0.2f segundos", vel);
      
      opcao = mvwgetch(submenuP->janela,0,0);
      sair = moverSeta(&vazio, &quantLinha, 0, 2, 0, 50, &opcao);
      
      if(opcao == KEY_RIGHT){
        wattron(submenuP->janela, COLOR_PAIR(AZUL_BRANCO)); 
        mvwprintw(submenuP->janela, lin, col+quantLinha, " "); 
        wattroff(submenuP->janela, COLOR_PAIR(AZUL_BRANCO));
      
      }else if(opcao == KEY_LEFT){

        wattron(submenuP->janela, COLOR_PAIR(PADRAO));
        mvwprintw(submenuP->janela, lin, col+quantLinha+1, " "); 
        wattroff(submenuP->janela, COLOR_PAIR(PADRAO));
      }
       wrefresh(submenuP->janela);
    }
    
  mundo->mundoConfig.vel = vel;
  return vel;    
}
//pergunta o tamanho da matriz
int obterTam(interface *submenuP){

    int tam;
    int colMax, linMax;
    getmaxyx(stdscr, linMax, colMax);

    
    
    mostrarJanela(submenuP, PADRAO); 
    desenharTituloJanela(submenuP, "TAMANHO ", PRETO_BRANCO);
    wattron(submenuP->janela, COLOR_PAIR(PRETO_BRANCO));
    mvwprintw(submenuP->janela, 3, 4 , "Qual sera o tamanho do seu mundo? ");
    //calcula o maximo que cabe no seu terminal
    mvwprintw(submenuP->janela, 4, 4 , "(Requisitos: minimo -> 2,  maximo -> %d): ", linMax-2);
    wattroff(submenuP->janela, COLOR_PAIR(PRETO_BRANCO));
    wrefresh(submenuP->janela);
    wscanw(submenuP->janela, "%d", &tam);

    while(tam >linMax-2 || tam < 2){
      beep();

      apagarJanela(submenuP);
      mostrarJanela(submenuP, PADRAO);
      desenharTituloJanela(submenuP, "ERRO", ALERTA);
      atrasarTela(0.2); 
      wattron(submenuP->janela, COLOR_PAIR(ALERTA));
      mvwprintw(submenuP->janela, 3, 1 , "Opps!! Voce deve ter digitado algo errado");
      atrasarTela(0.2);
      wrefresh(submenuP->janela);
      mvwprintw(submenuP->janela, 4, 1 , "Qual sera o tamanho do seu mundo? ");
      mvwprintw(submenuP->janela, 5, 1 , "(Sugestao: minimo -> 2, maximo -> %d): ", colMax/4);
      atrasarTela(0.2);
      wrefresh(submenuP->janela);
      wattroff(submenuP->janela, COLOR_PAIR(ALERTA));
      wscanw(submenuP->janela, "%d", &tam);
      
    }
    
    apagarJanela(submenuP);

  
    return tam;
}

//desenha o titulo da janela principal
void desenharTituloJanela(interface *a, char *titulo, int cor){ 
  int tituloLargura = strlen(titulo);
 
  //adiciona um caractere
  mvwaddch(a->janela, 2, 0, ACS_LTEE); 
  mvwhline(a->janela, 2, 1, ACS_HLINE, a->larg - 2);
  mvwaddch(a->janela, 2, a->larg - 1, ACS_RTEE); 
  

  wattron(a->janela, COLOR_PAIR(cor));
  mvwprintw(a->janela, 1, a->larg/2 - tituloLargura/2, "%s", titulo);
  wattroff(a->janela, COLOR_PAIR(cor));
  
  wrefresh(a->janela);
}

//desenha a borda do menu
void desenharBorda(){
  
    int comp, larg;
    getmaxyx(stdscr ,comp, larg);
    int largArq;

    largArq = strlen("|Arquivo|");
    //desenhar bordas
    mvhline( 0, 0, ACS_HLINE, larg);
    mvprintw(0, larg-largArq-6, "|Arquivo|");
    mvprintw(0, larg-largArq*2-8, "|Info|");
    attron(A_REVERSE);
    mvaddch(comp-3, 10, ACS_UARROW);
    mvprintw(comp-2, 2, "Utilize | |  - -  para locomover");
    mvaddch(comp-2, 14, ACS_LARROW);
    mvaddch(comp-2, 18, ACS_RARROW);
    mvaddch(comp-1, 12, ACS_DARROW);
    attroff(A_REVERSE);
    refresh();
}

 //destaca info e arquivo
void destacarBorda(int destaqueH, int destaqueV){
  int larg, largArq, comp;
  
  getmaxyx(stdscr, comp, larg);
  largArq = strlen("|Arquivo|");

  if(destaqueH == -1 && destaqueV == 0){
    attron(COLOR_PAIR(AZUL_BRANCO));    
    mvprintw(0, larg-largArq-6, "|Arquivo|");
    attroff(COLOR_PAIR(AZUL_BRANCO));     
    mvprintw(0, larg-largArq*2-8, "|Info|");
    refresh();
  }else if(destaqueH == -1 && destaqueV == -1){
    
    attron(COLOR_PAIR(AZUL_BRANCO));    
    mvprintw(0, larg-largArq*2-8, "|Info|");
    attroff(COLOR_PAIR(AZUL_BRANCO));
    mvprintw(0, larg-largArq-2-4, "|Arquivo|");
    refresh();
  }else{
    desenharBorda();
  }
}
//destaca a opção selecionada
void destacarItem(interface *a, int cor, int x, int y, int k, int modoSeta){
    
    for(int i = 0; i < a->nI; i++){
      
      if(i == a->destaqueH ){
        transformarMaius(a->item[i].str);
        wattron(a->janela, COLOR_PAIR(cor));
        
        if(modoSeta == 1){
          mvwprintw(a->janela, i*x+k, y, "-> %s", a->item[i].str);
    
        }else{
          mvwprintw(a->janela, i*x+k, y, "%s", a->item[i].str);
        }
        wattroff(a->janela, COLOR_PAIR(cor));
        transformarMinus(a->item[i].str);
        
      }else{
        mvwprintw(a->janela, i*x+k, y, "%s    ", a->item[i].str);
      }

      mostrarJanela(a, PADRAO);
    }
}

//função para escolher
char escolherModo(mundo *mundo ){
  char op;

  mostrarJanela(&(mundo->menu[0]), mundo->mundoConfig.corFundo);

  wattron(mundo->menu[0].janela,  A_REVERSE);
  mvwprintw(mundo->menu[0].janela, 1, 2, "A");
  mvwprintw(mundo->menu[0].janela,2, 2, "M");
  mvwprintw(mundo->menu[0].janela, 3, 2, "L");
  mvwprintw(mundo->menu[0].janela, 4, 2, "I");
  mvwprintw(mundo->menu[0].janela,5, 2, "S");
  mvwprintw(mundo->menu[0].janela,6, 2, "B");
  mvwprintw(mundo->menu[0].janela,7, 2, "V");
  wattroff(mundo->menu[0].janela, A_REVERSE); 

  
  mvwprintw(mundo->menu[0].janela, 1, 4, "- Inserir celulas aleatoriamente");
  mvwprintw(mundo->menu[0].janela, 2, 4, "- Inserir celulas manualmente");
  mvwprintw(mundo->menu[0].janela, 3, 4, "- Limpar Mundo");
  mvwprintw(mundo->menu[0].janela,4, 4, "- Iniciar Mundo");
  mvwprintw(mundo->menu[0].janela, 5, 4, "- Para sair"); 
  mvwprintw(mundo->menu[0].janela, 6, 4, "- Opcoes da Borda");
  mvwprintw(mundo->menu[0].janela, 7, 4, "- Vizinhos Futuros");

 
  wrefresh(mundo->menu[0].janela);
  op = mvwgetch(mundo->menu[0].janela, 7, 26 );
  op = toupper(op);
  return op;
}

//adiciona celulas de um modo manual ou aleatório

//desenha a celula no terminal
void desenharCel(mundo *mundo, float vel, int cor, int modo){ 
  // i = linha; j = coluna;
  int lin, col;
  for (int i = 0; i < mundo->vivo.qtdItens; i++) {
    lin = mundo->vivo.lista[i].linha;
    col = mundo->vivo.lista[i].coluna;
    
    if (mundo->celula[lin][col].status == 2) {
      desenharCelUnica(mundo, cor, lin, col, 2, 0);
    }
  }
  for (int i = 0; i < mundo->vivo.qtdItens; i++) {
    lin = mundo->vivo.lista[i].linha;
    col = mundo->vivo.lista[i].coluna;
    
    if (mundo->celula[lin][col].status == 1) {
        desenharCelUnica(mundo, mundo->mundoConfig.corCelula, lin, col,  2, vel);
    }
  }

  if(modo == 1){
    for(int i = 0; i < mundo->infoMundo.tamMundo; i++){
    
    for(int j = 0; j < mundo->infoMundo.tamMundo; j++){  
      
      if(mundo->celula[i][j].status == 0){
        desenharCelUnica(mundo, mundo->mundoConfig.corFundo, i, j,  0, 0);

        
      }
    } 
  }
  }

}



void desenharCelUnica(mundo *mundo, int cor, int lin, int col, int status, float vel){

  int  colConst, linConst; 
  
  getmaxyx(stdscr, linConst ,colConst);
  linConst = linConst/2 - mundo->infoMundo.tamMundo/2;
  colConst = colConst/2 - mundo->infoMundo.tamMundo/2 * TERMINAL_COL;

  move(linConst+lin+1, colConst+col*3+2); 

  attron(COLOR_PAIR(cor));
  printw("%c", mundo->celula[lin][col].desenho);
  mundo->celula[lin][col].status = status;
  attroff(COLOR_PAIR(cor));
  atrasarTela(vel);
  refresh();

}

void desenharCelVizinhos(mundo *mundo, int cor){

  criarGeracao(mundo->celula, mundo->infoMundo.tamMundo, &(mundo->vivo), &(mundo->possivelVivo),  &(mundo->mortoFuturo),  &(mundo->vivoFuturo));

  int  colConst, linConst; 
  int lin, col;
  getmaxyx(stdscr, linConst ,colConst);
  linConst = linConst/2 - mundo->infoMundo.tamMundo/2;
  colConst = colConst/2 - mundo->infoMundo.tamMundo/2 * TERMINAL_COL;
  
  for(int i = 0; i < mundo->vivoFuturo.qtdItens; i++){
    
      lin = mundo->vivoFuturo.lista[i].linha;
      col = mundo->vivoFuturo.lista[i].coluna;
      move(linConst+lin+1, colConst+col*3+2); 

      
    
        attron(COLOR_PAIR(INVERTIDO_2));
        printw("O");
        attroff(COLOR_PAIR(INVERTIDO_2));
        refresh();
     
      
    }

    for(int i = 0; i < mundo->mortoFuturo.qtdItens; i++){
    
      lin = mundo->mortoFuturo.lista[i].linha;
      col = mundo->mortoFuturo.lista[i].coluna;
      move(linConst+lin+1, colConst+col*3+2); 

      
        attron(COLOR_PAIR(INVERTIDO_1));
        printw("X");
        attroff(COLOR_PAIR(INVERTIDO_1));
        refresh();
      
    }


    

}


//inicializa a sub interface
void inicializarSubInter(interface submenuP[], interface *menuP){

  criarSubInter(menuP, &submenuP[0], menuP->comp-2, menuP->larg/4, 1, 1);
  criarSubInter(menuP, &submenuP[1], menuP->comp-2, menuP->larg - menuP->larg/4-3, 1, menuP->larg/4+2);
  criarSubInter(menuP, &submenuP[2], submenuP[1].comp/6+3, submenuP[1].larg - 4, 2, menuP->larg/4+4);
  
  submenuP[1].nI = 4;
  
  carregarItem(submenuP[1].item,
              "[Velocidade]",
              "[Cor de Celula]",
              "[Cor de Fundo]",
              "[Sair]",
              " ", submenuP[1].nI); 


  submenuP[0].nI = 3;
  
  carregarItem(submenuP[0].item,
              "<   comecar   >",
              "<    opcoes   >",
              "<     sair    >",
              " ",
              " ", submenuP[0].nI); 
}

//cria uma segunda interface
void criarSubInter(interface *a, interface *aSub, int  linha, int coluna, int compComeca, int largComeca){

  aSub->comp = linha;
  aSub->larg = coluna;
  aSub->compComeca = compComeca + a->compComeca;
  aSub->largComeca = largComeca + a->largComeca;
  aSub->janela = newwin(aSub->comp, aSub->larg, aSub->compComeca, aSub->largComeca);
}

//inicializa as cores
void inicializarCor(mundo *mundo){

  init_pair(ALERTA, COLOR_RED, COLOR_BLACK);
  init_pair(PADRAO, COLOR_WHITE, COLOR_BLACK);
  init_pair(DESTAQUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(PRETO_BRANCO, COLOR_BLACK, COLOR_WHITE);
  init_pair(BRANCO, COLOR_WHITE, COLOR_WHITE);
  //init_pair(VERDE_ESCURO, COLOR_GREEN, COLOR_BLACK);
  init_pair(CIANO, COLOR_CYAN, COLOR_BLACK);
  init_pair(AZUL_BRANCO, COLOR_WHITE, COLOR_BLUE);
  init_pair(AMARELO_ESCURO, COLOR_YELLOW, COLOR_BLACK);
  init_pair(INVERTIDO_2, COLOR_WHITE, COLOR_WHITE );



  init_pair(20, COLOR_RED, COLOR_BLACK);
  init_pair(21, COLOR_WHITE, COLOR_BLACK);


}

//inicializa uma interface
void inicializarInter(interface *menuP){
      
    int comp, larg;
    getmaxyx(stdscr ,comp, larg);
    
    //Janela das opções
    menuP->comp = comp/2 + comp/8;
    menuP->larg = larg/2 + larg/8;
    menuP->compComeca = comp/2 - menuP->comp/2;
    menuP->largComeca = larg/2 - menuP->larg/2;
    // fizemos de uma maneira generalizada para ter um padrao em qualquer pc
    menuP->janela = newwin(menuP->comp, menuP->larg, menuP->compComeca, menuP->largComeca); 
    keypad(menuP->janela, true); 


}

void apagarJanela(interface *a){
  werase(a->janela);
  refresh();
  wrefresh(a->janela);
  refresh();  
}

void iniciarGeracao(mundo *mundo,  int tam){

  interface geracao;
  int nG; //numero de gerações
  float seg;
  char op;
  
  clear();
  desenharBorda();
  desenharMundoEnum(mundo, 0);
   
  desenharCel(mundo, 0, mundo->mundoConfig.corFundo, 0);
  mostrarJanela(&(mundo->menu[2]), mundo->mundoConfig.corFundo);

  desenharTituloJanela(&(mundo->menu[2]), "Geracao", INVERTIDO_2);
  mvwprintw(mundo->menu[2].janela,3, 1, "Geracao manual ou automatica? (M|A):  ");
  wrefresh(mundo->menu[2].janela);
  
  op = mvwgetch(mundo->menu[2].janela, 3, 37);
  op = toupper(op);
  
  
  if(op == 'A') {
    mvwprintw(mundo->menu[2].janela,4, 1, "Quantas Geracoes voce deseja fazer?:    ");
    mvwscanw(mundo->menu[2].janela, 4, 39,"%d", &nG); 
    
  }

  if(op == 'M') {
      wattron(mundo->menu[2].janela, A_REVERSE);
    mvwprintw(mundo->menu[2].janela,4, 1, "Utilize -> para ir para a proxima geracao");
     wattroff(mundo->menu[2].janela, A_REVERSE);
    wrefresh(mundo->menu[2].janela);

  }
  desenharGeracao(op, nG, mundo);
  
}

void iniciarModoManual(mundo *mundo){
  
  int opSeta = 0;
  int lin = 0, col = 0;
  bool sair = false, sair2 = false;
  int  colConst, linConst; 
  int l = 0, c =0;
  tipoItem itemAux;

  getmaxyx(stdscr, linConst ,colConst);
  linConst = linConst/2 - mundo->infoMundo.tamMundo/2;
  colConst = colConst/2 - mundo->infoMundo.tamMundo/2 * TERMINAL_COL;

  
  clear();
  noecho();
  apagarJanela(&(mundo->menu[1]));
  desenharBorda();
  desenharCel(mundo, 0, mundo->mundoConfig.corFundo, 0);
  wbkgd(stdscr, COLOR_PAIR(mundo->mundoConfig.corFundo));
  desenharMundoEnum(mundo, 0);
  //desenharEnum(NULL, mundo->infoMundo.tamMundo, linConst, colConst, 0.0001, 0);
  
  attron(A_REVERSE);
  mvprintw(1, 1,"Por favor, verifique o canto inferior esquerdo e aperte <s> para sair");
  refresh();
  attroff(A_REVERSE);

  while(sair == false){
   
    sair = animarCursor(&l, &c, mundo->infoMundo.tamMundo, linConst, colConst, 0, NULL, &opSeta);
    
    desenharCel(mundo, 0, mundo->mundoConfig.corFundo, 0);
    definirCelViva(mundo->celula, l, c);
    itemAux.linha = l;
    itemAux.coluna = c;
    mundo->vivo.lista[mundo->vivo.qtdItens].estado = 1;
    inserirItemLista(&(mundo->vivo), itemAux);
    desenharCelUnica(mundo, mundo->mundoConfig.corCelula, l, c, 2, 0);
  }
}

void desenharGeracao(char op, int nG, mundo *mundo){

  int opcao = 0;
  
  for(int i = 0; i < nG; i++){
    
    if(op == 'A') { //automatico
      
      criarCelula(mundo->celula, mundo->infoMundo.tamMundo, &(mundo->vivo), &(mundo->possivelVivo),  &(mundo->mortoFuturo),  &(mundo->vivoFuturo));

      desenharCel(mundo, 0, mundo->mundoConfig.corFundo, 1);
      atrasarTela(mundo->mundoConfig.vel);

    } else if(op == 'M'){
      while(opcao != 's'){    
        
        opcao = getch();
        if(opcao != 's'){
          criarCelula(mundo->celula, mundo->infoMundo.tamMundo, &(mundo->vivo), &(mundo->possivelVivo),  &(mundo->mortoFuturo),  &(mundo->vivoFuturo));
          desenharCel(mundo, 0, mundo->mundoConfig.corFundo, 1);
        }
      }
    }
  }
}

//l => variavel que tem que ter uma valor constantemente mudado 
//de acordo com a entrada do usuario serve como auxiliar o mesmo vale
//para a variavel c
bool animarCursor(int *l, int *c,int tam, int lin, int col, int modo, interface *a, int *opSeta){
  
  bool sair = false;
 
  if(modo == 0){
    
    while(sair == false && (*opSeta != 's')){
      *opSeta = getch();     
      sair = moverSeta( l, c, 1, 1, tam-2, tam-2, opSeta);
      move(lin+(*l)+1, col+(*c)*3+2);
      refresh();
      if(*opSeta == 's'){
        return true;
      }
    }
  }

  if(modo == 1){
    
    while(sair == false && (*opSeta != 's')){
      *opSeta = getch(); 
      sair = moverSeta( l, c, 1, 1, tam-2, tam-2, opSeta);
      wmove(a->janela, lin+(*l)+1, col+(*c)*3+2);
      wrefresh(a->janela);
      if(*opSeta == 's'){
        return true;
      }
    }
  } 
}

void iniciarModoAleatorio(mundo *mundo){
  
  int lin = 0, col = 0, quant;
  tipoItem itemAux;

  wattron(mundo->menu[1].janela, COLOR_PAIR(mundo->mundoConfig.corFundo));  
  mvwprintw(mundo->menu[1].janela, 3, 1,"Quantas celulas voce deseja colocar? (da para colocar %d celulas)", mundo->infoMundo.tamMundo * mundo->infoMundo.tamMundo);
  wrefresh(mundo->menu[1].janela);
  mvwscanw(mundo->menu[1].janela, 3, 69,"%d", &quant);
  wattron(mundo->menu[1].janela, COLOR_PAIR(mundo->mundoConfig.corFundo));  
  
  srand(time(NULL));
    
  for(int i = 0; i < quant; i++){
    lin = rand() % mundo->infoMundo.tamMundo;
    col = rand() % mundo->infoMundo.tamMundo;
    if(mundo->celula[lin][col].status == 0){
      definirCelViva(mundo->celula, lin, col);
      itemAux.linha = lin;
      itemAux.coluna = col;
      mundo->vivo.lista[mundo->vivo.qtdItens].estado = 1;
      inserirItemLista(&(mundo->vivo), itemAux);
    }
    
  }
}

bool moverSeta(int *escolhaH, int *escolhaV, int minH, int minV, int maxH, int maxV, int *opcao){
  bool  sair = false;
  int escolhaAux = *escolhaH;
  int escolhaAux2 = *escolhaV;
  

  switch(*opcao){
    case KEY_UP:
      escolhaAux--;
      if(escolhaAux  < minH){
        escolhaAux  = minH-1;
      }
    break;

    case KEY_DOWN:
      escolhaAux++;
        if(escolhaAux  > maxH){
          escolhaAux  = maxH+1 ;
        }
    break;

    case KEY_LEFT:
      escolhaAux2--;
      if(escolhaAux2 < minV){
          escolhaAux2 = minV - 1;
        }
    break;

    case KEY_RIGHT:
      escolhaAux2++;
      if(escolhaAux2  > maxV){
          escolhaAux2  = maxV + 1; 
      } 
    break; 
    
    case '\n':
      sair = true;
    break;
  }
  
  *escolhaH = escolhaAux;
  *escolhaV = escolhaAux2;
  return sair;
}

void apagarFrases(interface *interfaceP, int lin, int col, char *palavra){
  mvwprintw(interfaceP->janela, lin, col, "%s", palavra);
  wrefresh(interfaceP->janela);
}
