#include <stdio.h>
#include <stdlib.h>

// LOGF output formatted message to STDERR.
// Usage: format has to be a literal.
#define LOGF(format, ...) \
        fprintf(stderr, format"\n"  __VA_OPT__(,) __VA_ARGS__)

