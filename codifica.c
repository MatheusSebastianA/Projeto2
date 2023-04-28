#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "codifica.h"

/*  Codifica carectere por caractere.
    Espaço = -1
    \n = -2
    caracter não encontrado = -3 */
int codifica_caractere(lista_c_t *l, char c, char *c_cod){
    int cont, i, tam;
    nodo_lc_t *aux;
    nodo_lp_t *aux_ini_pos;
    aux = l->ini;
    tam = 0;
    
    if (c == ' '){ /* Se for 'espaço' a codificação é -1 */
        c_cod[0] = '-';
        c_cod[1] = '1';
        c_cod[2] = '\0';
        return 1;
    }

    if (c == '\n'){ /* Se for '\n' a codificação é -2 */
        c_cod[0] = '-';
        c_cod[1] = '2';
        c_cod[2] = '\0';
        return 1;
    }

    if(c >= 'A' && c <= 'Z') /* Se for letra maíscula ela é transformada em minúscula  */
        c += 32;
    
    while (aux != NULL){
        if (aux->chave == c){ /* Se a chave atual for igual a chave procurada entra no laço e pega a quantidade de posições dessa chave */
            cont = aux->lista_pos->tamanho;

            if(cont == 1){ /* Se existir apenas uma posição que representa essa chave, aux_ini_pos recebe a primeira e unica posição dessa chave */
                aux_ini_pos = aux->lista_pos->ini;
                tam = strlen(aux_ini_pos->pos);
            }

            if (cont > 1){ /* Se existir mais de uma posição,será sorteado um valor entre 0 e a quantidade de posições */
                cont = rand() % (cont-1);
                aux_ini_pos = aux->lista_pos->ini;
                for (i = 0; i < cont; i++){ /* Será acessado a posição na posição aleatoriamente sorteada */        
                    aux_ini_pos = aux_ini_pos->prox;
                }
            }
            tam = strlen(aux_ini_pos->pos);

            if (tam == 1){ /* verifica se o tamahno da string é igual a um, se for insere manualmente o primeiro caracter e um \0 no segundo */ 
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

    /* Se não for encontrado nenhuma caractere = -3 */
    c_cod[0] = '-';
    c_cod[1] = '3';
    c_cod[2] = '\0';

    return 0;
}

/*  Codifica o arquivo inteiro com a mensagem original e escreve ela codificada em um arquivo de mensagem codificada.
    Quem chamou a função deve abrir e fechar o arquivo */
void codifica_arquivo(lista_c_t *l, FILE *mensagem_original, FILE *mensagem_codificada){
    char *letra_cod, c;

    letra_cod = malloc(sizeof(char)*16);

    c = fgetc(mensagem_original); /* pega primeiro caracter do arquivo com a mensagem original*/ 
    while ( c != EOF){  /* enquanto o caractere não for EOF entra no laço */
        codifica_caractere(l, c, letra_cod); /* codifica o caractere atual */
        fprintf(mensagem_codificada, "%s ", letra_cod); /* insere o valor codificado no arquivo de mensagem codificada */
        
        c = fgetc(mensagem_original); /* pega próximo caracter do arquivo */
    
    }

    free(letra_cod);

    return;
}
