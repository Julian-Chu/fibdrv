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
    char buf[256];
    char write_buf[] = "testing writing";
    int offset = 100; /* TODO: try test something bigger than the limit */
    struct timespec t_start, t_end;
    clockid_t clk_id = CLOCK_MONOTONIC;
    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    /* Now lock all current and future pages
       from preventing of being paged */
    if (mlockall(MCL_CURRENT | MCL_FUTURE))
        printf("mlockall failed:");

    for (int i = 0; i <= offset; i++) {
        lseek(fd, i, SEEK_SET);
        clock_gettime(CLOCK_MONOTONIC, &t_start);
        write(fd, write_buf, 256);
        clock_gettime(CLOCK_MONOTONIC, &t_end);
    }

    for (int i = 0; i <= offset; i++) {
        long long sz, kt, elapsed_time;
        lseek(fd, i, SEEK_SET);
        clock_gettime(clk_id, &t_start);
        sz = read(fd, buf, 1);
        kt = write(fd, write_buf, strlen(write_buf));
        clock_gettime(clk_id, &t_end);
        elapsed_time = (t_end.tv_sec * NANOSEC + t_end.tv_nsec) -
                       (t_start.tv_sec * NANOSEC + t_start.tv_nsec);
        printf("%d %lld %lld %lld %lld\n", i, sz, kt, elapsed_time,
               elapsed_time - kt);
    }


    close(fd);
    return 0;
}
