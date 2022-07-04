#include  <stdio.h>
#include <stdlib.h>
typedef struct TnoABP
{
    int chave;
    struct TnoABP *esq;
    struct TnoABP *dir;
} TnoABP;

int buscaFilhoUnico(TnoABP *raiz, int nFilhos)
{
    int nFilhosUnico = nFilhos;
    if(raiz == NULL)
        nFilhosUnico = nFilhosUnico + 0;
    if(raiz->esq == NULL && raiz->dir != NULL)
    {
        nFilhosUnico = nFilhosUnico + 1;
        buscaFilhoUnico(raiz->dir, nFilhosUnico);
    }
    if(raiz->esq != NULL && raiz->dir == NULL)
    {
        nFilhosUnico = nFilhosUnico + 1;
        buscaFilhoUnico(raiz->esq, nFilhosUnico);
    }
    if(raiz->esq != NULL && raiz->dir != NULL)
    {
        nFilhosUnico = nFilhosUnico + buscaFilhoUnico(raiz->esq, nFilhosUnico);
        nFilhosUnico = nFilhosUnico + buscaFilhoUnico(raiz->dir, nFilhosUnico);
    }
    return nFilhosUnico;
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
    int n, nFilhosUnico;

    printf("Quantos nos deseja inserir na ABP?\n");
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        printf("Inisira a chave\n");
        scanf("%d", &chaveInsere);
        novoNo = insereABP(&raiz,chaveInsere);
        printf("Nó de chave: %d inserido no endereço %p.\nRaiz da ABP em: %p\n", chaveInsere, novoNo, raiz);
    }
    nFilhosUnico = buscaFilhoUnico(raiz, 0);
    printf("%d Nó(s) tem filhos unicos\n", nFilhosUnico);
   return 0;
}
