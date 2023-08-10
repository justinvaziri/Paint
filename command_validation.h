#ifndef COMMAND_VALIDATION_H
    #define COMMAND_VALIDATION_H
    
    #include "board.h"
    #include <stdbool.h>
    #include <ctype.h>
    #include <math.h>
    #include <stdlib.h>
    #include <stdio.h>
   

    typedef struct Arguments_Struct {
        int row1; int row2;
        int col1; int col2;
        char row_col;
        int position;
        char file_name[50];
        FILE* file;
    } Arguments;

    void get_command(Board board, Arguments *args, char* command, char *command_character);
    bool check_command_type(Board board, char* command, Arguments *args, char *command_character);
    bool check_command_arguments(Board board, char* command, Arguments *args, char command_character, int alpha_chars);
    int num_digits(int num);

#endif