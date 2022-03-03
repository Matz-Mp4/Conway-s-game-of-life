#include "Headers/VidaArquivoModel.h"
#include "Headers/Lista.h"

//Se passar um caracter basta ativar 
void adicionarCaracterTxt(FILE *arq, char *arqNome, char caracter, int modo){
  
  if(modo == 1){   
    arq = fopen(arqNome, "w+");
  }

  if(arq == NULL){
    exit(1);
  }
  
  fputc(caracter, arq);
  
  if(modo == 1){   
    fclose(arq);
  }
}

void salvarArquivo(arquivoInfo *lista, mundo *mundoSalvo, int i){
  
  lista->arq = fopen(lista->nomeArq, "wb");
  
  if(lista->arq == NULL){
     exit(1);
  }
  
  fwrite(&(mundoSalvo->celula), sizeof(individuo), MAXLISTA , lista->arq);
  fwrite(&(mundoSalvo->infoMundo), sizeof(info), 1, lista->arq);
  fwrite(&(mundoSalvo->mundoConfig), sizeof(config), 1, lista->arq);
  fwrite(&(mundoSalvo->vivoFuturo), sizeof(tipoLista), 1, lista->arq);
  fwrite(&(mundoSalvo->mortoFuturo), sizeof(tipoLista), 1, lista->arq);
  fwrite(&(mundoSalvo->possivelVivo), sizeof(tipoLista), 1, lista->arq);
  fwrite(&(mundoSalvo->vivo), sizeof(tipoLista), 1, lista->arq);
  fclose(lista->arq);
}
void carregarArquivo(arquivoInfo *lista, mundo *mundoCarregar, int i){
  
  lista->arq = fopen(lista->nomeArq, "a+b");
    
  if(lista->arq == NULL){
    exit(1);
  }
  fread(&(mundoCarregar->celula), sizeof(individuo), MAXLISTA , lista->arq);
  fread(&(mundoCarregar->infoMundo), sizeof(info), 1, lista->arq);
  fread(&(mundoCarregar->mundoConfig), sizeof(config), 1, lista->arq);
  fread(&(mundoCarregar->vivoFuturo), sizeof(tipoLista), 1, lista->arq);
  fread(&(mundoCarregar->mortoFuturo), sizeof(tipoLista), 1, lista->arq);
  fread(&(mundoCarregar->possivelVivo), sizeof(tipoLista), 1, lista->arq);
  fread(&(mundoCarregar->vivo), sizeof(tipoLista), 1, lista->arq);

//  fread(mundoCarregar, sizeof(mundo), 1, lista->arq);
  
  fclose(lista->arq);
}



void inicializarArqInfo(arquivoInfo lista[]){

  for(int i = 0; i < 10; i++){

    lista[i].status = -1;
    strcpy(lista[i].nomeArq, "Save/");
  
  }

}
