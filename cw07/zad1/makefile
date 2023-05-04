CC = gcc
FLAGS = -Wall

all:
	make simulation
	make clients_input
	make barber

simulation:
	$(CC) $(FLAGS) simulation.c common.c -lrt -lpthread -o simulation

clients_input:
	$(CC) $(FLAGS) clients_input.c -o clients_input common.c

barber:
	$(CC) $(FLAGS) barber.c -o barber common.c

common:
	$(CC) $(FLAGS) common.c -o common
	
clean:
	rm -r clients_input
	rm -r simulation
	rm -r barber
	