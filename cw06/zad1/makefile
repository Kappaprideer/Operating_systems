CC = gcc
FLAGS = -Wall
C_SOURCE  = client.c 
S_SOURCE  = server.c
C_PROGRAM = client
S_PROGRAM = server

all:
	make compile
	

compile:
	$(CC) $(FLAGS) $(S_SOURCE) -o $(S_PROGRAM)
	$(CC) $(FLAGS) $(C_SOURCE) -o $(C_PROGRAM)

client:
	$(CC) $(FLAGS) $(C_SOURCE) -o $(C_PROGRAM)

server:
	$(CC) $(FLAGS) $(S_SOURCE) -o $(S_PROGRAM)

clean:
	rm -r $(C_PROGRAM)
	rm -r $(S_PROGRAM)

clean_all:
	make clean
	rm -r logs.txt