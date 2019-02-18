#include "item.h"
Item novo_item(){
	hashtag *nova_hastag= malloc(sizeof(hashtag));
	return nova_hastag;
}
	
int cmpitem(Item a, Item b){
	return (a->contador)-(b->contador);
}

void imprime_item(Item a){
	printf("#%s %d\n",a->palavra,a->contador);
}

void eliminar_item(Item a){
	free(a->palavra);
	free(a);
}
