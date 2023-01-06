CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = sfind
OBJS = sfind.o
all: $(MAIN)

$(MAIN): $(OBJS) sfind.c
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)
clean:
	rm *.o $(MAIN) core
