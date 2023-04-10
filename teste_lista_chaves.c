#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Nodo que apresenta uma chave, um ponteiro para o próximo nodo e uma lista de valores com as posições */
struct nodo_l_chave {
    char *chave;
    struct nodo_l_chave *prox;
};
typedef struct nodo_l_chave nodo_lc_t;

struct lista_chave {
    nodo_lc_t *ini;
    int tamanho; /* numero de caracteres na lista de chaves*/
};
typedef struct lista_chave lista_c_t;

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
lista_c_t *destroi_lista (lista_c_t *l){
    nodo_lc_t* aux;
    aux = l->ini;

    if (vazia_lista_chave(l)){
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

/*  Copia o valor da chave em um ponteiro dado. */
void copia_chave(char *chave, char *chave_copia){
    while (*chave != '\0'){
        *chave_copia = *chave;
        chave_copia++;
        chave++;
    }

    *chave_copia = '\0';

    return;
}

/*  Verifica se a chave já existe na lista de chaves. */
int existe_chave(lista_c_t *l, char *chave){
    nodo_lc_t *aux;
    if(*chave >= 'A' && *chave <= 'Z'){
        *chave += 32;
    }
    
    aux = l->ini;
    while (aux != NULL){
        if (*aux->chave == *chave)
            return 1;
        aux = aux->prox;
    }

    return 0;
}

/*  Insere a chave na lista.
    Retorna 1 se a operacao foi bem sucedida e 0 caso contrario. */
int insere_ini_lista_chave(lista_c_t *l, char *chave){
    nodo_lc_t *novo;

    if (vazia_lista_chave(l)){
        if (!(l->ini = malloc(sizeof(nodo_lc_t))))
            return 0;
        if (!(novo = malloc(sizeof(nodo_lc_t))))
            return 0;
        if (!(novo->chave = malloc(sizeof(char)*strlen(chave))))
            return 0;
        copia_chave(chave, novo->chave);
        l->ini = novo;
        l->ini->prox = NULL;
        l->tamanho++;
    }

    else{
        if (existe_chave(l, chave))
            return 0;
        if (!(novo = malloc(sizeof(nodo_lc_t))))
            return 0;
        if (!(novo->chave = malloc(sizeof(char)*strlen(chave))))
            return 0;
        novo->prox = l->ini;
        l->ini = novo;
        copia_chave(chave, l->ini->chave);
        l->tamanho++;
    }

    return 1;
}


/*  Insere a chave pela ordem.
    Retorna 1 se a chave foi adicionada e 0 caso contrario. */
int insere_ordem_lista_chave (lista_c_t *l, char *chave){
    nodo_lc_t *aux, *novo;

    if (existe_chave(l, chave)){
        return 0;
    }

    if (vazia_lista_chave(l) || (*(l->ini->chave) > *chave)){
        insere_ini_lista_chave(l, chave);
        return 1;
    } 

    if (!(novo = malloc(sizeof(nodo_lc_t))))
        return 0;
    
    aux = l->ini;

    while ((aux->prox != NULL) && (*(aux->prox->chave) <= *chave)){
        if (*aux->chave <= *chave)
        aux = aux->prox;
    }

    novo->prox = aux->prox;
    aux->prox = novo;
    novo->chave = malloc(sizeof(char)*strlen(chave));
    copia_chave(chave, novo->chave);
    l->tamanho++;

    return 1;
}

/* para depuracao */
void imprime_lista_chave(lista_c_t *l){
    nodo_lc_t *aux;
    if (vazia_lista_chave(l)){
        printf("Lista vazia");
        return;
    }
    
    aux = l->ini;
    while (aux != NULL){
        printf("%s: ", aux->chave);
        aux = aux->prox;
    }
}

int main(){
    char *valor;
    lista_c_t *lista_chave;
    lista_chave = cria_lista_chave();
    
    valor = malloc(sizeof(char)*1000);

    for(int i = 0; i < 5; i++){
        scanf("%s", valor);
        insere_ordem_lista_chave(lista_chave, valor);
        printf("Imprimindo a lista_chave: ");
        imprime_lista_chave(lista_chave);
        printf("\n");
    }


    return 0;
}  
