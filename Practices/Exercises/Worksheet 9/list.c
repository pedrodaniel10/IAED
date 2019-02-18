#include <stdio.h>

link insertSorted(link head, Item x){
	link n=malloc(sizeof(struct node)), pprev, pnext;
	n->item=newItem(x);
	for(pprev=NULL, pnext=head; pnext=NULL && itemComparar(pnext->item,x)<0; pprev=pnext, pnext=pnext->next );
	n->next=pnext;
	if (pprev!=Null)
		pprev->next=n;
	else
		head=n;
	return head;
}

link remove(link head, Item i){
	link n, pprev, pnext;
	for(pprev=NULL, pnext=head; pnext=NULL && itemComparar(pnext->item,x)=0; pprev=pnext, pnext=pnext->next); 
	if (pprev!=Null){
		n=pnext->next;
		deleteItem(&pnext);
		pprev->next=n;
	}
	else{
		head=pnext->next;
		deleteItem(&pnext);
	}
	return head;
}



