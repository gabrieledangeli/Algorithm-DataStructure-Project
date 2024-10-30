#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
	int numero;
	struct Nodo * next;
} Nodo;

typedef Nodo * Lista;

void VisualizzaLista (Lista l) {
	if (l == NULL)	
		printf("|");
	else if (l->next == NULL){
		printf("%d ", l->numero);
		VisualizzaLista(l->next);
	}
	else {
		printf("%d ---> ", l->numero);
		VisualizzaLista(l->next);
	}
}

Lista InizializzaLista (Lista l) {
	return NULL;
}

Lista InserisciNumeroTesta(Lista l, int n){
	Lista Aux;
	Aux = InizializzaLista(Aux);
	Aux = (Lista) malloc(sizeof(Nodo));
	Aux->numero = n;
	Aux->next = l;
	return Aux;
}

Lista InserisciNumeroCoda(Lista l, int n) {
	if (l == NULL){
		l = (Lista) malloc(sizeof(Nodo));
		l->numero = n;
		l->next = NULL;
	}
	else
		l->next = InserisciNumeroCoda(l->next, n);
	return l;
}

Lista Cerca(Lista l, int n){
	if(l == NULL)
		return l;
	if(l->next == NULL)	
		return l->next;
	if(l->next->numero == n)
		return l;
	return Cerca(l->next, n);
}

Lista CancellaElemento(Lista l, int dacanc) {
	if (l->numero == dacanc)
		return l->next;
		
	Lista punt;
	Lista aux;
	
	punt = Cerca(l, dacanc);															//punt punta al nodo precedente a quello da cancellare
	if(punt == NULL) {
		printf("Elemento non presente nella lista!\n");
		return l;
	}
	aux = punt->next;
	punt->next = aux->next;
	free(aux);
	return l;	
}




int main () {
	Lista Lis;
	int a;
	
	Lis = InizializzaLista(Lis);
	
	printf("Inserisci un numero: ");
	scanf("%d", &a);
	

	while (a != -1) {
		Lis = InserisciNumeroTesta(Lis, a);
		printf("Inserisci un numero: ");
		scanf("%d", &a);
	}
	
	VisualizzaLista(Lis);
	while(1){
		printf("\nChe elemento vuoi eliminare? ");
		scanf("%d", &a);
		
		Lis = CancellaElemento(Lis, a);
		VisualizzaLista(Lis);
	}
	
	return 0;
}
