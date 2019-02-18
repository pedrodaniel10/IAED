/*
 * (Vectores) Escreva em linguagem C um programa que pede ao utilizador uma sequência de valores inteiros. 
 * O programa começa por pedir ao utilizador para definir o tamanho da sequência a introduzir. 
 * Supondo que n é o tamanho da sequência, o programa deverá ler do standard input n inteiros. 
 * No final, mostra todos os inteiros positivos que compõem a sequência
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int *ler_vetor(int n){
	int * v=NULL;
	v= malloc(n * sizeof(int));
	memset(v, 0x00, n*sizeof(int));
	while (n--)
		scanf("%d", &v[n]);
	return v;
}

int main(){
	int n, *v;
	printf("Quantos numeros quer introduzir ?\n");
	scanf("%d", &n);
	v=ler_vetor(n);	
	return 0;
}

