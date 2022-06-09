#include <stdlib.h>
#include <stdio.h>
typedef struct Tno{
  int chave;
  struct Tno *prox;
}Tno;

Tno *insereInicio(Tno **prim, int k){
  Tno *aux = *prim;
  *prim = malloc(sizeof(Tno));

  if(*prim == NULL)
    return NULL;
  (*prim)->chave = k;
  (*prim)->prox = aux;
  return *prim;
}
void exibeLista(Tno **prim){
        Tno *aux;
        aux =*prim;
        if(aux==NULL){
                printf("Lista Vazia!\n");
                return;
        }
        while(aux!=NULL){
                printf("Chave: %d\n", (*aux).chave);
                aux = aux->prox;
        }
}
void removeUltimo(Tno **prim){
        Tno *aux;
        if((*prim)==NULL)
                return;
        if((*prim)->prox==NULL){
                *prim=NULL;
                return;
        }
        aux =*prim;
        printf("Chave: %d\n",aux->chave);
        printf("Prox: %p\n", aux->prox);
        printf("Conteudo de prox: %d\n",(*(aux->prox)).chave);
        *prim =(aux)->prox;
        free(aux);
}
int main(){
        int op;
        Tno *prim=NULL;
        int chave;

        do {
                printf("\nEscolha uma op\n");
                printf("0-Sair\n");
                printf("1-Inserir struct\n");
                printf("2-Imprimir lista\n");
                printf("3-Remove a ultima struct\n");
                scanf("%d", &op);

                switch(op){
                        case 1:
                                printf("Inisira a chave\n");
                                scanf("%d", &chave);
                                insereInicio(&prim, chave);
                                break;
                        case 2:
                                exibeLista(&prim);
                                break;
                        case 3:
                                removeUltimo(&prim);
                                exibeLista(&prim);
                                break;
                }

        }while(op!=0);
        return 0;
}

