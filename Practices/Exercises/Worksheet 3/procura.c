#include <stdio.h>

/*(Procura elemento num vector) Escreva um programa que leia um vector de inteiros e um valor K. O programa deverá escrever no terminal 
a posição em que o valor K ocorre, ou -1 se K não ocorre no vector. Implemente a função int procura(int v[], int n, int k); */

#define VECMAX 5
void leVetor(int vetor[], int n);
int procura(int v[], int n, int k);

int main(){
	int vetor[VECMAX];
	leVetor(vetor, VECMAX);
	printf("Posicao: %d\n", procura(vetor, VECMAX, 2));
}

void leVetor(int vetor[], int n){
	int i;
	for (i=0; i<n; i++){
		scanf("%d", &vetor[i] );
	}
}

int procura(int v[], int n, int k){
	int i;
	for (i=0; i<n; i++){
		if (v[i]==k)
			return i;
	}
	return -1;
}
