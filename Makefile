CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11

TARGET = chell
SRC = src/main.c src/parser.c src/executor.c src/builtin.c

.PHONY: all clean

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) $^ -o $(TARGET)

test:
	$(CC) $(CFLAGS) tests/test_parser.c src/parser.c -o test_parser
	./test_parser
	rm -f test_parser
	
	$(CC) $(CFLAGS) tests/test_builtin.c src/builtin.c -o test_builtin
	./test_builtin
	rm -f test_builtin

clean:
	rm -f $(TARGET)
