#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

int codifica_caractere(lista_c_t *l, char c, char *c_cod){
    int cont, i, tam;
    nodo_lc_t *aux;
    nodo_lp_t *aux_ini_pos;
    aux = l->ini;
    tam = 0;
    
    if (c == ' '){
        c_cod[0] = '-';
        c_cod[1] = '1';
        c_cod[2] = '\0';
        return 1;
    }

    if (existe_chave(l, &c)){
        while (aux != NULL){
            if (aux->chave == c){
                cont = aux->lista_pos->tamanho;

                if(cont == 1){
                    aux_ini_pos = aux->lista_pos->ini;
                    tam = strlen(aux_ini_pos->pos);
                }

                if (cont > 1){
                    cont = rand() % cont;
                    aux_ini_pos = aux->lista_pos->ini;
                    for (i = 0; i < cont; i++){                   
                        if(aux_ini_pos->prox != NULL){
                            aux_ini_pos = aux_ini_pos->prox;
                        }
                    }
                }
                tam = strlen(aux_ini_pos->pos);

                if (tam == 1){
                    c_cod[0] = aux_ini_pos->pos[0];
                    c_cod[1] = '\0';
                }

                for (i = 0; i < tam; i++){
                    c_cod[i] = aux_ini_pos->pos[i];
                    c_cod[i+1] = '\0';
                }
                return 1;
            }
        aux = aux->prox;
        }
    }

    c_cod[0] = 'N';
    c_cod[1] = 'F';
    c_cod[2] = '\0';

    return 0;
}

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


int main(){
    srand(time(NULL));
    int cont_posicao;
    char *pos, *palavra, primeira_letra, c, *letra_cod, letra_decod, *num_pos;
    FILE *arq, *arq_frase, *arq_dst, *arq_decod;
    lista_c_t *lista_chave;

    lista_chave = cria_lista_chave();

    pos = malloc(sizeof(char)*256);
    palavra = malloc(sizeof(char)*256);
    letra_cod = malloc(sizeof(char)*15);
    num_pos = malloc(sizeof(char)*256);
    cont_posicao = 0;

    arq = fopen("livro_cifras.txt", "r");

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

    arq_frase = fopen("frase.txt", "r");
    
    if ( ! arq_frase ){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    
    arq_dst = fopen("frase_cod.txt", "w");

    if ( ! arq_dst ){
        printf("Erro ao abrir arquivo");
        return 0;
    }

    c = fgetc(arq_frase);
    while ( c != EOF){  
        if (c != '\n'){
            printf("Letra a ser cod %c\n", c);
            codifica_caractere(lista_chave, c, letra_cod);
            printf("Codificado fica %s\n", letra_cod);
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
