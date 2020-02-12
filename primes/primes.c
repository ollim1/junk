#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <errno.h>
#include    <math.h>
#define     max(A, B) (A > B ? A : B)

unsigned *getprimes(unsigned limit);
unsigned remaining(unsigned *set);
void printset(unsigned *set, unsigned cols);
int isprime(unsigned *set, unsigned num, unsigned end);

int main(int argc, char **argv)
{
    unsigned limit = 1000;
    unsigned cols;
    unsigned *set = NULL;

    char *endptr = NULL;

    switch (argc) {
        case 2: {
            limit = (unsigned) strtol(argv[1], &endptr, 10);
            if (endptr == argv[1])
                return -1;

            set = getprimes(limit);
            if (!set)
                return -1;
            cols = (unsigned) sqrt((double) remaining(set));
            break;
        }
        case 3: {
            limit = (unsigned) strtol(argv[1], &endptr, 10);
            if (endptr == argv[1])
                return -1;

            endptr = NULL;
            cols = (unsigned) strtol(argv[2], &endptr, 10);
            if (endptr == argv[2])
                return -1;

            set = getprimes(limit);
            if (!set)
                return -1;
            break;
        }
        default: {
            set = getprimes(limit);
            if (!set)
                return -1;

            cols = (unsigned) sqrt((double) remaining(set));
        }
    }

    printset(set, cols);

    free(set);
    return 0;
}

unsigned *getprimes(unsigned limit)
{
    if (limit < 5)
        limit = 3;
    unsigned *set = calloc(limit / 2 + 2, sizeof(unsigned));
    unsigned *ptr;
    unsigned end;
    if (!set)
        return NULL;

    set[0] = 2; set[1] = 3;
    unsigned size = 2;

    for (unsigned n = 5; n < limit; n += 2) {
        ptr = set + 1;
        end = (unsigned) sqrt((float) n);

        while (*ptr <= end) {
            if (n % *ptr++ == 0)
                goto not_prime;
        }

        set[size++] = n;
        if (n % 6 == 1)
            n += 2;

        not_prime:;
    }
    set = realloc(set, (size + 1) * sizeof(unsigned));

    return set;
}

unsigned remaining(unsigned *set)
{
    unsigned n = 0;

    while (*set++ != 0)
        n++;

    return n;
}

void printset(unsigned *set, unsigned cols)
{
    unsigned col = 0;
    int hi = 0;
    unsigned size = remaining(set);

    for (unsigned i = 0; i < size; i++) {
        int len = (int) max(floor((log10((double) set[i]))), 0);
        if (len > hi)
            hi = len;
    }

    for (int i = 0; i < size; i++) {
        int len = (int) max(floor((log10((double) set[i]))), 0);
        for (int j = hi - len; j > 0; j--)
            putchar(' ');

        printf("%d", set[i]);
        col++;
        if (col >= cols) {
            putchar('\n');
            col = 0;
        } else {
            putchar(' ');
        }
    }
    if (col)
        putchar('\n');
}
