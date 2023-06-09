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
#include "lib_trata_arquivo.h"

int main(int argc, char **argv){
    srand(time(NULL));
    int option, casoE = 0, casoD = 0, qnt_arquivos[5] = {0};
    char *argB = NULL, *argM = NULL, *argO = NULL, *argC = NULL, *argI = NULL;
    FILE *LivroCifra = NULL, *MensagemOriginal = NULL, *ArquivoDeChaves = NULL, *MensagemDecodificada = NULL, *MensagemCodificada = NULL;
    lista_c_t *lista_chave;


    while ((option = getopt (argc, argv, "edb:m:o:c:i:")) != -1)
        switch (option){
            case 'e':
                casoE += 1;
                break;
            case 'd':
                casoD += 1;
                break;
            case 'b':
                argB = optarg;
                qnt_arquivos[0] += 1;
                break;
            case 'm':
                argM = optarg;
                qnt_arquivos[1] += 1;
                break;
            case 'o':
                argO = optarg;
                qnt_arquivos[2] += 1;
                break;
            case 'c':
                argC = optarg;
                qnt_arquivos[3] += 1;
                break;
            case 'i':
                argI = optarg;
                qnt_arquivos[4] += 1;
                break;
            default:
                printf ("O argumento passado não é válido\n");
	            return (1);
      }   



    if(casoE + casoD != 1){ /* Verifica se foi passado mais de um -e ou -d*/
        printf("A quantidade de argumentos '-e' ou '-d' é inválida\n");
        return 1;
    }

    if(casoE == 1 && argB != NULL && argM != NULL && argO != NULL && argO != NULL){ /* Verifica se está no caso -e e se todos os argumentos necessários foram passados */
        quantidade_arquivo_passado(qnt_arquivos, argB, argM, argO, argC, argI);

        if((arquivo_nao_existe(argB) || arquivo_nao_existe(argM))) /* Verifica se não existe o arquivo de livro cifra ou da mensagem original, se não existir termina o programa */
            return 1;

        if((arquivo_existe(argC) || arquivo_existe(argO))) /* Verifica se já existe o arquivo de chaves ou de mensagem codificada, se sim termina o programa */
            return 1;

        LivroCifra = abre_leitura_arquivo(argB);
        MensagemOriginal = abre_leitura_arquivo(argM);
        MensagemCodificada = abre_escrita_arquivo(argO);
        ArquivoDeChaves = abre_escrita_arquivo(argC);

        lista_chave = cria_lista_chave();
        valores_livro_cifra(lista_chave, LivroCifra);
        codifica_arquivo(lista_chave, MensagemOriginal, MensagemCodificada);
        imprime_lista_chave_arq(lista_chave, ArquivoDeChaves);

        fclose(ArquivoDeChaves);
        fclose(LivroCifra);
        fclose(MensagemOriginal);
        fclose(MensagemCodificada);
    }
    
    else{
        if(casoD == 1 && argC != NULL && argI != NULL && argO != NULL){ /* Significa que está no caso -d e se todos os argumentos necessários para decodificar a partir de um arquivo de chaves foram passados */
            quantidade_arquivo_passado(qnt_arquivos, argB, argM, argO, argC, argI);   

            if((arquivo_nao_existe(argC) || arquivo_nao_existe(argI))) /* Verifica se não existe o arquivo de chaves ou da mensagem codificada, se não existir termina o programa */
                return 1;

            if(arquivo_existe(argO)) /* Verifica se já existe o arquivo de mensagem decodificada, se sim termina o programa */
                return 1;
            
            ArquivoDeChaves = abre_leitura_arquivo(argC);
            MensagemCodificada = abre_leitura_arquivo(argI);
            MensagemDecodificada = abre_escrita_arquivo(argO);

            lista_chave = cria_lista_chave();
            valores_arquivo_chaves(lista_chave, ArquivoDeChaves);
            decodifica_arquivo(lista_chave, MensagemCodificada, MensagemDecodificada);
        
            fclose(ArquivoDeChaves);
            fclose(MensagemDecodificada);
            fclose(MensagemCodificada);
        }

        else{ /* Significa que está no caso -d  */
            if(casoD == 1 && argB != NULL && argI != NULL && argO != NULL){ /* verifica se todos os argumentos necessários para decodificar a partir de um livro de cifra foram passados */
                quantidade_arquivo_passado(qnt_arquivos, argB, argM, argO, argC, argI); 

                if((arquivo_nao_existe(argB) || arquivo_nao_existe(argI))) /* Verifica se não existe o arquivo de livro cifra ou da mensagem codificada, se não existir termina o programa */
                    return 1;

                if(arquivo_existe(argO)) /* Verifica se já existe o arquivo de mensagem decodificada, se sim termina o programa */
                    return 1;

                LivroCifra = abre_leitura_arquivo(argB);
                MensagemCodificada = abre_leitura_arquivo(argI);
                MensagemDecodificada = abre_escrita_arquivo(argO);

                lista_chave = cria_lista_chave();
                valores_livro_cifra(lista_chave, LivroCifra);;
                decodifica_arquivo(lista_chave, MensagemCodificada, MensagemDecodificada);

                fclose(LivroCifra);
                fclose(MensagemCodificada);
                fclose(MensagemDecodificada);

            }

            else{
                printf("A quantidade de argumentos passados é inválida\n");
                return 0;
            }
        }

        
    }

    destroi_lista_chave(lista_chave);
    
    return 0; 
}  
