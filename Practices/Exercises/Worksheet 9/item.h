#ifndef ITEM_H
#define ITEM_H
#include <stdio.h>
#include <string.h>
typedef char* Item;

#define newItem strdup
#define itemComparar strcmp
#define showItem(A) printf("%s\n",A)
#define deleteItem free
#endif
