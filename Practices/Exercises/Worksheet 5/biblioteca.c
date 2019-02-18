/*
 * Ficha 5 - Biblioteca IST
 * Obs: na definição de um novo tipo é possivel fazê-la anónima!
 */

#include <stdio.h>
#include <string.h>


#define NUMEROLIVROS 100 
#define MAXTITULO 40 
#define MAXNOME 20 
#define not_founded -1
#define error -1
enum Logico{False,True};

typedef struct Data{ 
  int dia; 
  int mes; 
  int ano; 
} Data; 

typedef struct Livro{ 
  char titulo[MAXTITULO+1]; 
  char autor[MAXNOME+1]; 
  long int isbn; 
  int anoPublicacao; 
  int numeroDaCopia; 
  Data dataEmprestimo; 
  Data dataRetorno; 
} Livro;

static Livro biblioteca[NUMEROLIVROS]; /*vetor de livros*/
static int indice_livro=0;

int data_valida(Data d){
	if (d.dia!=0)
		return False;
	else
		return True;
}

void escreve_menu(){
	printf( "****BIBLIOTECA DO IST**** \n"\
			"1 - Inserir novo livro\n"\
			"2 - Listar livros\n"\
			"3 - Procurar livro por isbn \n"\
			"4 - Procurar livro por título \n"\
			"5 - Alterar título do livro \n"\
			"6 - Apagar livro pelo isbn \n"\
			"7 - Registar data de empréstimo de um livro pelo isbn \n"\
			"8 - Registar data de retorno de um livro pelo isbn \n"\
			"0 - Sair \n"\
			"************************* \n");
}

int inserir_livro(){
	Livro l;
	printf("Titulo: ");
	scanf(" %[^\n]",l.titulo);
	printf("Autor: ");
	scanf(" %[^\n]",l.autor);
	printf("ISBN: ");
	scanf("%ld", &l.isbn);
	printf("Ano da Publicação: ");
	scanf("%d", &l.anoPublicacao);
	printf("Numero da Copia: ");
	scanf("%d", &l.numeroDaCopia);
	printf("Livro inserido com sucesso!\n");
	biblioteca[indice_livro]=l;
	indice_livro++;
	return 0;
}

void listar_livros(){
	int i, tamanho_titulo, n_livros;
	n_livros=indice_livro;
	printf("=========================\n");
	for (i=0; i < n_livros; i++){
		tamanho_titulo=strlen(biblioteca[i].titulo);
		if (tamanho_titulo>1){
			printf("-------------------------\n");
			printf("Titulo: %s\nAutor: %s\nISBN: %ld\n", biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].isbn);
			if (data_valida(biblioteca[i].dataEmprestimo))
				printf("Data Emprestimo: %d/%d/%d", biblioteca[i].dataEmprestimo.dia,\
													biblioteca[i].dataEmprestimo.mes,\
													biblioteca[i].dataEmprestimo.ano);
			if (data_valida(biblioteca[i].dataRetorno))
				printf("Data Emprestimo: %d/%d/%d", biblioteca[i].dataRetorno.dia,\
													biblioteca[i].dataRetorno.mes,\
													biblioteca[i].dataRetorno.ano); 
			printf("-------------------------\n");
		}
			
	}
	printf("=========================\n");
}

int procurar_livro_isbn(){
	int i,n_livros;
	long int isbn;
	n_livros=indice_livro;
	
	printf("ISBN: ");
	scanf("%ld", &isbn);
	
	for (i=0; i < n_livros; i++){
		if (biblioteca[i].isbn==isbn){
			printf("Titulo: %s\nAutor: %s\nISBN: %ld\n", biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].isbn);
			return i;
		}
	}
	printf("Livro não encontrado!\n");
	return not_founded;
}

int procurar_livro_titulo(){
	int i,n_livros;
	char titulo[MAXTITULO];
	n_livros=indice_livro;
	
	printf("Titulo: ");
	scanf("%s", titulo);
	
	for (i=0; i < n_livros; i++){
		if (!strcmp(biblioteca[i].titulo, titulo)){ /*se strings forem iguais*/
			printf("Titulo: %s\nAutor: %s\nISBN: %ld\n", biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].isbn);
			return i;
		}
	}
	printf("Livro não encontrado!\n");
	return not_founded;	
}

int procurar_livro(){
	int i,estado=0;
	printf("Procurar livro por:\n \
			1 - Titulo\n \
			2 - ISBN\n");
	scanf("%d", &estado);
	switch (estado){
		case 1:
			i=procurar_livro_titulo();
			break;
		case 2:
			i=procurar_livro_isbn();
			break;
		default:
			printf("Erro! Comando desconhecido\n");
			return error;
	}		
	if (i!=not_founded) /*Se o livro for encontrado*/
		return i;
	else
		return not_founded;

}

int altera_titulo(){
	int i;
	i=procurar_livro();
	if (i!=not_founded){ /*Se o livro for encontrado*/
		printf("Novo Titulo: ");
		scanf("%s", biblioteca[i].titulo);
		printf("Titulo alterado com sucesso!\n");
		return 0;
	}
	else
		return not_founded;
}

int apagar_livro_isbn(){
	int i;
	char yes_no;
	Livro l;
	i=procurar_livro_isbn();
	if (i!=not_founded){
		printf("Apagar? [S/N]: ");
		yes_no=getchar();
		if (yes_no=='S'){
			biblioteca[i]=l;
			printf("Livro eliminado com sucesso!\n");
			return 0;
		}
		else
			return error;
	}
	else
		return error;	
}

void registar_data_emprestimo(){
	int i;
	Data data;
	
	i=procurar_livro();
	if (i!=not_founded){
		printf("Data (dd/mm/aaaa): ");
		scanf("%d%d%d",&data.dia, &data.mes, &data.ano);
		biblioteca[i].dataEmprestimo=data;
	}	
}

void registar_data_retorno(){
	int i;
	Data data;
	
	i=procurar_livro();
	if (i!=not_founded){
		printf("Data (dd/mm/aaaa): ");
		scanf("%d%d%d",&data.dia, &data.mes, &data.ano);
		biblioteca[i].dataRetorno=data;
	}
}

int main(){
	int estado=-1;
	while (estado!=0){
		escreve_menu();
		
		scanf("%d", &estado);
		
		switch (estado){
			case 1:
				inserir_livro();
				break;
			case 2:
				listar_livros();
				break;
			case 3:
				procurar_livro_isbn();
				break;
			case 4:
				procurar_livro_titulo();
				break;
			case 5:
				altera_titulo();
				break;
			case 6:
				apagar_livro_isbn();
				break;
			case 7:
				registar_data_emprestimo();
				break;
			case 8:
				registar_data_retorno();
				break;	
			default:
				break;			
		}
	}
	return 0;
}

