#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib_lista_chave.h"
#include "lib_lista_posicao.h"
#include "codifica.h"
#include "decodifica.h"
#include <time.h>

int main(){
    srand(time(NULL));
    FILE *arq, *arq_frase, *arq_dst, *arq_decod, *arq_lista, *arq_chaves;
    lista_c_t *lista_chave;

    lista_chave = cria_lista_chave();

    
    if (!(arq = fopen("livro_cifras.txt", "r"))){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    valores_livro_cifra(lista_chave, arq);*/


    if (!(arq_chaves = fopen("arq_chaves.txt", "r"))){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    valores_arquivo_chaves(lista_chave, arq_chaves); 

    if (!(arq_decod = fopen("frase_deco.txt", "w"))){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    if (!(arq_lista = fopen("Chaves.txt", "w"))){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    imprime_lista_chave_arq(lista_chave, arq_lista);
    
    if (!(arq_frase = fopen("frase.txt", "r"))){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    if (!(arq_dst = fopen("frase_cod.txt", "w"))){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    codifica_arquivo(lista_chave, arq_frase, arq_dst);

    fclose(arq_dst);
    fclose(arq_decod);

    if (!(arq_decod = fopen("frase_deco.txt", "w"))){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    if (!(arq_dst = fopen("frase_cod.txt", "r")) ){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    decodifica_arquivo(lista_chave, arq_dst, arq_decod);
    

    fclose(arq); 
    fclose(arq_frase);
    fclose(arq_decod);
    fclose(arq_dst);
    fclose(arq_lista);
    destroi_lista_chave(lista_chave);
    return 0;
}  
