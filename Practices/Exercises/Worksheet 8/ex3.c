/*
 * 3) (Vectores de Estruturas) Considere que se pretende ler do standard 
 * input a informação de um conjunto de inscrições de alunos a disciplinas 
 * e respectivas notas. A estrutura que guarda a informação de uma inscrição 
 * está definida do seguinte modo:
 * 
 * a) Escreva em linguagem C a função Inscricao* lerInscricoes(int n) que lê 
 * um sequência de n inscrições do standard input e devolve um novo vector de 
 * inscrições de alunos em disciplinas. Assuma que o código de uma disciplina é 
 * uma sequência de letras e digitos com tamanho máximo de 10 caracteres. 
 * 
 * b) Escreva em linguagem C a função int* distribuicaoNotas(Inscricao* ins, int n, char* disc) 
 * que dado um vector de inscrições de tamanho n devolve um novo vector de inteiros com 
 * a distribuição das notas de uma disciplina. Ou seja, na posição indice i do vector 
 * deverá conter o número de alunos que teve nota i à disciplina.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CODE_MAX_LEN 10
#define MAX_NOTA 20

typedef struct { 
  int num_aluno; 
  char* cod_disc; 
  int nota; 
} Inscricao;

Inscricao * lerInscricoes(int n){
	Inscricao *v;
	int i;
	v= malloc(sizeof(Inscricao)*n);
	memset(v, 0x0, n*sizeof(Inscricao));
	for (i=0; i<n; i++){
		v[i].cod_disc= malloc(11*sizeof(char));
		scanf("%d%s%d", &v[i].num_aluno, v[i].cod_disc, &v[i].nota);
	}	
	return v;
}

void libertaInscricoes(Inscricao *v, int n){
	while (n--)
		free(v[n].cod_disc);
	free(v);
}

int* distribuicaoNotas(Inscricao* ins, int n, char* disc){
	int *histograma= malloc( sizeof(int) * (MAX_NOTA + 1)), i;
	memset(histograma, 0x0, sizeof(int) * (MAX_NOTA + 1));
	for (i=0; i < n; i++){
		if(strcmp(ins[i].cod_disc, disc)==0)
			histograma[ins[i].nota]++;			
	}
	return histograma;	
}

int main(){
	
	return 0;
}

