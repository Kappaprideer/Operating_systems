FLAGS = -Wall
CC = gcc
SOURCE_NAME = integral_round_two.c
PROGRAM_NAME = integral_round_two

all:
	make compile
	./$(PROGRAM_NAME) 0.0000000005 1 > raport.txt
	./$(PROGRAM_NAME) 0.0000000008 2 >> raport.txt
	./$(PROGRAM_NAME) 0.0000000009 10 >> raport.txt
	./$(PROGRAM_NAME) 0.0000000009 100 >> raport.txt
	./$(PROGRAM_NAME) 0.00000002 100 >> raport.txt


test:
	make compile
	./$(PROGRAM_NAME) 0.0000001 2

compile:
	$(CC) $(FLAGS) $(SOURCE_NAME) -o $(PROGRAM_NAME)
	$(CC) $(FLAGS) count_value.c -o count_value


clean:
	rm -r $(PROGRAM_NAME)
	rm -r count_value

clean_all:
	make clean
	rm -r raport.txt
