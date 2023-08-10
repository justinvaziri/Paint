#ifndef PAINT_H
    #define PAINT_H
    #include "board.h"
    #include <stdlib.h>

    void paint(int argc, char* argv[]);
    void setup_board(Board *board, int argc, char* argv[]);
    void paint_board(Board *board);

#endif