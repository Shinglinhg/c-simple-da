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
    dynamic_array(int) nums = {0}; // creates an int dynamic array
    
    // push two values
    sda_push(nums, 32);
    sda_push(nums, 12);

    // Print the value in the index 0
    printf("%d\n", sda_get(nums, 0));

    // Pop and print the last value
    printf("%d\n", sda_pop(nums));

    // Free array memory
    sda_free(nums);
    return 0;
}
```

**warning: sda_pop() does not zero out the popped element.**
