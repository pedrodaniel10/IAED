#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "item.h"

///////////////////// Abstracao Maxima - Listas ////////////////////////
Lista* nova_lista(){
	Lista *l= malloc( sizeof(Lista) );
	l->cabeca=NULL;
	l->cauda=NULL;
	return l;
}
int lista_vazia(Lista *l){
	return (l->cabeca==NULL && l->cauda==NULL);
}
void append_inicio( Lista *l, Item x){
	Elemento *el= malloc( sizeof(Elemento));
	Elemento *cabeca=l->cabeca;
	if (lista_vazia(l)){
		l->cabeca=el;
		l->cauda=el;
		el->item=x;
		el->elemento_anterior=NULL;
		el->elemento_seguinte=NULL;		 
	}
	else{
		el->elemento_anterior=NULL;
		el->elemento_seguinte=l->cabeca;
		el->item=x;
		cabeca->elemento_anterior=el;
		
				
		l->cabeca=el;
	}
}

void append_fim( Lista *l, Item x){
	Elemento *el= malloc( sizeof(Elemento));
	Elemento *cauda=l->cauda;
	if (lista_vazia(l)){
		l->cabeca=el;
		l->cauda=el;
		el->item=x;
		el->elemento_anterior=NULL;
		el->elemento_seguinte=NULL; 
	}	
	else{
		el->elemento_seguinte=NULL;
		el->elemento_anterior=l->cauda;
		el->item=x; 
		cauda->elemento_seguinte=el;
		
		l->cauda=el;
	}
}

Elemento* elemento(int posicao, Lista *l){
	int i;
	Elemento *res=l->cabeca;
	for (i=0; (i-posicao)!=0; i++){
		if (res->elemento_seguinte==NULL)
			return NULL;
		else
			res=res->elemento_seguinte;
	}
	return res;
}

Elemento* ultimo_elemento(Lista *l){
	Elemento *aux=l->cabeca, *el=NULL;
	for (; aux!= NULL; aux=aux->elemento_seguinte)
		el=aux;
	return el;
}

void remover_elemento(int posicao,Lista *l){
	Elemento *remover= elemento(posicao,l);
	Elemento *anterior=remover->elemento_anterior, *proximo=remover->elemento_seguinte;
	Elemento *cauda;
	
	anterior->elemento_seguinte= remover->elemento_seguinte;
	proximo->elemento_anterior= remover->elemento_anterior;
	
	eliminar_item(remover->item);
	free(remover);
	
	cauda= ultimo_elemento(l);
	l->cauda=cauda;	
}

int lenl(Lista *l){
	if (l==NULL)
		return 0;
	int i=0;
	Elemento *el=l->cabeca;
	while(el!=NULL){
		i++;
		el=el->elemento_seguinte;		
	}
	return i;
}

/*Liberta uma lista (Mas nao o conteudo)*/
void liberta_lista(Lista *l){
	if (lista_vazia(l))
		free(l);
	else{
		Elemento *el, *aux;
		for (el=l->cabeca, aux=(l->cabeca)->elemento_seguinte; aux!=NULL; el=aux, aux=aux->elemento_seguinte)
			free(el);	
		free(l->cauda); //liberta ultimo elemento 
		free(l);
	}
}

/*Recebe duas listas e devolve a lista que resulta da concatenacao l1|l2*/
Lista* concatena_listas(Lista *l1, Lista *l2){
	if (lista_vazia(l1)){
		liberta_lista(l1);
		return l2;
	}
	else if (lista_vazia(l2)){
		 liberta_lista(l2);
		 return l1;
	}
	else{
		(l1->cauda)->elemento_seguinte= l2->cabeca;
		(l2->cabeca)->elemento_anterior= l1->cauda;
		l1->cauda=l2->cauda;
		l2->cabeca=NULL;
		l2->cauda=NULL;
		liberta_lista(l2);
		return l1;
	}
}

/* Recebe duas listas e puxa o primeiro elemento de l2 para a posicao
 * final de l1*/
void push_elemento(Lista *l1, Lista *l2){
	if (lista_vazia(l2))
		return;
	else if (lista_vazia(l1) && l2->cabeca==l2->cauda){
		l1->cabeca=l2->cabeca;
		l1->cauda=l2->cauda;
		l2->cabeca=NULL;
		l2->cauda=NULL;		 
	}
	else if (lista_vazia(l1)){
		 l1->cabeca=l2->cabeca;
		 l1->cauda=l2->cabeca;
		 l2->cabeca=(l2->cabeca)->elemento_seguinte;
		 (l2->cabeca)->elemento_anterior=NULL;
		 (l1->cabeca)->elemento_anterior=NULL;
		 (l1->cabeca)->elemento_seguinte=NULL;
	}
	else if (l2->cabeca == l2->cauda){ // tem um elemento
		(l1->cauda)->elemento_seguinte=l2->cabeca;
		(l2->cabeca)->elemento_anterior=l1->cauda;
		l1->cauda=l2->cabeca;
		(l1->cauda)->elemento_seguinte=NULL;
		l2->cabeca= NULL;
		l2->cauda= NULL;
	}
	else{
		(l1->cauda)->elemento_seguinte=l2->cabeca;
		(l2->cabeca)->elemento_anterior= l1->cauda;
		l1->cauda= l2->cabeca;
		l2->cabeca= (l2->cabeca)->elemento_seguinte;
		(l1->cauda)->elemento_seguinte=NULL;
		(l2->cabeca)->elemento_anterior=NULL;
	}
}                                

void imprime_lista(Lista *l){
	Elemento *el;
	
	for (el= l->cabeca;el!=NULL; el=el->elemento_seguinte)
		imprime_item(el->item);
}
///////////////////// Funcoes Auxiliares - Listas ////////////////////////
/* Pega na lista l, cria uma lista l2 sendo que metade dos elementos de l
* fica em l e a outra metade fica em l2, devolvendo o ponteiro para lista
* l2. Se l nao tiver elementos ou tiver 1, devolve o ponteiro para uma
* lista vazia.*/
Lista * partition(Lista *l){
	 Lista *l2= nova_lista();
	 Elemento *head= l->cabeca;
	 Elemento *slow, *fast;
	 
	if (head==NULL || head->elemento_seguinte==NULL)
		return l2;
		
	else{
		slow=head;  //no fim do ciclo while slow vai apontar para o elemento do meio da lista
		fast=head->elemento_seguinte; //fast vai percorrer o vetor 2x mais rapido que slow
		while(fast!=NULL){
			fast=fast->elemento_seguinte;
			if (fast!=NULL){
				 slow=slow->elemento_seguinte;
				 fast=fast->elemento_seguinte;
			}
		}
		/*Agora slow aponta para a posicao intermediaria de l.
		 *Mudar os ponteiros desse elemento e do elemento seguinte para criar uma outra lista*/
		 Elemento *slow_mais_1 = slow->elemento_seguinte;
		slow_mais_1->elemento_anterior=NULL;
		slow->elemento_seguinte=NULL;
		l2->cabeca= slow_mais_1;
		l2->cauda= l->cauda;
		l->cauda= slow;
		return l2;
	}
}

Lista *merge_listas(Lista *a, Lista *b){
	Lista *mergedlist= nova_lista();
	if (lista_vazia(a)){
		liberta_lista(a);
		mergedlist=concatena_listas(mergedlist,b);
		return mergedlist;
	}
	if (lista_vazia(b)){
		liberta_lista(b);
		mergedlist=concatena_listas(mergedlist,a);
		return mergedlist;
	}
	while (!lista_vazia(a) && !lista_vazia(b)){
		Elemento *primeiroA= a->cabeca;
		Elemento *primeiroB= b->cabeca;
		if (cmpitem(primeiroA->item, primeiroB->item)>0)
			push_elemento(mergedlist,a);
		else if ((cmpitem(primeiroA->item, primeiroB->item)==0)){
			if (less(key(primeiroA->item), key(primeiroB->item)))
				push_elemento(mergedlist, a);
			else  if (equal(key(primeiroA->item), key(primeiroB->item)))
				push_elemento(mergedlist,a);
			else
				push_elemento(mergedlist,b);
		}
		else
			push_elemento(mergedlist,b);		
	}
	if (lista_vazia(a)){
		liberta_lista(a);
		mergedlist=concatena_listas(mergedlist,b);
		return mergedlist;
	}
	else{
		liberta_lista(b);
		mergedlist=concatena_listas(mergedlist,a);
		return mergedlist;
	}
}

Lista* merge_sort(Lista *l){
	if (l->cabeca==l->cauda || lista_vazia(l))
		return l;
	Lista *l2;
	l2=partition(l);
	l=merge_sort(l);
	l2=merge_sort(l2);
	l=merge_listas(l,l2);
	return l;	
} 
	


























