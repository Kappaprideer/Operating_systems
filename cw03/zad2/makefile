CC = gcc
FLAGS = -Wall
SOURCE_PROGRAM_NAME = path_ls.c
PROGRAM_NAME = path_ls
ARGUMENT = /

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