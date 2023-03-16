#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int v[] = {10, 20, 30, 40, 50, 60, 70};
    int inicio = 0;
    int fim = 6;
    int procurado = atoi(argv[1]); //atoi -> função que converte string em inteiro
    while(inicio<=fim){
        int meio = (inicio+fim)/2;
        if(procurado == v[meio]){
            printf("Achei na posicao %d\n", meio);
            return 0;
        }
        else if(procurado<v[meio]){
            fim = meio-1;
        }
        else {
            inicio = meio+1;
        }
    }
}