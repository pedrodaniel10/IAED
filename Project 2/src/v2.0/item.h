#ifndef ITEM_H
#define ITEM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define key(A) (A->palavra)
typedef char* Key;
#define less(A,B) (strcmp(A,B)<0)
#define equal(A,B) (strcmp(A,B)==0)
#define higher(A,B) (strcmp(A,B)>0)

typedef struct hashtag{
	char *palavra;
	int contador;
} hashtag;
typedef hashtag* Item;

Item novo_item();
int cmpitem(Item a, Item b);
int cmpqsort(const void *a, const void *b);
void eliminar_item(Item a);
void imprime_item(Item a);

#endif
