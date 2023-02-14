OBJ = main.o twitter.o htable.o tqueue.o user.o node.o tweet.o
CFLAGS = -ansi -Wall -g
CC = gcc

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o twitter

main.o: main.c twitter.c
	$(CC) $(CFLAGS) -c $< -o $@

htable.o: htable.c
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