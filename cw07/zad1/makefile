CC = gcc
FLAGS = -Wall

clients:
	$(CC) $(FLAGS) clients.c -o clients

simulation:
	$(CC) $(FLAGS) simulation.c -o simulation

all:
	make simulation
	make clients
	
clean:
	rm -r clients
	rm -r simulation