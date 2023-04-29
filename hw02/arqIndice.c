//nome: Isabele de Paula Rocha
//fiz o código trocando informações com João Terêncio e Bianca Gallicchio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;
typedef struct _Indice Indice;

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

struct _Indice {
    char cep[8]; // chave de busca
    int posicao; //corresponde à posição do registro onde o registro correspondente ao CEP da chave está armazenado
};

int compara(const void *e1, const void *e2)
{
    return strncmp(((Indice*)e1)->cep, ((Indice*)e2)->cep, 8); 
}

int busca_binaria(char** argv, Indice* indice_array, long qtd){
    FILE *f = fopen("cep.dat","rb");
    Endereco e;

    int inicio = 0;
    int fim = qtd - 1;

    while(inicio <= fim){
        int meio = (inicio + fim) / 2;

        fseek(f, indice_array[meio].posicao*sizeof(Endereco), SEEK_SET);
        fread(&e, sizeof(Endereco), 1, f);

        if(strncmp(argv[1], indice_array[meio].cep, 8) == 0){
            printf("Achei na posicao %d\n", meio);
            printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            fclose(f);
            return 0;
        }
        else if (strncmp(argv[1], indice_array[meio].cep, 8) < 0){
            fim = meio - 1;
        }
        else {
            inicio = meio + 1;
        }
    }

    printf("cep nao encontrado.\n");
    fclose(f);
    return 1;
} 

int main(int argc, char** argv)
{
    FILE *f_ceps = fopen("cep.dat", "rb");
    FILE *f_indices = fopen("indice.dat", "wb");
    Endereco endereco;
    Indice indice;
    long ultimo, qtd;

    if(argc != 2){
        fprintf(stderr, "USO: %s [CEP]", argv[0]);
        return 1;
    }

    int cont = 0; //contador para guardar o numero do registro atual

    while(fread(&endereco, sizeof(Endereco), 1, f_ceps) == 1){
        strcpy(indice.cep, endereco.cep); //copia strings. ([destino da copia], [origem da copia])
        indice.posicao = cont;
        fwrite(&indice, sizeof(Indice), 1, f_indices); //definir estrutura para arquivo indice
        cont++;
    }
    printf("O indice foi criado!\n");

    fclose(f_ceps);
    fclose(f_indices);

    f_indices = fopen("indice.dat", "rb");

    fseek(f_indices, 0, SEEK_END);
    ultimo = ftell(f_indices); //posicao do ultimo byte
    qtd = ultimo / sizeof(Indice); //quantidade total de registros no arquivo

    rewind(f_indices); //volta para o inicio do arquivo

    Indice* indice_array; //array de structs
    indice_array = (Indice*) malloc(qtd * sizeof(Indice)); // qtd * sizeof(Indice) = tamanho do array, ou seja, a quantidade de memoria q sera alocada
    fread(indice_array, sizeof(Indice), qtd, f_indices);

    qsort(indice_array, qtd, sizeof(Indice), compara);
    fclose(f_indices);

    f_indices = fopen("indice.dat", "wb");
    fwrite(indice_array, sizeof(Indice), qtd, f_indices);

    busca_binaria(argv, indice_array, qtd);

    free(indice_array);
    fclose(f_indices);

    return 0;
}