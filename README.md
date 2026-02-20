# **C Simple Dynamic Array**
### A simple **single-header** dynamic array implementation for C.

No linking or implementation guard is required just include "simple_da.h" and use it.

## Example usage:
```c
// Compile using: cc example.c -I.
#include <simple_da.h>

#include <stdio.h> // for printf

// This is actually the recommended way, though less convenient:
// typedef dynamic_array(int) IntArray; // creates a reusable dynamic array type

int main(void) {
    dynamic_array(int) numbers = {0}; // creates a dynamic array of integers

    // push some values
    for (int i = 1; i <= 5; ++i)
        sda_push(numbers, i * 10);

    // Allocate a new element manually and set it
    int *next = sda_allocate(numbers);
    *next = 999;

    // Print all values
    printf("Array contents: ");
    for (size_t i = 0; i < numbers.count; ++i)
        printf("%d ", sda_get(numbers, i));
    printf("\n");

    // Access the last element
    printf("Last element (back): %d\n", sda_back(numbers));

    // Pop the last element
    int popped = -1;
    sda_pop(numbers, &popped);
    printf("Popped element: %d\n", popped);

    // Free memory
    sda_free(numbers);
    return 0;
}
```

**warning: sda_pop() does not zero out the popped element.**
