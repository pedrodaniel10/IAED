
#include <stdio.h>


int main(){
	int estado=-1,num;
	char comando, vetor[4];
	while (estado!=0){
		comando=getchar();
		
		switch (comando){
			case 'A':
				scanf("%s%d",vetor,&num);
				printf("%c\t%s\t%d\n",comando, vetor, num);
				break;
			case 'B':
				scanf("%s",vetor);
				printf("%c\t%s\n",comando, vetor);
				break;
			case 'C':
				scanf("%d",&num);
				printf("%c\t%d\n",comando, num);
				break;
			case 4:
				printf("4\n");
				break;
			
		}
	}
	return 0;
}

