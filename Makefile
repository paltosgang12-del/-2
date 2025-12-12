CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = catcafe
SOURCES = main.c cat.c
OBJECTS = main.o cat.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

main.o: main.c cat.h
	$(CC) $(CFLAGS) -c main.c -o main.o

cat.o: cat.c cat.h
	$(CC) $(CFLAGS) -c cat.c -o cat.o

clean:
	rm -f $(OBJECTS) $(TARGET) catcafe.dat catcafe.bak

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
