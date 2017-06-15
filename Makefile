INCLUDE=.
LIBS=
CC=gcc
OFLAGS=-c
CFLAGS=-g -Wall -Wextra -std=gnu99 -pedantic-errors -I$(INCLUDE)

TARGET=snap
OBJECTS=snap.o

all: $(OBJECTS) Makefile
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

%o: %.c Makefile *.h
	$(CC) $(CFLAGS) $(OFLAGS) -o $@ $<

clean:
	rm $(OBJECTS) $(TARGET)

