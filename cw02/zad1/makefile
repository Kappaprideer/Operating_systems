CC = gcc
FLAGS = -Wall
SOURCE_PROGRAM_NAME = homemade_tr.c
PROGRAM_NAME = homemade_tr
SRC_CHAR = a
DEST_CHAR = z
SOURCE_FILENAME = plik1.txt
DESTINATION_FILENAME = plik2.txt

all:
	make compile
	./$(PROGRAM_NAME) $(SRC_CHAR) $(DEST_CHAR) $(SOURCE_FILENAME) $(DESTINATION_FILENAME) > pomiar_zad_1.txt

compile:
	$(CC) $(FLAGS) $(SOURCE_PROGRAM_NAME) -o $(PROGRAM_NAME)
run:
	make compile
	./$(PROGRAM_NAME) $(SOURCE_FILENAME) $(DESTINATION_FILENAME) 

clean:
	rm -r $(PROGRAM_NAME)

clean_all:
	rm -r $(PROGRAM_NAME)
	rm -r $(DESTINATION_FILENAME)

