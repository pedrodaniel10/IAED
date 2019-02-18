/*
 * 8. (Manipulação de Strings: Leitura e Escrita de Linhas de Texto) Escreva uma programa que lê caracteres do teclado, 
 * caracter a caracter, até encontrar o caracter '\n' e escreve a linha lida no terminal. Implemente a função 
 * int leLinha(char s[]) que lê a linha para a string s e devolve o número de caracteres lidos
 */

#include <stdio.h>
#include <string.h>

int leLinha(char s[]);
int main(){
	char vetor[100];
	leLinha(vetor);
	return 0;
}

int leLinha(char s[]){
	int i=0,c,contador=1;
	c=getchar();
	s[i]=c;
	printf("%c",s[i++]);
	while (c!='\n'){
		c=getchar();
		s[i]=c;
		printf("%c",s[i]);
		contador++;
		i++;
	}
	printf("%c",s[i]);
	return contador;
}

