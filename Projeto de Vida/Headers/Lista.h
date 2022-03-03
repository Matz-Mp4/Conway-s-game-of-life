#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#define MAXLISTA 10000
#include <stdbool.h>

typedef struct Celula {
  int linha;
  int coluna;
  int estado;
} tipoCelula;

typedef tipoCelula tipoItem;

typedef struct Lista {
  tipoItem lista[MAXLISTA];
  int qtdItens;
} tipoLista;

//typedef tipo_Item *iterator;
void removerDuplicatas(tipoLista *plista);
void copiarLista (tipoLista *pDestino, tipoLista *pFonte);
void inicializarLista(tipoLista *pLista); // inicializa��o da lista
int inserirItemLista(tipoLista *pLista, tipoItem item); // inser��o de elemento na lista
int removerItemLista(tipoLista *pLista, int pos); // remover elemento da lista a partir da posi��o
bool obterItemListaPos(tipoLista *pLista,tipoItem *item, int pos); // obter um elemento da lista a partir da posi��o
int tamanhoLista (tipoLista *pList); // retorna o tamanho da lista
void limparLista(tipoLista *pLista); // limpa a lista.
bool listaEstaVazia(tipoLista *pLista); // retorna se a lista est� vazia ou n�o


#endif // LISTA_H_INCLUDED
