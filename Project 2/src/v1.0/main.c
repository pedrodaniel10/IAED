/* Projeto 2 - IAED 2015/2016 2 Semestre
 * Hashtags
 * Francisco Pinheira 85333 - Grupo 81 - Taguspark
 * Pedro Lopes 83540 - Grupo 38 - Alameda
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
				printf("Erro, comando %c desconhecido!\n",comando);
				break;
		}
	}	
	return EXIT_FAILURE;
}

