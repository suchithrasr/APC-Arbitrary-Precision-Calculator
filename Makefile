# ============================================================
#  Makefile — Arbitrary Precision Calculator (APC)
#  Author  : Suchithra S
# ============================================================

# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g

# Output binary name
TARGET  = apc

# Source files
SRCS    = main.c \
          apc.c \
          addition.c \
          subtraction.c \
          multiplication.c \
          division.c

# Object files (auto-derived from SRCS)
OBJS    = $(SRCS:.c=.o)

# Header dependency
DEPS    = apc.h

# ============================================================
# Default target — build the binary
# ============================================================
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build successful --> ./$(TARGET)"

# ============================================================
# Compile each .c file to .o
# ============================================================
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# ============================================================
# Run a quick sanity test
# ============================================================
test: $(TARGET)
	@echo "--- Addition ---"
	./$(TARGET) 999 + 1
	./$(TARGET) -10 + 5
	@echo "--- Subtraction ---"
	./$(TARGET) 1000 - 1
	./$(TARGET) 20 - 50
	@echo "--- Multiplication ---"
	./$(TARGET) 99 '*' 99
	./$(TARGET) -10 '*' -5
	@echo "--- Division ---"
	./$(TARGET) 100 / 5
	./$(TARGET) 10 / 0

# ============================================================
# Remove object files and binary
# ============================================================
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Cleaned."

# Declare non-file targets
.PHONY: all clean test
