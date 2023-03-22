CC = gcc
FLAGS = -Wall
SOURCE_PROGRAM_NAME = dir_tree.c
PROGRAM_NAME = dir_tree
ARGUMENT_1 = /home/endrew/tmp/
ARGUMENT_2 = aaabaaaaa

all:
	make compile

compile:
	$(CC) $(FLAGS) $(SOURCE_PROGRAM_NAME) -o $(PROGRAM_NAME)

test:
	make compile
	./$(PROGRAM_NAME) $(ARGUMENT_1) $(ARGUMENT_2)

clean:
	rm -r $(PROGRAM_NAME)

clean_all:
	rm -r $(PROGRAM_NAME)