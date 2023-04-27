#include <stdlib.h>
#include <stdio.h>

int arquivo_existe(char *arg){
    FILE *arquivo;

    if ((arquivo = fopen(arg, "r"))){
        printf("O arquivo %s já existe e não será editado\n", arg);
        if(arquivo != NULL)
            fclose(arquivo);
        return 1;
    }

    return 0;
}

FILE* abre_leitura_arquivo(char* arg){
    FILE* arquivo = fopen(arg, "r"); 
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo %s\n", arg);
        exit(1);
    }

    return arquivo;
}

FILE* abre_escrita_arquivo(char* arg){
    FILE* arquivo = fopen(arg, "w"); 
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo %s\n", arg);
        exit(1);
    }

    return arquivo;
}
