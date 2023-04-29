#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

//Função de comparação que compara dois registros de endereço com base em seus CEPs. É usada pela função qsort() da biblioteca padrão do C para ordenar os registros por CEP.
//e1 e e2 sao ponteiros genéricos que são convertidos para Endereco* usando cast para acessar o campo CEP.
int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8); //retorna um valor negativo se a string cep do primeiro registro for menor que a do segundo, um valor positivo se for maior, e zero se forem iguais
}

int main(int argc, char**argv)
{
	FILE *f;
	Endereco *e;
	long posicao, qtd;

	f = fopen("cep.dat","rb");

	fseek(f,0,SEEK_END); //cursor do arquivo é posicionado no final do arquivo(último byte)
	posicao = ftell(f); //retorna a posição do ultimo byte
	qtd = posicao/sizeof(Endereco); //tamanho do arquivo em bytes é divido pelo tamanho de cada registro, retornando a quantidade total de registros no arquivo
	e = (Endereco*) malloc(posicao);
	//malloc: permite alocar dinamicamente um bloco de memoria no heap (área de memória livre do programa) em tempo de execução
	//recebe como argumento o tamanho em bytes do bloco de memoria que se deseja alocar e retorna um ponteiro para o início do bloco

	if(e == NULL) {
		printf("Erro: Nao consegui alocar a memoria\n");
		fclose(f);
		return -1;
	}
	rewind(f); // Vai para o inicio do arquivo
	if(fread(e,sizeof(Endereco),qtd,f) == qtd) {
		printf("Lido = OK\n");
	}
	fclose(f);
	qsort(e,qtd,sizeof(Endereco),compara);
	printf("Ordenado = OK\n");
	
	f = fopen("cep_ordenado2.dat","wb");
	fwrite(e,sizeof(Endereco),qtd,f);
	fclose(f);
	printf("Escrito = OK\n");
	free(e);
}

