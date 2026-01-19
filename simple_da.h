// CC0 Simple dynamic arrays in C. 
// Doesn't require STB style implementation nor linking, 
// include this header wherever you need and start using it!

#ifndef SDA_H
#define SDA_H

// C++ Warning message
#ifndef SDA_ALLOW_CPP
#    ifdef __cplusplus
#        if defined(_MSC_VER)
#            pragma message("simple_da.h: This library is intended for C, not C++. If you REALLY want to use it, define a macro 'SDA_ALLOW_CPP' before including this file")
#        else
#            warning "simple_da.h: This library is intended for C, not C++. If you REALLY want to use it, define a macro 'SDA_ALLOW_CPP' before including this file"
#        endif
#    endif
#endif

#ifndef NO_STANDARD_LIBRARY
#   include <stddef.h>
#   include <stdlib.h>
#endif

// Initial capacity of an empty array
#ifndef SDA_INITIAL_CAPACITY
#   define SDA_INITIAL_CAPACITY 8
#endif

// Which realloc and free function should be used
#ifndef SDA_FUNC_REALLOC
#   define SDA_FUNC_REALLOC realloc
#endif
#ifndef SDA_FUNC_FREE
#   define SDA_FUNC_FREE free
#endif

// What the library should do when out of memory for reallocations
#ifndef SDA_ON_OOM
#   ifndef NO_STANDARD_LIBRARY
#       include <stdio.h>
#   endif
#   define SDA_ON_OOM do { fprintf(stderr, "Out of memory\n"); exit(EXIT_FAILURE); } while (0)
#endif

#define dynamic_array(type) struct { \
    type *items; \
    size_t count; \
    size_t capacity; \
}

#define sda_push(array, val) do { \
    if ((array).count >= (array).capacity) { \
        (array).capacity = (array).capacity ? (array).capacity * 2 : SDA_INITIAL_CAPACITY; \
        void *tmp = SDA_FUNC_REALLOC((array).items, (array).capacity * sizeof(*(array).items)); \
        if (!tmp) SDA_ON_OOM; \
        (array).items = tmp; \
    } \
    (array).items[(array).count++] = (val); \
} while (0)

#define sda_get(array, index) ((array).items[(index)])
#define sda_back(array) ((array).count > 0 ? (array).items[(array).count - 1] : 0)
// WARNING: POP DOESN'T ZERO OUT THE POPPED ELEMENT
#define sda_pop(array) ((array).count > 0 ? (array).items[--(array).count] : 0)
#define sda_free(array) do { SDA_FUNC_FREE((array).items); (array).items = NULL; (array).count = (array).capacity = 0; } while (0)

#endif // SDA_H