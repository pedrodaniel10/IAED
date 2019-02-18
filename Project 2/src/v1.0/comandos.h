#ifndef COMANDOS_H
#define COMANDOS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
#include "lista.h"
#include "item.h"
#define MAXLINESIZE 145
#define NUMSEP 11
#define M 10000

//Variaveis locais e globais
static const char separators[] = {' ','\t',',',';','.','?','!','"','\n',':','\0'};
char mensagem[MAXLINESIZE+1];
tree* hashtable[M];
Lista* dados;
hashtag* mais_popular;
long int nr_hashtags;
long int nr_ocorrencias;
int ordenado;

//Comandos do programa
void comando_a();
void comando_s();
void comando_m();
void comando_l();
void comando_x();

//Funcoes auxiliares
unsigned long int hash(char *str);
hashtag* procura_hashtag(char *palavra);
hashtag* insere_hashtag(char *palavra);
void compara_atualiza_mais_popular(hashtag *hashtag_nova);
void processa_palavra(char* palavra);
void split(char *line);

#endif
