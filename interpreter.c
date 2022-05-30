/*the interpreter has several function mostly used to understand the input , or convert it as needed */

#include "header.h"
extern int DC;
extern int IC;


char *getLine(char s[]){/* get a line  from input and change it */
    int i, j = 0;
    char c ;
    char temp[MAX_STATEMENT];
    char *line;
    for(i = 0; i < strlen(s) || i == MAX_STATEMENT - 1;i++) {
        if(s[i] == ';'){
            return (char*)NULL;
        }
        if(isspace(s[i]) == 0){
            c = s[i];
            temp[j++] = c;
            temp[j] = '\0'; 
        }
    }
    
    line = malloc(sizeof(temp));
    line = temp;
    
    return line;


}

void getLines(FILE *fp){/*get all lines from input and store each line in array lineptr*/
    char line[MAX_STATEMENT];
    int lineCount = 0;
    char  *p;
    char s[MAX_STATEMENT];

    while(fgets(line, MAX_STATEMENT, fp)) {
    
        if(getLine(line) != NULL){
            
            p = getLine(line);
            strcpy(s,p);
            if(strlen(s) < 1 || strlen(s) > MAX_STATEMENT){
                continue;
            }
            if(lineCount < MAX_INPUT){
                p = (char*)malloc(strlen(s));
                strcpy(p,s);
                lineptr[lineCount++] = p;
            }
        }
    }
}

char * numInterpreter(char s[]){/*check number values are valid*/
    int i, c = 0;
    int negative = FALSE, numDetected = FALSE;/*flags*/
    char *temp;
    temp = (char*)malloc(strlen(s));
    
    for(i =0; s[i] != '\0'; i++){

        if(s[i] == ',' && strlen(temp) < 1){/*check if comma present before number*/
            printf("\ninvalid syntax\n");
            break;
        }
        else if(s[i] == ','){/*check if end of first parameter*/
            return temp;
            
        }
        if(s[i] == '#')/*ignore */
            continue;

        if(s[i] == '+')/*ignore */
            continue;
        
        if(s[i] == '-'){/*check if negative*/
            negative = TRUE;
            temp[c++] = '-';
            temp[c] = '\0';
            continue;
        }

        if(isdigit(s[i]) != 0){/*check if num*/
            numDetected = 1;
            temp[c++] = s[i];
            temp[c] = '\0';
        }
        
    }
    if(strlen(temp) == 0)/*if no numbers detected*/
        return NULL;
    if(negative == TRUE && numDetected == FALSE)/*if negative but no numbers*/
        return NULL;
    else
        return temp; /*return the number as char pointer*/  
         
}



void statementInterpreterFirst(char s[]){
    
    int i, c = 0;
    int wordsCounter; 
    int label = FALSE;/*flag*/
    int address;
    char temp[MAX_LABEL];
    symbols * curr;

    for(i = 0; s[i] != '\0' ; i++){/*loop over the line*/
        
        
        temp[c]= s[i];/*copy each char to temp*/
        temp[c+1] = '\0';/*add end of  string to temp*/
        c++;  
        
        if(s[i] == ','){
            c = 0;/*reset temp*/
            continue;
        }
            
    
        if(currentSymbol(temp) != NULL){/*check for label*/

            label = TRUE;
            
            curr = currentSymbol(temp);/*identify current symbol */
            i++;/*skip ':' coz already checked label validity*/
            c = 0;/*reset temp*/
            continue;
        }

        if(getAction(temp) != NULL){ /*if action */
            int address;
            int words;
            wordsCounter = 1;
            words = calcActionWords(temp, s, i+1 );
            strcpy(curr->type, "code");/*add symbol type*/
            
            while(wordsCounter <= words){
                address = programCounter();
                if(label == TRUE){
                    curr->address =  address;
                    label = FALSE;
                }
                ram[address].address = address;
                wordsCounter++;
            }
            
            c = 0;
            continue;
        }

        if(isInstruction(temp) != NULL){
            int words;
            if(strcmp(temp, instruct[2].name) == 0){
                if(currentSymbol(s + strlen(temp)) == NULL){
                    printf("\ninvalid label name %s for entry\n", s + strlen(temp));
                    break;
                }
                else
                {
                    curr = currentSymbol(s + strlen(temp));
                    curr->entryFlag = TRUE;
                    break;
                }   
            }

            if(strcmp(temp, instruct[3].name) == 0){
               
                curr = currentSymbol(s + strlen(temp));
                strcpy(curr->type, "extern");
                curr->externFlag = TRUE;
                
                break;
            }


            wordsCounter = 1;
            
            
            words = calcInstructWords(temp, strchr(s,INSTRUCTION_DEF) + strlen(temp));
            strcpy(curr->type, "data");
            while(wordsCounter <= words){
                address = programCounter();
                if(label == TRUE){
                    curr->address =  address;
                    label = FALSE;
                }
                wordsCounter++;
                ram[address].address = address;
            }
            i += strlen(strchr(s,INSTRUCTION_DEF) +strlen(temp));/*jump to end of arguments passed for instruction*/
            c = 0;
        }
    }    
}

void statementInterpreterSecond(char s[]){
    
    int i,j, c = 0;
    char temp[MAX_NAME_LENGTH];
    
   
    for(i = 0; s[i] != '\0' ; i++){
        if(strchr(s, LABEL_DEF) != NULL){/*if label definition present ignore the label skip to the end of it*/
            s = (strchr(s, LABEL_DEF))+1;
        }

        temp[c]= s[i];/*copy each char to temp*/
        temp[c+1] = '\0';/*add end of  string to temp*/
        c++;
        

        if(getAction(temp) != NULL){
            action2Bits(temp, s + strlen(temp), IC);/*if action detected , send action name and values */
            
            IC += calcActionWords(temp, s , i+1);
            break;
        }

        if(isInstruction(temp) != NULL){
            int addressGap;
            if(strcmp(temp, instruct[2].name) == 0 ||strcmp(temp, instruct[3].name) == 0){
                break;
            }
            
            addressGap = calcInstructWords(temp, strchr(s,INSTRUCTION_DEF) + strlen(temp) );
            instruction2Bits(temp, s + strlen(temp), DC);
            
            DC +=  addressGap;
            
            break;
        }
    }
    for(i = MEMORY_START + IC, j = 0; j < DC; i++, j++){
        ram[i].address = i;
        strcpy(ram[i].word, data[j].word);
    }


}

char* convert2binary(int decimal, int length){
    char *b;
    int i;
    int negative = FALSE;
    if(decimal < 0){
        
        negative = TRUE;
        decimal = ~decimal;  
    }
    
    length += 1;
     
    b= (char*)malloc(length * sizeof(char));
    
    i = length - 2;
    
    b[length - 1] = '\0';
    
    while (decimal / 2 > 0 || i >= 0){  
        if(decimal / 2 >= 0){
            b[i] = (decimal % 2) + 48 ;
            decimal = decimal / 2 ;
        }
        else{
            b[i] = '0';
        }
        i--;
    
    }

    if(negative == TRUE){
        
        for(i = 0; i < strlen(b); i++){
            if(b[i] == '0')
                b[i] = '1';

            else if(b[i] == '1')
                b[i] = '0';
        }
     
    }
    return (char *) b;  
}

void bin2Hex(char s[], int index){
    char *hex;
    char temp[4];
    int i , c = 0;
    hex = (char*)malloc( 10 * sizeof(char));
    hex[0] = '\0';
    
    
    
    for(i = 0; i <= strlen(s);){
        temp[c++] = s[i++];
        temp[c] = '\0';
        
        
        if(i > 0 && (i % 4 == 0) ){
            c = 0;
            if(getHex(temp) != NULL){
                if(hex[0] == '\0'){
                    
                    strcpy(hex, getHex(temp)) ; 
                }
                else{
                    
                    strcat(hex, getHex(temp)) ; 
                }
                
            }
            
        }

    }
    
    ram[index].hex = hex;
    
    
}






