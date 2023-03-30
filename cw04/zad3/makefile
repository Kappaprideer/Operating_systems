CC = gcc
FLAGS = -Wall
CATCHER_NAME = catcher.c
SENDER_NAME = sender.c
CATCHER = catcher
SENDER = sender

all:
	make compile

compile:
	$(CC) $(FLAGS) $(CATCHER_NAME) -o $(CATCHER)
	$(CC) $(FLAGS) $(SENDER_NAME) -o $(SENDER)

clean:
	rm -r $(CATCHER)
	rm -r $(SENDER)
