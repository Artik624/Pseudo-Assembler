/*this file deals with labels , get labels , verify and add to symbols  */
#include "header.h"

char label[MAX_LABEL];

char *isLabel(char s[]){
    char *temp[MAX_LABEL];
    
    if((*temp = strchr(s,LABEL_DEF)) == NULL){/* check if label condition present*/
        return NULL;
    }
    else{
        int i;
        for(i = 0; s[i] != LABEL_DEF; i++){
            label[i] = s[i];
            if(i == 0 && !isalpha(label[i]))/*check if valid label name*/
                return NULL;
            
            if(i == MAX_LABEL)/*check if valid length*/
                return NULL;  
        }

        if(getAction(label) != NULL){/*check for saved word(action name)*/
            return NULL;/*MISSING OTHER SAVED WORDS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
        }
        if(getRegistry(label) != NULL)
            return NULL;
        
        if(isInstruction(label) != NULL)
            return NULL;
        
        
    }
   
    return (char*) label;  
}

void getLabels(char s[]){/*get all labels from current input and add to synbols  table*/
    int i, c = 0;
    char temp[MAX_LABEL];
    for(i = 0; s[i] != '\0' ; i++){
        temp[c]= s[i];/*copy each char to temp*/
        temp[c+1] = '\0';/*add end of  string to temp*/
        c++;  

        if(isLabel(temp) != NULL){/*check for label*/
            temp[c-1] = '\0';
            if(head == NULL){/*check if first label detected*/
                head = (symbols *)malloc(sizeof(symbols));/*allocate memory for first label in symbols table*/
                strcpy((char*)head->label, temp);/*copy the data*/
            }
            else
                addSymbol(head, temp);

            c = 0;/*reset temp*/
            continue;
        }

        if(strcmp(temp,instruct[3].name) == 0){
            temp[c] = '\0';

            if(head == NULL){/*check if first label detected*/
                head = (symbols *)malloc(sizeof(symbols));/*allocate memory for first label in symbols table*/
                strcpy((char*)head->label, s + strlen(temp));/*copy the data*/
                
            }
            else
                addSymbol(head, s + strlen(temp));

            c = 0;/*reset temp*/
            continue;
        }


    }  
}
