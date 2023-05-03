CC = gcc
FLAGS = -Wall

all:
	make simulation
	make clients_input
	make clients

simulation:
	$(CC) $(FLAGS) simulation.c -o simulation

common:
	$(CC) $(FLAGS) common.c -o common

clients:
	$(CC) $(FLAGS) client.c -o client

clients_input:
	$(CC) $(FLAGS) clients_input.c -o clients_input
	
clean:
	rm -r client
	rm -r clients_input
	rm -r simulation