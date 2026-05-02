CC = gcc
CFLAGS = -I./src -Wall
TARGET = scheduler

SRCS = src/main.c src/utils.c src/greedy.c src/brute_force.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)