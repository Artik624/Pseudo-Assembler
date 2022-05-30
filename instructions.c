/*this file deals with instructions , load library , verify and calculate */
#include "header.h"
#define WORD 24
extern int DC;
extern int IC;
void loadInstructions(){
    struct Instructions *data ;
    struct Instructions *string ;
    struct Instructions *entry;
    struct Instructions *ext;

    instruct = malloc(MAX_ACTIONS * sizeof(struct Instructions));

    data = (struct Instructions*)malloc(sizeof(struct Instructions));
    strcpy(data->name , ".data");

    string = (struct Instructions*)malloc(sizeof(struct Instructions));
    strcpy(string->name , ".string"); string->num_of_param = 1;
 
    entry = (struct Instructions*)malloc(sizeof(struct Instructions));
    strcpy(entry->name , ".entry"); string->num_of_param = 1;

    ext = (struct Instructions*)malloc(sizeof(struct Instructions));
    strcpy(ext->name , ".extern"); ext->num_of_param = 1;

    instruct[0] = *data;
    instruct[1] = *string;
    instruct[2] = *entry;
    instruct[3] = *ext;
}

char *isInstruction(char s[]){
    int i;
    char *temp ;

    if((temp = strchr(s,INSTRUCTION_DEF)) == NULL){/*check if instruction condition present*/
            return (char*)NULL;                                /* and assign pointer temp to that spot*/
    }
    else{
        for(i = 0; i < MAX_INSTRUCTIONS; i++){
            if(strncmp(temp, instruct[i].name,strlen(instruct[i].name)) == 0){
                    return (char*)instruct[i].name;
            }/*check if names match*/
                
        }  
    }
    return (char*)NULL;   
}

int calcInstructWords(char instructName[], char line[]){
    int i = 0, c = 0;/*indecies*/
    int words = 0;/*words counter*/
    char temp[MAX_NAME_LENGTH];
    
    if (strcmp(instructName,instruct[0].name) == 0){/* if instruction is of data type */
        

        while(line[i] != '\0'){/*loop until end of line*/
            if(line[i] == ','){/*/ if encountered a comma */
                
                if(numInterpreter(temp) != NULL){/*check if value is of number type */
                    words++;/*count word for that number*/
                }
                else{/*if not a number*/
                    
                    return 0;
                }
                c = 0;
                i++;/*skip the comma and continue checkung the values*/
                continue;
            }
            temp[c++] = line[i++];
            temp[c] = '\0';
        }
        if(numInterpreter(temp) != NULL){
            words++;
        }
        return words;
        
    }
    

    else if (strcmp(instructName, instruct[1].name) == 0){/*if instruction is of string type */
        int quoteCount = 0;
        
        while(line[i] != '\0' || quoteCount < 2){/*loop until end of line or 2 quotes */
            
            if(line[i] == '\"'){/*if a quote , count it and skip tothe next value*/
                quoteCount++;
                i++;
                continue; 
            }
            words++;
            i++;

        }
        if(quoteCount == 2 && i < strlen(line)){/*if there are 2 quotes and havent reached end of line*/
            printf("\ninvalid syntax for %s , argumantes after closing \"", instructName);
            return -1;
        }
        else if(quoteCount == 2 && line[i] == '\0'){
            words++;
            return words;
        }
 
    }
    return 0;
}

void instruction2Bits(char instructName[], char values[], int DC ){
    int i = 0, c = 0;
    int wordsCounter = 0;


    if (strcmp(instructName,instruct[0].name) == 0){/* if instruction is of data type */
        
        char *temp;
        temp = (char*)malloc(strlen(values));
        
        
        while(values[i] != '\0'){/*loop until end of line*/
            
            
            if(values[i] == ','){/*/ if encountered a comma */
                if(numInterpreter(temp) != NULL){/*check if value is of number type */
                   
                    strcpy(data[DC + wordsCounter].word, convert2binary(atoi(numInterpreter(temp)), 24));
                    data[DC + wordsCounter].address = DC + wordsCounter;
                    wordsCounter++;
                }
                
                c = 0;
                i++;/*skip the comma and continue checkung the values*/
                
                continue;
            }
            temp[c++] = values[i++];
            temp[c] = '\0';
            
        }
        
        if(numInterpreter(temp) != NULL){
            strcpy(data[DC + wordsCounter].word, convert2binary(atoi(numInterpreter(temp)), 24));
            data[DC + wordsCounter].address = DC + wordsCounter;
            wordsCounter++;
        }
       
    }
    

    if(strcmp(instructName, instruct[1].name) == 0){/*string*/
        int quoteCount = 0;
        
        while(values[i] != '\0' || quoteCount < 2){/*loop until end of line or 2 quotes */
            
            if(values[i] == '\"'){/*if a quote , count it and skip tothe next value*/
                quoteCount++;
                i++;
                continue; 
            }
            
            data[DC + wordsCounter].address = DC + wordsCounter;
           
            strcpy(data[DC + wordsCounter].word, convert2binary(values[i], WORD));
            wordsCounter++;
            i++;

        }
       
        data[DC + wordsCounter].address = DC + wordsCounter;
        strcpy(data[DC + wordsCounter].word, convert2binary(0, WORD));
        wordsCounter++;
    }

}


