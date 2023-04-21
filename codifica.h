#ifndef codifica
#define codifica
#include "lib_lista_chave.h"

/*Função que faz a codificação de uma chave passada para uma posição*/

int codifica_caractere(lista_c_t *l, char c, char *c_cod);  

void codifica_arquivo(lista_c_t *l, FILE *mensagem_original, FILE *mensagem_codificada);

#endif /* codifica */
