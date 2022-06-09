//Exemplo de uso da funcao SHA256 da biblioteca Open SSL
// Este código requer a instalação do pacote libssl-dev
// Para compilar este código use gcc hash.c -lcrypto

#include "openssl/crypto.h" //def SHA256_DIGEST_LENGTH
#include "openssl/sha.h" //def func SHA256
#include <string.h>
#define tam SHA256_DIGEST_LENGTH

typedef struct Tno{
  int chave;
  unsigned char hash[tam];
  struct Tno *prox;
}Tno;


void printHash(unsigned char hash[], int length)
{
  int i;
  for(i=0;i<length;++i)
    printf("%02x", hash[i]);

  printf("\n");
}
void copiaHash(unsigned char vetor1[],unsigned char vetor2[])
{
        for(int i=0; i<tam;i++)
                vetor2[i] = vetor1[i];
}

int main(int argc, char *argv[])
{


  int valor;
        unsigned char hash2[tam];
        unsigned char hash[tam];//vetor que armazenará o resultado do hash. Tamanho definido pela libss
  //A funcao SHA256 requer tres parametros
  //1. o ponteiro para um vetor de unsigned char contendo o dado cujo hash você deseja calcular
  //2. o tamanho em bytes do dado cujo hash você deseja calcular
  //3. o ponteiro para um vetor de unsigned char que armazenará o resultado do hash calculado.

  do{
                printf("Informe o valor inteiro cujo hash deseja calcular\n");
    printf("OU 0 para sair\n");
    scanf("%d", &valor);//le white spaces
                SHA256((unsigned char *)&valor, sizeof(valor), hash);
                copiaHash(hash, hash2);
                printHash(hash, tam);
                printHash(hash2, tam);
        }while(valor!=0);
  return 0;
}
