#include <stdio.h>

// Declare functions from other test files
void run_test_lru_cache_basics();
void run_test_lru_cache_stats();

int main()
{
    printf("Running basic tests...\n");
    run_test_lru_cache_basics();

    printf("\nRunning stats tests...\n");
    run_test_lru_cache_stats();

    printf("\nAll tests completed.\n");
    return 0;
}
