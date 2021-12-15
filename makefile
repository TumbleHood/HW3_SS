CC = gcc
AR = ar
CFLAGS = -Wall -g
OBJS = main.o my_mat.o
OUT = stringProg

main.o: main.c my_mat.h
	$(CC) $(CFLAGS) -c main.c

my_mat.o: my_mat.c my_mat.h
	$(CC) $(CFLAGS) -c my_mat.c

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

clean:
	rm -f $(OBJS) $(OUT)

.PHONY: clean all