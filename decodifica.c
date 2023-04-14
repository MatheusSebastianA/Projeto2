#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodifica.h"

int posicao_existe_lista_pos(lista_p_t *l_p, char *chave_pos){
    int i, igual, tam;
    nodo_lp_t *aux;

    aux = l_p->ini;

    while (aux != NULL){
        tam = strlen(chave_pos);
        igual = 0;

        if (tam == strlen(aux->pos)){
            for(i = 0; i < tam; i++){
                if(chave_pos[i] == aux->pos[i])
                    igual++;
            }
            if(igual == tam){
                return 1;
            }
        }
       aux = aux->prox;
    }

    return 0;
}

void decodifica_caractere(lista_c_t *l, char *chave_pos, char *c_decod){
    nodo_lc_t *aux_chave;

    if (chave_pos[0] == '-' && chave_pos[1] == '1'){
        *c_decod = ' ';
        return;
    }
    
    aux_chave = l->ini;

    while(aux_chave != NULL){ /*Laço que passa por todas as chaves*/
        if (posicao_existe_lista_pos(aux_chave->lista_pos, chave_pos)){ /*Para cada lista de posições dessa chave, chama uma função para verificar se existe alguma posição que representa o código procurado*/ 
            *c_decod = aux_chave->chave;
            return;
        }
        aux_chave = aux_chave->prox;
    }

    *c_decod = '-'; /*Caso não tenha sido encontrado a posição é retornado "-" para representar "Not Found"*/

    return;
}