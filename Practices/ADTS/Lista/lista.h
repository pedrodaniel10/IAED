#ifndef LIST_H
#define LIST_H
#include "item.h"


typedef struct Elemento{
	Item item;
	struct Elemento *elemento_anterior;
	struct Elemento *elemento_seguinte;	
} Elemento;

typedef struct Lista{
	Elemento *cabeca;
	Elemento *cauda;	
} Lista;

Lista* nova_lista();
void append_inicio( Lista *l, Item x);
void append_fim( Lista *l, Item x);
void remover_elemento(int posicao,Lista *l);
Elemento* elemento(int posicao, Lista *l);
int lenl(Lista *l);
void liberta_lista(Lista *l);
Lista* concatena_listas(Lista *l1, Lista *l2);
void push_elemento(Lista *l1, Lista *l2);
void imprime_lista(Lista *l);
Elemento* ultimo_elemento(Lista *l);
Lista * partition(Lista *l);
Lista *merge_listas(Lista *a, Lista *b);
Lista* merge_sort(Lista *l);
#endif
