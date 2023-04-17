#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib_lista_chave.h"

//*  Cria uma lista vazia e a retorna, se falhar retorna NULL. */
lista_c_t *cria_lista_chave(){
    lista_c_t *l;
    if (!(l = malloc(sizeof(lista_c_t))))
        return NULL;
    
    l->ini = NULL;
    l->tamanho = 0;

    return l;
}

/*  Retorna o numero de chaves da lista. */
int tamanho_lista_chave(lista_c_t *l){
    return l->tamanho;
}

/*  Retorna 1 se a lista está vazia ou 0 caso contrário */
int vazia_lista_chave(lista_c_t *l){
    if (tamanho_lista_chave(l) == 0)
        return 1;

    return 0;
}

/*  Destrói uma lista vazia e a retorna, se falhar retorna NULL. */
lista_c_t *destroi_lista_chave(lista_c_t *l){
    nodo_lc_t* aux;
    aux = l->ini;

    if (vazia_lista_chave(l)){
        free(l->ini);
        free(l);
        return NULL;
    }
      
    while (aux->prox != NULL){
        aux = aux->prox;
        destroi_lista_pos(l->ini->lista_pos);
        free(l->ini);
        l->ini = aux;
    }
    destroi_lista_pos(l->ini->lista_pos);
    free(l->ini);
    free(l);

    return NULL;
}

/*  Verifica se a chave já existe na lista de chaves. */
int existe_chave(lista_c_t *l, char *chave){
    nodo_lc_t *aux;
    if(*chave >= 'A' && *chave <= 'Z'){
        *chave += 32;
    }
    
    aux = l->ini;
    while (aux != NULL){
        if (aux->chave == *chave)
            return 1;
        aux = aux->prox;
    }

    return 0;
}

/*  Insere a chave na lista.
    Retorna 1 se a operacao foi bem sucedida e 0 caso contrario. */
int insere_ini_lista_chave(lista_c_t *l, char chave, char *pos){
    nodo_lc_t *novo;

    if (vazia_lista_chave(l)){
        if (!(l->ini = malloc(sizeof(nodo_lc_t))))
            return 0;
        l->ini->chave = chave;
        l->ini->prox = NULL;
        l->ini->lista_pos = cria_lista_pos();
        insere_ordem_lista_pos(l->ini->lista_pos, pos);
        l->tamanho++;
    }

    else{
        if (existe_chave(l, &chave)){
            insere_ordem_lista_pos(l->ini->lista_pos, pos);
            return 0;
        }
        if (!(novo = malloc(sizeof(nodo_lc_t))))
            return 0;
        novo->prox = l->ini;
        l->ini = novo;
        l->ini->chave = chave;
        l->ini->lista_pos = cria_lista_pos();
        insere_ordem_lista_pos(l->ini->lista_pos, pos);
        l->tamanho++;
    }

    return 1;
}


/*  Insere a chave pela ordem.
    Retorna 1 se a chave foi adicionada e 0 caso contrario. */
int insere_ordem_lista_chave (lista_c_t *l, char chave, char *pos){
    nodo_lc_t *aux, *novo;
    
    if (chave < 0 || chave > 255)
        return 1;
       
    if (existe_chave(l, &chave)){
        aux = l->ini;
        while (aux != NULL){
            if (aux->chave == chave)
                insere_ordem_lista_pos(aux->lista_pos, pos);
            aux = aux->prox;
        }
        return 0;
    }

    if (vazia_lista_chave(l) || (l->ini->chave > chave)){
        insere_ini_lista_chave(l, chave, pos);
        return 1;
    } 

    if (!(novo = malloc(sizeof(nodo_lc_t))))
        return 0;
    
    aux = l->ini;

    while ((aux->prox != NULL) && (aux->prox->chave <= chave)){
        if (aux->chave <= chave)
        aux = aux->prox;
    }

    novo->chave = chave;
    novo->prox = aux->prox;
    aux->prox = novo;
    aux->prox->lista_pos = cria_lista_pos();
    insere_ordem_lista_pos(aux->prox->lista_pos, pos);
    l->tamanho++;

    return 1;
}

/* para depuracao */
void imprime_lista_chave_arq(lista_c_t *l, FILE *arq_destino_chaves){
    nodo_lc_t *aux;

    if (vazia_lista_chave(l)){
        printf("Lista vazia");
        return;
    }
    
    aux = l->ini;
    while (aux != NULL){
        fprintf(arq_destino_chaves, "%c: ", aux->chave);
        imprime_lista_pos_arq(aux->lista_pos, arq_destino_chaves);
        aux = aux->prox;
    }
}
