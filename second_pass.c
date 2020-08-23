#include "MAIN.h"
#include "error_check.h"

typedef struct
{
    char *func_name;
    int func_num;
    int op_code;
} func_table;

func_table func_table_1[] = {
    {"mov", NULL, 0}, {"cmp", NULL, 1}, {"add", 1, 2}, {"sub", 2, 2}, {"lea", NULL, 4}, {"clr", 1, 5}, {"not", 2, 5}, {"inc", 3, 5}, {"dec", 4, 5}, {"jmp", 1, 9}, {"bne", 2, 9}, {"jsr", 3, 9}, {"red", NULL, 12}, {"prn", NULL, "13"}, {"rts", NULL, 14}, {"stop", NULL, 15}

};

void completeLabelAddress(int IC) 
{
    symbols_table *tempLabel = labelList;

	/* Search in the array for .entry / .data / .string label */
	while (tempLabel)
    {    
		if (!strcmp(tempLabel->type_of_symbol,"entry"))
        {
            if (!tempLabel->address)
            {
			    /* Increase the address */
			    tempLabel->address += INITIAL_ADDRESS + IC;
            }
		}
        else if (!strcmp(tempLabel->type_of_symbol,"data") || !(tempLabel->type_of_symbol,"string"))
        {
			/* Increase the address */
			tempLabel->address += INITIAL_ADDRESS + IC;
		}

        tempLabel = tempLabel->next;
    }

}


/* check if there is an illegal entry label */
int countIllegalEntries() 
{
	int errorFlag = 0 ;
	symbols_table *entryLabel = entryLabelsList;
    symbols_table *labelToComper = labelList;

	while (entryLabel) 
    {
        if(!defined_label(entryLabel->label, entryLabel->line))
        {
            show_error(undifinedLabel, entryLabel->line);
            errorFlag++;
        }
        else
        {
        
            while (labelToComper)
            {
                if (!strcmp(entryLabel->label, labelToComper->label))
                {
			        if (!strcmp(labelToComper->type_of_symbol, "exstern")) 
                    {
				        printError("error in line: %d The parameter .entry can't be external label.", entryLabel->line);
				        errorFlag++;
			    
                    }
                }
            
                labelToComper = labelToComper->next;
            }
            
        }

        entryLabel = entryLabel->next;

	}
    return errorFlag;
}

int entryLabelAlreadyInList(char *entryLabelName) 
{
    symbols_table *tempEntryLabel = labelList;

	while (tempEntryLabel) 
    {
		if (!strcmp(entryLabelName, tempEntryLabel->label))
        {
			return TRUE;
		}

        tempEntryLabel = tempEntryLabel->next;
	}
	return FALSE;
}



