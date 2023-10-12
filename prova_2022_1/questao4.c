#include <stdio.h>
#include <string.h>

typedef struct Registro Registro;

struct Registro {
    char cpf[15];
    char curso[20];
    char dataNacimento[11];
    char sexo;
    char email[40];
    char opcaoQuadro;
};

int main() {
    FILE *arquivo;
    Registro registro;
    char curso_atual[20] = "", curso_anterior[20] = "";
    int cont = 0;

    arquivo = fopen("candidatos.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fread(&registro, sizeof(Registro), 1, arquivo);
    strcpy(curso_atual, registro.curso);
    strcpy(curso_anterior, curso_atual);
    cont++;

    while (!feof(arquivo)) {
        if (strcmp(curso_atual, curso_anterior) != 0) {
            printf("Curso: %s, Inscrições: %d\n", curso_anterior, cont);
            strcpy(curso_anterior, curso_atual);
            cont = 0;
        }
        cont++;
        fread(&registro, sizeof(Registro), 1, arquivo);
        strcpy(curso_atual, registro.curso);
    }

    printf("Curso: %s, Inscrições: %d\n", curso_anterior, cont);

    fclose(arquivo);

    return 0;
}