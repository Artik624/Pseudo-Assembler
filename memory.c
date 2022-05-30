/*this file deals with memory in general */
#include "header.h"
static int pc = MEMORY_START;



void loadRegistry(){ 
    struct Registry *r0;
    struct Registry *r1;
    struct Registry *r2;
    struct Registry *r3;
    struct Registry *r4;
    struct Registry *r5;
    struct Registry *r6;
    struct Registry *r7;

    reg = malloc(MAX_REGISTRY * sizeof(struct Registry));   

    r0 = (struct Registry*)malloc(sizeof(struct Registry));
    strcpy(r0->name , "r0"); r0->code = 0;


    
    r1 = (struct Registry*)malloc(sizeof(struct Registry));
    strcpy(r1->name , "r1"); r1->code = 1;

    
    r2 = (struct Registry*)malloc(sizeof(struct Registry));
    strcpy(r2->name , "r2"); r2->code = 2;

    
    r3 = (struct Registry*)malloc(sizeof(struct Registry));
    strcpy(r3->name , "r3"); r3->code = 3;

    
    r4 = (struct Registry*)malloc(sizeof(struct Registry));
    strcpy(r4->name , "r4"); r4->code = 4;

    
    r5 = (struct Registry*)malloc(sizeof(struct Registry));
    strcpy(r5->name , "r5"); r5->code = 5;

    
    r6 = (struct Registry*)malloc(sizeof(struct Registry));
    strcpy(r6->name , "r6"); r6->code = 6;

    
    r7 = (struct Registry*)malloc(sizeof(struct Registry));
    strcpy(r7->name , "r7"); r7->code = 7;

    reg[0] = *r0;
    reg[1] = *r1;
    reg[2] = *r2;
    reg[3] = *r3;
    reg[4] = *r4;
    reg[0] = *r5;
    reg[5] = *r0;
    reg[6] = *r6;
    reg[7] = *r7;
}

int programCounter(){
    
    return pc++;
}

/*add new synmbol to synbols table*/
void addSymbol(symbols *head, char s[]){    
        symbols * cur = head;
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = (symbols *)malloc(sizeof(symbols));
        strcpy((char*)cur->next->label, s);
        cur->entryFlag = 0;
        cur->externFlag = 0;
}

/*get current label from symbols table*/
symbols *currentSymbol(char s[]){
    symbols * curr = head;
    
    while(curr != NULL){
        if(strcmp((char*)curr->label,s) == 0){
            return curr;
        }
            
        curr = curr->next;
    }
    return NULL;
    
}

/*get a registry from library*/
struct Registry *getRegistry(char s[]){
    struct Registry *r;
    int i;
    for(i = 0; i < MAX_REGISTRY; i++){
        if((strcmp(s, reg[i].name)) == 0){
            r = (struct Registry*)malloc(sizeof(struct Registry));
            *r = reg[i];
            return r;/* if found*/
        }
    }
    return NULL;/* if not found*/
}

void hexTable(){
    
    struct hex *zero, *one, *two, *three, *four, *five, *six, *seven, *eight, *nine, *a, *b, *c, *d, *e, *f;;
    map = malloc( 16 * sizeof(struct hex));

    zero = (struct hex*)malloc(sizeof(struct hex*));
    one = (struct hex*)malloc(sizeof(struct hex*));
    two = (struct hex*)malloc(sizeof(struct hex*));
    three = (struct hex*)malloc(sizeof(struct hex*));
    four = (struct hex*)malloc(sizeof(struct hex*));
    five = (struct hex*)malloc(sizeof(struct hex*));
    six = (struct hex*)malloc(sizeof(struct hex*));
    seven = (struct hex*)malloc(sizeof(struct hex*));
    eight = (struct hex*)malloc(sizeof(struct hex*));
    nine = (struct hex*)malloc(sizeof(struct hex*));
    a = (struct hex*)malloc(sizeof(struct hex*));
    b = (struct hex*)malloc(sizeof(struct hex*));
    c = (struct hex*)malloc(sizeof(struct hex*));
    d = (struct hex*)malloc(sizeof(struct hex*));
    e = (struct hex*)malloc(sizeof(struct hex*));
    f = (struct hex*)malloc(sizeof(struct hex*));

    zero->hex = "0";zero->binary = "0000";
    one->hex = "1";one->binary = "0001";
    two->hex = "2"; two->binary = "0010";
    three->hex = "3";three->binary = "0011";
    four->hex = "4";four->binary = "0100";
    five->hex = "5";five->binary = "0101";
    six->hex = "6";six->binary = "0110";
    seven->hex ="7";seven->binary = "0111";
    eight->hex = "8";eight->binary = "1000";
    nine->hex = "9";nine->binary = "1001";
    a->hex = "a";a->binary = "1010";
    b->hex = "b";b->binary = "1011";
    c->hex = "c";c->binary = "1100";
    d->hex = "d";d->binary = "1101";
    e->hex = "e";e->binary = "1110";
    f->hex = "f";f->binary = "1111";

    
    map[0] = *zero;
    map[1] = *one;
    map[2] = *two;
    map[3] = *three;
    map[4] = *four;
    map[5] = *five;
    map[6] = *six;
    map[7] = *seven;
    map[8] = *eight;
    map[9] = *nine;
    map[10] = *a;
    map[11] = *b;
    map[12] = *c;
    map[13] = *d;
    map[14] = *e;
    map[15] = *f;
}

/*get relevant hex values from hex table*/
char *getHex(char s[]){
    int i;
    for(i = 0; i < 16; i++){

        if(strcmp(s, map[i].binary) == 0){
            
            char *h = malloc(sizeof(map[i].hex));
            h = map[i].hex;
            return (char*)h ;
        }
    }
    return NULL;
}


