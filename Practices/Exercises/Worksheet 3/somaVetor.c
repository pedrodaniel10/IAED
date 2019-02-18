#include <stdio.h>

/*(Soma dos elementos de um vector) Escreva um programa que calcula a soma dos elementos de um vector de inteiros cujo tamanho é o 
valor especificado pela constante VECMAX. Implemente a função int somaVector(int v[], int n); e use a função void leVector (int v[], int n)
já implementada.*/

#define VECMAX 5
int somaVetor(int vetor[]);
void leVetor(int vetor[], int n);

int main(){
	int v[VECMAX];
	leVetor(v, VECMAX);
	printf("A soma e: %d\n", somaVetor(v));
	return 0;
}

int somaVetor(int vetor[]){
	int i, soma=0;
	for (i=0; i<VECMAX; i++){
		soma=soma + vetor[i];
	}
	return soma;
}

void leVetor(int vetor[], int n){
	int i;
	for (i=0; i<n; i++){
		scanf("%d", &vetor[i] );
	}
}