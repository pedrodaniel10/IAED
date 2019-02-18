/*
 * 1) (Aritmética de ponteiros) Implemente duas versões da função strlen, uma em que utiliza índices e outra em que aplique aritmética de ponteiros.
 */

#include <stdio.h>

int strlen1(char s[]){
	int i,contador=0;
	
	for (i=0; s[i]!='\0';i++)
		contador++;
	return conador
}
/*outra versao, quadro*/
int strl1_1(char s[]){
	int l=0;
	
	while(s[l++]);
	return l;
}
/*Com ponteiros*/
int strlen2(char *s){
	int l=0;
	while (*s++)
		l++;
	return l;
}

/*Fazer strcpy*/
void strcpy1( char *d, char *o){
	while (*d++=*o++);  /*A atribuicao devolve sempre o valor da atribuicao, quando chegar ao \0, devolve \0, que e falso. */
}

int main()
{
	
	return 0;
}

