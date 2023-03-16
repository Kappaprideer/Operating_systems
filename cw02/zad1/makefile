CC = gcc
FLAGS = -Wall
SOURCE_PROGRAM_NAME = zamien.c
PROGRAM_NAME = zamien
SRC_CHAR = a
DEST_CHAR = z
SOURCE_FILENAME = plik1.txt
DESTINATION_FILENAME = plik2.txt

all:
	make compile
	./$(PROGRAM_NAME) $(SRC_CHAR) $(DEST_CHAR) $(SOURCE_FILENAME) $(DESTINATION_FILENAME) > pomiar_zad_1.txt

compile:
	$(CC) $(FLAGS) $(SOURCE_PROGRAM_NAME) -o $(PROGRAM_NAME)

clean:
	rm -r $(PROGRAM_NAME)

clean_all:
	rm -r $(PROGRAM_NAME)
	rm -r $(DESTINATION_FILENAME)
	rm -r pomiar_zad_1.txt
