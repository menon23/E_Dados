#include <stdio.h>
#include "mtwister.c"

int main() {
  MTRand semente = seedRand(1234567);

  unsigned char data[184];
  unsigned char nTrans;

  nTrans = (1+ genRandLong(&semente)%61)*3;
  printf("Numero de transacoes: %d \n", nTrans/3);

  //data deve ser inicializado com 0;
  printf("Data:\n");
  printf("Origem\tDestino\tBitcoin\n");
  for(int i = 0; i<184; i++)
    data[i] = 0;

  for(int l=0; l<nTrans; l=l+3)
  {
    data[l] = genRandLong(&semente)%256;//0-255 endereço de origem
    printf("%02x\t",data[l]);
    data[l+1] = genRandLong(&semente)%256;//0-255 endereço de destino
        printf("%02x\t",data[l+1]);
    data[l+2] = genRandLong(&semente)%51;//0-50 valor em bitcoins
    printf("%d\t",data[l+2]);
    printf("\n");
  }
  return 0;
}
