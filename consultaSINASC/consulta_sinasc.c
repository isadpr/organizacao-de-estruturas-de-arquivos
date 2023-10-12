#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 2048

struct DadosNascimento {
    int index;
    int CODMUNRES;
    char data_nasc[11];
    int PESO;
    int SEMAGESTAC;
    float adeq_peso_id_gestac;
    int SEXO;
    int IDANOMAL;
    int RACACOR;
    int ESCMAEAGR1;
    int ESTCIVMAE;
    int IDADEMAE;
    int CONSULTAS;
    int PARTO;
    int STTRABPART;
    int KOTELCHUCK;
    int APGAR5;
    int TPROBSON;
};

int separaData(char* data, int *ano)
{
    return atoi(strtok(data,"-"));
}

float totalPesoTeresina = 0;
float totalPesoCuritiba = 0;
int contadorTeresina = 0;
int contadorCuritiba = 0;
int anoAtual = 0;
int contPrematuros = 0;
int contPre =0;

int main()
{
   char *prox = NULL;
    static char buffer[MAX];
    struct DadosNascimento dn;
    char* linha[18];
    int i, ano;
    FILE *f = fopen("sinasc.csv","r");

    fgets(buffer,MAX,f);
    fgets(buffer,MAX,f);

    while(!feof(f)) {
        linha[0] = strtok_r(buffer,",\n",&prox);
        for(i=1; i<18; i++) {
            linha[i] = strtok_r(NULL,",\n",&prox);
            if(linha[i]==NULL) {
                linha[i]="";
            }
        }
        dn.index = atoi(linha[0]);
        dn.CODMUNRES = atoi(linha[1]);
        strcpy(dn.data_nasc,linha[2]);
        dn.PESO = atoi(linha[3]);
        dn.SEMAGESTAC = atoi(linha[4]);
        dn.adeq_peso_id_gestac = atof(linha[5]);
        dn.SEXO = atoi(linha[6]);
        dn.IDANOMAL = atoi(linha[7]);
        dn.RACACOR = atoi(linha[8]);
        dn.ESCMAEAGR1 = atoi(linha[9]);
        dn.ESTCIVMAE = atoi(linha[10]);
        dn.IDADEMAE = atoi(linha[11]);
        dn.CONSULTAS = atoi(linha[12]);
        dn.PARTO = atoi(linha[13]);
        dn.STTRABPART = atoi(linha[14]);
        dn.KOTELCHUCK = atoi(linha[15]);
        dn.APGAR5 = atoi(linha[16]);
        dn.TPROBSON = atoi(linha[17]);
        ano = separaData(dn.data_nasc, &ano);

        if(ano == 2015 && dn.CODMUNRES == 221100){
            totalPesoTeresina += dn.PESO;
            contadorTeresina++;
            //printf("CONTADOR TERESINA: %d", contadorTeresina);
        }

        if(ano == 2015 && dn.CODMUNRES == 410690){
            totalPesoCuritiba += dn.PESO;
            contadorCuritiba++;
            //printf("CONTADOR CURITIBA: %d", contadorCuritiba);    
        }

        
        if(dn.CODMUNRES == 330455 && dn.SEMAGESTAC <= 37){
            if (anoAtual != 0 && ano != anoAtual) {
                printf("Ano %d: %d prematuros\n", anoAtual, contPrematuros);  
                contPrematuros = 0;
            }
            contPrematuros ++;
            anoAtual = ano;
        }

        fgets(buffer,MAX,f);
    }

    // printar prematuros do ultimo ano
    if (anoAtual != 0) {
        printf("Ano %d: %d prematuros\n", anoAtual, contPrematuros);
    }


    float pesoMedioTeresina = 0;
    float pesoMedioCuritiba = 0;

    if (contadorTeresina > 0) {
        pesoMedioTeresina = totalPesoTeresina/contadorTeresina;
    }

    if (contadorCuritiba > 0) {
        pesoMedioCuritiba = totalPesoCuritiba/contadorCuritiba;
    }

    printf("Peso médio dos nascidos em 2015 em Teresina (221100): %.2f\n", pesoMedioTeresina);
    printf("Peso médio dos nascidos em 2015 em Curitiba (410690): %.2f\n", pesoMedioCuritiba);

    fclose(f);
    return 0;
}