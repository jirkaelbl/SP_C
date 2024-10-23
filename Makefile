CC = gcc # c compiler
OBJS = graph.o error_messages.o stack.o parser.o
BIN = graph
CCFLAGS = -Wall -Wextra -pedantic -ansi -g

all: clean $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) graph.o error_messages.o stack.o parser.o -o graph

graph.o: graph.c
	$(CC) $(CCFLAGS) -c graph.c

error_messages.o: error_messages.c
	$(CC) $(CCFLAGS) -c error_messages.c

stack.o: stack.c
	$(CC) $(CCFLAGS) -c stack.c

parser.o: parser.c
	$(CC) $(CCFLAGS) -c parser.c	

clean:
	rm -f $(OBJS) $(BIN)