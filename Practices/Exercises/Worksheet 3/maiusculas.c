/*
 * 9. (Manipulação de Strings: Maiusculas) Escreva um programa que lê uma linha do terminal (use a função do exercício anterior) 
 * e que escreve no terminal o mesmo texto, mas com as letras minusculas substituidas pelas respectivas maiusculas. 
 * Implemente a função void maiusculas(char s[]); Nota: a string é alterada pela função maiusculas. 
 */


#include <stdio.h>
int leLinha(char s[]);
void maiusculas(char s[]);
int main(){
	char vetor[100];
	leLinha(vetor);
	maiusculas(vetor);
	return 0;
}

void maiusculas(char s[]){
	int i=0;
	while (s[i]!='\n'){
		if (s[i]>='a' && s[i]<='z')
			s[i]=s[i]-32;
		printf("%c",s[i]);
		i++;
	}
	printf("\n");
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

