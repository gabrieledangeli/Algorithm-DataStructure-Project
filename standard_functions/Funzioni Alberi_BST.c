#include <stdio.h>
#include <stdlib.h>

typedef struct Foglia {
	int numero;
	struct Foglia * left;
	struct Foglia * right;
} Foglia;

typedef Foglia * Tree;

Tree InizializzaAlbero (Tree t) {
	return NULL;
}

Tree InserisciBST (Tree t, int num) {
	if(t == NULL){
		t = (Tree) malloc(sizeof(Foglia));
		t -> numero = num;
		t -> left = t -> right = NULL;
		return t;
	}
	else if(num > t -> numero){
		t->right = InserisciBST(t->right, num);
		return t;
	}
	else if(num < t -> numero){
		t->left = InserisciBST(t->left, num);
		return t;
	}
	
	else if(num == t -> numero)
		return t;
}

void VisualizzaCrescente(Tree t){
	if(t == NULL)	return;
	VisualizzaCrescente(t->left);
	printf("%d  ", t->numero);
	VisualizzaCrescente(t->right);
}

void VisualizzaDecrescente(Tree t){
	if(t == NULL)	return;
	VisualizzaDecrescente(t->right);
	printf("%d  ", t->numero);
	VisualizzaDecrescente(t->left);
}


int main (){
	Tree albero;
	
	int i = 0;
	
	albero = InizializzaAlbero(albero);
	
	printf("Inserisci un numero: ");
	scanf("%d", &i);
	while(i != -1){
		albero = InserisciBST(albero, i);
		printf("Inserisci un numero: ");
		scanf("%d", &i);
	}

	while(i <= 5){
		albero = InserisciBST(albero, i);		
		albero = InserisciBST(albero, 10 - i);
		i++;
		VisualizzaCrescente(albero);
		putchar('\n');
		putchar('\n');
	}
	
	return 0;
}
