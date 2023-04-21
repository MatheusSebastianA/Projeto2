#ifndef lib_lista_chave
#define lib_lista_chave

#include "lib_lista_posicao.h"

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

lista_c_t *cria_lista_chave ();

int tamanho_lista_chave(lista_c_t *l);

int vazia_lista_chave(lista_c_t *l);

lista_c_t *destroi_lista_chave (lista_c_t *l);

void copia_chave(char chave, char chave_copia);

int existe_chave(lista_c_t *l, char *chave);

int insere_ini_lista_chave(lista_c_t *l, char chave, char *pos);

int insere_ordem_lista_chave (lista_c_t *l, char chave, char *pos);

void imprime_lista_chave_arq(lista_c_t *l, FILE *arquivo_chaves);

void valores_livro_cifra(lista_c_t *l, FILE *livro_cifra);

void valores_arquivo_chaves(lista_c_t *l, FILE *arquivo_chaves);

#endif /* lib_lista_chave */
