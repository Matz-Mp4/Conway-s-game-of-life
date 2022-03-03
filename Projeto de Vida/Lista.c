
#include "Headers/Lista.h"
void removerDuplicatas(tipoLista *plista){

 for (int k=0; k < plista->qtdItens; k++){
       
   for (int j = 0; j < plista->qtdItens; j++){
      //Limpando a lista de mortos das duplicatas das celulas
      if ((k!=j) && (plista->lista[k].linha == plista->lista[j].linha) && (plista->lista[k].coluna == plista->lista[j].coluna)){
              
        if(j!=plista->qtdItens)
                  
          for(int z = j + 1; z < plista->qtdItens; z++){          
            plista->lista[z - 1].linha = plista->lista[z].linha;
            plista->lista[z - 1].coluna = plista->lista[z].coluna;
          }
              //Diminuindo o tamanho da lista
              j--;
              plista->qtdItens--;
          }

      }
    }
}

/*  Descrição: Inicializção da Lista
    Parâmetros: pLista (ponteiro para a Lista)
    Retorno: void
*/
void inicializarLista(tipoLista *pLista) {
  pLista->qtdItens = 0;
}

/*  Descrição: Insere um item no final da lista
    Parâmetros: pLista (ponteiro para a Lista), item (Item a ser inserido)
    Retorno: 0 se sucesso. -1 ser a lista estiver cheia
*/
int inserirItemLista(tipoLista *pLista, tipoItem item) {
      int resultado = 0;
      int posicao;

      if (pLista->qtdItens < MAXLISTA-1) {
          posicao = pLista->qtdItens;
          pLista->lista[posicao] = item;
          pLista->qtdItens++;
      } else
          resultado = -1;

     return resultado;
}

/*  Descrição: Remove um item da lista.
    Parãmetros: pLista (ponteiro para a Lista), pos (posi��o na lista)
    Retorno: 0 se sucesso na remo��o. retorna -1 ser a posi��o estiver fora do limite superior da lista
*/
int removerItemLista(tipoLista *pLista, int pos) {
    int resultado = 0;
    int i;

    if (pos < pLista->qtdItens) {
     for(i=pos;i<pLista->qtdItens-1;i++)
        pLista->lista[i] = pLista->lista[i+1];
     pLista->qtdItens--;
    } else
       resultado = -1;

    return resultado;
}

/*  Descri��o: Retorna um item da lista a partir de uma posi��o
    Par�metros: pLista (ponteiro para a Lista), pos (posi��o na lista), item (item da lista)
    Retorno: true se a posi��o � valida na lista e false se n�o � valida
*/
bool obterItemListaPos(tipoLista *pLista, tipoItem *item, int pos) {

   bool resultado = false;

   if (pos < pLista->qtdItens) {
       *item = pLista->lista[pos];
       resultado = true;
   }

   return resultado;
}
/*  Descri��o: Quantidade de elementos na lista
    Par�metros: pLista (ponteiro para a Lista)
    Retorno: quantidade de elementos na lista.
*/
int tamanhoLista (tipoLista *pLista) {
    return pLista->qtdItens;
}


/*  Descri��o: A quantidade de elementos da lista eh zerado. A lista fica limpa.
    Par�metros: pLista (ponteiro para a Lista)
    Retorno:
*/
void limparLista(tipoLista *pLista) {
   pLista->qtdItens = 0;
}

/*  Descri��o: retorna se a lista est� vazia ou n�o.
    Par�metros: pLista (ponteiro para a Lista)
    Retorno: true se alista est� vazia e false se contem elementos
*/
bool listaEstaVazia(tipoLista *pLista) {
   bool resultado = true;

   if (pLista->qtdItens > 0)
        resultado = false;

   return resultado;
}

void copiarLista (tipoLista *pDestino, tipoLista *pFonte){
    for(int i = 0; i < pFonte->qtdItens; i++){
        pDestino->lista[i] = pFonte->lista[i];
    }
    pDestino->qtdItens = pFonte->qtdItens;
    pFonte->qtdItens = 0;
}
