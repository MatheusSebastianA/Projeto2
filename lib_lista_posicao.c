#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib_lista_posicao.h"

/*  Cria uma lista vazia de posições e a retorna, se falhar retorna NULL. */
lista_p_t *cria_lista_pos(){
    lista_p_t *l;
    if (!(l = malloc(sizeof(lista_p_t))))
        return NULL;
    
    l->ini = NULL;
    l->tamanho = 0;

    return l;
}

/*  Retorna o numero de posições da lista de posições. */
int tamanho_lista_pos(lista_p_t *l){
    return l->tamanho;
}

/*  Retorna 1 se a lista de posições está vazia ou 0 caso contrário */
int vazia_lista_pos(lista_p_t *l){
    if (tamanho_lista_pos(l) == 0)
        return 1;

    return 0;
}

/*  Destrói uma lista de posições e retorna NULL. */
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
        free(l->ini->pos);
        free(l->ini);
        l->ini = aux;
    }

    free(l->ini->pos);
    free(l->ini);
    free(l);

    return NULL;
}

/*  Função que verifica se existe alguma chave com aquela posição.
    Retorna 1 se existe e 0 caso contrário */
int posicao_existe_lista_pos(lista_p_t *l_p, char *chave_pos){
    nodo_lp_t *aux;

    aux = l_p->ini;

    while (aux != NULL){
        if(atoi(aux->pos) == atoi(chave_pos))
            return 1;
        aux = aux->prox;
    }

    return 0;
}

/*  Copia o valor da posicao em um ponteiro dado. */
void copia_pos(char *pos, char *pos_copia){
    int i, tam;

    tam = strlen(pos);

    for (i = 0; i < tam; i++)
        pos_copia[i] = pos[i];

    pos_copia[i] = '\0';

    return;
}

/*  Insere a posição no inicio da lista de posições.
    Retorna 1 se a operacao foi bem sucedida e 0 caso contrario. */
int insere_ini_lista_pos(lista_p_t *l, char *pos){
    nodo_lp_t *novo;

    if (vazia_lista_pos(l)){
        if (!(l->ini = malloc(sizeof(nodo_lp_t))))
            return 0;
        if (!(l->ini->pos = malloc(sizeof(char)*strlen(pos)+1)))
            return 0;
        copia_pos(pos, l->ini->pos);
        l->ini->prox = NULL;
        l->tamanho++;
    }

    else{
        novo = l->ini;
        if (!(l->ini = malloc(sizeof(nodo_lp_t))))
            return 0;
        if (!(l->ini->pos = malloc(sizeof(char)*strlen(pos)+1)))
            return 0;
        copia_pos(pos, l->ini->pos);
        l->ini->prox = novo;
        l->tamanho++;
    }

    return 1;
}

/*  Insere a posição em ordem decrescente.
    Retorna 1 se a posição foi adicionada e 0 caso contrário. */
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
    

    novo->pos = malloc(sizeof(char)*strlen(pos)+1);
    copia_pos(pos, novo->pos);
    novo->prox = aux->prox;
    aux->prox = novo;
    l->tamanho++;

    return 1;
}

/*  Insere a lista de posições em ordem decrescente em um arquivo de destino.
    Os valores são inseridos em ordem decrescente */
void imprime_lista_pos_arq(lista_p_t *l, FILE *arq_destino_chaves){
    nodo_lp_t *aux;

    if (vazia_lista_pos(l)){
        printf("Lista vazia");
        return;
    }
    
    aux = l->ini;
    while (aux != NULL){
        if (aux->prox == NULL)
            fprintf(arq_destino_chaves, "%s\n", aux->pos);
        else
            fprintf(arq_destino_chaves, "%s ", aux->pos);
        aux = aux->prox;
    }
}
