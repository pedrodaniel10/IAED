#include "comandos.h"


//////////////////// Comandos do programa //////////////////////////
void comando_a(){
	ordenado=0;
	split(mensagem);
}

void comando_s(){
	printf("%ld %ld\n",nr_hashtags,nr_ocorrencias);
}

void comando_m(){
	if (mais_popular!=NULL)
		imprime_item(mais_popular);
}

void comando_l(){
	if (dados==NULL)
		return;
	else if (ordenado)
		imprime_lista(dados);
	else{
		dados=merge_sort(dados);
		imprime_lista(dados);
		ordenado=1;
	}
}

void comando_x(){
	int i;
	for (i=0; i<M; i++)
		if (hashtable[i]!=NULL)
			destroi_arvore(hashtable[i]);
	if (dados!=NULL)
		liberta_lista(dados);
		
	
}

//////////////////// Funcoes auxiliares ///////////////////////////
// Hash function - algoritmo djb2
unsigned long int hash(char *str){ 
	unsigned long int hash = 5381;
    int c;
		while((c=*str++))
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % M;	
}

//Procura uma hashtag devolvendo o ponteiro para esta. Devolve NULL se nao encontrar
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

//Insere uma hashtag na hashtable e na lista com o contador a 1
hashtag* insere_hashtag(char *palavra){
	unsigned long int indice= hash(palavra);
	hashtag *nova_hashtag= novo_item();
	nova_hashtag->palavra= palavra;
	nova_hashtag->contador=1;
	if (hashtable[indice]==NULL){
		 tree *arvore= nova_arvore();
		 hashtable[indice]=arvore;
	}
	inserir_elemento(hashtable[indice], nova_hashtag);
	if (dados==NULL)
		dados=nova_lista();
	append_fim(dados, nova_hashtag);
	return nova_hashtag;	
}

//Recebe uma palavra e compara com a mais popular, atualizando a variavel se necessario
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

//Insere ou incrementa o contador da palavra
void processa_palavra(char* palavra){
	hashtag *hashtag_nova;
	hashtag_nova= procura_hashtag(palavra);
	if (hashtag_nova==NULL){
		hashtag_nova=insere_hashtag(palavra);
		nr_hashtags++;
		nr_ocorrencias++;
		compara_atualiza_mais_popular(hashtag_nova);
	}
	else{
		 hashtag_nova->contador++;
		 nr_ocorrencias++;
		 compara_atualiza_mais_popular(hashtag_nova);
		 free(palavra);
	}	
}

//Funcao split como no enunciado
void split(char *line){
	int i, j, k;
	char buffer[MAXLINESIZE], *palavra;
	for(i = 0, k = 0; line[i] != '\0'; i++, k++) {
		buffer[k] = tolower(line[i]);
		for(j = 0; j < NUMSEP; j++) {
			if(line[i] == separators[j]) {
				if(k != 0) {
					buffer[k] = '\0';
					
					if (buffer[0]=='#'){
						palavra=strdup(buffer+1);
						processa_palavra(palavra);
					}
				}
				k = -1;
			}			
		}
	}
}
