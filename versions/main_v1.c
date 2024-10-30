#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1024
#define COM_LEN 64

typedef struct riga {
	char stringa[MAX_LEN + 1];
	struct riga * next;
} Riga;

typedef Riga * Documento;

Documento comando_c(char * string, Documento d) {
	int ind1, ind2, i;
	Documento p = d;
	
	sscanf(string, "%d,%d", &ind1, &ind2);
	
	i = ind2 - ind1 + 1;
	if(p == NULL){
		p = (Documento) calloc(1, sizeof(Documento));
		gets(p->stringa);
		p->next = NULL;
		d = p;
	}
	
	p = 
	
	return d;	
	
}

void VisualizzaDoc(Documento d) {
	if(d == NULL)
		return;
	puts(d -> stringa);
	VisualizzaDoc(d->next);
}

int main () {
	Documento d = NULL;
	char comando[COM_LEN];
	int i = 0;

	gets(comando);
	for(i = 0; comando[i] < 'a' ||  comando[i] > 'z'; i++);
	
	while(comando[i] != 'q'){
		
		switch(comando[i]) {
			case 'c':	d = comando_c(comando, d);
						break;
			case 'd':	break;
			case 'p':	break;
			case 'u':	break;
			case 'r':	break;
		}
	
	VisualizzaDoc(d);
		
	gets(comando);
	for(i = 0; comando[i] < 'a' ||  comando[i] > 'z'; i++);		
	
	}
	
	return 0;
}
