#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mm_malloc.h>

#define INITIAL_ADDRESS 100
#define ONE_BYTE_SIZE 8
#define ONE_WORD_SIZE 24

/*---------------------structers------------------------*/
typedef struct
{
    unsigned int Addressing_Mode;
    char *operand_value;

} operand;

struct symbols_table
{
    struct symbols_table *next;
    char *label;
    char *value;
    char *type_of_symbol;
    int address;
    int line;
    int L;
};

typedef struct
{
    char *name;
    unsigned int funct;
    unsigned int opcode;
    int numOfParams;

} command;

struct command_line
{
    char *label;        /*A pointer to the symbol_table*/
    const command *cmd; /* A pointer to the command in g_cmdArr */
    operand *operand_src;
    operand *operand_dest;
    struct command_line *next;
    int cLine;
    unsigned int A_R_E;
};

struct instruction_line
{
    char *label; /*A pointer to the symbol_table*/
    char *type_of_inst;
    int *info;
    struct instruction_line *next;
};

/* ****************************** structer to use in the Second Read ******************************/
typedef struct fullMemoryWord /* 24 bits */
{
    unsigned int A_R_E : 3;

    union memWordType
    {
        struct
        {
            unsigned int funct : 5;
            unsigned int regDest : 3;
            unsigned int modeDest : 2;
            unsigned int regSrc : 3;
            unsigned int modeSrc : 2;
            unsigned int opcode : 6;

        } instructionBits;

        unsigned int number : 21

    } wordVal;

} memWordCode;

/*------------------------functions - first pass----------------------------*/

int main_pass(char *); //going through a text file
int ignore_line(char *);
int go_through_line(char *);                                    //analyzng eache character throught the line
int check_if_com_or_inst(char *);                               //checking if it's a command or an instruction
int search_row_in_symbol_table(char *, struct symbols_table *); //searching for the adress of a specific label
int kind_of_addressing(operand *, char *, char *, char *);      //checking the type od addressing
int add_symbol(char *, char *, int, char *);                    //adding a new symbol to the symbols list

/*------------------------functions - second pass----------------------------*/

void completeLabelAddress(int IC, int DC, struct symbols_table *EntryTemp, struct symbols_table *dataTable, struct symbols_table *tempLabel, int *numOfEntries, struct instruction_line *instruction_line_list);
int countIllegalEntries(struct symbols_table *entryLabel, int *numOfEntries, struct symbols_table *LabelList);
struct symbols_table *searchLabel(char *labelName, struct symbols_table *LabelList);
int returnIntMemoryWord(memWordCode memory);
int returnModeOpType(operand op);
int regNum(operand op);
memWordCode lineMemWordCode(struct command_line line, struct symbols_table *LabelList);
void addWordToMemory(int *wordMemoryArr, int *memCount, memWordCode memory, int IC, int DC);
void pushdataToMemory(struct symbols_table *dataTable, int *wordMemoryArr, int *memCount, int DC);
void second_pass(char *fileName, int IC, int DC, int error, struct symbols_table *LabelList, struct command_line *comLine, struct instruction_line *instruction_line_list);

/*------------------------functions - symbols----------------------------*/

int insert_into_symbols_table(int, char *, char *, char *, struct symbols_table *, int, int);      //inserting a new node to the linked list of symbols
int insert_into_instruction_list(int, char *, char *, char *, struct instruction_line *);          //inserting a new node to the linked list of instructions
int insert_into_command_list(int, command *, char *, operand *, operand *, struct command_line *); //inserting a new node to the linked list of commands
void erase_symbol_table(struct symbols_table *);                                                   //erasing the whole symbols list
void erase_command_list(struct command_line *);                                                    //erasing the whole command list
void erase_instruction_list(struct instruction_line *);                                            //erasing the whole instruction list
void erase_instruction_line(struct instruction_line *);                                            //erasing the current node from the instruction line
void erase_command_line(struct command_line *);                                                    //erasing the current node from the command line

/*------------------------Commands List ------------------------*/
char command_list[17][3] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop", NULL};