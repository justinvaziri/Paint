#ifndef BOARD_H
    #define BOARD_H

    typedef struct Board_Struct{
        int numRows;
        int numCols;
        char** arr;
    } Board;

    void make_board(Board *board, int rows, int cols);
    void fill_board(Board board);
    void print_board(Board board);

#endif