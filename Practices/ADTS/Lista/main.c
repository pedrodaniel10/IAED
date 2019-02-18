#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "item.h"

int main(){
	char comando;
	Lista *list=nova_lista();
	Lista *list2=nova_lista();
	Elemento* el;
	int *num,aux,i;
	while (1){
		scanf("%c", &comando);
		
		switch (comando){
			case 'i':  //append fim
				num= novo_item();
				scanf("%d",num);
				append_fim(list,num);
				break;
			case 'a':  //auto teste
				for (i=0; i<5; i++){
					num= novo_item();
					*num=i;
					append_fim(list,num);
				}
				imprime_lista(list);
				printf("\n");
				for (i=5; i<10; i++){
					num= novo_item();
					*num=i;
					append_fim(list2,num);
				}
				imprime_lista(list2);
				printf("\n");
				list=concatena_listas(list,list2);
				imprime_lista(list);
				printf("\n");
				break;
			case 'e': //elimina
				 scanf("%d",&aux);
				 remover_elemento(aux,list);
				 break;
			case 'p': //append inicio
				num= novo_item();
				scanf("%d",num);
				append_inicio(list,num);
				break;
			case 'n': //#elementos
				aux=lenl(list);
				printf("%d\n",aux);
				break;
			case 'o': //elemento n
				scanf("%d",&aux);
				el=elemento(aux,list);
				imprime_item(el->item);
				break;
			case 'm': //mergesort
				list=merge_sort(list);
				break;
			case 's': //imprime arvore 
				imprime_lista(list);
				printf("\n");
				break;
			default:
				liberta_lista(list);
				liberta_lista(list2);
				return 0;
		}
		getchar();
		
	}
	
	return 0;
}

