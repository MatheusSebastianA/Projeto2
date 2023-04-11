#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Nodo que apresenta uma string e um ponteiro para o próximo nodo */
struct nodo_l_pos {
    char *pos;
    struct nodo_l_pos *prox;
};
typedef struct nodo_l_pos nodo_lp_t;

struct lista_pos {
    nodo_lp_t *ini;
    int tamanho; /* numero de string na lista */
};
typedef struct lista_pos lista_p_t;

/* Nodo que apresenta uma chave, um ponteiro para o próximo nodo e uma lista de valores com as posições */
struct nodo_l_chave {
    char chave;
    struct nodo_l_chave *prox;
    lista_p_t *lista_pos;
};
typedef struct nodo_l_chave nodo_lc_t;

struct lista_chave {
    nodo_lc_t *ini;
    int tamanho; /* numero de caracteres na lista de chaves*/
};
typedef struct lista_chave lista_c_t;

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
lista_p_t *destroi_lista_pos (lista_p_t *l){
    nodo_lp_t* aux;
    aux = l->ini;

    if (vazia_lista_pos(l)){
        free(l->ini->pos);
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
        if (!(l->ini->pos = malloc(sizeof(char)*10)))
            return 0;  
        
        copia_pos(pos, l->ini->pos);
        l->ini->prox = NULL;
        l->tamanho++;
    }

    else{
        if (!(novo = malloc(sizeof(nodo_lp_t))))
            return 0;
        if (!(novo->pos = malloc(sizeof(char)*10)))
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
    

    novo->pos = malloc(sizeof(char)*10);
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
void imprime_lista_chave(lista_c_t *l){
    nodo_lc_t *aux;
    if (vazia_lista_chave(l)){
        printf("Lista vazia");
        return;
    }
    
    aux = l->ini;
    while (aux != NULL){
        printf("%c: ", aux->chave);
        imprime_lista_pos(aux->lista_pos);
        aux = aux->prox;
    }
}

int main(){

    int cont_posicao;
    char *pos, *palavra, primeira_letra;
    FILE *arq;
    lista_c_t *lista_chave;

    lista_chave = cria_lista_chave();

    pos = malloc(sizeof(char)*256);
    palavra = malloc(sizeof(char)*256);
    cont_posicao = 0;

    arq = fopen("numeros.txt", "r");

    if ( ! arq ){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    while (fscanf (arq, "%s", palavra) !=  EOF){
        primeira_letra = *palavra+0;
        sprintf(pos, "%d", cont_posicao);
        cont_posicao++;
        insere_ordem_lista_chave(lista_chave, primeira_letra, pos);
    }
    
    imprime_lista_chave(lista_chave);
    fclose(arq);

    destroi_lista_chave(lista_chave);
    free(pos);
    free(palavra);
    return 0;
}  
