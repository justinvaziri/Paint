#include "command_validation.h"
#include "input_validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void get_command(Board board, Arguments *args, char* command, char *command_character) {
    
    /**
        Prompts the user for the commands until program is quitted. Each input is validated
        by this function.

        @param board: a board struct that contains all the data for a board/canvas
        @param args: a pointer to an arguments struct that contains variables for all possible command arguments
        @param command: the user input stored as a string
        @param command_character: a pointer to the first character the user inputs; indicates command type
    */

    do {
        print_board(board);
        printf("Enter your command: ");
        fgets(command, 100, stdin);
    } while(!check_command_type(board, command, args, command_character));
}

bool check_command_type(Board board, char* command, Arguments *args, char *command_character) {
    
    /**
        Checks if the command character is valid and if the input entered is actually something usable.
        Then it checks if the command arguments are valid.

        @param board: a board struct that contains all the data for a board/canvas
        @param args: a pointer to an arguments struct that contains variables for all possible command arguments
        @param command: the user input stored as a string
        @param command_character: a pointer to the first character the user inputs; indicates command type
        @return: true if the command is valid
    */
    
    int num_commands = 9;
    char* command_type = "qhweradsl";
    int command_length;
    
    if(command == NULL) { //nothing was entered
        return false;
    }
    else {
        command_length = strlen(command);
    }

    int args_read = sscanf(command, " %c", command_character);
    if(args_read == 0) {
        return false;
    }

    int alpha_chars = 0;
    if(*command_character == 'l' || *command_character == 's') {
        for(int i = 0; i < command_length; i++) {
            if(isalnum(command[i]) || command[i] == '.') {
                alpha_chars++;
            }
        }
    }
    else {
        for(int i = 0; i < command_length; i++) {
            if(isalnum(command[i])) {
                alpha_chars++;
            }
        }
    }
    
    
    for(int i = 0; i < num_commands; i++) {
        if(command_type[i] == *command_character) {
            return check_command_arguments(board, command, args, *command_character, alpha_chars);
        }
    }
    printf("Unrecognized command. Type h for help.\n");
    return false;

}

bool check_command_arguments(Board board, char* command, Arguments *args, char command_character, int alpha_chars) {
    
    /**
        Check if inputted command arguments are valid. Checks against requirements for every possible command.

        @param board: a board struct that contains all the data for a board/canvas
        @param args: a pointer to an arguments struct that contains variables for all possible command arguments
        @param command: the user input stored as a string
        @param command_character: the first character the user inputs; indicates command type
        @param alpha_chars: the number of alphanumeric characters and periods in the command input
        @return: true if the command arguments are valid for the given command character
    */
    
    // Check first letter (the command symbol) to see which command is being executed
    int args_read = 0;
    
    switch(command_character) {
        case 'q':
            // num no command args
            if(alpha_chars != 1){
                printf("Unrecognized command. Type h for help.\n");
                return false;
            }
            return true;
        case 'h':
            // no command args
            if(alpha_chars != 1){
                printf("Unrecognized command. Type h for help.\n");
                return false;
            }
            return true;
        case 'w':
            args_read = sscanf(command, " %c %d %d %d %d", &command_character, &(args -> row1), &(args -> col1), &(args -> row2), &(args -> col2));

            //check number of arguments
            if(args_read != 5) {
                printf("Improper draw command.\n");
                return false;
            }

            if(alpha_chars != (1 + num_digits(args -> row1) +
                             num_digits(args -> row2) +
                             num_digits(args -> col1) +
                             num_digits(args -> col2))) {
                printf("Improper draw command.\n");
                return false;
            }
            
            //translate to corrected indexes and store in arguments
            args -> row1 = board.numRows - 1 - (args -> row1);
            args -> row2 = board.numRows - 1 - (args -> row2);
            
            //check in bounds
            if(!(inbetween(args->row1, 0, board.numRows - 1) && 
                inbetween(args->row2, 0, board.numRows - 1) && 
                inbetween(args->col1, 0, board.numCols - 1) && 
                inbetween(args->col2, 0, board.numCols - 1))) {
                    printf("Improper draw command.\n");
                    return false;
            }
            
            //check if possible line
            int row_diff = abs((args -> row1) - (args -> row2));
            int col_diff = abs((args -> col1) - (args -> col2));
            int overall = row_diff - col_diff;
            if((args -> row1 == args -> row2) || (args -> col1 == args -> col2) || overall == 0){
                return true;
            }
            else{
                printf("Improper draw command.\n");
                return false;
            }
            
        case 'e':
            args_read = sscanf(command, " %c %d %d", &command_character, &(args -> row1), &(args -> col1));
            
            if(args_read != 3) {
                printf("Improper erase command.\n");
                return false;
            }

            if(alpha_chars != (1 + num_digits(args -> row1) +
                             num_digits(args -> col1))) {
                printf("Improper erase command.\n");
                return false;
            }
            
            args -> row1 = board.numRows - 1 - (args -> row1);
            
            if(!(inbetween(args->row1, 0, board.numRows - 1) && 
                inbetween(args->col1, 0, board.numCols - 1))) {
                printf("Improper erase command.\n");
                return false;
            }
            
            return true;
        case 'r':
            args_read = sscanf(command, " %c %d %d", &command_character, &(args -> row1), &(args -> col1));
            
            if(args_read != 3){
                printf("Improper resize command.\n");
                return false;
            }

            if(alpha_chars != (1 + num_digits(args -> row1) +
                             num_digits(args -> col1))) {
                printf("Improper resize command.\n"); 
                return false;
            }

            if(!(args -> row1 > 0 && args -> col1 > 0)){
                printf("Improper resize command.\n");
                return false;
            }
            
            return true;
        case 'a':
            args_read = sscanf(command, " %c %c %d", &command_character, &(args -> row_col), &(args -> position));
            
            if(args_read != 3){
                printf("Improper add command.\n");
                return false;
            }

            if(alpha_chars != (2 + num_digits(args -> position))) {
                return false;
            }
            
            if(args -> row_col == 'r') {
                if(!inbetween(args -> position, 0, board.numRows)){ // if adding to end of row is possible, then don't do - 1
                    printf("Improper add command.\n");
                    return false;
                }
                args -> position = board.numRows - 1 - (args -> position);
            }
            else if(args -> row_col == 'c') {
                if(!inbetween(args -> position, 0, board.numCols)){
                    printf("Improper add command.\n");
                    return false;
                }
            }
            else {
                printf("Improper add command.\n");
                return false;
            }
            
            return true;
        case 'd':
            args_read = sscanf(command, " %c %c %d", &command_character, &(args -> row_col), &(args -> position));
            
            if(args_read != 3){
                printf("Improper delete command.\n");
                return false;
            }

            if(alpha_chars != (2 + num_digits(args -> position))) {
                printf("Improper delete command.\n");
                return false;
            }
            
            if(args -> row_col == 'r') {
                if(!inbetween(args -> position, 0, board.numRows - 1)) { // if adding to end of row is possible, then don't do - 1
                    printf("Improper delete command.\n");
                    return false;
                }
                args -> position = board.numRows - 1 - (args -> position);
            }
            else if(args -> row_col == 'c') {
                if(!inbetween(args -> position, 0, board.numCols - 1)){
                    printf("Improper delete command.\n");
                    return false;
                }
            }
            else {
                printf("Improper delete command.\n");
                return false;
            }
            
            return true;
        case 's':
            args_read = sscanf(command, " %c %s", &command_character, args -> file_name);
            
            if(args_read != 2) {
                printf("Improper save command.\n");
                return false;
            }

            if(alpha_chars != (1 + strlen(args -> file_name))) {
                printf("Improper save command.\n");
                return false;
            }

            args -> file = fopen(args -> file_name, "w");

            if(args -> file == NULL) {
                printf("Improper save command.\n");
                return false;
            }
            
            return true;
        case 'l':
            args_read = sscanf(command, " %c %s", &command_character, args -> file_name);
            
            if(args_read != 2) {
                printf("Improper load command.\n");
                return false;
            }

            if(alpha_chars != (1 + strlen(args -> file_name))) {
                printf("Improper load command.\n");
                return false;
            }

            args -> file = fopen(args -> file_name, "r");

            if(args -> file == NULL) {
                printf("Improper load command.\n");
                return false;
            }

            return true;
        default:
            return false;
    }
}

int num_digits(int num) {
    
    /**
        Counts the number of digits of a number

        @param num: an integer number
        @return: the number of digits num has
    */
    
    int sum = 0;

    if(num == 0) {
        return 1;
    }
    else {
        while(num > 0) {
            num /= 10;
            sum++;
        }
    }

    return sum;
}
