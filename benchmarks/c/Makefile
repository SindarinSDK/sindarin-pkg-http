CC = gcc
CFLAGS = -O3 -pthread -Wall -Wextra
TARGET = server

all: $(TARGET)

$(TARGET): server.c
	$(CC) $(CFLAGS) -o $(TARGET) server.c

clean:
	rm -f $(TARGET)

.PHONY: all clean
