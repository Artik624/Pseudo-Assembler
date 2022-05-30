/*main function gets input from user via commamd line arguments 
calls  all required functions for program to use before before doing anything
in the end the function writes to files 
*/
#include "header.h"
#define fileNameLength 30
int *DC = 0;
int *IC = 0;
int main(int argc, char *argv[]){
    
    symbols *cur;
    FILE *fp, *ent , *ext , *this;
    int i;
    int fileCounter = argc -1;
    int loadersFlag =  0;
    char extName[fileNameLength];
    char entName[fileNameLength];
    char thisName[fileNameLength];
    
    head = NULL;
    while(fileCounter > 0){
        fp =  fopen(argv[fileCounter],"r");

        if(fp == NULL){
            printf("\ncouldnt open file %s\n",argv[fileCounter]);
            fileCounter--;
            continue;
        }
        
        if(loadersFlag == 0){
            loadActions();/*load actions library*/
            loadRegistry();/*load registry library*/
            loadInstructions();/*load instructions library*/
            loadersFlag = 1;
        }
        
        getLines(fp);/*get lines from input*/
        hexTable();

        
        
        for(i = 0; lineptr[i] != NULL; i++){
            getLabels(lineptr[i]);
        }
        
        for(i = 0; lineptr[i] != NULL; i++){
            statementInterpreterFirst(lineptr[i]);
        }

        
        cur= head;
        
        for(i = 0; lineptr[i] != NULL; i++){
            statementInterpreterSecond(lineptr[i]);
        }

    
        

        
        
        strcpy(entName, argv[fileCounter]);
        strcat(entName,".ent");
        ent = fopen(entName, "w");

        strcpy(extName, argv[fileCounter]);
        strcat(extName,".ext");
        ext = fopen(extName, "w");

        strcpy(thisName, argv[fileCounter]);
        strcat(thisName,".ob");
        this = fopen(thisName, "w");

        cur = head;
        while (cur != NULL){
            if(cur->entryFlag == TRUE){
                fprintf(ent, "%s %d\n", (char*)cur->label , cur->address);
                
            }
            if(cur->externFlag == TRUE){
                fprintf(ext,"%s\n", (char*)cur->label);
                
            }

            cur = cur->next;
        }
        fclose(ent);
        fclose(ext);

        

        for(i = 0; ram[MEMORY_START + i].word[0] != '\0'; i++){
            bin2Hex(ram[MEMORY_START + i].word, MEMORY_START + i);
            fprintf(this, "%d  %s\n", ram[MEMORY_START + i].address,ram[MEMORY_START + i].hex );
            
            
            
        }

        
        
        fclose(this);

        fileCounter--;

        
    }
    
    printf("\nprogram finished succefully\n");

    return 0;
    
}


    


