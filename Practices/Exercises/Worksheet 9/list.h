#ifndef LIST_H
#define LIST_H
#include "item.h"
typedef struct node *link;
struct node{
	Item item;
	link next;
}
#endif
