#include "board.h"
#include <stdlib.h>
#include <stdio.h>

void make_board(Board *board, int rows, int cols){
    
    /**
        Makes a board with the given dimensions

        @param board: a pointer to a board struct that contains data for a board/canvas
        @param rows: the number of rows of the board (height of canvas)
        @param cols: the number of columns of the board (width of the canvas)
    */

    board -> numRows = rows;
    board -> numCols= cols;
    
    board -> arr = (char**)calloc(rows, sizeof(char*));
    for(int i = 0; i < rows; i++){
        (board -> arr)[i] = (char*)calloc(cols, sizeof(char));
    }

    fill_board(*board);
}

void fill_board(Board board) {
    
    /**
        Fills a board with empty characters (asterisks in this case)

        @param board: a board struct that contains all the data for a board/canvas
    */
    
    for(int r = 0; r < board.numRows; r++) {
        for(int c = 0; c < board.numCols; c++) {
            (board.arr)[r][c] = '*';
        }
    }
}

void print_board(Board board){
    
    /**
        Displays the board to the terminal. Shows row numbers on the left
        and column numbers below the board.

        @param board: a board struct that contains all the data for a board/canvas
    */
    
    for(int r = 0; r < board.numRows; r++){
        printf(" %d ", board.numRows - 1 - r);
        for(int c = 0; c < board.numCols; ++c){
            printf(" %c ", board.arr[r][c]);
        }
        printf("\n");
    }
    
    // Print col numbers
    printf("   ");
    for(int i = 0; i < board.numCols; i++) {
        printf(" %d ", i);
    }

    printf("\n");
}