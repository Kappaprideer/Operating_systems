FLAGS = -Wall
CC = gcc
SOURCE_NAME = integral.c
PROGRAM_NAME = integral

all:
	make compile
	./$(PROGRAM_NAME) 0.0000000005 1 >> raport.txt
	./$(PROGRAM_NAME) 0.0000000008 2 >> raport.txt
	./$(PROGRAM_NAME) 0.0000000009 10 >> raport.txt
	./$(PROGRAM_NAME) 0.0000000009 100 >> raport.txt

compile:
	$(CC) $(FLAGS) $(SOURCE_NAME) -o $(PROGRAM_NAME)

clean:
	rm -r $(PROGRAM_NAME)

clean_all:
	make clean
	rm -r raport.txt