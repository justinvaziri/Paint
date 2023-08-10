#ifndef COMMANDS_H
    #define COMMANDS_H
    
    #include "board.h"
    #include "command_validation.h"

    void execute_command(Board *board, char command_character, Arguments args);
    void quit(Board *board);
    void help();
    void write(Arguments args, Board board);
    void erase(Board board, Arguments args);
    void add(Board *board, Arguments args);
    void delete(Board *board, Arguments args);
    void resize(Board *board, Arguments *args);
    void save(Board board, Arguments *args);
    void load(Arguments *args, Board *board);

#endif