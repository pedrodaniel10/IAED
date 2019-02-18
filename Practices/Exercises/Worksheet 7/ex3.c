/*
 * 3) (Ponteiros) Altere a função desenvolvida no exercício anterior por forma a que a função devolva um ponteiro para um número complexo que tem o resultado da soma.
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct Complexo{
	float real,imag;
	} complex;

complex le_complexo() {
    complex c;
    char sinal;
    
    scanf("%f%c%fi", &c.real, &sinal, &c.imag);
 
    if (sinal == '-')
        c.imag *= -1;

    return c;
}

complex* soma_complexo(complex *a, complex *b){
	complex *r= malloc( sizeof(complex) );
	(*r).real=(*a).real+(*b).real;
	(*r).imag+=(*a).imag+(*b).imag;
	return r;
}

int main(){
	complex a,b, *c;
	printf("Somar Complexos\na= ");
	a=le_complexo();		
	printf("b= ");
	b=le_complexo();
	c=soma_complexo(&a,&b);
	printf("%f + %fi\n",(*c).real,(*c).imag);
	return 0;
}
