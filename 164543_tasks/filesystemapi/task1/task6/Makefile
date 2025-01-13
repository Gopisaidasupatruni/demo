# Define the compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2

# Executable names
EXECUTABLES = simpcat1 simpcat2 simpcat3

# Build all executables
all: $(EXECUTABLES)

# Rules to build each simpcat variant
simpcat1: simpcat1.c
	$(CC) $(CFLAGS) -o simpcat1 simpcat1.c

simpcat2: simpcat2.c
	$(CC) $(CFLAGS) -o simpcat2 simpcat2.c

simpcat3: simpcat3.c
	$(CC) $(CFLAGS) -o simpcat3 simpcat3.c

# Clean up generated files
clean:
	rm -f $(EXECUTABLES)

