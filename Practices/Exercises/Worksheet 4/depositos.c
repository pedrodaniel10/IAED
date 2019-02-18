/*
 * 5. (Estruturas) Escreva um programa que lê um depósito do utilizador e que calcula o valor bruto 
 * e liquido dos juros do depósito após um ano. Considere que o valor bruto dos juros é o produto do 
 * valor depositado pela TAN, e que o valor liquido dos juros é o valor bruto menos 21 % de imposto.
 */


#include <stdio.h>
#define IRS 0.21
typedef struct deposito_s{
	float saldo tanb; /*0<=tanb<=1 */
	} deposito;
	
float juros_apos_1_ano(deposito d){
	return d.saldo*d.tanb;
}

float saldo_apos_1_ano(deposito listad[],int n){
	int i=0;
	float saldo=0.0;
	for(;i<n;i++){
		saldo+=listad[i].saldo + juros_apos_1_ano(listad[i])*(1-IRS); 
	/*
	 * Como ao chamar a função juros_apos_1_ano() o tipo deposito é passado por 
	 * valor é possivel fazer define de modo a substituir e o tipo deposito não é chamada
	 * para a função. Exemplo:
	 * #define JUROS_1_ANO(d) ((d)saldo*(d)tanb)
	 * é APENAS substituido e não é avaliado!!! 
	 */
	}
	return saldo;	
}
int main()
{
	
	return 0;
}

