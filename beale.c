#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include "lib_lista_chave.h"
#include "lib_lista_posicao.h"
#include "codifica.h"
#include "decodifica.h"

int arquivo_existe(char *arg){
    FILE *arquivo;

    if ((arquivo = fopen(arg, "r"))){
        printf("O arquivo %s já existe e não será editado\n", arg);
        if(arquivo != NULL)
            fclose(arquivo);
        return 1;
    }

    return 0;
}

FILE* abre_leitura_arquivo(char* arg){
    FILE* arquivo = fopen(arg, "r"); 
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo %s.\n", arg);
        exit(1);
    }

    return arquivo;
}

FILE* abre_escrita_arquivo(char* arg){
    FILE* arquivo = fopen(arg, "w"); 
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo %s \n", arg);
        exit(1);
    }

    return arquivo;
}

int main(int argc, char **argv){
    srand(time(NULL));
    int option, casoED;
    char *argB = NULL, *argM = NULL, *argO = NULL, *argC = NULL, *argI = NULL;
    FILE *LivroCifra = NULL, *MensagemOriginal = NULL, *ArquivoDeChaves = NULL, *MensagemDecodificada = NULL, *MensagemCodificada = NULL;
    lista_c_t *lista_chave;


    while ((option = getopt (argc, argv, "edb:m:o:c:i:")) != -1)
        switch (option){
            case 'e':
                casoED = 0;
                break;
            case 'd':
                casoED = 1;
                break;
            case 'b':
                argB = optarg;
                break;
            case 'm':
                argM = optarg;
                break;
            case 'o':
                argO = optarg;
                break;
            case 'c':
                argC = optarg;
                break;
            case 'i':
                argI = optarg;
                break;
            default:
                printf ("O argumento passado não é válido\n");
	            return (1);
      }   

    if(casoED == 0){
        if(arquivo_existe(argO) || arquivo_existe(argC))
            return 1;
        
        LivroCifra = abre_leitura_arquivo(argB);
        lista_chave = cria_lista_chave();

        valores_livro_cifra(lista_chave, LivroCifra);
        ArquivoDeChaves = abre_escrita_arquivo(argC);
        imprime_lista_chave_arq(lista_chave, ArquivoDeChaves);
        MensagemOriginal = abre_leitura_arquivo(argM);
        MensagemCodificada = abre_escrita_arquivo(argO);
        codifica_arquivo(lista_chave, MensagemOriginal, MensagemCodificada);

        fclose(LivroCifra);
        fclose(ArquivoDeChaves);
        fclose(MensagemOriginal);
        fclose(MensagemCodificada);
    }
    
    else{
        if(argC != NULL){
            if(arquivo_existe(argO))
                return 1;

            ArquivoDeChaves = abre_leitura_arquivo(argC);
            lista_chave = cria_lista_chave();

            valores_arquivo_chaves(lista_chave, ArquivoDeChaves);
            MensagemCodificada = abre_leitura_arquivo(argI);
            MensagemDecodificada = abre_escrita_arquivo(argO);
            decodifica_arquivo(lista_chave, MensagemCodificada, MensagemDecodificada);
        
            fclose(ArquivoDeChaves);
            fclose(MensagemDecodificada);
            fclose(MensagemCodificada);
        }

        else{
            if(arquivo_existe(argO))
                return 1;

            LivroCifra = abre_leitura_arquivo(argB);
            lista_chave = cria_lista_chave();
            
            valores_livro_cifra(lista_chave, LivroCifra);
            MensagemCodificada = abre_leitura_arquivo(argI);
            MensagemDecodificada = abre_escrita_arquivo(argO);
            decodifica_arquivo(lista_chave, MensagemCodificada, MensagemDecodificada);

            fclose(LivroCifra);
            fclose(MensagemCodificada);
            fclose(MensagemDecodificada);
        }
    }
    
    destroi_lista_chave(lista_chave);
    return 0; 
}  
