#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodifica.h"

/*  Decodifica uma chave passada para uma posição
    Insere o caracter que representa o código decodificado se funcionou ou "-" se não encontrou a posição em c_decod*/
void decodifica_caractere(lista_c_t *l, char *chave_pos, char *c_decod){
    nodo_lc_t *aux_chave;

    if (chave_pos[0] == '-' && chave_pos[1] == '1'){ /* Se for encontrado -1 retorna ' '*/
        *c_decod = ' ';
        return;
    }

    if (chave_pos[0] == '-' && chave_pos[1] == '2'){ /* Se for encontrado -2 retorna '\n' */
        *c_decod = '\n';
        return;
    }
    
    if (chave_pos[0] == '-' && chave_pos[1] == '3'){ /* Se for encontrado -3 retorna '-' para representar que o caractere não existe*/
        *c_decod = '-';
        return;
    }
    
    aux_chave = l->ini;

    while(aux_chave != NULL){ /*Laço que passa por todas as chaves*/
        if (posicao_existe_lista_pos(aux_chave->lista_pos, chave_pos)){ /* Para cada lista de posições dessa chave, chama uma função para verificar se existe alguma posição que representa o código procurado*/ 
            *c_decod = aux_chave->chave;
            return;
        }
        aux_chave = aux_chave->prox;
    }

    *c_decod = '-'; /* Se não for encontrado retorna '-' para representar que o caractere não existe*/
    
    return;
}

/*  Decodifica um arquivo com uma mensagem codificada e insere em outro arquivo a mensagem codificada.
    Quem chamou a função deve abrir e fechar o arquivo. */
void decodifica_arquivo(lista_c_t *l, FILE *mensagem_codificada, FILE *mensagem_decodificada){
    char *num_pos, letra_decod;

    if(!(num_pos = malloc(sizeof(char)*256)))
        return;

    while(fscanf(mensagem_codificada, "%s", num_pos) != EOF){ /* Enquanto tiver uma palavra, será decodificado a string lida do arquivo */
        decodifica_caractere(l, num_pos, &letra_decod); 
        fprintf(mensagem_decodificada, "%c", letra_decod); /* Insere valor decodificado no arquivo de mensagem decodificada */
    }

    free(num_pos);

    return;
}
