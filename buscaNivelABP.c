#include  <stdio.h>
#include <stdlib.h>
typedef struct TnoABP
{
    int chave;
    struct TnoABP *esq;
    struct TnoABP *dir;
} TnoABP;

int buscaNivel(TnoABP *raiz,int chaveBusca, int nivel)
{
    if(raiz == NULL)
        return -1;
    if(raiz->chave == chaveBusca)
        return nivel + 0;
    if(chaveBusca > raiz->chave)
        buscaNivel(raiz->dir, chaveBusca, nivel +1);
    else
        buscaNivel(raiz->esq, chaveBusca, nivel +1);

}

TnoABP *insereABP(TnoABP **raiz, int k)
{
    if(*raiz == NULL)
    {
        *raiz = malloc(sizeof(TnoABP));
        if(*raiz == NULL)
        {
            printf("Espaco insuficiente\n");
            return NULL;
        }
        (*raiz)->chave = k;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
    }
    if((*raiz)->chave == k)//se já existe retorna o end
        return *raiz;
    if((*raiz)->chave < k)//se menor q raiz insere à dir
        return insereABP(&(*raiz)->dir, k );
    else//senão insere à esq
        return insereABP(&(*raiz)->esq, k );
 }

int main(void)
{
    TnoABP *raiz=NULL;
    TnoABP *novoNo;
    int chaveInsere;
    int chaveBusca;
    int n, nBusca;
    
    printf("Quantos nos deseja inserir na ABP?\n");
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        printf("Inisira a chave\n");
        scanf("%d", &chaveInsere);
        novoNo = insereABP(&raiz,chaveInsere);
        printf("Nó de chave: %d inserido no endereço %p.\nRaiz da ABP em: %p\n", chaveInsere, novoNo, raiz);
    }

    printf("\nInsira a chave de busca\n");
    scanf("%d", &chaveBusca);
    nBusca = buscaNivel(raiz, chaveBusca, 0);
    if(nBusca == -1)
        printf("Chave de busca %d nao encontrada\n", chaveBusca);
    else
        printf("Chave de busca %d encontrada no nivel %d\n", chaveBusca, nBusca);
   return 0;
}
