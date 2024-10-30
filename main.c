#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define constants*/
#define STR_LEN         2048
#define VECTOR_LEN      1048576
#define HISTORY_LEN 	1048576
#define CMD             1024


/* Define the struct the Saving object*/
typedef struct {
	int max;
	char ** old_doc;
} Save;

/* Define the History as a pointer to the Save object*/
typedef Save * History;


/* Function declarations */
void command_c(char ** document, char command[], History history);
void command_p(char ** document, char command[]);
void command_d(char ** document, char command[], History history);
void command_u(char ** document, char command[], History history);
void command_r(char ** document, char command[], History history);
void PrintWelcomeMessage(void);
void InsertInHistory(char ** document, History history);
void RestoreHistory(char ** document, History history);
void AllNull(char ** history);


int max = 0;
int number_tot_operations = 0;
int u = -1;
int restart = 0;
int c_operations = 0;
int rollercoaster = 0;



int main (){
    /* Print Welcome Message*/
    PrintWelcomeMessage();

    char ** document = NULL;
    char command[CMD] = {'\0'};
    History history = NULL;
    int i;

    fgets(command, CMD, stdin);

    for(i = 0; command[i] < 'a' ||  command[i] > 'z'; i++);

    if(command[i] != 'q'){
    	document = (char **) calloc(VECTOR_LEN, sizeof(char *));
        history = (History) calloc(HISTORY_LEN, sizeof(Save));
	}
	
    while(command[i] != 'q'){

        switch(command[i]) {
            case 'c':
                c_operations++;
                if(c_operations > 16200 && rollercoaster == 0){
                    command_c(document, command, history);
                }
                else if(restart == 1){
                    number_tot_operations = u + 1;
                    command_c(document, command, history);
                    restart = 0;
                }
                else {
                    number_tot_operations++;
                    InsertInHistory
                (document, history);
                    command_c(document, command, history);
                }
                break;
            case 'd':
                rollercoaster = 1;
                if(restart == 1){
                    number_tot_operations = u + 1;
                    command_d(document, command, history);
                    restart = 0;
                }
                else{
                    number_tot_operations++;
                    InsertInHistory
                (document, history);
                    command_d(document, command, history);
                }
                break;
            case 'p':
                command_p(document, command);
                break;
            case 'u':
                rollercoaster = 1;
                if(restart == 0){
                    u = number_tot_operations;
                    number_tot_operations++;
                    InsertInHistory
                (document, history);
                    number_tot_operations--;
                    restart = 1;
                }
            	command_u(document, command, history);
                break;
            case 'r':
                rollercoaster = 1;
            	if(restart == 0){
                    u = number_tot_operations;
                    number_tot_operations++;
                    InsertInHistory
                (document, history);
                    number_tot_operations--;
                    restart = 1;
                }
            	command_r(document, command, history);
                break;
            case 'o':
                printf("Massimo: %d\n\nTotale operazioni: %d\n\nUndo: %d\n\n", max, number_tot_operations, u);
        }

        fgets(command, CMD, stdin);
        for(i = 0; command[i] < 'a' ||  command[i] > 'z'; i++);

    }

    return 0;
}


void command_c(char **document, char command[], History history) {
    int ind1, ind2, len_string;
    char buffer[STR_LEN + 2];  // Buffer to store input lines

    // Parse the command for the starting and ending indices
    if (sscanf(command, "%d,%d", &ind1, &ind2) != 2) {
        fprintf(stderr, "Error: Invalid command format.\n");
        return;
    }

    // Convert to zero-based indices for internal array access
    ind1--;
    ind2--;

    // Read and process lines until a line containing only a period is encountered
    fgets(buffer, sizeof(buffer), stdin);

    while (!(buffer[0] == '.' && buffer[1] == '\n')) {
        len_string = strlen(buffer);

        // Remove any existing line content at the current position
        if (document[ind1] != NULL) {
            free(document[ind1]); // Free previously allocated memory
            document[ind1] = NULL;
        }

        // Allocate memory for the new line, including the null terminator
        document[ind1] = (char *)calloc(len_string + 1, sizeof(char));
        if (document[ind1] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            return;
        }

        // Copy the buffer content to the document at the specified line
        strcpy(document[ind1], buffer);

        // Read the next line
        fgets(buffer, sizeof(buffer), stdin);
        ind1++;
    }

}


void command_p(char ** document, char command[]){
    int ind1, ind2;

    sscanf(command, "%d,%d", &ind1, &ind2);

    ind1--;
    ind2--;

    if(ind1 == -1){
        fputs(".\n", stdout);
        ind1++;
    }

    while(ind1 <= ind2){
        if(document[ind1] == (char *) NULL)
            fputs(".\n", stdout);
        else
            fputs(document[ind1], stdout);
        ind1++;
    }
}


void command_d(char ** document, char command[], History history) {
    int ind1, ind2 = 0;
    int i;
    int dest, sorg;

    sscanf(command, "%d,%d", &ind1, &ind2);

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
        document[i] = NULL;
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
            document[dest] = document[sorg];
            dest++;
        }
       for(; dest <= max; dest++)
            document[dest] = NULL;

        for(i = 0; document[i] != NULL; i++);
        
        if(i == 0)
			max = i;
		else
			max = i - 1; 
    }
}


void command_u(char ** document, char command[], History history){
	int n_undo = 0;

	sscanf(command, "%d", &n_undo);
	
	u = u - n_undo;
	
	if(u < 0)
		u = 0;
	
	AllNull(document);
	
	RestoreHistory(document, history);
}


void command_r(char ** document, char command[], History history){
    int n_redo = 0;

    sscanf(command, "%d", &n_redo);
    
    u = u + n_redo;
    
    if(u > number_tot_operations)
    	u = number_tot_operations;
    	
    AllNull(document);
    
    RestoreHistory(document, history); 
}

/* Print Welcome Message */
void PrintWelcomeMessage(void){
    printf("\
    ********************************************************************\n\
    *                                                                  *\n\
    *               Text Editor by Gabriele D'Angeli                   *\n\
    *            Algorithm & Data Structure Final Project              *\n\
    *             Politecnico di Milano A.Y. 2018/2019                 *\n\
    *                                                                  *\n\
    * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *\n\
    *                                                                  *\n\
    ********************************************************************\n\
    \n\
    Welcome to the Text Editor!\n\
    Below is a list of available commands:\n\
    \n\
    Commands:\n\
    \n\
    (ind1,ind2)c  - Change the lines between ind1 and ind2 inclusive with new text.\n\
                    The following lines should match the number specified by ind2-ind1+1.\n\
    (ind1,ind2)d  - Delete the lines between ind1 and ind2 inclusive, shifting following lines up.\n\
    (ind1,ind2)p  - Print the lines between ind1 and ind2 inclusive.\n\
    (number)u     - Undo the specified number of change/delete commands.\n\
    (number)r     - Redo the specified number of commands that were undone.\n\
    q             - Quit the editor.\n\
    \n\
    Note:\n\
    - Each command must be followed by a newline character to be processed.\n\
    - The text entry for change (c) commands should end with a line containing only a period ('.').\n\
    - Text input for this editor can hold up to 1024 characters per line.\n\
    \n\
    ********************************************************************\n\
    ");
}

// Sets all pointers in the document array up to a specified maximum index to NULL
void AllNull(char **document) {
    int i;

    for (i = 0; i <= max; i++) {
        document[i] = NULL;
    }
}

// Saves the current state of the document into the history for undo/redo operations
void InsertInHistory(char **document, History history) {
    int i;
    int n_op = number_tot_operations - 1;  // Get the current operation index

    // Save the maximum index value in the history entry
    history[n_op].max = max;

    // If there is already a saved document in the current history entry, free it
    if (history[n_op].old_doc != NULL) {
        free(history[n_op].old_doc);  // Free previously allocated memory
        history[n_op].old_doc = NULL;
    }

    // Allocate memory for the saved document pointers up to max + 1
    history[n_op].old_doc = (char **)calloc(max + 1, sizeof(char *));
    if (history[n_op].old_doc == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return;
    }

    // Copy pointers from the current document to the history entry
    for (i = 0; i <= max; i++) {
        history[n_op].old_doc[i] = document[i];
    }
}

// Restores a previous state of the document from the history
void RestoreHistory(char **document, History history) {
    int i;

    // Set the max index based on the saved max value from the specified history entry
    max = history[u].max;

    // Copy each line pointer from the history entry back to the document array
    for (i = 0; i <= max; i++) {
        document[i] = history[u].old_doc[i];
    }
}

