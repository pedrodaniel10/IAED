#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include "item.h"

typedef struct no* link;
typedef struct no {
	Item item;
	link esquerda, direita;
	int profundidade;
	} no; 
	
typedef struct tree{
	link raiz;
	} tree;

//Abstracao Maxima - Arvores	
tree* nova_arvore();
void inserir_elemento(tree *arvore, Item elemento);
void eliminar_elemento(tree *arvore, Key elemento);
link procura(tree *arvore, Key v);
int profundidade(tree *arvore);
link max(tree *arvore);
link min(tree *arvore);
int numero_elementos(tree *arvore);
void destroi_arvore(tree *arvore);
void imprime_arvore(tree *arvore);

//Funcoes Auxiliares
link novo_no(Item dados, link esquerda, link direita);
link procura_no(link noh, Key v);
link max_no(link h);
link min_no(link h);
int numero_nos(link h);
int profundidade_no(link h);
link rodar_E(link h);
link rodar_D(link h);
link rodar_ED(link h);
link rodar_DE(link h);
int balance(link h);
link AVLbalance(link h);
link inserir_no(link h, Item item);
link eliminar_no(link h, Key k);
link liberta_no(link h);
void imprime_nivel(link h, int nivel);

#endif
