#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "list.h"


int main(int argc, char *argv[]]){
	link l=Null;
	for (i=0;i<arg; i++)
		l=insertSorted(l,argv[i]);
	show(l);
	l=remove(l,argv[0]);
	show(l);
	deleteAll(l);
	return 0;
}

