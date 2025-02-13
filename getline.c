#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Custom getline implementation for Windows
ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
    size_t pos;
    int c;

    if (lineptr == NULL || stream == NULL || n == NULL) {
        errno = EINVAL;
        return -1;
    }

    // Allocate buffer if needed
    if (*lineptr == NULL) {
        *n = 128; // Initial buffer size
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL) {
            return -1;
        }
    }

    pos = 0;

    while ((c = getc(stream)) != EOF) {
        if (pos + 1 >= *n) {
            size_t new_size = *n + (*n >> 2);
            char *new_ptr = (char *)realloc(*lineptr, new_size);
            if (new_ptr == NULL) {
                return -1;
            }
            *n = new_size;
            *lineptr = new_ptr;
        }

        (*lineptr)[pos++] = c;

        if (c == '\n') {
            break;
        }
    }

    if (pos == 0) {
        return -1;
    }

    (*lineptr)[pos] = '\0';
    return pos;
}