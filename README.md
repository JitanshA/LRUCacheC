# LRU Cache Project

This project implements a **Least Recently Used (LRU) Cache** in C, designed for high efficiency and modularity. The cache is built to handle operations with optimal performance and offers several extensible features to adapt to various use cases.

---

## Features

### Core Cache Features
- **Key-Value Pair Management**: Handles data in a key-value format with efficient lookup.
- **LRU Eviction Policy**: Automatically removes the least recently used items when the cache reaches its capacity.
- **Dynamic Resizing**: Allows for increasing or decreasing the cache size dynamically.
- **Cache Statistics**: Tracks:
  - Cache hits
  - Cache misses
  - Miss rates
  - Ability to reset statistics during runtime.

---

## Directory Structure

```plaintext
LRUCacheC/
├── include/               # Header files
│   ├── hash_utils.h       # Hashing utility functions
│   ├── key_value_pair.h   # Key-value pair management
│   ├── lru_cache.h        # LRU Cache API
│   ├── node_utils.h       # Node management utilities
├── src/                   # Source files
│   ├── hash_utils.c       # Hashing utility implementations
│   ├── key_value_pair.c   # Key-value pair management implementations
│   ├── lru_cache.c        # LRU Cache core functionality
│   ├── node_utils.c       # Node management utility implementations
├── tests/                 # Test files
│   ├── test_main.c        # Entry point for test cases
│   ├── test_lru_cache_basics.c # Tests for basic operations
│   ├── test_lru_cache_stats.c  # Tests for statistics and resizing
├── build/                 # Compiled object files (generated during build)
├── Makefile               # Build system
├── README.md              # Project documentation
```

---

## Setup and Usage

### Prerequisites
- **Compiler**: GCC or Clang
- **Build System**: Make

### Building the Project
1. Clone the repository:
    ```bash
    git clone <repository_url>
    cd LRUCacheC
    ```
2. Build the project:
    ```bash
    make
    ```

---

### Running Tests
Run all test cases to verify the functionality:
```bash
make test
```

---

## Testing Highlights

The project includes comprehensive test cases to validate its functionality:

### Basic Cache Operations
- Adding key-value pairs.
- Retrieving values.
- Eviction on reaching capacity.

### Dynamic Resizing
- Resizing the cache both up and down while maintaining data integrity.

### Cache Statistics
- Validating hit/miss counts.
- Resetting statistics.

### Edge Cases
- Handling invalid inputs.
- Operations on empty or full caches.