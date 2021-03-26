#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define NANOSEC 1e9

int main()
{
    struct timespec t_start, t_end;
    long long k = 500;
    const int size = 1000;
    long long elapsed_time_clz[size], elapsed_time[size];

    int i = 0;
    for (; i <= size; i++) {
        long long msb = 0;

        clock_gettime(CLOCK_MONOTONIC, &t_start);
        for (long long j = k; j; j >>= 1) {
            msb++;
        }
        clock_gettime(CLOCK_MONOTONIC, &t_end);
        elapsed_time[i] = (t_end.tv_sec * NANOSEC + t_end.tv_nsec) -
                          (t_start.tv_sec * NANOSEC + t_start.tv_nsec);
    }

    i = 0;
    for (; i <= size; i++) {
        long long msb = 0;

        clock_gettime(CLOCK_MONOTONIC, &t_start);
        msb = 64 - __builtin_clz(k);
        clock_gettime(CLOCK_MONOTONIC, &t_end);
        elapsed_time_clz[i] = (t_end.tv_sec * NANOSEC + t_end.tv_nsec) -
                              (t_start.tv_sec * NANOSEC + t_start.tv_nsec);
    }

    i = 0;
    for (; i <= size; i++) {
        printf("%d %lld %lld \n", i, elapsed_time[i], elapsed_time_clz[i]);
    }
    return 0;
}
