#include <stdio.h>

typedef struct carteira
{
    unsigned char id;
    int valor;
} carteira;
void impreCarteira(carteira vetor[], int tam)
{
    
    for(int i=0; i<tam; i++)
    {
        printf("Id:%02x\nBitcoins:\n%d\n", vetor[i].id,vetor[i].valor);
    }
}

void ordenaCarteira(carteira    vetor[], int ini, int fim)
{
    if(ini>fim||ini==fim)
        return;
    carteira iMenor;
    carteira aux;

    iMenor = vetor[ini];
    for(int i=ini; i<fim; i++)
    {
        
        if(iMenor.valor>vetor[i].valor)
        {
            aux = iMenor;
            iMenor = vetor[i];
            vetor[i] = aux;
            //printf("vetor[i].valor: %d\n", vetor[i].valor);
        }
    }
    
    ordenaCarteira(vetor, ini+1, fim);
}

int main()
{
    carteira bitcoin[10];
    //preenchendo ao contrario
    for(int i=0; i<10; i++)
        bitcoin[i].id= i;
    for(int i=10; i>=0; i--)        
        bitcoin[i].valor = 10 -i;
    //imprimindo antes
    printf("Antes\n");
    printf("bitcoin[0].valor: %d\n", bitcoin[0].valor);
    //impreCarteira(bitcoin, 10);
    ordenaCarteira(bitcoin, 0, 9);
    printf("\nDepois\n");
    printf("bitcoin[0].valor: %d\n", bitcoin[0].valor);
    //impreCarteira(bitcoin,10);
    
    return 0;
}
