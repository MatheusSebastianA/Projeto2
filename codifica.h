#ifndef codifica
#define codifica
#include "lib_lista_chave.h"

int codifica_caractere(lista_c_t *l, char c, char *c_cod);  

void codifica_arquivo(lista_c_t *l, FILE *mensagem_original, FILE *mensagem_codificada);

#endif /* codifica */
