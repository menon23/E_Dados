#include <stdio.h>
typedef struct carteira
{
    unsigned char id;
    int valor;
} carteira;

void transacao(int nTrans, unsigned char vetor[])
{
    carteira bitcoin[6];
    //zerando
    for(int i=0; i<6; i++)
    {
        bitcoin[i].id = i;
        bitcoin[i].valor = 0;
    }
    //dando os valores
    for(int i=0; i<nTrans*3; i++)
    {
        if(vetor[i]==i)
        {
            bitcoin[i].valor = bitcoin[i].valor -  vetor[i+2];
            if(bitcoin[i].valor<0)
                bitcoin[i].valor =0;
        }
    }
    for(int i=1; i<nTrans*3; i=i+3)
    {
        if(vetor[i]==i)
            bitcoin[i].valor = bitcoin[i].valor +  vetor[i+1];
    }
    //imprime
    for(int i=0; i<6; i++)
    {
        printf("Id:%02x\nBitcoins:\n%d\n", bitcoin[i].id,bitcoin[i].valor);
    }
    
}

int main()
{
    
    unsigned char data[15] = {0,1,2, 2,1,1, 3,1,3, 5,1,2, 5,1,1};
    transacao(5, data);
    return 0;
}
