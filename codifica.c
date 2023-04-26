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

    
    while (aux != NULL){
        if (aux->chave == c){ /* Se a chave atual for igual a chave procurada entra no laço e pega a quantidade de posições dessa chave */
            cont = aux->lista_pos->tamanho;

            if(cont == 1){ /* Se existir apenas uma posição que representa essa chave, aux_ini_pos recebe a primeira e unica posição dessa chave */
                aux_ini_pos = aux->lista_pos->ini;
                tam = strlen(aux_ini_pos->pos);
            }

            if (cont > 1){ /* Se existir mais de uma posição,será sorteado um valor entre 0 e a quantidade de posições */
                cont = rand() % cont;
                aux_ini_pos = aux->lista_pos->ini;
                for (i = 0; i < cont; i++){ /* Será acessado a posição na posição aleatoriamente sorteada */        
                    if(aux_ini_pos->prox != NULL){
                        aux_ini_pos = aux_ini_pos->prox;
                    }
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
