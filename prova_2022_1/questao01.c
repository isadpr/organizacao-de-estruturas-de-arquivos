#include <stdio.h>
#include <stdlib.h>

int main (int agrc, char** argv) {
    FILE *entrada, *saida;
    int c;
    char c = "\n";

    if(argc != 3) {
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM]. \n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1], "rb");
    if(!entrada){
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }

    saida = fopen(argv[2], "wb");
    c = fgetc(entrada); // c vai olhar caracter por caracter
    while (c != EOF){
        if(c == n){
            fputc("\r", saida);
        }   
        fputc(c, saida);
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}


// int main(int argc, char** argv){
// 	FILE *entrada, *saida;
//     int c;
//     char n = '\n';

//     if(argc != 2)
// 	{
// 		fprintf(stderr,"Erro na chamada do comando.\n");
// 		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM].\n", argv[0]);
// 		return 1;
// 	}

//     entrada = fopen(argv[1],"rb");
//     if(!entrada)
// 	{
// 		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
// 		return 1;
// 	}

//     int cont = 1;
//     c = fgetc(entrada); // c vai olhar caracter por caracter
// 	while(c != EOF)
// 	{
// 		if(c == n){
//             cont++;
//         }
// 		c = fgetc(entrada);
// 	}

//     fclose(entrada);
//     printf("Número de linhas: %d\n", cont);
// 	return 0;
// }
