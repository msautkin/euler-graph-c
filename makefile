# makefile for euler-graph-c

CC = gcc
CFLAGS = -Wall -g

graph: main.c graph.c
	$(CC) $(CFLAGS) -o graph main.c graph.c

clean:
	rm -f graph *.o
