#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "item.h"

int main(){
	char comando;
	tree *arvore=nova_arvore();
	link h;
	int *num,aux;
	while (1){
		scanf("%c", &comando);
		
		switch (comando){
			case 'i':  //insere
				num= novo_item();
				scanf("%d",num);
				inserir_elemento(arvore,num);
				break;
			case 'e': //elimina
				 scanf("%d",&aux);
				 eliminar_elemento(arvore,aux);
				 break;
			case 'p': //procura
				scanf("%d",&aux);
				h=procura(arvore,aux); 
				if (h!=NULL) imprime_item(h->item);
				else printf("Nao encontrado\n");
				break;
			case 'h': //profundidade
				aux=profundidade(arvore);
				printf("%d",aux);
				break;
			case 'M': //max
				h=max(arvore);
				imprime_item(h->item);
				printf("\n");
				break;
			case 'm': //min
				h=min(arvore);
				imprime_item(h->item);
				break;
			case 'n': //#elementos
				aux=numero_elementos(arvore);
				printf("%d\n",aux);
				printf("\n");
				break;
			case 's': //imprime arvore 
				imprime_arvore(arvore);
				printf("\n");
				break;
			default:
				printf("Comando errado\n");
				return 0;
		}
		getchar();
		
	}
	
	return 0;
}

