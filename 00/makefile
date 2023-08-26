# Compiler and compiler flags
CC := gcc
CFLAGS := -std=c11 -Wall

# Name of the executable
TARGET := main

# Source files
SRCS := main.c

# Object files
OBJS := $(SRCS:.c=.o)

# Check for the operating system
ifeq ($(OS),Windows_NT)
	RM := del /Q
	EXE := .exe
else
	RM := rm -f
	EXE :=
endif

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET)$(EXE) $(OBJS)

# Run target to build and run the program
run: $(TARGET)
	./$(TARGET)$(EXE)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	$(RM) $(OBJS) $(TARGET)$(EXE)

