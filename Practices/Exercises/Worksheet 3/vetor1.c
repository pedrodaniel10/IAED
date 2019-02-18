#include <stdio.h>

/*(Leitura e Escrita de Vectores) Escreva um programa que leia n (n< VECMAX) inteiros do teclado, e escreva depois no terminal os valores guardados. 
Implemente as funções void leVector (int v[], int n) e void escreveVector(int v[], int n). */

#define VECMAX 5

void leVetor(int vetor[], int n);
void escreveVetor(int vetor[], int n);

int main(){
	int v[VECMAX];
	leVetor(v, VECMAX);
	escreveVetor( v, VECMAX);
	return 0;
}

void leVetor(int vetor[], int n){
	int i;
	for (i=0; i<n; i++){
		scanf("%d", &vetor[i] );
	}
}

void escreveVetor(int vetor[], int n){
	int i;
	printf("Indice\tConteudo\n");
	for (i=0; i<n; i++){
		printf("%d\t%d\n",i,vetor[i]);
	}
}


		
