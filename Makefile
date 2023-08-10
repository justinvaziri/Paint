FLAGS = -g -Wall -Werror

TARGET = paint.out
OBJS = main.o paint.o board.o command_validation.o commands.o input_validation.o

$(TARGET): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(TARGET)

main.o: main.c paint.h 
	gcc $(FLAGS) -c main.c

paint.o: paint.c paint.h command_validation.h commands.h
	gcc $(FLAGS) -c paint.c
	
board.o: board.c board.h
	gcc $(FLAGS) -c board.c

command_validation.o: command_validation.c command_validation.h input_validation.h
	gcc $(FLAGS) -c command_validation.c

commands.o: commands.c commands.h
	gcc $(FLAGS) -c commands.c

input_validation.o: input_validation.c input_validation.h 
	gcc $(FLAGS) -c input_validation.c

clean:
	rm -f $(TARGET) $(OBJS)