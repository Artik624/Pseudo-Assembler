/*this file deals with actions , load library , verify and calculate */
#include "header.h"
#define OPCODE 6
#define RESOLUTION 2
#define REGISTRY 3
#define FUNCT 5
#define WORD_NO_SUFFIX 21
#define SUFFIX 3
extern int DC;
extern int IC;



void loadActions(){/*function loads the actions library and stores it in a an array of struct*/
    struct Actions *mov, *cmp, *add, *sub, *lea, *clr, *not, *inc, *dec, *jmp, *bne, *jsr, *red, *prn, *rts, *stop ;

    act = malloc(MAX_ACTIONS * sizeof(struct Actions));

    mov = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(mov->name ,"mov"); mov->funct = 0; mov->opcode = 0; mov->num_of_operands = 2;

    cmp = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(cmp->name , "cmp"); cmp->funct = 0; cmp->opcode = 1; cmp->num_of_operands = 2;

    add = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(add->name ,"add"); add->funct = 1; add->opcode = 2, add->num_of_operands = 2;

    sub = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(sub->name ,"sub"); sub->funct = 2; sub->opcode = 2; sub->num_of_operands = 2;

    
    lea = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(lea->name ,"lea"), lea->funct = 0, lea->opcode = 4, lea->num_of_operands = 2;

    
    clr = (struct Actions*)malloc(sizeof(struct Actions*)); 
    strcpy(clr->name , "clr"); clr->funct = 1; clr->opcode = 5; clr->num_of_operands = 1;

    
    not = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(not->name ,"not"); not->funct = 2; not->opcode = 5; not->num_of_operands = 1;

    
    inc = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(inc->name , "inc"); inc->funct = 3; inc->opcode = 5; inc->num_of_operands = 1;

    
    dec = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(dec->name ,"dec"); dec->funct = 4; dec->opcode = 5; dec->num_of_operands = 1;

    
    jmp = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(jmp->name ,"jmp"); jmp->funct = 1; jmp->opcode = 9; jmp->num_of_operands = 1;

    
    bne = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(bne->name ,"bne"); bne->funct = 2; bne->opcode = 9; bne->num_of_operands = 1;
    
    jsr = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(jsr->name ,"jsr"); jsr->funct = 3; jsr->opcode = 9; jsr->num_of_operands = 1;
    
    red = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(red->name ,"red"); red->funct = 0; red->opcode = 12; red->num_of_operands = 1;
    
    prn = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(prn->name ,"prn"); prn->funct = 0; prn->opcode = 13; prn->num_of_operands = 1;
    
    rts = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(rts->name ,"rts"); rts->funct = 0; rts->opcode = 14; rts->num_of_operands = 0;
    
    stop = (struct Actions*)malloc(sizeof(struct Actions*));
    strcpy(stop->name ,"stop"); stop->funct = 0; stop->opcode = 15; stop->num_of_operands = 0;
  
    act[0] = *mov;
    act[1] = *cmp;
    act[2] = *add;
    act[3] = *sub;
    act[4] = *lea;
    act[5] = *clr;
    act[6] = *not;
    act[7] = *inc;
    act[8] = *dec;
    act[9] = *jmp;
    act[10] = *bne;
    act[11] = *jsr;
    act[12] = *red;
    act[13] = *prn;
    act[14] = *rts;
    act[15] = *stop;

    
}


struct Actions *getAction(char s[]){/*checks if action is present in action library*/
    struct Actions *a;
    
    int i;
    for(i= 0; i < MAX_ACTIONS; i++){/*loop over all actions*/
       if ((strcmp(s, act[i].name)) == 0){/*if strings match*/
            a = (struct Actions*)malloc(sizeof(struct Actions*));
            *a = act[i];
            return  a;  /* 1 if found*/
       }
    }
    return NULL;/* 0 if not found*/
}


/*calculate words required for action statement*/
int calcActionWords(char action[], char line[], int index){
    
    int i  , c = 0 ;/* indecies*/
    int regCount = 0, words = 1, commaCount = 0;/*counters*/
    char temp[MAX_NAME_LENGTH];

    for(i = index; line[i] != '\0' ; i++){
        temp[c]= line[i];/*copy each char to temp*/
        temp[c+1] = '\0';/*add end of  string to temp*/
        c++; 

        if(line[i] == '#'){/*check for direct resolution*/
            char *ptr = strchr(line, '#');
            if(numInterpreter(ptr) != NULL){
                words++;

            }
            c= 0;
            continue;
        }
            

        if(line[i] == '&'){/*check for relative resolution*/
            if(strcmp(action, "jmp") == 0 || strcmp(action, "bne") == 0 || strcmp(action,"jsr") == 0){
                c = 0;
                for(i++; line[i] != '\0' ; i++){/*loop over label name afte operator &*/
                    temp[c]= line[i];/*copy each char to temp*/
                    temp[c+1] = '\0';/*add end of  string to temp*/
                    c++; 
                    
                    continue;
                }

                if(currentSymbol(temp)!= NULL){/*if label reserver memory*/
                        words++;
                    }

                if(currentSymbol(temp) == NULL){/*if label name no present , error message*/
                    printf("\n invalid label name %s\n", temp);
                    return 0;
                }
                return words;
            }
            
            else{
                printf("\naction %s is invalid for relative operand '&' \n", action);
                return 0; 
            }      
        }

        if(getRegistry(temp) != NULL){/*check registry */
            regCount++;
            c= 0;
            continue;
        }

        if(currentSymbol(temp) != NULL){/*check if label and  reserve memory */
            words++;
            c=0;
            continue;
        }

        if(line[i] == ',' ){/*check for commas*/
            commaCount++;
           
            
            if(getAction(action)->num_of_operands <= commaCount){/*check there are less commas than opearnds for action*/
                printf("\nnum of operands for action %s is %d\n", action, getAction(action)->num_of_operands);
                printf("\ninvalid syntax too many arguments for action %s", action);
                
            }
            c= 0;
            continue;
        }
    }
    
    return words;

}

/*convert action statement to bits */
void action2Bits(char action[], char line[], int ramCounter){
    symbols *labelPtr;
    struct Actions* actionPtr;
    int i , c = 0, wordsCounter = 0;/*counters*/
    int operands;
    int wordsForAction;
    int secondOperand = FALSE, labelFlag = FALSE, numFlag = FALSE, relativeFlag = FALSE;/*flags*/
    int numValue[2];/*num storage*/
    int IC = MEMORY_START + ramCounter; /*instruction counter for curremt free address*/
    char temp[MAX_LABEL];
    /*-----hold the relevant values calculated in the macros */
    char * immidiate_reolution = convert2binary(0,RESOLUTION);
    char *direct_reolution = convert2binary(1,RESOLUTION);
    char *relative_reolution = convert2binary(2,RESOLUTION);
    char *direct_registry_reolution = convert2binary(3,RESOLUTION);
    /*---- load with 0's as default ---- */
    
    char *srcResolution , *destResolution ,*srcRegistry ,*destRegistry;
    srcResolution = convert2binary(0,RESOLUTION);
    destResolution = convert2binary(0,RESOLUTION);
    srcRegistry = convert2binary(0,REGISTRY);
    destRegistry = convert2binary(0,REGISTRY);

    


    /* get the current action from library */
    actionPtr = getAction(action);
    
    operands = actionPtr->num_of_operands;

    
    wordsForAction = calcActionWords(action, line , 0);/*get number of words for statment */
    
    strcpy(ram[IC + wordsCounter].word, convert2binary(actionPtr->opcode, OPCODE));/*load current word with the opcode */

    for(i = 0; line[i] != '\0' ; i++){/*loop until end of line*/
         
        temp[c]= line[i];/*copy each char to temp*/
        temp[c+1] = '\0';/*add end of  string to temp*/
        c++;

        
        if(line[i] == ','){/*check if reached end of first operand*/
            if(numFlag == TRUE){/*if number was detected*/
                temp[c-1] = '\0';/*remove the comma */
                numValue[0] = atoi(temp);/*convert to int*/
            }
            c = 0;
            secondOperand = TRUE;
        }

        if(line[i] == '#' && secondOperand == FALSE){/*check for immidiate resolution for source */
            srcResolution = immidiate_reolution;/*store binary code  for source*/
            numFlag = TRUE;
            c = 0;
            
            
        }
        else if(line[i] == '#' && secondOperand == TRUE){/*check for immidiate resolution for destination */

            destResolution = immidiate_reolution;/*store binary code for destination*/
            numFlag = TRUE; 
            c = 0;
            
        }
    
        if(line[i] == '&' && secondOperand == FALSE){/*check for direct resolution for source*/
            relativeFlag = TRUE;
            if(operands ==1){
                secondOperand =1 ;
                destResolution = relative_reolution;/*store binary code for destination*/
            }
            else{
                srcResolution = relative_reolution;/*store binary code for source*/
                c = 0;
            }
            c = 0;
            
        }
        else if(line[i] == '&' && secondOperand == TRUE){/*/*check for direct resolution for destination*/
            relativeFlag= TRUE;
            c = 0;
            destResolution = relative_reolution;/*store binary code for destination*/
        }

        if(currentSymbol(temp) != NULL &&  secondOperand == FALSE ){/*check if direct resolution operand & first operand*/
            if(relativeFlag == FALSE){/*check if not  relative resolution*/
                if(operands == 1){/*if only one operand for action*/
                
                    secondOperand = TRUE;
                    labelPtr = currentSymbol(temp);
                    labelFlag = TRUE;
                    destResolution = direct_reolution;/*store code as destination*/
                }
                else{/*if more than 1 operand*/
                    labelPtr = currentSymbol(temp);
                    labelFlag = TRUE;
                    srcResolution = direct_reolution;/*store code for source*/
                }
            }
            else{
                labelPtr = currentSymbol(temp);
                labelFlag = TRUE;
            }
            
          
            
        }
        else if (currentSymbol(temp) != NULL && secondOperand == TRUE){/*check if relative resolution destination*/
            if(relativeFlag == FALSE){
                if(operands == 1){/*if only one operand for action*/
                
                    secondOperand = TRUE;
                    labelPtr = currentSymbol(temp);
                    labelFlag = TRUE;
                    destResolution = direct_reolution;/*store code as destination*/
                }
                else{/*if more than 1 operand*/
                    labelPtr = currentSymbol(temp);
                    labelFlag = TRUE;
                    srcResolution = direct_reolution;/*store code for source*/
                }
            }
            else{
                labelPtr = currentSymbol(temp);
                    labelFlag = TRUE;
            }
        }

        if(getRegistry(temp) != NULL && secondOperand == FALSE){/*check if registry resolution source*/
            struct Registry *regPtr;
            if(wordsForAction == 1 && operands == 1){/*if only one word and one operand for statment*/
                secondOperand = TRUE;
                
                regPtr = getRegistry(temp);

                destResolution = direct_registry_reolution;/*store binary code as destination*/
                destRegistry = convert2binary(regPtr->code, REGISTRY);/*store registry code */
                
            }
            else{/*if more than one words and operands*/
                
                struct Registry *regPtr = getRegistry(temp);
                srcResolution = direct_registry_reolution;/*store binary as source resolution*/
                srcRegistry = convert2binary(regPtr->code, REGISTRY);/*store binary as source registry*/
            }
            
        }
        else if(getRegistry(temp) != NULL && secondOperand == TRUE){/*check if registry resolution destination*/
        
            struct Registry *regPtr = getRegistry(temp);
            destResolution = direct_registry_reolution;/*store destination resolution code*/
            destRegistry = convert2binary(regPtr->code, REGISTRY);/*store destination registry code*/
        }

        if(numFlag == TRUE && secondOperand == FALSE){/*if number detected and first operand*/
            numValue[0] = atoi(temp);/*add the number to first array index*/
            
        }
        else if(numFlag == TRUE && secondOperand == TRUE){/*if the number is second operand , add it to second index*/
            numValue[1] = atoi(temp);
        
        }

        
        
    }/*end for loop*/

    /*add and append all binary codes to the first word*/
    strcat(ram[IC + wordsCounter].word, srcResolution);
    strcat(ram[IC + wordsCounter].word, srcRegistry);
    strcat(ram[IC + wordsCounter].word, destResolution);
    strcat(ram[IC + wordsCounter].word, destRegistry);
    strcat(ram[IC + wordsCounter].word, convert2binary(actionPtr->funct,FUNCT));
    strcat(ram[IC + wordsCounter].word, convert2binary(A,SUFFIX) );

    
    if(labelFlag == TRUE && relativeFlag == FALSE){/*if label present as operand*/
        wordsCounter++;/*add word counter*/
        strcpy(ram[IC + wordsCounter].word, convert2binary(labelPtr->address, WORD_NO_SUFFIX));/*add binary code to word at address*/
        strcat(ram[IC + wordsCounter].word, convert2binary(R, SUFFIX));

    }

    if(relativeFlag == TRUE && labelFlag == TRUE){/*if relative resolution & label were detected*/
        int addressGap = (labelPtr->address) - (IC + wordsCounter);/*calculate address gap*/
        wordsCounter++;
        strcpy(ram[IC + wordsCounter].word, convert2binary(addressGap, WORD_NO_SUFFIX));/*convert to binary and add to address*/
        strcat(ram[IC + wordsCounter].word, convert2binary(A, SUFFIX));/* add A for A,R,E*/
        
    }

    
    if(numFlag == TRUE){/* if number as operand*/
        if(secondOperand == FALSE){/*if first operand */
            wordsCounter++;
            strcpy(ram[IC + wordsCounter].word, convert2binary(numValue[0], WORD_NO_SUFFIX));
            strcat(ram[IC + wordsCounter].word, convert2binary(A, SUFFIX));
        }
        else{/*if second operand*/
        
            wordsCounter++;
            strcpy(ram[IC + wordsCounter].word, convert2binary(numValue[1], WORD_NO_SUFFIX));
            strcat(ram[IC + wordsCounter].word, convert2binary(A, SUFFIX));
        }
        
    } 
}

