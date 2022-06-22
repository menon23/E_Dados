#include "openssl/crypto.h" //def SHA256_DIGEST_LENGTH
#include "openssl/sha.h" //def func SHA256
#include <string.h>
#include "mtwister.c"

typedef struct BlocoNaoMinerado
{
  unsigned int numero;//4
	unsigned long int nonce;//4
	unsigned char data[184];//nao alterar. Deve ser inicializado com zeros.
  unsigned char hashAnterior[SHA256_DIGEST_LENGTH]; //32
} BlocoNaoMinerado;
typedef struct BlocoMinerado
{
  BlocoNaoMinerado bloco;
  unsigned char hash[SHA256_DIGEST_LENGTH]; //32 bytes
	struct BlocoMinerado *prox;
} BlocoMinerado;

BlocoMinerado *insereBloco(BlocoMinerado **chain, BlocoNaoMinerado bloco, unsigned char hash[])
{
	BlocoMinerado *aux = *chain;
	*chain = malloc(sizeof(BlocoMinerado));

	if(*chain ==NULL)//se não tiver espaço para o malloc
	{
		printf("Bloco vazio\n");
		return NULL;
	}
	(*chain)->bloco = bloco;
	
	printf("Inseriu Bloco:\n");
	printf("Bloco n: %d\n", (*chain)->bloco.numero);
	printf("Hahs: ");
	for(int i=0; i<SHA256_DIGEST_LENGTH;i++)
	{
		(*chain)->hash[i] = hash[i];
		printf("%02x", (*chain)->hash[i]);
	}
	(*chain)->prox = aux;
	return *chain;
}
void consultaHash(BlocoMinerado **chain)
{
	BlocoMinerado *aux;
	aux = *chain;
	int nBloco;
	if(aux == NULL)
	{
		printf("\nBlockChain vazia\n");
		return;
	}
	printf("Insira o n do bloco que deseja consultar o hash:\n");
	scanf("%d", &nBloco);
	if(nBloco<1 ||nBloco>1000)
	{
		printf("Bloco invalido\n");
		return;
	}
	printf("Bloco n: %d\n", nBloco);
	printf("Hash:\n");
	for(int i= 0; i<SHA256_DIGEST_LENGTH; i++)
		printf("%02x", aux->hash[i]);
}

void consultaBitcoin(BlocoMinerado **chain)
{
  BlocoMinerado *aux;
  aux = *chain;
  int endereco;
	int bitcoin=0;
  if(aux == NULL)
  {
    printf("\nBlockChain vazia\n");
    return;
  }
  printf("Insira o n do endeco que deseja consultar os Bitcoins:\n");
  scanf("%d", &endereco);
	if(endereco<0||endereco>255)
	{
		printf("Endereco invalido\n");
		return;
	}
  while(aux->prox!=NULL)
	{
		for(int i=0; i<184; i=i+3)
		{
			if(aux->bloco.data[i]==endereco)
				bitcoin = bitcoin-aux->bloco.data[i+2];
		}
		for(int j=1; j<184; j=j+3)
		{
			if(aux->bloco.data[j]==endereco)
				bitcoin = bitcoin+aux->bloco.data[j+1];
		}
		aux = aux->prox;
	}
	printf("O endereco %d, possui %d bitcoins\n", endereco, bitcoin);
}
void carteira(BlocoMinerado **chain)
{
	BlocoMinerado *aux = *chain;
	int endereco[255][1];
	int bitcoin;
	for(int i = 0; i<256; i++)//enderecos de usuarios
	{
		endereco[i][0] = 0;
		bitcoin =0;
		for(int j=0; j<184; j=j+3)
		{
			if(aux->bloco.data[j]==i)
				bitcoin = bitcoin - aux->bloco.data[j+2];
		}
    for(int k=1; k<184; k=k+3)
    {
      if(aux->bloco.data[k]==i)
				bitcoin = bitcoin + aux->bloco.data[k+1];
    }
		endereco[i][0] = bitcoin;
    aux = aux->prox;
		printf("Endereco[%d]: %d \n",i,endereco[i][0]);
		
	}
}


int main()
{
	MTRand semente = seedRand(1234567);
	BlocoMinerado *chain = NULL;
	BlocoNaoMinerado bloco;
	unsigned char hash[SHA256_DIGEST_LENGTH];
	unsigned char nTrans;

	//inicializando o hashAnterior do bloco genesis
	for(int i = 0; i<SHA256_DIGEST_LENGTH; i++)
	{
		bloco.hashAnterior[i] = 0;
//		printf("%u", bloco.hashAnterior[i]);
	}

	//loop de inserção dos blocos 0 a 1000
	for(int j=1; j<=3;j++)
	{
		bloco.numero = j;

		printf("Bloco n: %d\n", bloco.numero);
		printf("Data:\n ");
		//data deve ser inicializado com 0;
		for(int k=0; k<184; k++)
			bloco.data[k] = 0;
				
		//sortearndo o numero de transações por bloco
		//de 1 a 61
		nTrans = (1 + genRandLong(&semente) % 61)*3;
		//preenchendo os val das transações
		for(int l=0; l<nTrans; l=l+3)
		{
			bloco.data[l] = genRandLong(&semente)%256;//0-255 endereço de origem
			bloco.data[l+1] = genRandLong(&semente)%256;//0-255 endereço de destino
			bloco.data[l+2] = genRandLong(&semente)%51;//0-50 valor em bitcoins
		}
		//imprimindo os valores de data
		for(int k=0; k<184; k++)
    {
			if(k%3==0)
				printf("\t");
      printf("%02x", bloco.data[k]);
    }
    printf("\n");
		
		//calculando nonce
		unsigned long int nonce=0;
		do//teste da dificuldade de 4 primeiros elem de hash ==0 
		{
			bloco.nonce = nonce;
			SHA256((unsigned char*)&bloco, sizeof(BlocoNaoMinerado), hash);
			nonce++;
		}while(!(hash[0]==0 && hash[1]==0));// && hash[2]==0 && hash[3]==0));
		insereBloco(&chain, bloco, hash);
	}
	int op;
	do
	{
		printf("\nQual op deseja utilizar?\n");
		printf("1 - Consultar hash\n");
		printf("2 - Consultar Bitcoins\n");
		printf("3 - Endereco mais 'rico'\n");
		printf("4 - Lista crescente\n");
		printf("5 - Sair\n");
		scanf("%d", &op);

		switch(op)
		{
			case 1:
				consultaHash(&chain);
				break;
			case 2:
				consultaBitcoin(&chain);
				break;
			case 3:
				carteira(&chain);
				break;
		}
	}while(op!=5);
		

	return 0;

}
