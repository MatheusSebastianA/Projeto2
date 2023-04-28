#ifndef lib_trata_arquivo
#define lib_trata_arquivo

int arquivo_existe(char *arg);

void quantidade_arquivo_passado(int qnt_arquivos[], char *argB,  char *argM, char *argO, char *argC, char *argI);

FILE* abre_leitura_arquivo(char* arg);

FILE* abre_escrita_arquivo(char* arg);

#endif /* lib_trata_arquivo */
