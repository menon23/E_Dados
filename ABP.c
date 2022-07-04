#include  <stdio.h>
#include <stdlib.h>
typedef struct TnoABP
{
    int chave;
    struct TnoABP *esq;
    struct TnoABP *dir;
} TnoABP;

TnoABP *buscaABP(TnoABP *raiz, int k)
{
    if(raiz == NULL)
        return NULL;
    if(raiz->chave == k)
        return raiz;
    if(k<raiz->chave)
        return buscaABP(raiz->esq, k);
    else
        return buscaABP(raiz->dir, k);
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
    int op;
    
    do
    {
        printf("\nEscolha uma op\n");
        printf("1-Inserir ABP\n");
        printf("2-Pesquisar\n");
        printf("\n0-Encerrar programa\n");
        scanf("%d", &op);
        
        switch(op)
        {
            case 1:
                printf("Inisira a chave\n");
                scanf("%d", &chaveInsere);
                novoNo = insereABP(&raiz,chaveInsere);
                printf("Nó de chave: %d inserido no endereço %p.\nRaiz da ABP em: %p\n", chaveInsere, novoNo, raiz);                   
                break;
            case 2:
                printf("Insira o o valor de chave que deseja buscar\n");
                scanf("%d", &chaveBusca);
                novoNo = buscaABP(raiz, chaveBusca);
                if(novoNo == NULL)
                    printf("Chave de busca nao encontrada na arvore\n");
                else
                    printf("Chave de busca encontrada no endereco:%p\n", novoNo);
                break;
        }
        
        
    }while(op!=0);
    return 0;
}
