#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024
#define ADD_VETT 2048
#define LEN 2048
#define COM 16

int max = 0, len = LEN;

char ** Espandi(char * doc[],int old_len){
	char ** new_doc = NULL;
	int i;
	
	new_doc = (char **) calloc(old_len + ADD_VETT * ((max - len)/ADD_VETT + 1), sizeof(char *));
	
	for(i = 0; i < old_len; i++)
		new_doc[i] = doc[i];
	
	for(i = old_len; i < old_len + ADD_VETT * ((max - len)/ADD_VETT + 1); i++)
		new_doc[i] = NULL;
		
	free(doc);
	return new_doc;
}

char ** comando_c(char *doc[], char comando[]) {
	int ind1, ind2, lun_riga;
	
	sscanf(comando, "%d,%d", &ind1, &ind2);
	
	ind1--;
	ind2--;
	
	if(ind1 < 0){
		putchar('.');
		return;
	}
	
	
	if(ind2 > max)
		max = ind2;
	
	if(max + 1 > len){
		doc = Espandi(doc, len);
		len = len + ADD_VETT * ((max - len)/ADD_VETT + 1);
	}
	
	char buffer[MAX_LEN + 1 + 1];	
	fgets(buffer, MAX_LEN + 1, stdin);
	

	
	while(buffer[0] != '.' && buffer[1] != '\0' && ind1 <= ind2){
		
		lun_riga = strlen(buffer);
		
		if(doc[ind1] != NULL)
			free(doc[ind1]);
		
		doc[ind1] = (char *) calloc(lun_riga + 1, sizeof(char));
		
		strcpy(doc[ind1], buffer);
		
		fgets(buffer, MAX_LEN, stdin);
		ind1++;		
	}
	
	return doc;
		
}

void comando_p(char * doc[], char com[]){
	FILE * fp = fopen("C:\\Users\\dange\\Desktop\\Per test.txt", "w+");
	int ind1, ind2;
	
	sscanf(com, "%d,%d", &ind1, &ind2);
	
	ind1--;
	ind2--;
	
//	if(ind1 < 0){
//		fputs(".\n", stdout);
//		return;
//	}
	
	while(ind1 <= ind2){
		if(doc[ind1] == NULL)
			fputs(".\n", stdout);
		
		fputs(doc[ind1], stdout);
		ind1++;
	}
}

//void comando_p(char * doc[], char com[]){
//	int ind1, ind2, sentinella;
//	
//	sscanf(com, "%d,%d", &ind1, &ind2);
//	
//	ind1--;
//	ind2--;
//	
//	if(doc == NULL){
//		for(sentinella = ind1; sentinella <= ind2; sentinella++)
//			fputs(".\n", stdout);
//		return;
//	}
//	
//	if(ind1 < 0){
//		fputs(".\n", stdout);
//		return;
//	}
//	
//	if(ind2 > max){
//		sentinella = ind2 - max;
//		ind2 = max;
//	}
//	
//	while(ind1 <= ind2){
//		fputs(doc[ind1], stdout);
//		ind1++;
//	}
//	
//	while(sentinella > 0){
//		fputs(".\n", stdout);
//		sentinella--;
//	}
//}

char ** comando_d(char * documento[], char com[]){
	
	if(documento == NULL)
		return;
	
	int ind1, ind2, da_canc, i = 0, new_max, len;
	
	sscanf(com, "%d,%d", &ind1, &ind2);
	
	ind1--;
	ind2--;
	
	if(ind1 > max || ind2 > max);
	else {
	
		da_canc = ind2 - ind1 + 1;
		
		for(i = ind1; i <= max - da_canc; i++){
			free(documento[i]);
			documento[i] = documento[i + da_canc];
		}
		
		new_max = i;
		
		for(; i <= max; i++){
			documento[i] = NULL;
		}
		
		max = new_max;
	}
	
	return documento;
}


//void Visualizza(char * doc[], int n){
//	if(doc == NULL) {
//		printf("Il tuo documento è vuoto.\n");
//		return;
//	}
//	int i;
//	
//	printf("\nEcco il tuo documento:\n");
//	
//	for(i = 0; i < n; i++){
//		printf("(%d)  %d: ", i, i+1);
//		if(doc[i] == NULL)
//			putchar('\n');
//		else {
//			fputs(doc[i], stdout);
//		}
//	}
//}

int main (){
	char ** doc = NULL;
	char comando[COM];
	int i;
		
	fgets(comando, COM, stdin);

	for(i = 0; comando[i] < 'a' ||  comando[i] > 'z'; i++);
	
	if(comando[i] != 'q')
		doc = (char **) calloc(LEN, sizeof(char *));
	
	
	while(comando[i] != 'q'){
		
		switch(comando[i]) {
			case 'c':	doc = comando_c(doc, comando);
						break;
			case 'd':	doc = comando_d(doc, comando);
						break;
			case 'p':	comando_p(doc, comando);
						break;
			case 'u':	break;
			case 'r':	break;
		}
		
//		Visualizza(doc, len);
	
		fgets(comando, COM, stdin);	
		for(i = 0; comando[i] < 'a' ||  comando[i] > 'z'; i++);		
	
	}	
	
	return 0;
}
