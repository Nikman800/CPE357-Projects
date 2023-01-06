CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = tree
OBJS = tree.o
all: $(MAIN)

$(MAIN): $(OBJS) tree.c
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)
clean:
	rm *.o $(MAIN) core
