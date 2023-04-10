#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib_lista_posicao.h"

//*  Cria uma lista vazia e a retorna, se falhar retorna NULL. */
lista_p_t *cria_lista_pos(){
    lista_p_t *l;
    if (!(l = malloc(sizeof(lista_p_t))))
        return NULL;
    
    l->ini = NULL;
    l->tamanho = 0;

    return l;
}

/*  Retorna o numero de poss da lista. */
int tamanho_lista_pos(lista_p_t *l){
    return l->tamanho;
}

/*  Retorna 1 se a lista está vazia ou 0 caso contrário */
int vazia_lista_pos(lista_p_t *l){
    if (tamanho_lista_pos(l) == 0)
        return 1;

    return 0;
}

/*  Destrói uma lista vazia e a retorna, se falhar retorna NULL. */
lista_p_t *destroi_lista_pos(lista_p_t *l){
    nodo_lp_t* aux;
    aux = l->ini;

    if (vazia_lista_pos(l)){
        free(l->ini);
        free(l);
        return NULL;
    }
      
    while (aux->prox != NULL){
        aux = aux->prox;
        free(l->ini);
        l->ini = aux;
    }

    free(l->ini);
    free(l);

    return NULL;
}

/*  Copia o valor da posicao em um ponteiro dado. */
void copia_pos(char *pos, char *pos_copia){
    while (*pos != '\0'){
        *pos_copia = *pos;
        pos_copia++;
        pos++;
    }

    *pos_copia = '\0';

    return;
}

/*  Insere a pos na lista.
    Retorna 1 se a operacao foi bem sucedida e 0 caso contrario. */
int insere_ini_lista_pos(lista_p_t *l, char *pos){
    nodo_lp_t *novo;

    if (vazia_lista_pos(l)){
        if (!(l->ini = malloc(sizeof(nodo_lp_t))))
            return 0;
        if (!(novo = malloc(sizeof(nodo_lp_t))))
            return 0;
        if (!(novo->pos = malloc(sizeof(char)*strlen(pos))))
            return 0;
        copia_pos(pos, novo->pos);
        l->ini = novo;
        l->ini->prox = NULL;
        l->tamanho++;
    }

    else{
        if (!(novo = malloc(sizeof(nodo_lp_t))))
            return 0;
        if (!(novo->pos = malloc(sizeof(char)*strlen(pos))))
            return 0;
        novo->prox = l->ini;
        l->ini = novo;
        copia_pos(pos, l->ini->pos);
        l->tamanho++;
    }

    return 1;
}

/*  Insere a pos pela ordem.
    Retorna 1 se a pos foi adicionada e 0 caso contrario. */
int insere_ordem_lista_pos (lista_p_t *l, char *pos){
    nodo_lp_t *aux, *novo;

    if (vazia_lista_pos(l) || (atoi(l->ini->pos) <= atoi(pos))){
        insere_ini_lista_pos(l, pos);
        return 1;
    } 
    if (!(novo = malloc(sizeof(nodo_lp_t))))
        return 0;
    
    aux = l->ini;
    
    while ((aux->prox != NULL) && (atoi(aux->prox->pos) > atoi(pos)))    
        aux = aux->prox;
    

    novo->pos = malloc(sizeof(char)*strlen(pos));
    copia_pos(pos, novo->pos);
    novo->prox = aux->prox;
    aux->prox = novo;
    l->tamanho++;

    return 1;
}

/* para depuracao */
void imprime_lista_pos(lista_p_t *l){
    nodo_lp_t *aux;
    if (vazia_lista_pos(l)){
        printf("Lista vazia");
        return;
    }
    
    aux = l->ini;
    while (aux != NULL){
        if (aux->prox == NULL)
            printf("%s\n", aux->pos);
        else
            printf("%s ", aux->pos);
        aux = aux->prox;
    }
}