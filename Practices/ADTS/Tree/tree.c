/* Funcoes necessarias definir em item.h para funcionamento correto
 * -> typedef (Tipo) Item;
 * -> int cmpitem(Item item1, Item item2) - devolve 0 se iguais, menor que 0 
 * se item1<item2 e maior que zero se item1>item2
 */
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "item.h"
///////////////////////// Abstracao Maxima - Arvores /////////////////////////
/* Cria uma arvore vazia e devolve o ponteiro para esta */
tree* nova_arvore(){
	tree* arvore= malloc(sizeof(tree));
	arvore->raiz=NULL;
	return arvore;
}

/*Insere o elemento na arvore*/
void inserir_elemento(tree *arvore, Item elemento){
	link h = inserir_no(arvore->raiz, elemento);
	arvore->raiz=h;
}

/*Insere o elemento na arvore*/
void eliminar_elemento(tree *arvore, Key elemento){
	link h = eliminar_no(arvore->raiz, elemento);
	arvore->raiz=h;
}

/*Procura o elemento v na arvore*/
link procura(tree *arvore, Key v){
	return procura_no(arvore->raiz, v);
}

/*Profundidade da arvore*/
int profundidade(tree *arvore){
	return profundidade_no(arvore->raiz);
}

/*Devolve o no que contem o maior elemento da arvore*/
link max(tree *arvore){
	return max_no(arvore->raiz);
} 

/*Devolve o no que contem o menor elemento da arvore*/
link min(tree *arvore){
	return min_no(arvore->raiz);
}

/*Devolve o numero de elementos da arvore*/
int numero_elementos(tree *arvore){
	return numero_nos(arvore->raiz);
}

/*Destroi a arvore (liberta a memoria alocada))*/
void destroi_arvore(tree *arvore){
	arvore->raiz= liberta_no(arvore->raiz);
	free(arvore);
}

/*Imprime a arvore por niveis*/
void imprime_arvore(tree *arvore){
	int h = profundidade(arvore);
	int i;
    for (i=1; i<=h; i++){
        imprime_nivel(arvore->raiz, i);
        printf("\n");
	}
}




////////////////////// Funcoes auxiliares para arvores ///////////////////////
/* Cria um noh de acordo com os parametros e devolve o ponteiro para este */
link novo_no(Item dados, link esquerda, link direita){
	link noh= malloc( sizeof(no) );
	noh->item=dados;
	noh->esquerda=esquerda;
	noh->direita=direita;
	noh->profundidade=1;
	return noh;	
}

/* Procura o no que contem o elemento v */
link procura_no(link noh, Key v){
	if (noh==NULL)
		return NULL;
	if ( equal(key(noh->item), v) ) /*Se forem iguais*/
		return noh;
	if ( less(key(noh->item), v)<0 ) /*Se noh.item for menor que v*/
		return procura_no(noh->esquerda, v);
	else
		return procura_no(noh->direita, v);
}

/*Devolve o no com maior elemento partindo do no h*/
link max_no(link h) { 
	if (h==NULL || h->direita==NULL) 
		return h; 
	else 
		return max_no(h->direita); 
} 

/*Devolve o no com maior elemento partindo do no h*/
link min_no(link h) { 
	if (h==NULL || h->esquerda==NULL) 
		return h; 
	else 
		return min_no(h->esquerda); 
} 

/*Devolve o numero de nos de h para baixo + h*/
int numero_nos(link h){
	if (h==NULL)
		return 0;
	else
		return 1 + numero_nos(h->esquerda) + numero_nos(h->direita);
}

/*Devolve a profundidade do noh h*/
int profundidade_no(link h){	
	if (h==NULL)
		return 0;
	return h->profundidade;
}

/*Rotacao simples para a esquerda*/
link rodar_E(link h){
	int prof_esq, prof_dir;
	link x = h->direita;
	h->direita=x->esquerda;
	x->esquerda=h;
	
	prof_esq= profundidade_no(h->esquerda);
	prof_dir= profundidade_no(h->direita);
	h->profundidade= (prof_esq > prof_dir) ? prof_esq + 1 : prof_dir + 1;
	
	prof_esq= profundidade_no(h->esquerda);
	prof_dir= profundidade_no(x->direita);
	x->profundidade= (prof_esq > prof_dir) ? prof_esq + 1 : prof_dir + 1;	
	return x;
}

/*Rotacao simples para a direita*/
link rodar_D(link h){
	int prof_esq, prof_dir;
	link x = h->esquerda;
	h->esquerda=x->direita;
	x->direita=h;
	
	prof_esq= profundidade_no(h->esquerda);
	prof_dir= profundidade_no(h->direita);
	h->profundidade= (prof_esq > prof_dir) ? prof_esq + 1 : prof_dir + 1;
	
	prof_esq= profundidade_no(h->esquerda);
	prof_dir= profundidade_no(x->direita);
	x->profundidade= (prof_esq > prof_dir) ? prof_esq + 1 : prof_dir + 1;	
	return x;
}

/*Rotacao dupla esquerda direita*/
link rodar_ED(link h){
	if (h==NULL)
		return h;
	h->esquerda=rodar_E(h->esquerda);
	return rodar_D(h);
}

/*Rotacao dupla esquerda direita*/
link rodar_DE(link h){
	if (h==NULL)
		return h;
	h->direita=rodar_D(h->direita);
	return rodar_E(h);
}

/*Balance factor*/
int balance(link h){
	if (h==NULL)
		return 0;
	return profundidade_no(h->esquerda)-profundidade_no(h->direita);
}

/*Balanceia a arvore cuja raiz e h*/
link AVLbalance(link h){
	int balanceFactor;
	if (h==NULL)
		return h;
	balanceFactor= balance(h);
	if (balanceFactor > 1){
		if (balance(h->esquerda)>=0)
			h=rodar_D(h);
		else
			h=rodar_ED(h);
	}
	else if (balanceFactor < -1){
		if (balance(h->direita) <= 0)
			h=rodar_E(h);
		else
			h=rodar_DE(h);
	}
	else{
		int prof_esq=profundidade_no(h->esquerda);
		int prof_dir=profundidade_no(h->direita);
		h->profundidade= (prof_esq > prof_dir) ? prof_esq + 1 : prof_dir + 1;
	}
	return h;
}

/*Insere um no com o elemento item na arvore cuja raiz e h*/
link inserir_no(link h, Item item){
	if (h==NULL)
		return novo_no(item, NULL, NULL);
	if (cmpitem(item, h->item) < 0)
		h->esquerda= inserir_no(h->esquerda,item);
	else
		h->direita= inserir_no(h->direita,item);
	h=AVLbalance(h);
	return h;
}

/*Elimina o noh que contem o elemento k*/
link eliminar_no(link h, Key k){
	if (h==NULL)
		return h;
	else if (less(k, key(h->item)))
		h->esquerda=eliminar_no(h->esquerda,k);
	else if (less(key(h->item), k))
		h->direita=eliminar_no(h->direita,k);
	else{
		if(h->esquerda!=NULL && h->direita!=NULL){
			link aux= max_no(h->esquerda);
			{Item x; x=h->item; h->item=aux->item; aux->item=x;}
			h->esquerda=eliminar_no(h->esquerda, key(aux->item));
		}
		else{
			 link aux=h;
			 if(h->esquerda==NULL && h->direita==NULL)
				h=NULL;
			else if (h->esquerda==NULL)
				h=h->direita;
			else 
				h=h->esquerda;
			eliminar_item(aux->item);
			free(aux);
		}		
	}
	h=AVLbalance(h);
	return h;
}

/*Liberta o no (liberta memoria alocada de um no)*/
link liberta_no(link h){
	if (h==NULL)
		return h;
	h->esquerda= liberta_no(h->esquerda);
	h->direita= liberta_no(h->direita);
	return eliminar_no(h, key(h->item));
}

/*Imprime um nivel de uma arvore de raiz h*/
void imprime_nivel(link h, int nivel){
    if (h == NULL){
		printf("NULL ");
        return;
	}
    if (nivel == 1)
        imprime_item(h->item);
    else if (nivel > 1){
        imprime_nivel(h->esquerda, nivel-1);
        imprime_nivel(h->direita, nivel-1);
    }
}


