/* Projeto 2 - IAED 2015/2016 2 Semestre
 * Hashtags
 * Francisco Pinheira 85333 - Grupo 81 - Taguspark
 * Pedro Lopes 83540 - Grupo 38 - Alameda
 * 
 * Estrutura do Programa:
 * --> Hashtable, em que cada posicao tem um ponteiro para uma arvore. 
 * --> Existe um vetor que recebe os ponteiros das hashtags cada vez que
 * e adicionada uma.
 * --> E feito quicksort nesse vetor usando a funcao em stdlib.h qsort().
 * --> A memoria alocada dinamicamente e libertada pela funcao "void comando_x()".
 * 
 * Outras Observacoes:
 * --> As funcoes definidas em tree.c sao baseadas e adaptadas das aulas teoricas.
 * --> A funcao "unsigned long int hash(char *str)" foi retirada do website: 
 * http://www.cse.yorku.ca/~oz/hash.html
 * --> A funcao "void split(char *line)" foi retirada do enunciado.
 */
#include <stdio.h>
#include <stdlib.h>
#include "comandos.h"

int main(){
	char comando;
	while (1){
		fgets(mensagem, MAXLINESIZE+1, stdin);
		comando=mensagem[0];
		switch (comando){
			case 'a': 
				comando_a();
				break;
			case 's':  
				comando_s();
				break;
			case 'm':  
				comando_m();
				break;	
			case 'l':  
				comando_l();
				break;
			case 'x':  
				comando_x();
				return EXIT_SUCCESS;	
			default:
				printf("Erro, comando desconhecido!\n");
				break;
		}
	}	
	return EXIT_FAILURE;
}
