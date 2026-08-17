// CC0 Simple dynamic arrays in C. 
// Doesn't require STB style implementation nor linking, 
// include this header wherever you need and start using it!

#ifndef SDA_H_
#define SDA_H_

#ifndef NO_LIBC
#include <stddef.h>
#include <stdlib.h>
#endif

#ifndef SDA_INITIAL_CAPACITY
#define SDA_INITIAL_CAPACITY 8 // Initial capacity of an empty array
#endif

#ifndef SDA_REALLOC
#define SDA_REALLOC realloc
#endif
#ifndef SDA_FREE
#define SDA_FREE free
#endif

#ifndef SDA_EXIT_FAILURE
#ifdef EXIT_FAILURE
#define SDA_EXIT_FAILURE EXIT_FAILURE
#else
#define SDA_EXIT_FAILURE 1
#endif
#endif

// What the library should do when out of memory for allocations
#ifndef SDA_ON_OOM
#   ifndef NO_LIBC
#       include <stdio.h>
#   endif
#   define SDA_ON_OOM do { fprintf(stderr, "Out of memory\n"); exit(SDA_EXIT_FAILURE); } while (0)
#endif

#define dynamic_array(type) \
struct { \
    type *items; \
    size_t count; \
    size_t capacity; \
}

#define sda_size(array) ((array)->count)

#define sda_push(array, ...) do { \
    if ((array)->count >= (array)->capacity) { \
        (array)->capacity = (array)->capacity ? (array)->capacity * 2 : SDA_INITIAL_CAPACITY; \
        void *tmp = SDA_REALLOC((array)->items, (array)->capacity * sizeof(*(array)->items)); \
        if (!tmp) SDA_ON_OOM; \
        (array)->items = tmp; \
    } \
    (array)->items[(array)->count++] = (__VA_ARGS__); \
} while (0)

#define sda_allocate(array) ({ \
    if ((array)->count >= (array)->capacity) { \
        (array)->capacity = (array)->capacity ? (array)->capacity * 2 : SDA_INITIAL_CAPACITY; \
        void *tmp = SDA_REALLOC((array)->items, (array)->capacity * sizeof(*(array)->items)); \
        if (!tmp) SDA_ON_OOM; \
        (array)->items = tmp; \
    } \
    &(array)->items[(array)->count++]; \
})


#define sda_get_val(array, index) ((array)->items[(index)])
#define sda_get(array, index) (&(array)->items[(index)])
#define sda_back_val(array) ((array)->count > 0 ? (array)->items[(array)->count - 1] : NULL)
#define sda_back(array) ((array)->count > 0 ? &((array)->items[(array)->count - 1]) : NULL)

#define sda_free(array) \
    do { \
        SDA_FREE((array)->items); \
        (array)->items = NULL; \
        (array)->count = (array)->capacity = 0; \
    } while (0)

#define sda_pop(array, out_ptr) \
    do { \
        if ((array)->count > 0) \
            *(out_ptr) = (array)->items[--(array)->count]; \
    } while (0)

#endif // SDA_H_
