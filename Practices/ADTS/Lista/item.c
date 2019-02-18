#include "item.h"
Item novo_item(){
	int *inteiro= malloc(sizeof(int));
	return inteiro;
}
	
int cmpitem(Item a, Item b){
	return (*a-*b);
}

void imprime_item(Item a){
	printf("%d ",*a);
}

void eliminar_item(Item a){
	free(a);
}
