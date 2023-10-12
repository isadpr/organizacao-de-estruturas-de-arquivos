#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 256

int main(int argc, char *argv[]) {
    FILE *entrada;
    if(argc != 2) {
fprintf(stderr,"Erro na chamada do comando.\n");
fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM].\n", argv[0]);
return 1;
}
    entrada = fopen(argv[1],"rb");
    if(!entrada) {
fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
return 1;
}

    int freq[MAX_CHAR] = {0};
    int c;

    while ((c = fgetc(entrada)) != EOF) {
        freq[c]++;
    }
    fclose(entrada);
    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i] > 0) {
            printf("caractere '%c' : %d\n", i, freq[i]);
        }
    }
    return 0;
} 
