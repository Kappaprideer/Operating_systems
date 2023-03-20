CC = gcc
FLAGS = -Wall
SOURCE_PROGRAM_NAME = n_processes.c
PROGRAM_NAME = n_processes
ARGUMENT = 5

all:
	make compile

compile:
	$(CC) $(FLAGS) $(SOURCE_PROGRAM_NAME) -o $(PROGRAM_NAME)

test:
	make compile
	./$(PROGRAM_NAME) $(ARGUMENT)

clean:
	rm -r $(PROGRAM_NAME)

clean_all:
	rm -r $(PROGRAM_NAME)
