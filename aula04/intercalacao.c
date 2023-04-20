/*Feito por João Terêncio e Isabele Rocha*/

#include<stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct  _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int main(int args, char **argv){
    FILE  *fa, *fb, *fc;
    fa = fopen("cep_a.dat","rb");
    fb = fopen("cep_b.dat","rb");
    fc = fopen("saida.dat","wb");

    Endereco ea, eb;

    fread(&ea, sizeof(Endereco), 1, fa);
    fread(&ea, sizeof(Endereco), 1, fb);

    while(!feof(fa) && !feof(fb)){
        if(strncmp(ea.cep, eb.cep, 8)<0){
            fwrite(&ea, sizeof(Endereco), 1, fc);
            fread(&ea, sizeof(Endereco), 1, fa);
        }
        else {
            fwrite(&eb, sizeof(Endereco), 1, fc);
            fread(&eb, sizeof(Endereco), 1, fb);
        }
    }

    while(!feof(fa)){
        fwrite(&ea, sizeof(Endereco), 1, fc);
        fread(&ea, sizeof(Endereco), 1, fa);
    }

        while(!feof(fb)){
        fwrite(&ea, sizeof(Endereco), 1, fc);
        fread(&ea, sizeof(Endereco), 1, fa);
    }

    fclose(fa);
    fclose(fb);
    fclose(fc);
}
