CC = gcc
FLAGS = -Wall
LIB_NAME = lib_one
LIB_DIR = ../zad1
SOURCE_NAME = library

static:
	$(CC) $(FLAGS) main.c -o main -I$(LIB_DIR) $(LIB_DIR)/$(LIB_NAME).a
shared:
	$(CC) $(FLAGS) main.c -o main -L$(LIB_DIR) -I$(LIB_PATH) -l_one
dynamic:
	$(CC) $(FLAGS) -I$(LIB_DIR) main.c -ldl -D DYNAMIC -o main
clean:
	rm -r main

set_path:
	export LD_LIBRARY_PATH="/home/endrew/Github/Operating_systems/cw01/zad2"