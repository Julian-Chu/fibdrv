#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>  // Needed for mlockall()
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"
#define NANOSEC 1e9

int main()
{
    struct timespec t_start, t_end;
    long long k = 500;

    for (int i = 0; i <= 1000; i++) {
        long long msb = 0;
        long long elapsed_time, elapsed_time_clz;

        clock_gettime(CLOCK_MONOTONIC, &t_start);
        for (long long j = k; j; j >>= 1) {
            msb++;
        }
        clock_gettime(CLOCK_MONOTONIC, &t_end);
        elapsed_time_clz = (t_end.tv_sec * NANOSEC + t_end.tv_nsec) -
                           (t_start.tv_sec * NANOSEC + t_start.tv_nsec);

        msb = 0;
        clock_gettime(CLOCK_MONOTONIC, &t_start);
        msb = 64 - __builtin_clz(k);
        clock_gettime(CLOCK_MONOTONIC, &t_end);
        elapsed_time = (t_end.tv_sec * NANOSEC + t_end.tv_nsec) -
                       (t_start.tv_sec * NANOSEC + t_start.tv_nsec);


        printf("%d %lld %lld %lld\n", i, elapsed_time, elapsed_time_clz, msb);
    }

    return 0;
}
