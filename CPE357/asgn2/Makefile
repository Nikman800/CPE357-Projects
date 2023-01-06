CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = guess
OBJS = guess.o
all: $(MAIN)

$(MAIN): $(OBJS) guess.c
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)
clean:
	rm *.o $(MAIN) core
