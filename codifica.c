#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib_lista_chave.h"

int codifica_caractere(lista_c_t *l, char c, char *c_cod){
    int cont, i;
    nodo_lc_t *aux;
    aux = l->ini;

    if (c == 32){
        c_cod[0] = '-';
        c_cod[1] = '1';
        c_cod[2] = '\0';
        return 1;
    }

    if (existe_chave(l, &c))
        while (aux != NULL){
        if (aux->chave == c){
            if (aux->lista_pos->tamanho > 1){
                cont = rand() % (aux->lista_pos->tamanho - 1);
                for (i = 0; i < cont; i++)
                    aux->lista_pos->ini = aux->lista_pos->ini->prox;
            }
            
            for (i = 0; i < strlen(aux->lista_pos->ini->pos); i++)
                c_cod[i] = aux->lista_pos->ini->pos[i];
            c_cod[i+1] = '\0';
            return 1;
        }
        aux = aux->prox;
    }

    return 0;
}
