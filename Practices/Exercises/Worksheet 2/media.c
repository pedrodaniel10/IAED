#include <stdio.h>

/*(Média) Escreva um programa que calcule o média de N números reais dados pelo utilizador usando a função float media (int N);
Sugestões: a) a leitura dos valores pode ser feita dentro da função "media"; b) Comece por perguntar ao utilizador quantos números vai introduzir.*/

float soma=0,num, media(int N);
int i,n,N;

int main(){
	scanf("%d", &n);
	printf("A media e: %.2f\n", media(n));
	return 0;
}

float media(int N){
	for (i=0; i<N; i++){
		scanf("%f", &num);
		soma=soma + num;
	}
	return soma/n;
}