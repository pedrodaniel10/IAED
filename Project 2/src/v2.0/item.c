#include "item.h"

//Cria um novo item do tipo Item
Item novo_item(){
	hashtag *nova_hastag= malloc(sizeof(hashtag));
	return nova_hastag;
}

//Compara dois Item 	
int cmpitem(Item a, Item b){
	return (a->contador)-(b->contador);
}

//Funcao de comparacao para o qsort()
int cmpqsort(const void *ptra, const void *ptrb){
	Item a=*(Item*)ptra, b=*(Item*)ptrb;
	if (cmpitem(a,b)>0)	//se a for maior retorna negativa de forma a ficar descendente
		return -1;
	else if (cmpitem(a,b)==0){
		if (less(key(a),key(b)))
			return -1;
		else
			return 1;
	}
	else
		return 1;
}

//Imprime um item.
void imprime_item(Item a){
	printf("#%s %d\n",a->palavra,a->contador);
}

//Elimina um item.
void eliminar_item(Item a){
	free(a->palavra);
	free(a);
}
