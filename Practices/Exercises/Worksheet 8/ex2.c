/*
 *2) (Pontos 2D e Rectângulos) Considere que um ponto é definido pelas 
 * suas coordenadas e que um rectângulo é definido pelos pontos dos cantos 
 * superior esquerdo e inferior direito. Considere ainda as seguintes definições 
 * para pontos e rectângulos:  
 * 
 * a) Implemente a função Ponto * lePontos(int n) que lê um conjunto de 
 * n pontos e retorna um vector contendo todos os pontos. 
 * Considere que n é um número pedido ao utilizador. 
 *
 * b) Implemente a função void escrevePontos(Ponto * pontos, int n) que mostra 
 * no standard output os pontos contidos num vector de tamanho n. 
 *
 * c) Implemente a função Rectangulo * defineRectangulo(Ponto * pontos, int n)
 *  que dado um vector de pontos de tamanho n devolve o rectângulo de menor 
 * área que contém todos os pontos do vector. 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Ponto{ 
  int x; 
  int y; 
} Ponto; 

typedef struct Retangulo{ 
  Ponto se; 
  Ponto id; 
} Retangulo; 

Ponto *lePontos(int n){
	Ponto *v=NULL;
	v=malloc(n * sizeof(Ponto));
	memset(v, 0x00, n*sizeof(Ponto));
	while(n--)
		scanf("%d %d", &v[n].x, &v[n].y);		
	return v;
}

void escrevePontos(Ponto * pontos, int n){
	while(n--)
		 printf("(%d,%d)\n",pontos[n].x, pontos[n].y);  		 
}

Retangulo * defineRetangulo(Ponto * pontos, int n){
	Retangulo *r= malloc(sizeof(Retangulo));
	int INT_MAX=0, INT_MIN=0;
	r->se.x= r->id.y=INT_MAX;
	r->se.y= r->id.x=INT_MIN;
	while (n--){
		if (pontos[n].x < r->se.x) r->se.x=pontos[n].x;
		if (pontos[n].x > r->id.x) r->id.x=pontos[n].x;
		if (pontos[n].y < r->se.y) r->se.y=pontos[n].y;
		if (pontos[n].y > r->id.y) r->id.y=pontos[n].y;
	}
	return r;
}

int main(){
	int n;
	Ponto *v;
	printf("Quantos pontos quer introduzir ?\n");
	scanf("%d", &n);
	v=lePontos(n);
	escrevePontos(v,n);
	
	return 0;
}

