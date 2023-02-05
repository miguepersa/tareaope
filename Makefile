OBJ = main.o htable.o node.o tqueue.o tweet.o twitter.o user.o
CFLAGS = -ansi -Wall -g
CC = gcc

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o twitter

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

htabl.o: htable.c
	$(CC) $(CFLAGS) -c $< -o $@

node.o: node.c
	$(CC) $(CFLAGS) -c $< -o $@

tqueue.o: tqueue.c
	$(CC) $(CFLAGS) -c $< -o $@

tweet.o: tweet.c
	$(CC) $(CFLAGS) -c $< -o $@

twitter.o: twitter.c
	$(CC) $(CFLAGS) -c $< -o $@

user.o: user.c
	$(CC) $(CFLAGS) -c $< -o $@