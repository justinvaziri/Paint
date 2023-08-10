#include "paint.h"
#include "commands.h"
#include "command_validation.h"
#include <stdio.h>

void paint(int argc, char* argv[]) {
    
    /**
        Sets up the board and calls the paint board function
        which starts a paint session.

        @param args: the number of command line arguments entered
        @param argv: each command line argument stored as an array of strings
    */
    
    Board board;
    
    setup_board(&board, argc, argv);
    paint_board(&board);
}

void setup_board(Board *board, int argc, char* argv[]) {
    
    /**
        Sets up a board (or canvas) to be displayed on terminal by validating
        command line argument input, and displaying the default length and width
        of a canvas/board if no args or invalid args are inputted (10 x 10)

        @param board: a pointer to a board struct that contains data for a board/canvas
        @param args: the number of command line arguments entered
        @param argv: each command line argument stored as an array of strings
    */
    
    int rows; int cols;

    if(argc == 1){
        rows = 10; cols = 10;
    }
    else if(argc != 3){
        printf("Wrong number of command line arguments entered.\n");
        printf("Usage: ./paint.out [num_rows num_cols]");
        printf("Making default board of 10 X 10.\n");
        rows = 10; cols = 10;
    }
    else if(atoi(argv[1]) < 1 ){
        printf("The number of rows is less than 1.\n");
        printf("Making default board of 10 X 10.\n");
        rows = 10; cols = 10;
    }
    else if(atoi(argv[2]) < 1){
        printf("The number of columns is less than 1.\n");
        printf("Making default board of 10 X 10.\n");
        rows = 10; cols = 10;
    }
    else {
        rows = atoi(argv[1]); cols = atoi(argv[2]);
    }
    
    make_board(board, rows, cols);
   
} 

void paint_board(Board *board) {
    
    /**
        The function that initiates the painting session. When called, the user
        can now start painting on an empty board. Will continue to ask for commands
        until the program is exited with the 'q' command.

        @param board: a pointer to a board struct that contains data for a board/canvas
    */
    
    Arguments args;
    char command[100];
    char command_character;
    
    do {
        get_command(*board, &args, command, &command_character);
        execute_command(board, command_character, args);
    } while(true); // 'q' exits(0) so we don't need to worry about loop ending
}