/*
 * Fazer funcao char* strstr(const char* haystack, const char* niddle), procurar a afulha no palheiro
 * const significa que a memoria apontada não é alterada.
 */


#include <stdio.h>
#include <stdlib.h>

char* strstr(const char* haystack, const char* niddle){
	char *h, *n;
	for (; haystack; haystack++)
		for (n=niddle, h=haystack; *n && *h; n++,h++)
			if (*n!=*h)
				break;
		if (!*n)
			return haystack;
	return NULL	
}
