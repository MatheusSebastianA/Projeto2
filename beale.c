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
    int cont_posicao;
    char *pos, *palavra, primeira_letra, c, *letra_cod, letra_decod, *num_pos, nome_arq[100];
    FILE *arq, *arq_frase, *arq_dst, *arq_decod, *arq_lista;
    lista_c_t *lista_chave;

    lista_chave = cria_lista_chave();

    pos = malloc(sizeof(char)*256);
    palavra = malloc(sizeof(char)*256);
    letra_cod = malloc(sizeof(char)*15);
    num_pos = malloc(sizeof(char)*256);
    cont_posicao = 0;


    if (!(arq =fopen("livro_cifras.txt", "r"))){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    while (fscanf (arq, "%s", palavra) !=  EOF){
        primeira_letra = *palavra+0;
        sprintf(pos, "%d", cont_posicao);
        cont_posicao++;
        insere_ordem_lista_chave(lista_chave, primeira_letra, pos);
    }

    if (!(arq_decod = fopen("frase_deco.txt", "w"))){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    printf("Digita um nome ae irmao: ");
    scanf("%s", nome_arq);

    if (!(arq_lista = fopen(nome_arq, "w"))){
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

    c = fgetc(arq_frase);
    while ( c != EOF){  
        if (c != '\n'){
            codifica_caractere(lista_chave, c, letra_cod);
            fprintf(arq_dst, "%s ", letra_cod);
        }
        c = fgetc(arq_frase);
    }

    fclose(arq_dst);

    if (!(arq_decod = fopen("frase_deco.txt", "w"))){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    if (!(arq_dst = fopen("frase_cod.txt", "r")) ){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    while(fscanf(arq_dst, "%s", num_pos) != EOF){
        decodifica_caractere(lista_chave, num_pos, &letra_decod);
        fprintf(arq_decod, "%c", letra_decod);
    }

    
    fclose(arq_frase);
    fclose(arq);
    fclose(arq_decod);
    fclose(arq_dst);
    destroi_lista_chave(lista_chave);
    free(letra_cod);
    free(pos);
    free(palavra);
    free(num_pos);
    return 0;
}  
