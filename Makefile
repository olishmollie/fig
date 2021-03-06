CC=cc
CFLAGS=-c -g -Wall
LDFLAGS=-ledit
SOURCES:=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=bin/fig

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm src/*.o $(EXECUTABLE)
