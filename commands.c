#include "commands.h"
#include <stdio.h>
#include <stdlib.h>

void execute_command(Board *board, char command_character, Arguments args) {
    switch(command_character) {
        case 'q':
            quit(board);
            break;
        case 'h':
            help();
            break;
        case 'w':
            write(args, *board);
            break;
         case 'e':
            erase(*board, args);
            break;
        case 'r':
            resize(board, &args);
            break;
        case 'a':
            add(board, args);
            break;
        case 'd':
            delete(board, args);
            break;
         case 's':
             save(*board, &args);
             break;
         case 'l':
             load(&args, board);
             break;
    }
}
void quit(Board *board){
    exit(0);
}

void help() {
    printf("Commands:\n");
    printf("Help: h\n");
    printf("Quit: q\n");
    printf("Draw line: w row_start col_start row_end col_end\n");
    printf("Resize: r num_rows num_cols\n");
    printf("Add row or column: a [r | c] pos\n");
    printf("Delete row or column: d [r | c] pos\n");
    printf("Erase: e row col\n");
    printf("Save: s file_name\n");
    printf("Load: l file_name\n");
}

void write(Arguments args, Board board) {
    // draw line from start row and start col to end row and end col
    if(args.row1 == args.row2) {
        //check if incrementing or decrementing
        if(args.col1 < args.col2){ //increment
            for(int i = args.col1; i <= args.col2; i++){
                if((board.arr)[args.row1][i] == '*' || (board.arr)[args.row1][i] == '-'){
                    (board.arr)[args.row1][i] = '-';
                }
                else{
                    (board.arr)[args.row1][i] = '+';
                }
            }
        }
        else { //decrement
            for(int i = args.col1; i >= args.col2; i--){
                if((board.arr)[args.row1][i] == '*' || (board.arr)[args.row1][i] == '-'){
                    (board.arr)[args.row1][i] = '-';
                }
                else{
                    (board.arr)[args.row1][i] = '+';
                }
            }
        }
    }
    else if(args.col1 == args.col2) {
        if(args.row1 < args.row2){ //increment
            for(int i = args.row1; i <= args.row2; i++){
                if((board.arr)[i][args.col1] == '*' || (board.arr)[i][args.col1] == '|'){
                    (board.arr)[i][args.col1] = '|';
                }
                else {
                    (board.arr)[i][args.col1] = '+';
                }
            }
        }
        else { //decrement
            for(int i = args.row1; i >= args.row2; i--){
                if((board.arr)[i][args.col1] == '*' || (board.arr)[i][args.col1] == '|'){
                    (board.arr)[i][args.col1] = '|';
                }
                else {
                    (board.arr)[i][args.col1] = '+';
                }
            }
        } 
    }
    else if((args.row1 > args.row2 && args.col1 > args.col2) || (args.row2 > args.row1 && args.col2 > args.col1)) {
        if(args.row1 > args.row2 && args.col1 > args.col2) {
            for(int i = 0; args.row1 + i >= args.row2; i--) {
                if((board.arr)[args.row1 + i][args.col1 + i] == '*' || (board.arr)[args.row1 + i][args.col1 + i] == '\\') {
                    (board.arr)[args.row1 + i][args.col1 + i] = '\\';
                }
                else {
                    (board.arr)[args.row1 + i][args.col1 + i] = '+';
                }
            }
        }
        else {
            int j = args.col2;
            for(int i = args.row2; i >= args.row1; i--){
                if((board.arr)[i][j] == '\\' || (board.arr)[i][j] == '*'){
                    board.arr[i][j] = '\\';
                }
                else{
                    (board.arr)[i][j] = '+';
                }
                j--;
            }
        }
    }
    else {
        if(args.row1 < args.row2) {
            for(int i = 0; args.row1 + i <= args.row2; i++) {
                if((board.arr)[args.row1 + i][args.col1 - i] == '*' || (board.arr)[args.row1 + i][args.col1 - i] == '/') {
                    (board.arr)[args.row1 + i][args.col1 - i] = '/';
                }
                else {
                    (board.arr)[args.row1 + i][args.col1 - i] = '+';
                }
            }
        }
        else{
            int j = args.col1;
            for(int i = args.row1; i >= args.row2; i--){
                if((board.arr)[i][j] == '/' || (board.arr)[i][j] == '*'){
                    board.arr[i][j] = '/';
                }
                else{
                    (board.arr)[i][j] = '+';
                }
                j++;
            }
        }
    }
}

void erase(Board board, Arguments args) {
    (board.arr)[args.row1][args.col1] = '*';
}

void add(Board *board, Arguments args) {
    if(args.row_col == 'r') {
        // add row to numRows
        (board -> numRows)++;
        board -> arr = (char**)realloc(board -> arr, sizeof(char*) * (board -> numRows));

        int new_position = args.position + 1;

        // allocate memory to last row
        (board -> arr)[(board -> numRows) - 1] = (char*)calloc(board -> numCols, sizeof(char));
        
        for(int r = (board -> numRows) - 1; r > new_position; r--) { // position locale changes
            for(int c = 0; c < (board -> numCols); c++) {
                // change each col index in row to col index in row before
                (board -> arr)[r][c] = (board -> arr)[r - 1][c];
            }
        }

        // now change all values in position row to asterisks
        for(int c = 0; c < (board -> numCols); c++) {
            (board -> arr)[new_position][c] = '*';
        }
    }
    else {
        (board -> numCols)++;
        for (int i = 0; i < board -> numRows ; i++){
            board -> arr[i] = (char*)realloc(board -> arr[i], sizeof(char) * (board -> numCols));
        }
        for(int r = 0; r < (board -> numRows); r++){
            for(int c = (board -> numCols) - 1; c >= args.position; c--){
                (board -> arr[r][c]) = (board -> arr[r][c - 1]);
            }
        }
        for(int r = 0; r < (board -> numRows); r++){
            (board -> arr[r][args.position]) = '*';
        }
    }
}

void delete(Board *board, Arguments args) {
    if(args.row_col == 'r') {
        for(int r = args.position; r < ((board -> numRows) - 1); r++){
            for(int c = 0; c < (board -> numCols); c++){
            (board -> arr)[r][c] = (board -> arr)[r+1][c];
            }
        }
        
        (board -> numRows)--;
        
        free((board -> arr)[board -> numRows]);
    }
    else{
        // copy values at every row on each col to one after it, starting at position, so that last one can be deleted
        for(int c = args.position; c < (board -> numCols) - 1; c++) {
            for(int r = 0; r < (board -> numRows); r++) {
                (board -> arr)[r][c] = (board -> arr)[r][c + 1];
            }
        }
        
        // remove col from numCols
        (board -> numCols)--;
        
        // reallocate each column
        for(int r = 0; r < board -> numRows; r++) {
            (board -> arr)[r] = (char*)realloc((board -> arr)[r], sizeof(char) * (board -> numCols));
        }
    }
}

void resize(Board *board, Arguments *args){
    
    args -> row_col = 'r';

    if(args -> row1 > (board -> numRows)) {
        args -> position = -1;
        for(int r = (board -> numRows); r < args -> row1; r++) {
            add(board, *args);
        }
    }
    else {
        args -> position = 0;
        for(int r = (board -> numRows); r > args -> row1; r--) {
            delete(board, *args);
        }
    }
    
    args -> row_col = 'c';
    
    if(args -> col1 > (board -> numCols)) {
        for(int c = (board -> numCols); c < args -> col1; c++) {
            args -> position = c;
            add(board, *args);
        }
    }
    else {
        for(int c = (board -> numCols); c > args -> col1; c--) {
            args -> position = board -> numCols - 1;
            delete(board, *args);
        }
    }
}

void save(Board board, Arguments *args) {
    fprintf(args -> file, "%d %d ", board.numRows, board.numCols); //put num rows and num cols first
    
    for(int r = 0; r < board.numRows; r++) {
        for(int c = 0; c < board.numCols; c++) {
            fprintf(args -> file, "%c", (board.arr)[r][c]);
        }
    }

    fclose(args -> file);
}

void load(Arguments *args, Board *board){
    fscanf(args -> file, "%d %d", &(args -> row1), &(args -> col1));
    
    resize(board, args);
    
    for(int r = 0; r < board -> numRows; r++) {
        for(int c = 0; c < board -> numCols; c++) {
            fscanf(args -> file, " %c", &((board -> arr)[r][c]));
        }
    }

    fclose(args -> file);
}