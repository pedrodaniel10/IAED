/*
 2) (Ponteiros) Altere a função desenvolvida no exercício anterior por forma a que esta não devolva o 
 * resultado da soma mas que o resultado da soma venha no primeiro argumento da função.
 */


#include <stdio.h>
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

void soma_complexo(complex *a, complex *b){
	(*a).real+=(*b).real;
	(*a).imag+=(*b).imag;
}

int main(){
	complex a,b;
	printf("Somar Complexos\na= ");
	a=le_complexo();		
	printf("b= ");
	b=le_complexo();
	soma_complexo(&a,&b);
	printf("%f + %fi\n",a.real,a.imag);
	return 0;
}

