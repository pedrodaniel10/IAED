#include "comandos.h"

//////////////////// Comandos do programa //////////////////////////
//Processa uma mensagem incrementando para cada hashtag encontrada o contador respectivo.
void comando_a(){
	ordenado=0;
	split(mensagem);
}

//Mostra o numero de hashtags distintas e o numero total ocorrencias de todas as hashtags.
void comando_s(){
	printf("%ld %ld\n",nr_hashtags,nr_ocorrencias);
}

//Mostra a hashtag mais popular.
void comando_m(){
	if (mais_popular!=NULL)
		imprime_item(mais_popular);
}

//Lista todas as hashtags por ordem decrescente do numero de ocorrencias. Em caso de
//igualdade, as hashtags sao ordenadas alfabeticamente alfabeticamente.
void comando_l(){
	if (dados==NULL)
		return;
	else if (ordenado)
		imprime_vetor(dados);
	else{
		qsort(dados,nr_hashtags,sizeof(hashtag*),cmpqsort);
		imprime_vetor(dados);
		ordenado=1;
	}
}

//Liberta toda a memoria utilizada durante o programa.
void comando_x(){
	int i;
	for (i=0; i<M; i++)
		if (hashtable[i]!=NULL)
			destroi_arvore(hashtable[i]);
	if (dados!=NULL)
		free(dados);	
}

//////////////////// Funcoes auxiliares ///////////////////////////
// Hash function - algoritmo djb2 (Retirada da internet).
unsigned long int hash(char *str){ 
	unsigned long int hash = 5381;
    int c;
		while((c=*str++))
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % M;	
}

//Procura uma hashtag devolvendo o ponteiro para esta. Devolve NULL se nao encontrar.
hashtag* procura_hashtag(char *palavra){
	unsigned long int indice= hash(palavra);
	if (palavra==NULL || hashtable[indice]==NULL)
		return NULL;
	else{
	    link el= procura(hashtable[indice],palavra);
	    if (el==NULL)
			return NULL;
		else
			return el->item;
	}
}

//Insere uma hashtag na hashtable e na lista com o contador a 1.
hashtag* insere_hashtag(char *palavra){
	static int alloc = VETOR_INIT;
	if (dados==NULL)
		dados=malloc(sizeof(hashtag*) * alloc);
	if (nr_hashtags==alloc){
		alloc*=2;
		dados= realloc(dados, sizeof(hashtag*) * alloc);
	}
	
	unsigned long int indice= hash(palavra);
	hashtag *nova_hashtag= novo_item();
	Item *vetor= (Item*) dados+nr_hashtags;
	
	nova_hashtag->palavra= palavra;
	nova_hashtag->contador=1;
	if (hashtable[indice]==NULL){
		 tree *arvore= nova_arvore();
		 hashtable[indice]=arvore;
	}
	inserir_elemento(hashtable[indice], nova_hashtag);
	*vetor=nova_hashtag;
	return nova_hashtag;	
}

//Recebe uma palavra e compara com a mais popular, atualizando a variavel se necessario.
void compara_atualiza_mais_popular(hashtag *hashtag_nova){
	if (mais_popular==NULL)
		mais_popular=hashtag_nova;
	if (cmpitem(hashtag_nova,mais_popular)>0)
		mais_popular=hashtag_nova;
	else if (cmpitem(hashtag_nova,mais_popular)==0){
		 if (less(key(hashtag_nova),key(mais_popular)))
			mais_popular=hashtag_nova;
	} 	
}

//Insere ou incrementa o contador da palavra.
void processa_palavra(char* palavra){
	hashtag *hashtag_nova;
	hashtag_nova= procura_hashtag(palavra);
	if (hashtag_nova==NULL){
		char *nova_palavra= strdup(palavra);
		hashtag_nova=insere_hashtag(nova_palavra);
		nr_hashtags++;
		nr_ocorrencias++;
		compara_atualiza_mais_popular(hashtag_nova);
	}
	else{
		 hashtag_nova->contador++;
		 nr_ocorrencias++;
		 compara_atualiza_mais_popular(hashtag_nova);
	}	
}

//Funcao split como no enunciado.
void split(char *line){
	int i, j, k;
	char buffer[MAXLINESIZE];
	for(i = 0, k = 0; line[i] != '\0'; i++, k++) {
		buffer[k] = tolower(line[i]);
		for(j = 0; j < NUMSEP; j++) {
			if(line[i] == separators[j]) {
				if(k != 0) {
					buffer[k] = '\0';
					
					if (buffer[0]=='#'){
						processa_palavra(buffer+1);
					}
				}
				k = -1;
			}			
		}
	}
}

//Imprime o vetor dados (que contem ponteiros para as hashtags).
void imprime_vetor(){
	Item* vetor= (Item*) dados;
	int i;
	for (i=0; i < nr_hashtags; i++)
		imprime_item(*(vetor + i));
}
