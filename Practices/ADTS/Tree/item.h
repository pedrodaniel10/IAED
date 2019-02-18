#ifndef ITEM_H
#define ITEM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define key(A) (*A)
typedef int Key;
#define less(A,B) (A<B)
#define equal(A,B) (A==B)
#define higher(A,B) (A>B)

typedef int* Item;
int cmpitem(Item a, Item b);
void imprime_item(Item a);
Item novo_item();
void eliminar_item(Item a);

#endif
