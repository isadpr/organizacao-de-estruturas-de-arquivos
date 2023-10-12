#include<stdio.h>
#include <string.h>

typedef  struct Registro Registro;

struct Registro {
    char cpf[15];
    char curso[20];
    char dataNacimento[11];
    char sexo;
    char email[40];
    char opcaoQuadro;
    };

int main (int argc, char** argv ) {
    FILE *entrada_a, *entrada_b, *saida;
    entrada_a = fopen("candidatos2021.dat","rb");
    entrada_b = fopen("candidatos2022.dat","rb");
    saida = fopen("saida.dat","wb");

    Registro ea, eb;

    //Lê o primeiro registro de cada arquivo
    fread(&ea, sizeof(Registro), 1, entrada_a );
    fread(&eb, sizeof(Registro), 1, entrada_b );

    while (!feof(entrada_a) && !feof(entrada_b)) {
        if(strncmp(ea.cpf, eb.cpf, 15) == 0){
            fwrite(&ea, sizeof(Registro), 1, saida);
            fread(&ea, sizeof(Registro), 1, entrada_a);
        }
        else {
            fwrite(&eb, sizeof(Registro), 1, saida);
            fread(&eb, sizeof(Registro), 1, entrada_b);
        }
    }

    while(!feof(entrada_a)){
        fwrite(&ea, sizeof(Registro), 1, saida);
        fread(&ea, sizeof(Registro), 1, entrada_a);
    }

    while(!feof(entrada_b)){
        fwrite(&ea, sizeof(Registro), 1, saida);
        fread(&ea, sizeof(Registro), 1, entrada_a);

    }

    fclose(entrada_a);
    fclose(entrada_b);
    fclose(saida);
    
}