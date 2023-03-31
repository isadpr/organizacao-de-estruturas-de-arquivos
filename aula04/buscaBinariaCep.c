#include <stdio.h>
#include <stdlib.h>
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

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	f = fopen("cep_ordenado.dat","r"); 
    fseek(f, 0, SEEK_END); //vai até o final para descobrir o tamanho do arquivo
    //Tamanho do arquivo em registros:
    qt = ftell(f)/sizeof(Endereco);

    int inicio = 0;
    int fim = qt - 1;

    while(inicio<=fim){
        int meio = (inicio + fim) / 2;

        fseek(f, meio*sizeof(Endereco), SEEK_SET);
        fread(&e, sizeof(Endereco), 1, f);

        if(strncmp(argv[1], e.cep, 8) == 0){
            printf("Achei na posicao %d\n", meio);
            printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            return 0;
        }
        else if (strncmp(argv[1], e.cep, 8) < 0){
            fim = meio - 1;
        }
        else {
            inicio = meio + 1;
        }
    }

    printf("cep nao encontrado");

	fclose(f);
}