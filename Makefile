CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11

TARGET = chell
SRC = src/main.c src/parser.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) $^ -o $(TARGET)

test:
	$(CC) $(CFLAGS) tests/test_parser.c src/parser.c -o test_parser
	./test_parser
	rm -f test_parser

clean:
	rm -f $(OBJ) $(TARGET)
