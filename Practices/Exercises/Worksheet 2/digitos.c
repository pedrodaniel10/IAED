#include <stdio.h>

/*(Digitos) Escreva um programa que  pede ao utilizador um valor positivo N. O seu programa deverá voltar a pedir um valor para N 
caso o utilizador introduza um valor inválido. No output, deverá mostrar o número de dígitos que compõem N,assim como a soma dos dígitos
de N. Por exemplo, o número 12345 tem 5 dígitos e a soma desses dígitos é 15.  */

int n=0, soma=0, digito, numero=0, x;

int main(){
	while (n<=0){
		printf("Escreva um inteiro positivo: ");
		scanf("%d", &x);
		n=x;
	}
	while (n!=0){
		digito= n%10;
		soma= soma + digito;
		numero++;
		n=n/10;
	}
	printf("O numero %d tem %d digitos e a sua soma e %d\n",x,numero,soma);
}