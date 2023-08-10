#include "paint.h"

// Implements a text-based version of paint. This program shows the user a canvas
// so that the user can enter commands and paint on the board with characters as they please.

int main(int argc, char* argv[]){
    
    /**
        Calls the master paint function, that calls all other functions
        to create a board and start the paint session on the terminal
        until the program is exited with 'q'

        @param args: the number of command line arguments entered
        @param argv: each command line argument stored as an array of strings
        @return: 0, if the program finishes successfully
    */

    paint(argc, argv); 

    return 0;
}