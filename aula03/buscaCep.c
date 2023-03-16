#include <stdio.h>
#include <string.h>
#define SEEK_SET 0

typedef struct _Endereco Endereco;

// registroCEP = struct.Struct("72s72s72s72s2s8s2s")

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e; //&e -> posição do endereço no espaço da memória
	int qt;
	int c;

                                                                                                                                                                                                                                                                                                           

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	c = 0;
	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
	f = fopen("cep.dat","r"); //cep.dat nome do arquivo / r: read
    fseek(f,390560*sizeof(Endereco), SEEK_SET);
	qt = fread(&e,sizeof(Endereco),1,f); //ler elemento com 300 bytes
	while(qt > 0)
	{
		c++;
		// argv[1] < e.cep  => strcmp(argv[1],e.cep) < 0
		// argv[1] > e.cep  => strcmp(argv[1],e.cep) > 0
		// argv[1] == e.cep  => strcmp(argv[1],e.cep) == 0
		if(strncmp(argv[1],e.cep,8)==0) //argv[1] cep que está sendo procurado. e.cep todos os ceps que estao sendo procurados
		{
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;
		} 
		qt = fread(&e,sizeof(Endereco),1,f); //importante! nao esquecer de colocar fread no final do loop	
	}
	printf("Total Lido: %d\n", c);
	fclose(f);
}

