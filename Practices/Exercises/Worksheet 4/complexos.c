/*
 * 2. (Leitura Formatada) Números complexos são identificados pela sua parte real e imaginária. 
 * Faça um programa que lê dois números complexos (um de cada vez) no formato x+yi (ex: 5+3i). 
 * 
 * 3. (Estruturas) Implemente uma função complexo soma(complexo a, complexo b) que recebe dois 
 * números complexos como argumento e devolva a soma dos dois. 
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

complex soma_complexo(complex a, complex b){
	a.real+=b.real;
	a.imag+=b.imag;
	return a;
}

int main(){
	complex a,b,c;
	printf("Somar Complexos\na= ");
	a=le_complexo();		
	printf("b= ");
	b=le_complexo();
	c=soma_complexo(a,b);
	printf("%f + %fi\n",c.real,c.imag);
	return 0;
}

