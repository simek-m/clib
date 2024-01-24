#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>


// TODO: Where is it defined?
#define SIZE_WIDTH __SIZE_WIDTH__

// Fat pointer metadata offsets.
#define STR_METADATA_T size_t
#define STR_LEN_OFFSET SIZE_WIDTH
#define STR_CAP_OFFSET (SIZE_WIDTH * 2)

// Default capacity for empty strings.
#define STR_DEFAULT_CAP 8

// Compute default size.
#define STR_METADATA_SIZE (SIZE_WIDTH * 2)
#define STR_DEFAULT_BUFFER_SIZE (sizeof(char) * STR_DEFAULT_CAP)
#define STR_DEFAULT_SIZE (STR_METADATA_SIZE + STR_DEFAULT_BUFFER_SIZE)

typedef char* str_t;

// str_empty allocates and initializes
// a new empty str_t with a default capacity
// (see STR_DEFAULT_CAP).
// Safety: can be only fully freed with str_free().
// Freeing through the returned str_t leaks memory!
// FIXME: Does it leak memory or is UB?!
str_t str_empty() {
    // Zero initialize.
    void *s = malloc(STR_DEFAULT_SIZE);
    if (s == NULL)
            return NULL;
    if (memset_s(s, STR_DEFAULT_SIZE, 0, STR_DEFAULT_SIZE) != 0)
                    return NULL;

    // Set capacity (length=0).
    // FIXME: Ugly!
    *((size_t*)(s + STR_METADATA_SIZE - STR_CAP_OFFSET))
            = STR_DEFAULT_CAP;

    return (char*) (s + STR_METADATA_SIZE);
}

size_t str_len(str_t s) {
        return *(s - STR_LEN_OFFSET);
}

size_t str_cap(str_t s) {
        return *(s - STR_CAP_OFFSET);
}

void str_free(str_t s) {
        free(s - STR_METADATA_SIZE);
}

///   TODO:
/// - interning (immutable)?
int main() {
        str_t s = str_empty();
        if (s == NULL) {
                fprintf(stderr, "failed to create an empty string.");
                exit(EXIT_FAILURE);
        }

        printf("string: \"%s\", length: %zu, capacity: %zu\n",
                        s, str_len(s), str_cap(s));
        str_free(s);
}
