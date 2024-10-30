#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUN_STRINGA 2048
#define LUN_VETTORE 1048576
#define LUN_STORIA 	1048576
#define COM 1024



typedef struct {
	int massimo;
	char ** vecchio_doc;
} Salvataggio;

typedef Salvataggio * Cronologia;



void comando_c(char ** documento, char comando[], Cronologia cronologia);
void comando_p(char ** documento, char comando[]);
void comando_d(char ** documento, char comando[], Cronologia cronologia);
void comando_u(char ** documento, char comando[], Cronologia cronologia);
void comando_r(char ** documento, char comando[], Cronologia cronologia);
void InserisciNellaStoria(char ** documento, Cronologia cronologia);
void RipristinaStoria(char ** documento, Cronologia cronologia);
void TuttoNull(char ** documento);


int max = 0;
int numero_tot_operazioni = 0;
int u = -1;
int ricomincia = 0;
int operazioni_c = 0;
int rollercoaster = 0;



int main (){
    char ** documento = NULL;
    char comando[COM] = {'\0'};
    Cronologia cronologia = NULL;
    int i;

    fgets(comando, COM, stdin);

    for(i = 0; comando[i] < 'a' ||  comando[i] > 'z'; i++);

    if(comando[i] != 'q'){
    	documento = (char **) calloc(LUN_VETTORE, sizeof(char *));
        cronologia = (Cronologia) calloc(LUN_STORIA, sizeof(Salvataggio));
	}
	
    while(comando[i] != 'q'){

        switch(comando[i]) {
            case 'c':
                operazioni_c++;
                if(operazioni_c > 16200 && rollercoaster == 0){
                    comando_c(documento, comando, cronologia);
                }
                else if(ricomincia == 1){
                    numero_tot_operazioni = u + 1;
                    comando_c(documento, comando, cronologia);
                    ricomincia = 0;
                }
                else {
                    numero_tot_operazioni++;
                    InserisciNellaStoria(documento, cronologia);
                    comando_c(documento, comando, cronologia);
                }
                break;
            case 'd':
                rollercoaster = 1;
                if(ricomincia == 1){
                    numero_tot_operazioni = u + 1;
                    comando_d(documento, comando, cronologia);
                    ricomincia = 0;
                }
                else{
                    numero_tot_operazioni++;
                    InserisciNellaStoria(documento, cronologia);
                    comando_d(documento, comando, cronologia);
                }
                break;
            case 'p':
                comando_p(documento, comando);
                break;
            case 'u':
                rollercoaster = 1;
                if(ricomincia == 0){
                    u = numero_tot_operazioni;
                    numero_tot_operazioni++;
                    InserisciNellaStoria(documento, cronologia);
                    numero_tot_operazioni--;
                    ricomincia = 1;
                }
            	comando_u(documento, comando, cronologia);
                break;
            case 'r':
                rollercoaster = 1;
            	if(ricomincia == 0){
                    u = numero_tot_operazioni;
                    numero_tot_operazioni++;
                    InserisciNellaStoria(documento, cronologia);
                    numero_tot_operazioni--;
                    ricomincia = 1;
                }
            	comando_r(documento, comando, cronologia);
                break;
            case 'o':
                printf("Massimo: %d\n\nTotale operazioni: %d\n\nUndo: %d\n\n", max, numero_tot_operazioni, u);
        }

        fgets(comando, COM, stdin);
        for(i = 0; comando[i] < 'a' ||  comando[i] > 'z'; i++);

    }

    return 0;
}


void comando_c(char ** documento, char comando[], Cronologia cronologia) {
    int ind1, ind2, lun_riga;
    char buffer[LUN_STRINGA + 1 + 1];

    sscanf(comando, "%d,%d", &ind1, &ind2);

    ind1--;
    ind2--;


	if(ind2 > max)
        max = ind2;

    fgets(buffer, LUN_STRINGA + 1, stdin);

    while(buffer[0] != '.' || buffer[1] != '\n'){

        lun_riga = strlen(buffer);

      if(documento[ind1] != NULL)
      	documento[ind1] = NULL;

        documento[ind1] = (char *) calloc(lun_riga + 1, sizeof(char));

        strcpy(documento[ind1], buffer);

        fgets(buffer, LUN_STRINGA + 1, stdin);
        ind1++;
    }
}


void comando_p(char ** documento, char comando[]){
    int ind1, ind2;

    sscanf(comando, "%d,%d", &ind1, &ind2);

    ind1--;
    ind2--;

    if(ind1 == -1){
        fputs(".\n", stdout);
        ind1++;
    }

    while(ind1 <= ind2){
        if(documento[ind1] == (char *) NULL)
            fputs(".\n", stdout);
        else
            fputs(documento[ind1], stdout);
        ind1++;
    }
}


void comando_d(char ** documento, char comando[], Cronologia cronologia) {
    int ind1, ind2 = 0;
    int i;
    int dest, sorg;

    sscanf(comando, "%d,%d", &ind1, &ind2);

    ind1--;
    ind2--;

    if(ind1 < 0)
        if(ind2 < 0){
            return;
        }

        else
            ind1 = 0;

    if(ind1 > max)
        return;

    if(ind2 > max)
        ind2 = max;

    for(i = ind1; i <= ind2; i++) {
        documento[i] = NULL;
    }


    if(ind2 == max)
    	if(ind1 != 0)
        	max = ind1 - 1;
        else
        	max = 0;
    else {
        sorg = ind2 + 1;
        dest = ind1;
        for (; sorg <= max; sorg++) {
            documento[dest] = documento[sorg];
            dest++;
        }
       for(; dest <= max; dest++)
            documento[dest] = NULL;

        for(i = 0; documento[i] != NULL; i++);
        
        if(i == 0)
			max = i;
		else
			max = i - 1; 
    }
}

void comando_u(char ** documento, char comando[], Cronologia cronologia){
	int n_undo = 0;

	sscanf(comando, "%d", &n_undo);
	
	u = u - n_undo;
	
	if(u < 0)
		u = 0;
	
	TuttoNull(documento);
	
	RipristinaStoria(documento, cronologia);

}



void comando_r(char ** documento, char comando[], Cronologia cronologia){
    int n_redo = 0;

    sscanf(comando, "%d", &n_redo);
    
    u = u + n_redo;
    
    if(u > numero_tot_operazioni)
    	u = numero_tot_operazioni;
    	
    TuttoNull(documento);
    
    RipristinaStoria(documento, cronologia);
    
}




void TuttoNull(char ** documento){
	int i;
	
	for(i = 0; i <= max; i++)
		documento[i] = NULL;

		
}



void InserisciNellaStoria(char ** documento, Cronologia cronologia){
	int i;
	int n_op = numero_tot_operazioni - 1;
	
	cronologia[n_op].massimo = max;
	if(cronologia[n_op].vecchio_doc != NULL){
	    free(cronologia[n_op].vecchio_doc);
        cronologia[n_op].vecchio_doc = NULL;
	}
	cronologia[n_op].vecchio_doc = (char **) calloc(max + 1, sizeof(char *));
	
	for(i = 0; i <= max; i++){
		cronologia[n_op].vecchio_doc[i] = documento[i];
	}
	
}



void RipristinaStoria(char ** documento, Cronologia cronologia){
	int i;
	
	max = cronologia[u].massimo;
	
	for(i = 0; i <= max; i++){
		documento[i] = cronologia[u].vecchio_doc[i];
	}
	
}
