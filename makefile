# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c99  # flags de compilacao

CC = gcc

# arquivos-objeto
	objects = beale.o lib_lista_chave.o  lib_lista_posicao.o codifica.o decodifica.o lib_trata_arquivo.o
     
beale: beale.o lib_lista_chave.o  lib_lista_posicao.o codifica.o decodifica.o lib_trata_arquivo.o 
	$(CC) -o beale beale.o lib_lista_chave.o  lib_lista_posicao.o codifica.o decodifica.o lib_trata_arquivo.o

lib_trata_arquivo.o: lib_trata_arquivo.c
	$(CC) -c $(CFLAGS) lib_trata_arquivo.c

lib_lista_chave.o: lib_lista_chave.c
	$(CC) -c $(CFLAGS) lib_lista_chave.c

lib_lista_posicao.o: lib_lista_posicao.c
	$(CC) -c $(CFLAGS)  lib_lista_posicao.c

codifica.o: codifica.c
	$(CC) -c $(CFLAGS) codifica.c

decodifica.o: decodifica.c
	$(CC) -c $(CFLAGS) decodifica.c

beale.o: beale.c
	$(CC) -c $(CFLAGS) beale.c

clean:
	rm -f $(objects) 

purge:
	rm *.o beale
