#include "MAIN.h"
#include "error_check.h"



int main_pass(char *filename)
{
    FILE *fd;
    int line_count = 0;
    char temp[81];
    const char s[2] = " ";
    char *token;

    fd = fopen(filename, "r");

    if (fd == NULL)
    {
        printf("Could not open file %s", filename);
        return 1;
    }

    while (fgets(temp, max_row_len + 1, fd) != NULL)

    {
        line_count++;
        error = 0;
        symbols_table *symbols_table = NULL;
        token = strtok(temp, s);

        //checking if the length of the line is more than 80 characters
        if (temp[81] != '/n')
        {
            show_error(20, line_count);
        }
        else
        {
            if (ignore_line(token) == 0)
            {
                go_through_line(token, symbols_table);
            }
        }

        fclose(filename);

        second_pass();

        return 0;
    }

    //checking if it's an empty line or a comment line
    int ignore_line(char *token)
    {

        return (skip_white_space(token) == NULL) || (strcmp(token, ";"));
    }

    //analyzing what's in the current line
    int go_through_line(char *token, symbols_table *symbols_table)
    {
        char *temp_label = NULL;
        char *temp_com_or_inst;

        //checking if there's a label and taking care of it
        if (strchr(str, ':') != NULL)
        {
            if (legal_label(token) == 1)
            {
                temp_label = token;
            }
        }

        token = strtok(NULL, s)

            if (check_if_com_or_inst(token) == 1)
        {
            temp_com_or_inst = "data";

            if (strcmp(token, ".data"))
            {
            }

            else if (strcmp(token, ".string"))
            {
            }

            else if (strcmp(token, ".extern"))
            {
            }
            /*if it's a .entry */
            else
            {

                return 0;
            }
        }

        else
        {
            temp_com_or_inst = "code";
            if (name_function() == 1)
            {
            }
            else
            {
                return 0;
            }
        }

        if (temp_label != NULL)
        {
            insert_into_symbols_table(temp_label, temp_com_or_ins);
        }

        token = strtok(NULL, s)

            if (token != NULL)
        {
            token = strtok(NULL, s)

                if (token != NULL)
            {
            }
        }
    }
}

//determine if it's a command line or a instruction line
int check_if_com_or_inst(char *token)
{

    //if it's an instruction
    if (strchr(str, '.') != NULL)
    {
        return 1;
    }
    //if it's a command
    return 0;
};

int skip_white_space(char *token)
{
    char temp = *token;
    while ((isspace() != 0) && (token != NULL))
    {
        token = ++token;
        temp = *token;
    }
    return 0;
}
