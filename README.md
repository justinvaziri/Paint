# Paint

The Paint Program is a simple console-based application that simulates a painting session on a canvas. Users can interact with the program by entering commands to paint, modify, and manipulate the canvas.

## Getting Started

Follow these instructions to set up and run the Paint Program on your local machine.

### Prerequisites
You need a C compiler, such as GCC, to compile and run the program.
Git is required to clone the repository.

### How to use
To build and run the Paint Program using the provided Makefile, follow these steps:

1. **Clone the repository or download the source files.**

2. **Compile the code using the provided Makefile:**

   Open your terminal and navigate to the project directory. Run the following command:
   
   ```bash
   make
   ```
Run the program:
  ```bash
./paint.out num_rows num_cols
```
Where you replace 'num_rows' and 'num_cols' with their desired values.

If no arguments are provided, the program defaults to a canvas size of 10x10.
If num_rows or num_cols is less than 1, the default canvas size is used.
### Commands
The Paint Program supports the following commands:

- h: Help (display available commands)
- q: Quit the program
- w: row_start col_start row_end col_end: Draw a line from (row_start, col_start) to (row_end, col_end)
- r: num_rows num_cols: Resize the canvas to num_rows rows and num_cols columns
- a: [r | c] pos: Add a row or column at position pos (use r for row, c for column)
- d: [r | c] pos: Delete a row or column at position pos (use r for row, c for column)
- e: row col: Erase the cell at (row, col)
- s: file_name: Save the canvas to a file named file_name
- l: file_name: Load a canvas from a file named file_name
The program will continue to prompt for commands until you exit using the 'q' command.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](https://opensource.org/license/mit/).
