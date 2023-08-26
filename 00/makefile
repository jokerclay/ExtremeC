# Compiler and compiler flags
CC := gcc
CFLAGS := -std=c11 -Wall

# Name of the executable
TARGET := main.exe

# Source files
SRCS := main.c 

# Object files
OBJS := $(SRCS:.c=.o)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Run target to build and run the program
run: $(TARGET)
	$(TARGET)


# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	del $(OBJS) $(TARGET)

