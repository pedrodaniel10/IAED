#include <stdio.h>

/*(Produto ou Soma) Escreva um programa que calcule o produto dos numeros inteiros pares e a soma dos 
numeros inteiros impares entre N1 e N2 (inclusive), dados pelo utilizador. */

int a,b,num,soma=0,produto=1;

int main(){
	scanf("%d%d", &a, &b);
	num=a;
	while (num<=b){
		if (num%2==0){
			produto=produto * num;
		}
		if (num%2!=0){
			soma = soma + num;
		}
		num++;
	}
	printf("O produto dos pares e: %d\nA soma dos impares e: %d\n", produto, soma);
	return 0;
}