#ifndef decodifica
#define decodifica
#include "lib_lista_chave.h"

void decodifica_caractere(lista_c_t *l, char *chave_pos, char *c_decod);

void decodifica_arquivo(lista_c_t *l, FILE *mensagem_codificada, FILE *mensagem_decodificada);

#endif /* decodifica */
