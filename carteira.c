#include <stdio.h>
typedef struct carteira
{
    unsigned char id;
    int valor;
} carteira;

void transacao(unsigned char vetor[],int nTrans, int tam)
{
    carteira bitcoin[tam];
    //zerando
    for(int i=0; i<tam; i++)
    {
        bitcoin[i].id = i;
        bitcoin[i].valor = 0;
    }
    //dando os valores
    for(int j=0; j<nTrans; j++)
    {
        for(int i=0; i<nTrans*3; i=i+3)
        {
            if(vetor[i]==j)
            {
                bitcoin[j].valor = bitcoin[j].valor -  vetor[i+2];
                if(bitcoin[j].valor<0)
                    bitcoin[j].valor =0;
            }
            if(vetor[i+1]==j)
                bitcoin[j].valor = bitcoin[j].valor +  vetor[i+2];
        }
    }
    //imprime
    for(int i=0; i<6; i++)
    {
        printf("Id:%02x\nBitcoins:\n%d\n", bitcoin[i].id,bitcoin[i].valor);
    }
    
}

int main()
{
    
    unsigned char data[15] = {0,1,2, 1,2,1, 3,2,3, 5,0,2, 1,5,1};
    transacao(data, 5, 6);
    return 0;
}
