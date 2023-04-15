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
