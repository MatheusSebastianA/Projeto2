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

/*  Destrói uma lista e retorna NULL. */
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

    if(*chave >= 'A' && *chave <= 'Z'){ /* Se for letra maíscula ela é transformada em minúscula  */
        *chave += 32;
    }
    
    aux = l->ini;
    while (aux != NULL){ /* laço para verificar todas as chaves da lista */
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

    if (vazia_lista_chave(l)){ /*Se a lista estiver vazia, será criado um nodo início que receberá a chave e será criada uma lista de posições para essa nodo*/
        if (!(l->ini = malloc(sizeof(nodo_lc_t))))
            return 0;
        l->ini->chave = chave;
        l->ini->prox = NULL;
        l->ini->lista_pos = cria_lista_pos();
        insere_ordem_lista_pos(l->ini->lista_pos, pos);
        l->tamanho++;
    }

    else{
        if (existe_chave(l, &chave)){ /*Se a lista não estiver vazia, será criado um novo nodo início que receberá a chave e será criada uma lista de posições para essa nodo e o próximo nodo será o antigo nodo inicio*/
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

    if (chave < 0 || chave > 127) /*Se a chave não estiver na tabela ASCII será ignorado*/
        return 0;

    if (existe_chave(l, &chave)){ /*Se a chave existir, será adicionado apenas a posição nova no nodo já existente*/
        aux = l->ini;
        while (aux != NULL){
            if (aux->chave == chave)
                insere_ordem_lista_pos(aux->lista_pos, pos);
            aux = aux->prox;
        }
        return 1;
    }

    if (vazia_lista_chave(l) || (l->ini->chave > chave)){ /*Se a lista estiver vazia ou o a chave do início representar um valor maior na tabela ASCII, a chave será inserida no início da lista*/
        insere_ini_lista_chave(l, chave, pos);
        return 1;
    } 

    if (!(novo = malloc(sizeof(nodo_lc_t))))
        return 0;
    
    aux = l->ini;

    while ((aux->prox != NULL) && (aux->prox->chave <= chave)){ /*Se entrar nesse looping, significa que não será adicionado no inicio, será adicionado uma posição antes de um nodo com chave maior */
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

/*  Imprime a lista de chaves em um arquivo dado, o tratamento de abertura do arquivo é feito por quem chama essa função */
void imprime_lista_chave_arq(lista_c_t *l, FILE *arquivo_chaves){
    nodo_lc_t *aux;

    if (vazia_lista_chave(l)){ /* Se a lista estiver vazia, não será impresso nada no arquivo e será impresso na tela "lista vazia" */
        printf("Lista vazia");
        return;
    }
    
    aux = l->ini;
    while (aux != NULL){ 
        fprintf(arquivo_chaves, "%c: ", aux->chave); /* será impresso a "chave":  */
        imprime_lista_pos_arq(aux->lista_pos, arquivo_chaves); /* será impresso a lista da chave atual e no final um \n */
        aux = aux->prox;
    }

    return;
}

/*  Lê os valores das chaves e suas posições a partir de um livro de cifras*/
void valores_livro_cifra(lista_c_t *l, FILE *livro_cifra){
    int cont_posicao = 0;
    char primeira_letra, *pos, *palavra;

    palavra = malloc(sizeof(char)*256);
    pos = malloc(sizeof(char)*256);

    while (fscanf (livro_cifra, "%s", palavra) !=  EOF){ /* pega próxima palavra até que seja EOF */
        primeira_letra = *palavra+0; /* pega a primeira letra da palavra  */
        sprintf(pos, "%d", cont_posicao); /* convete o valor da posição atual (inteiro) para uma string  */
        cont_posicao++;
        insere_ordem_lista_chave(l, primeira_letra, pos); /* insere em ordem o valor da chave e sua posição */
    }

    free(pos);
    free(palavra);

    return;
}

/*  Lê os valores das chaves e suas posições a partir de um arquivo de chaves*/
void valores_arquivo_chaves(lista_c_t *l, FILE *arquivo_chaves){
    char *letra_ponto, *pos, chave, teste;

    letra_ponto = malloc(sizeof(char)*3);
    pos = malloc(sizeof(char)*256);

    while (fscanf (arquivo_chaves, "%s", letra_ponto) !=  EOF){ /* enquanto tiverem palavras no arquivo entrará no seguinte laço*/
        chave = letra_ponto[0]; /* chave recebe o valor da primeira palavra que sempre será "chave": e atribui o primeiro valor para chave */
        teste = fgetc(arquivo_chaves); /* se o próximo valor valer '\n' é porque acabaram as posições dessa chave */
        while(teste != '\n'){
            fseek (arquivo_chaves, -1*(sizeof(char)), SEEK_CUR); /* volta uma posição já que o teste verifica a próxima palavra */
            fscanf(arquivo_chaves, "%s", pos); /* le o próximo valor que representa uma posição */
            insere_ordem_lista_chave(l, chave, pos); /* insere a chave a posição atual na lista de chaves */
            teste = fgetc(arquivo_chaves); /* insere a chave a posição atual na lista de chaves */
        }
    }

    free(letra_ponto);
    free(pos);
    
    return;
}
