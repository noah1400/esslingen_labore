/*
 * Benchmark-Utility functions & macros
 *
 * Author: Rainer Keller, HS Esslingen
 */

#ifndef __BENCH_UTILS_H__
#define __BENCH_UTILS_H__

/**************************************************************
 * Macro definitions
 **************************************************************/

#ifndef MEASUREMENTS
// If not defined in the test, or on gcc's command-line, define here.
// ATTENTION: Make sure, a computed value like 10*1000 is in ()!!!
#    define MEASUREMENTS (100*1000)
#endif

#define ERROR(s,e) do {                                     \
        fprintf (stderr, "ERROR: %s (strerror of %d:%s)\n", \
                 (s), (e), strerror((e)));                  \
        exit (e);                                           \
    } while(0)


/* Comment out the following line to get DEBUG-output */
#define DEBUG(x) x;
//#define DEBUG(x)


/**************************************************************
 * Function definitions and declarations (protected from C++)
 **************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif
inline static unsigned long long int getrdtsc(void) __attribute__((always_inline));

inline static unsigned long long int getrdtsc(void)
{   
    uint64_t x;
#if defined (__i386__)
    __asm__ volatile ("rdtsc\n" : "=A" (x));
#else
    uint32_t hi, lo;
    __asm__ volatile ("rdtsc\n" : "=a" (lo), "=d" (hi));
    x = ((uint64_t)hi << 32 | lo);
#endif
    return x;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif /* __BENCH_UTILS_H__ */
