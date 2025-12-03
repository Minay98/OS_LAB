/* A very small unit test header (inspired by minunit, but simplified). */

#ifndef MINUNIT_H
#define MINUNIT_H

#include <stdio.h>

#define MU_ASSERT(message, test) do { if (!(test)) return message; } while (0)
#define MU_RUN_TEST(test) do { \
    const char *message = test(); \
    tests_run++; \
    if (message) return message; \
} while (0)

extern int tests_run;

#endif /* MINUNIT_H */
