# Compiler and compiler flags
CC := gcc
CFLAGS := -std=c11 -Wall
DEBUG_CFLAGS := -g

# Name of the executable
TARGET := main.exe

# Source files
SRCS := main.c

# Object files
OBJS := $(SRCS:.c=.o)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Debug target to build the executable with debug information
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: clean $(TARGET)

# Run target to build and run the program
run: $(TARGET)
	$(TARGET)

# Clean rule
clean:
	del $(OBJS) $(TARGET)
