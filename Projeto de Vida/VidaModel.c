#include "Headers/VidaModel.h"

//obtem a data de criação do mundo
void obterDataCriacaoMundo(info *infoMundo){
  
  //variave do tipo time_t para armazenar o temp
  time_t segundos;

  struct tm *data;
  //obtendo o tempo em segundos
  time(&segundos);
  
  //para converter de segundos para o tempo local
  //utilizando a função localtime
  data = localtime(&segundos);
  
  infoMundo->dia = data->tm_mday;
  infoMundo->mes = data->tm_mon+1;
  infoMundo->ano = data->tm_year+1900;
}

//faz um delay em certas ações
void  delay(float delay1) {

   if (delay1<0.001) return; // pode seDTree Toggle t tevita-se valores negativos.

   float inst1=0, inst2=0;

   inst1 = (float)clock()/(float)CLOCKS_PER_SEC;

   while (inst2-inst1<delay1) inst2 = (float)clock()/(float)CLOCKS_PER_SEC;

   return;

}

//faz uma animação de atraso na tela
void atrasarTela(float tempo){
    
    if(tempo > 0){
      fflush (stdout);
      delay(tempo);
    }
}



//transformas as letras em maiúsculo
void transformarMaius(char *str){

    int i = 0;
  
    while(str[i] != '\0'){
        str[i] = toupper(str[i]);
        i++;
    }
}

//transformas as letras em minusculo
void transformarMinus(char *str){

    int i = 0;
  
    while(str[i] != '\0'){
        str[i] = tolower(str[i]);
        i++;
    }
}
//faz a criaçao das opções do menu principal
void carregarItem(Item a[], char *str1, char *str2, char *str3, char *str4, char *str5, int nA){

    strcpy(a[Q_ITEM-5].str, str1);
    strcpy(a[Q_ITEM-4].str, str2);
    strcpy(a[Q_ITEM-3].str, str3);
    strcpy(a[Q_ITEM-2].str, str4);
    strcpy(a[Q_ITEM-1].str, str5);

    for(int i = 0; i< nA; i++){
      a[i].nS = strlen(a[i].str);
    }
}


//defini o status da célula como morta
void limparMatriz(individuo celula[100][100], int tam){
  
  for(int lin = 0; lin < tam; lin++){
    for(int col = 0; col < tam; col++) {
      celula[lin][col].status = 0;
      celula[lin][col].desenho = ' ';
      celula[lin][col].vizinho = 0;


      
    }
  }
}

//limpa todos os vizinhos
void limparVizinhos(individuo celula[100][100], int tam, tipoLista *lista){
    int lin, col;
    
    for(int i = 0; i < lista->qtdItens; i++) {
      lin = lista->lista[i].linha;
      col = lista->lista[i].coluna;  
      celula[lin][col].vizinho = 0;

      
    }
  
}

//defini o status da celula como morta
void definirCelMorta(individuo celula[100][100], int lin, int col){
  
  celula[lin][col].status = 0; 
  celula[lin][col].desenho = ' ';
}

//define status da celula como viva
void definirCelViva(individuo celula[100][100], int lin, int col){
  celula[lin][col].status = 1;
  celula[lin][col].desenho = 'O';
}
/*

 modo = 0 → verifica se a célula irá sobreviver ou não
 modo = 1 → verifica quais das posições sem célula irão viver na próxima geração

*/
void criarGeracao(individuo celula[100][100], int tam, tipoLista *vivo, tipoLista *possivelVivo, tipoLista *mortoFuturo, tipoLista *vivoFuturo){

    
  //limparVizinhos(celula, tam, vivoFuturo);
  //limparVizinhos(celula, tam, mortoFuturo);
  //limparVizinhos(celula, tam, possivelVivo);
  
  inicializarLista(possivelVivo);
  inicializarLista(vivoFuturo);
  inicializarLista(mortoFuturo);
  
  contarVizinho(0 ,vivo, vivoFuturo, mortoFuturo,  celula, tam);

  estimarCelFuturas(vivo, possivelVivo, tam, celula);
  
  contarVizinho(1,possivelVivo, vivoFuturo, mortoFuturo,  celula, tam);
  

}

void criarCelula(individuo celula[100][100], int tam, tipoLista *vivo, tipoLista *possivelVivo, tipoLista *mortoFuturo, tipoLista *vivoFuturo){

  int lin, col;
  int contVizinhos = 0;
  
  criarGeracao(celula, tam, vivo, possivelVivo, mortoFuturo, vivoFuturo);
  
  for(int i = 0; i < vivoFuturo->qtdItens; i ++){
    
    lin = vivoFuturo->lista[i].linha;
    col = vivoFuturo->lista[i].coluna;
    definirCelViva(celula, lin, col);
  }  
 
   for(int i = 0; i < mortoFuturo->qtdItens; i++){
    
    lin = mortoFuturo->lista[i].linha;
    col = mortoFuturo->lista[i].coluna;

    definirCelMorta(celula, lin, col);
    
  }
    
  copiarLista(vivo , vivoFuturo);
  removerDuplicatas(vivo); 
}

//faz a verificação das celulas vizinhas
void estimarCelFuturas(tipoLista *vivo, tipoLista *possivelVivo,  int tam, individuo celula[100][100]){
  
  
  int lin, col;
   int  linMin, linMax, colMin, colMax;
  tipoItem itemAux;
  int i , l, j;

  for (int l = 0; l < vivo->qtdItens ; l++){       
     lin = vivo->lista[l].linha;
     col = vivo->lista[l].coluna;
     
   

     if(lin <= 0)
       linMin = 0;
     else
       linMin = lin - 1;

     if(lin >= tam-1)
        linMax = tam-1;
     else 
        linMax = lin + 1;
     
     if(col <= 0)
       colMin = 0;
     else
       colMin = col - 1;

     if(col >= tam-1)
        colMax = tam-1;
     else 
        colMax = col + 1;
    if(celula[lin][col].vizinho >= 0){

     for(i = linMin; i <= linMax; i++){

       for(j = colMin; j <= colMax; j++){

         if(i != lin || j!= col){
           
          if(celula[i][j].status == 0){
              itemAux.linha = i;
              itemAux.coluna = j;
              inserirItemLista(possivelVivo, itemAux);
           }  
         }
        }
      }
    }
  }
}

//compLista == lista para ser objeto de comparação 
void contarVizinho(int modo, tipoLista *compLista, tipoLista *vivoFuturo, tipoLista *mortoFuturo,  individuo celula[100][100], int tam){

  int contVizinhos;
  int lin, col;
   int  linMin, linMax, colMin, colMax;
  tipoItem itemAux;
  int i , l, j;

  for (int l = 0; l < compLista->qtdItens ; l++){       
     lin = compLista->lista[l].linha;
     col = compLista->lista[l].coluna;
     
     celula[lin][col].vizinho = 0;

     if(lin <= 0)
       linMin = 0;
     else
       linMin = lin - 1;

     if(lin >= tam-1)
        linMax = tam-1;
     else 
        linMax = lin + 1;
     
     if(col <= 0)
       colMin = 0;
     else
       colMin = col - 1;

     if(col >= tam-1)
        colMax = tam-1;
     else 
        colMax = col + 1;

     for(i = linMin; i <= linMax; i++){

       for(j = colMin; j <= colMax; j++){
          
         if(i != lin || j!= col){
           
           if(celula[i][j].status == 2 || celula[i][j].status == 1){
             
             celula[lin][col].vizinho ++;
           }
         }
        }
      }
      
      definirCelPresentes(modo, vivoFuturo, mortoFuturo, lin, col, contVizinhos, celula);
  }    
}

//verifica quais candidatos irão/vão permanecer vivos
void definirCelPresentes(int modo ,tipoLista *vivoFuturo, tipoLista *mortoFuturo, int lin, int col, int contVizinhos, individuo celula[100][100]){

  tipoItem itemAux;
  
  if(modo == 1){
    if(celula[lin][col].vizinho == 3){
    
      itemAux.linha = lin;
      itemAux.coluna = col;
      vivoFuturo->lista[vivoFuturo->qtdItens].estado = 1;
      inserirItemLista(vivoFuturo, itemAux);
    }
  }else{ 

    if(celula[lin][col].vizinho == 3 || celula[lin][col].vizinho == 2){
    
      itemAux.linha = lin;
      itemAux.coluna = col;
      vivoFuturo->lista[vivoFuturo->qtdItens].estado = 1;
      inserirItemLista(vivoFuturo, itemAux);
    }  
  }
  if((celula[lin][col].vizinho < 2 || celula[lin][col].vizinho > 3) && celula[lin][col].status == 2 || celula[lin][col].status == 1){
    
    itemAux.linha = lin;
    itemAux.coluna = col;
    mortoFuturo->lista[mortoFuturo->qtdItens].estado = 0;
    inserirItemLista(mortoFuturo, itemAux);
    
  }
}


