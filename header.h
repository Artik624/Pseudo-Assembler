#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NAME_LENGTH 10
#define MAX_ACTIONS 16
#define MAX_INSTRUCTIONS 4
#define MAX_LABEL 32
#define MAX_INPUT 1000 /* max size of input line or total lines*/
#define MAX_STATEMENT 80 /* max length of a line*/
#define WORD_LENGTH 25
#define MAX_REGISTRY 8
#define MEMORY_START 100
#define MAX_MEMORY 2^21
#define MAX_DC_MEMORY 1000 /*memory slots for data , assuming there wont be more than a 1000 */ 
#define INSTRUCTION_DEF '.'
#define LABEL_DEF ':'
#define A 4
#define R 2
#define E 1
#define TRUE 1
#define FALSE 0


/*static int IC ;counts the addresses used 
static int  DC;*/


typedef char word[WORD_LENGTH];/*memory word*/



/*----------------Registries defenition----------------------------*/
struct Registry/*define a registry*/
{
    char name[MAX_NAME_LENGTH];
    int code;
};
struct Registry *reg;
/*struct Registry reg[MAX_REGISTRY];array of registries*/

/*-----------------------------------------------------------------*/



/*---------------Actions defenition--------------------*/
struct Actions{/*define an action */
    char name[MAX_NAME_LENGTH];
    int funct;
    int opcode;
    int num_of_operands;
};
struct Actions * act;
/*----------------------------------------------------*/


/*---------------Instructions defenition--------------------*/
struct Instructions{/*define an action */
    char name[MAX_NAME_LENGTH];
    int num_of_param;
};
struct Instructions *instruct;/*array of actions*/
/*----------------------------------------------------*/

/*-------------define a memory slot------------------*/
struct Mem_Address{
    int address;
    word word; 
    char *hex;
    
    
};
/*------------------------------------------------*/
struct Mem_Address ram[MAX_MEMORY];/*array of addresses */
struct Mem_Address data[MAX_DC_MEMORY];/*array for data*/

/*------------define symbols table--------------------------*/
typedef struct symb {
    char *label[MAX_LABEL];
    int address;
    char type[MAX_NAME_LENGTH];
    int externFlag;
    int entryFlag;
    struct symb *next;
}symbols; 
symbols *head;


struct hex{
        char *binary;
        char *hex;
    };
    struct hex *map;

/*---------------------------------------------------------*/


char *lineptr[MAX_INPUT];/*array of statments */


/*-----------get input */
void getLines(FILE *fp);/*function to get lines from input*/
char *getLine(char s[]);/*function toget one line after removing spaces etc.*/
void getLabels(char s[]);/*get all labels in program*/

/*--- loaders */
void loadActions();/*load actions library*/
void loadRegistry();/*registry library*/
void loadInstructions();/*instruction library*/
void hexTable();/*hex values table*/

/*----getters*/
struct Registry *getRegistry(char s[]);/*get a registry item*/
symbols *currentSymbol();/*get current symbol*/
char *isInstruction(char s[]);/*check if valid instruction name*/
struct Actions *getAction(char *s);/*get actions item*/
char *getHex(char s[]);/*get hex for hex table*/


/*---verifications */
char *isLabel(char s[]);/*check if a label name*/
char * numInterpreter(char s[]);/*verify number value*/

/*---actions */
void addSymbol(symbols *head, char s[]);/*add ne wsymbol to symbols table*/
int calcActionWords(char action[], char line[], int index);/*calculate words for action*/
int calcInstructWords(char instructName[], char line[]);/*calculate instruction words*/
char* convert2binary(int decimal, int length);/*convert decimals to numbers*/
void action2Bits(char action[], char line[], int words);/*convert action statement to bits*/
void instruction2Bits(char instruction[], char values[], int DC );/*convert instruction statement to bits*/
void bin2Hex(char s[], int index);/*convert binary values to hex*/


/*---assembler loops */
void statementInterpreterFirst(char s[]);/*first loop of assembler*/
void statementInterpreterSecond(char s[]);/*second loop of assembler*/


int programCounter();/*PC next free memore counter*/