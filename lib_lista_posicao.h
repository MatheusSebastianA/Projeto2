#ifndef lib_lista_posicao
#define lib_lista_posicao

/* Nodo que apresenta uma string e um ponteiro para o próximo nodo */
struct nodo_l_pos{
    char *pos;
    struct nodo_l_pos *prox;
};
typedef struct nodo_l_pos nodo_lp_t;

struct lista_pos{
    nodo_lp_t *ini;
    int tamanho; /* numero de string na lista */
};
typedef struct lista_pos lista_p_t;

lista_p_t *cria_lista_pos ();

int tamanho_lista_pos(lista_p_t *l);

int vazia_lista_pos(lista_p_t *l);

lista_p_t *destroi_lista_pos (lista_p_t *l);

void copia_pos(char *pos, char *pos_copia);

int insere_ini_lista_pos(lista_p_t *l, char *string);

int insere_ordem_lista_pos(lista_p_t *l, char *string);

void imprime_lista_pos_arq(lista_p_t *l, FILE *arq_destino_chaves);

#endif /* lib_lista_posicao */
