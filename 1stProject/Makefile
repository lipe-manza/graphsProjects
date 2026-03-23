CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -fsanitize=address -fno-omit-frame-pointer

TARGET = programa

OBJS = main.o graphs.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c graphs.h
	$(CC) $(CFLAGS) -c main.c

graphs.o: graphs.c graphs.h
	$(CC) $(CFLAGS) -c graphs.c

run: all
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
