/* Projeto 1 - IAED 2015/2016 2 Semestre
 * Rede de Aeroportos
 * Francisco Pinheira 85333 - Grupo 81 - Taguspark
 * Pedro Lopes 83540 - Grupo 38 - Alameda
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 4
#define MAX_AEROPORTOS 1001
#define MAX_VOOS 1001
#define NOT_FOUNDED -1
/* Funcao que devolve as partidas e chegadas do aeroporto indice i*/
#define PARTIDAS_CHEGADAS(i) for (j=0; j < MAX_AEROPORTOS; j++){ partidas+= voos[i][j]; chegadas+= voos[j][i]; } 

enum Logico{False,True};
enum Estado{Fechado,Aberto};
typedef struct Aeroporto{
	char codigo[MAX_NOME];
	int capacidade;
	int estado;} Aeroporto;
typedef struct ID{
	char id[MAX_NOME];
	int posicao;  } ID;

Aeroporto aeroportos[MAX_AEROPORTOS];
ID ordenar_aeroportos[MAX_AEROPORTOS];
int voos[MAX_AEROPORTOS][MAX_AEROPORTOS]={{0}};
int nr_aeroportos=0;

/* ******************************************************************* *
 * ************************PROTOTIPOS********************************* *
 * ******************************************************************* */
void comando_a();
void comando_i();
void comando_f();
void comando_g();
void comando_r();
void comando_s();
void comando_n();
void comando_p();
void comando_q();
void comando_v();
void comando_c();
void comando_o();
void comando_l();
int procura_id( char codigo[] );
int nr_voos_aeroporto(char codigo[], int indice);
int aeroporto_mais_voos();
void remove_todos_voos( int indice);
int nr_ligacoes_aeroporto(char codigo[], int indice);
int aeroporto_mais_ligacoes();
int nr_total_voos();
void sort(ID vetor[], int l, int r);

/* ******************************************************************* *
 * ***********************FUNCAO MAIN********************************* *
 * ******************************************************************* */
int main(){
	char comando;
	int nr_voos;

	while (True){
		scanf("%c", &comando);
	
		switch (comando){
			case 'A':
				comando_a();
				break;
			case 'I':
				comando_i();
				break;
			case 'F':
				comando_f();
				break;
			case 'G':
				comando_g();
				break;
			case 'R':
				comando_r();
				break;
			case 'S':
				comando_s();
				break;
			case 'N':
				comando_n();
				break;
			case 'P':
				comando_p();
				break;
			case 'Q':
				comando_q();
				break;
			case 'V':
				comando_v();
				break;
			case 'C':
				comando_c();
				break;
			case 'O':
				comando_o();
				break;
			case 'L':
				comando_l();
				break;
			case 'X':
				nr_voos= nr_total_voos();
				printf("%d:%d\n", nr_voos, nr_aeroportos);
				return EXIT_SUCCESS;
				break;
			default:
				printf("Erro: comando desconhecido.\n");
				break;
		}
		getchar();
	}
	return EXIT_FAILURE;
}
/* ******************************************************************* *
 * ******************FUNCOES PRINCIPAIS******************************* *
 * ******************************************************************* */
 void comando_a(){
/* Adiciona um novo aeroporto
 * Adiciona o aeroporto com o identificador e capacidade respetivas.
 */
	Aeroporto novo_aeroporto;
	ID novo_id;
	
	scanf("%s%d", novo_aeroporto.codigo, &novo_aeroporto.capacidade);
	if (novo_aeroporto.capacidade > 0 && \
		nr_aeroportos < MAX_AEROPORTOS){
		 novo_aeroporto.estado= Aberto;
		 aeroportos[nr_aeroportos]= novo_aeroporto;
		        
		 strcpy(novo_id.id, novo_aeroporto.codigo);
		 novo_id.posicao= nr_aeroportos;
		 ordenar_aeroportos[nr_aeroportos]= novo_id;
		 nr_aeroportos++;
	}
}

void comando_i(){
/* Altera a capacidade maxima de operacao de um aeroporto
 * Altera a capacidade maxima de operacao do aeroporto <id> de acordo com o valor 
 * introduzido. A nova capacidade maxima sera sempre superior ou igual ao numero 
 * de voos atuais do aeroporto.
 */
	char codigo[MAX_NOME];
	int soma_capacidade, i;
	
	scanf("%s%d", codigo, &soma_capacidade);  
	i=procura_id(codigo);
	
	if ( i!=NOT_FOUNDED && \
		aeroportos[i].estado==Aberto && \
		soma_capacidade!=0 && \
		(aeroportos[i].capacidade + soma_capacidade) >= nr_voos_aeroporto(codigo, i) && \
		(aeroportos[i].capacidade + soma_capacidade) > 0)
			aeroportos[i].capacidade += soma_capacidade;
	else
		printf("*Capacidade de %s inalterada\n", codigo);
}	

void comando_f(){
/* Adiciona voo de ida e volta
 * Adiciona os voos de ida e volta entre os aeroportos indicados.
 */
	char codigo1[MAX_NOME], codigo2[MAX_NOME];
	int i,j;
	
	scanf("%s%s", codigo1, codigo2);
	i= procura_id(codigo1);
	j= procura_id(codigo2);
	
	if (i!= NOT_FOUNDED && j!=NOT_FOUNDED && \
		aeroportos[i].estado==Aberto && aeroportos[j].estado==Aberto && \
		(aeroportos[i].capacidade - nr_voos_aeroporto(codigo1, i)) > 1 && \
		(aeroportos[j].capacidade - nr_voos_aeroporto(codigo2, j)) > 1){
			voos[i][j]++;
			voos[j][i]++;
	}
	else
		printf("*Impossivel adicionar voo RT %s %s\n", codigo1, codigo2);
		
}

void comando_g(){
/* Adiciona rota
 * Adiciona o voo de ida de id_1 para id_2.
 */
	char codigo1[MAX_NOME], codigo2[MAX_NOME];
	int i,j;
	
	scanf("%s%s", codigo1, codigo2);
	i= procura_id(codigo1);
	j= procura_id(codigo2);
	
	if (i!= NOT_FOUNDED && j!=NOT_FOUNDED && \
		aeroportos[i].estado==Aberto && aeroportos[j].estado==Aberto && \
		(aeroportos[i].capacidade - nr_voos_aeroporto(codigo1, i)) > 0 && \
		(aeroportos[j].capacidade - nr_voos_aeroporto(codigo2, j)) > 0)
			voos[i][j]++;
	else
		printf("*Impossivel adicionar voo %s %s\n", codigo1, codigo2);
}

void comando_r(){
/* Remove voo
 * Remove o voo com partida em <id_1> e chegada a <id_2>.
 */
	char codigo1[MAX_NOME], codigo2[MAX_NOME];
	int i,j;
	
	scanf("%s%s", codigo1, codigo2);
	i= procura_id(codigo1);
	j= procura_id(codigo2);
	
	if (i!= NOT_FOUNDED && j!=NOT_FOUNDED && \
		aeroportos[i].estado==Aberto && aeroportos[j].estado==Aberto && \
		voos[i][j]>0)
			voos[i][j]--;
	else
		printf("*Impossivel remover voo %s %s\n", codigo1, codigo2);
}

void comando_s(){
/* Remove voo de ida e volta
 * Remove o voo de ida e volta entre <id1> e <id2>. So e efetuada caso seja  
 * possivel remover ambos os voos.
 */
	char codigo1[MAX_NOME], codigo2[MAX_NOME];
	int i,j;
	
	scanf("%s%s", codigo1, codigo2);
	i= procura_id(codigo1);
	j= procura_id(codigo2);
	
	if (i!= NOT_FOUNDED && j!=NOT_FOUNDED && \
		aeroportos[i].estado==Aberto && aeroportos[j].estado==Aberto && \
		voos[i][j]>0 && voos[j][i]>0){
			voos[i][j]--;
		    voos[j][i]--;
		}			
	else
		printf("*Impossivel remover voo RT %s %s\n", codigo1, codigo2);
}

void comando_n(){
/* Numero de voos
 * Retorna o numero de voos entre os aeroportos <id_1> e <id_2>, saindo de <id_1>  
 * para <id_2> e de <id_2> para <id_1>.
 */
	char codigo1[MAX_NOME], codigo2[MAX_NOME];
	int i,j;
	
	scanf("%s%s", codigo1, codigo2);
	i= procura_id(codigo1);
	j= procura_id(codigo2);
	
	if (i!= NOT_FOUNDED && j!=NOT_FOUNDED){
		int partidas, chegadas;
		partidas= voos[i][j];
		chegadas= voos[j][i];
		printf("Voos entre cidades %s:%s:%d:%d\n", codigo1, codigo2, partidas, chegadas);			
	}			
	if (i== NOT_FOUNDED) 
		printf("*Aeroporto %s inexistente\n", codigo1);
		
	if (j== NOT_FOUNDED) 
		printf("*Aeroporto %s inexistente\n", codigo2);
}

 void comando_p(){
/* Aeroporto com o maior numero de voos 
 * Retorna o aeroporto <id> com o maior numero total de voos (soma das partidas e chegadas).
 */
	int i,j, partidas=0, chegadas=0;
	
	i=aeroporto_mais_voos();
	PARTIDAS_CHEGADAS(i);	 
	printf("Aeroporto com mais rotas %s:%d:%d\n", aeroportos[i].codigo, partidas, chegadas);
}

 void comando_q(){
/* Aeroporto mais conectado
 * Retorna o aeroporto <id> com o maior numero de outros aeroportos conectados.
 */
	int i;
	
	i=aeroporto_mais_ligacoes();
	printf("Aeroporto com mais ligacoes %s:%d\n", aeroportos[i].codigo, nr_ligacoes_aeroporto(aeroportos[i].codigo, i) );
}

void comando_v(){
/* Voo mais popular
 * Retorna o par de aeroportos <id_1> <id_2> com o maior numero de voos (Nvoos) a
 * sair de <id_1> e a chegar a <id_2>.
 */
	int i,j, mais_voos=0,nr_voos, k=0, u=0;
	
	for (i=0; i < nr_aeroportos; i++){
		for (j=0; j < nr_aeroportos; j++){
			if ( voos[i][j] > mais_voos ){
				mais_voos= voos[i][j];
				k=i;
				u=j;					
			}
		}
	}
	if (k==0 && u==0 && nr_aeroportos>1)
		u=1;
	nr_voos= voos[k][u];
	printf("Voo mais popular %s:%s:%d\n", aeroportos[k].codigo, aeroportos[u].codigo, nr_voos);
}

void comando_c(){
/* Encerra aeroporto
 * Encerra o aeroporto atualmente em operação <id> removendo todos os voos com
 * partida ou chegada a <id>.
 */
	char codigo[MAX_NOME];
	int i;
	
	scanf("%s", codigo);
	i= procura_id(codigo);
	if (i==NOT_FOUNDED)
		printf("*Aeroporto %s inexistente\n", codigo);	
	else{
		remove_todos_voos(i);
		aeroportos[i].estado= Fechado;
	}
}

void comando_o(){
/* Reabre aeroporto
 * Reabre o aeroporto atualmente encerrado <id>.
 */
	char codigo[MAX_NOME];
	int i;
	
	scanf("%s", codigo);
	i= procura_id(codigo);
	if (i==NOT_FOUNDED)
		printf("*Aeroporto %s inexistente\n", codigo);
	else
		aeroportos[i].estado= Aberto;
}

void comando_l(){
	int tipo,i,j,k,partidas,chegadas,mais_voos=0, histograma[MAX_VOOS]={0}, nr_voos;
	
	scanf("%d", &tipo);
	switch (tipo){
		case 0:
			for (i=0; i < nr_aeroportos; i++){
				 partidas=chegadas=0;
				 PARTIDAS_CHEGADAS(i);
				 printf("%s:%d:%d:%d\n", aeroportos[i].codigo, aeroportos[i].capacidade, partidas, chegadas);
			}
			break;
			
		case 1:
			sort(ordenar_aeroportos,0,nr_aeroportos-1);
			for (i=0; i < nr_aeroportos; i++){
				 partidas=chegadas=0;
				 k= ordenar_aeroportos[i].posicao;
				 PARTIDAS_CHEGADAS(k);
				 printf("%s:%d:%d:%d\n", aeroportos[k].codigo, aeroportos[k].capacidade, partidas, chegadas);
			}
			break;
			
		case 2:
			for (i=0; i < nr_aeroportos; i++){
				 nr_voos= nr_voos_aeroporto(aeroportos[i].codigo, i);
				 histograma[nr_voos]++;
				 if (nr_voos > mais_voos)
					mais_voos= nr_voos;
			}
			if (mais_voos > MAX_VOOS)
				mais_voos= MAX_VOOS -1;
			for (i=0; i <= mais_voos; i++){
				if (histograma[i]!=0)
					printf("%d:%d\n", i, histograma[i]);
			}
			break;
			
		default:
			break;
	}
}

/* ******************************************************************* *
 * ******************FUNCOES AUXILIARES******************************* *
 * ******************************************************************* */ 
int procura_id( char codigo[] ){
/* procura_id: Cadeia Caracteres -> Inteiro
 * Esta funcao recebe o codigo de um aeroporto e devolve o indice da posicao 
 * do aeroporto no vetor aeroportos[]. Caso nao esteja no vetor e devolvido
 * NOT_FOUNDED=-1 
 */
	int i;
	
	for (i=0; i < nr_aeroportos; i++)
		if ( !strcmp( codigo, aeroportos[i].codigo) ) /*se strings iguais*/
			return i;
			
	return NOT_FOUNDED;
}


int nr_voos_aeroporto(char codigo[], int indice){
/* nr_voos_aeroporto: Cadeia Caracteres x Inteiro -> Inteiro
 * Esta funcao recebe o codigo do aeroporto e o indice da posicao do aeroporto 
 * e devolve a soma dos voos de partida e chegada.
 * OBS: Quando nao se sabe o indice, o segundo argumento sera NOT_FOUNDED e a 
 * funcao procura o indice.
 */
	int i,j,soma=0;
	
	i= (indice==NOT_FOUNDED) ? procura_id(codigo) : indice;
	for (j=0; j < nr_aeroportos; j++)
		soma= soma + voos[i][j] + voos[j][i];
			
	return soma;
}

int aeroporto_mais_voos(){
/* aeroporto_mais_voos: Void -> Inteiro
 * Esta funcao nao recebe nenhum argumento e devolve o indice da posicao 
 * do aeroporto com mais voos.
 * No caso de haver mais do que um aeroporto na mesma situacao, sera devolvido
 * o menor indice.
 */
	int i,nr_voos, mais_voos=0, indice_aeroporto_mais_voos=0;
	
	for (i=0; i < nr_aeroportos; i++){
		nr_voos = nr_voos_aeroporto( aeroportos[i].codigo, i);
		if (nr_voos > mais_voos){
			mais_voos= nr_voos;
			indice_aeroporto_mais_voos= i;
		}
	}
	return indice_aeroporto_mais_voos;
}

void remove_todos_voos( int indice){
/* remove_todos_voos: Inteiro -> Void
 * Esta funcao recebe um indice da posicao de um aeroporto e remove todos
 * os voos de partida e chegada desse mesmo. 
 * Na matriz voos, a linha e a coluna desse aeroporto e alterada para 0.
 */
	int j;
	
	for (j=0; j < nr_aeroportos; j++){
		voos[indice][j]=0;
		voos[j][indice]=0;
	}
}

int nr_ligacoes_aeroporto(char codigo[], int indice){
/* nr_ligacoes_aeroporto: Cadeia Caracteres x Inteiro -> Inteiro
 * Esta funcao recebe o codigo do aeroporto e o indice da posicao do aeroporto 
 * e devolve o total de ligacoes desse mesmo.
 * OBS: Quando nao se sabe o indice, o segundo argumento sera NOT_FOUNDED e a 
 * funcao procura o indice.
 */
	int i,j,ligacoes=0;
	
	i= (indice==NOT_FOUNDED) ? procura_id(codigo) : indice;
	for (j=0; j < nr_aeroportos; j++){
		if ((voos[i][j]!=0) || (voos[j][i]!=0))
			ligacoes++;
	}
	return ligacoes;
}

int aeroporto_mais_ligacoes(){
/* aeroporto_mais_ligacoes: Void -> Inteiro
 * Esta funcao nao recebe nenhum argumento e devolve o indice da posicao 
 * do aeroporto com mais ligacoes.
 * No caso de haver mais do que um aeroporto na mesma situacao, sera devolvido
 * o menor indice.
 */
	int i, nr_ligacoes, mais_ligacoes=0, indice_aeroporto_mais_ligacoes=0;
	
	for (i=0; i < nr_aeroportos; i++){
		nr_ligacoes= nr_ligacoes_aeroporto( aeroportos[i].codigo, i );
		if (nr_ligacoes > mais_ligacoes){
			mais_ligacoes= nr_ligacoes;
			indice_aeroporto_mais_ligacoes= i;
		}
	}
	return indice_aeroporto_mais_ligacoes;
}

int nr_total_voos(){
/* nr_total_voos: Void -> Inteiro
 * Esta funcao nao recebe nenhum argumento e devolve a soma de todos os
 * voos. 
 */
	int i,j,soma=0;
	
	for (i=0; i < MAX_AEROPORTOS; i++){
		for (j=0; j < MAX_AEROPORTOS; j++)
			soma+= voos[i][j];
	}
	return soma;
}

void sort(ID vetor[], int l, int r){
/* sort: ID x Inteiro x Inteiro -> Void
 * Esta funcao recebe um vetor do tipo ID, e dois inteiros que representam
 * respetivamente o limite esquerdo e o limite direito, e ordena o vetor
 * usando o algoritmo SelectionSort. Ficando o vetor ordenado de forma crescente
 * de ID.x
 */
	int i,j;
	
	for (i=l; i < r; i++){
		int min=i;
		ID aux_id;
		for (j=i+1; j<=r; j++)
			if (strcmp(vetor[j].id, vetor[min].id) < 0)
				min=j;
				
		aux_id= vetor[i];
		vetor[i]= vetor[min];
		vetor[min]= aux_id;
		
	}	
}
