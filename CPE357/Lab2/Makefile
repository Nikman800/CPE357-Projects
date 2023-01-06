CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = uniq
all: $(MAIN)

$(MAIN): $(OBJS) uniq.c
	$(CC)$(CFLAGS) -o $(MAIN) $(OBJS)
clean:
	rm *.o$(MAIN) core