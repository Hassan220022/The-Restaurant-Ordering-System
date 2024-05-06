# Makefile for Restaurant Ordering System

CC=gcc
CFLAGS=-Wall -pthread
DEPS = restaurant_system.h
OBJ = main.o restaurant_system.o

# Pattern rule for object files
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Linking all object files into the executable
restaurant_system: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Phony target for cleaning up the project
.PHONY: clean

clean:
	rm -f $(OBJ) restaurant_system
	rm -f *conflict*
	rm -rf .vscode
