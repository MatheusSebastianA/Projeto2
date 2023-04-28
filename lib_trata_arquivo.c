#include <stdlib.h>
#include <stdio.h>

/*  Verifica se o arquivo existe, se existir retorna uma mensagem de erro falando que não poderá ser editado.
    Retorna 1 se existe, 0 se não existe */
int arquivo_existe(char *arg){
    FILE *arquivo;

    if ((arquivo = fopen(arg, "r"))){
        printf("O arquivo %s já existe e o programa não será executado\n", arg);
        if(arquivo != NULL)
            fclose(arquivo);
        return 1;
    }

    return 0;
}

/*  Verifica se a quantidade de argumentos iguais é maior que 2
    Se for >= 2 significa que passaram 2 argumentos válidos iguais e será considerado o último */
void quantidade_arquivo_passado(int qnt_arquivos[], char *argB,  char *argM, char *argO, char *argC, char *argI){
    if(qnt_arquivos[0] >= 2)
        printf("Foi passado mais de um arquivo válido para -b, o arquivo escolhido será o %s\n", argB);
    
    if(qnt_arquivos[1] >= 2)
       printf("Foi passado mais de um arquivo válido para -m, o arquivo escolhido será o %s\n", argM);
    
    if(qnt_arquivos[2] >= 2)
        printf("Foi passado mais de um arquivo válido para -o, o arquivo escolhido será o %s\n", argO);  

    if(qnt_arquivos[3] >= 2)
        printf("Foi passado mais de um arquivo válido para -c, o arquivo escolhido será o %s\n", argC);  

    if(qnt_arquivos[4] >= 2)
        printf("Foi passado mais de um arquivo válido para -i, o arquivo escolhido será o %s\n", argI);   

    return; 
}

/*  Verifica se o arquivo foi passado e se foi possível abri-lo em forma de leitura
    Se o arquivo não pode ser aberto o programa é encerrado*/
FILE* abre_leitura_arquivo(char* arg){
    FILE* arquivo = fopen(arg, "r"); 
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo %s\n", arg);
        exit(1);
    }

    return arquivo;
}

/*  Verifica se o arquivo foi passado e se foi possível abri-lo em forma de escrita
    Se o arquivo não pode ser aberto o programa é encerrado*/
FILE* abre_escrita_arquivo(char* arg){
    FILE* arquivo = fopen(arg, "w"); 
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo %s\n", arg);
        exit(1);
    }

    return arquivo;
}
