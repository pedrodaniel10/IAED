#include <stdio.h>
#include <string.h>
#define MAXTAM 100
#define True 1
#define False 0

int palindromo(char s[]);
int main(){
	char s[MAXTAM];
	scanf("%s",s);
	if (palindromo(s)==True)
		printf("Palindromo\n");
	else
		printf("Não é Palindromo\n");
	return 0;
}

int palindromo(char s[]){
	int i,j;
	for (i=0, j=strlen(s)-1; i<j; i++, j--){
		if (s[i]!=s[j])
			return False;
	}
	return True;
}