# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -Iinclude

# Directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Targets and sources
TARGET = test_lru_cache
SRC_SOURCES = $(SRC_DIR)/lru_cache.c $(SRC_DIR)/node_utils.c $(SRC_DIR)/hash_utils.c $(SRC_DIR)/key_value_pair.c
TEST_SOURCES = $(TEST_DIR)/test_main.c $(TEST_DIR)/test_lru_cache_basics.c $(TEST_DIR)/test_lru_cache_stats.c
SOURCES = $(SRC_SOURCES) $(TEST_SOURCES)
OBJECTS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SOURCES)))

# Build the test executable
all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $(OBJECTS)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run tests
test: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean test
