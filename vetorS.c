#include<stdio.h>
#include<stdlib.h>
#define tam 10

typedef struct Tno{
  int chave;
  unsigned char vetor[tam];
  struct Tno *prox;
}Tno;

void copiaVetor(unsigned char vetor1[],unsigned char vetor2[])
{
        for(int i=0; i<tam;i++)
                vetor2[i] = vetor1[i];
}

Tno *insereInicio(Tno **prim, int k, unsigned char vetor[]){
  Tno *aux = *prim;
  *prim = malloc(sizeof(Tno));

  if(*prim == NULL)
    return NULL;
  (*prim)->chave = k;
  (*prim)->prox = aux;
        for(int i=0; i<tam; i++)
                (*prim)->vetor[i] = vetor[i];
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
          for(int i = 0; i<tam; i++)
                        printf("%d",aux->vetor[i]);
                printf("\nFim do vetor\n");
                aux = aux->prox;
        }
}


int main()
{
        unsigned char vetorMain[tam]={0,1,2,3,4,5,6,7,8,9};
        int chave;
        Tno *prim=NULL;
        printf("Insira a chave do vetor\n");
        scanf("%d", &chave);
        insereInicio(&prim, chave, vetorMain);
        exibeLista(&prim);
        return 0;
}
