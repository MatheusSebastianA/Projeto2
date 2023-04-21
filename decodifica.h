#ifndef decodifica
#define decodifica
#include "lib_lista_chave.h"

/*
Função que verifica se existe alguma chave com aquela posição
retorna 1 se existe e 0 caso contrário
*/
int posicao_existe_lista_pos(lista_p_t *l_p, char *chave_pos);

/*
Função que faz a decodificação de uma chave passada para uma posição
Insere o caracter que representa o código decodificado funcionou ou "-" se não encontrou a posição em c_decod
*/
void decodifica_caractere(lista_c_t *l, char *chave_pos, char *c_decod);

/*
Função que faz a decodificação de um arquivo com uma mensagem codificada e insere em outro arquivo
*/
void decodifica_arquivo(lista_c_t *l, FILE *mensagem_codificada, FILE *mensagem_decodificada);

#endif /* decodifica */
