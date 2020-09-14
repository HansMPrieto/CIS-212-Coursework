/*
 * itest - show how to instrument a function and print the results
 *
 * usage: ./itest [--calls=<number of calls>]
 * 
 * the instrumented function will be called `calls' times; default is 1000
 *
 * outputs number of calls and ms of elapsed time on stderr
 *
 * Author: Joe Sventek
 */
#include <stdio.h>         /* for fprintf() */
#include <string.h>        /* for strncmp() */
#include <stdlib.h>        /* for atoi() */
#include <time.h>          /* for struct timespec & nanosleep() */
#include <sys/time.h>      /* for struct timeval & gettimeofday() */

#define USESTR "usage: %s [--calls=n]\n"

typedef struct accumulator {
    char *name;
    long long calls;
    long long musecs;
} Accumulator;

long nAccumulators = 0L;
Accumulator *accumulators[1000];

void instrumented_function(void) {
    struct timeval t1, t2;
    static int init = 1;
    static Accumulator ac = {"instrumented_function", 0LL, 0LL};

    if (init) {
        accumulators[nAccumulators++] = &ac;
        init = 0;
    }
    (void)gettimeofday(&t1, NULL);
    {
        struct timespec oneMs = {0, 1000000L}; /* one millisecond */
        nanosleep(&oneMs, NULL);
    }
    (void)gettimeofday(&t2, NULL);
    ac.musecs += 1000000 * (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec);
    ac.calls += 1LL;
}

void dumpAccumulators(FILE *fd) {
    long k;

    for (k = 0L; k < nAccumulators; k++) {
        Accumulator *ac = accumulators[k];
        long long musecs = ac->musecs;
        fprintf(fd, "%-20s ", ac->name);
        fprintf(fd, "%12Ld calls ", ac->calls);
        fprintf(fd, "%15Ld.%03dms\n", musecs / 1000, (int)(musecs % 1000));
    }
}

int main(int argc, char *argv[]) {
    int i, n = 1000;

    for (i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--calls=", 8) == 0)
            n = atoi(argv[i]+8);
        else {
            fprintf(stderr, "Illegal flag: %s\n", argv[i]);
            fprintf(stderr, USESTR, argv[0]);
            return 1;
        }
    }
    /* initialize the instrumentation system - nothing to do */
    for (i = 0; i < n; i++) {
        instrumented_function();
    }
    dumpAccumulators(stderr);
    return 0;
}
