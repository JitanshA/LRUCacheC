# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -Iinclude

# Directories
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests

# Targets and sources
TARGET = test_lru_cache
SOURCES = $(SRC_DIR)/lru_cache.c $(SRC_DIR)/key_value_pair.c $(TEST_DIR)/test_lru_cache.c
OBJECTS = $(SOURCES:.c=.o)

# Build the test executable
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run tests
test: $(TARGET)
	./$(TARGET)
