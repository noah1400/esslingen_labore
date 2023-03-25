#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include "bench_utils.h"

#define MAX_SIZE 16777216
#define SLEEP_TIME 1

int main(int argc, char *argv[])
{
    const int sizes[] = {64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216};
    const int sizes_num = sizeof(sizes) / sizeof(sizes[0]);
    int pipefd[2] = {0};
    pid_t pid;
    char *buff;
    int ret;

    for (int i = 0; i < sizes_num; i++)
    {
        ret = pipe(pipefd);
        if (ret == -1)
        {
            err(EXIT_FAILURE, "pipe");
        }

        pid = getpid();
        pid_t pid_child = fork();
        if (pid_child == -1)
        {
            err(EXIT_FAILURE, "fork");
        }

        buff = malloc(sizes[i]);
        if (buff == NULL)
        {
            err(EXIT_FAILURE, "malloc");
        }

        if (pid_child == 0)
        {
            /* CHILD */
            int nread = 1;
            close(pipefd[1]);

            while (nread != 0)
            {
                nread = read(pipefd[0], buff, sizes[i]);
            }

            free(buff);
            exit(EXIT_SUCCESS);
        }
        else
        {
            int *ticks = malloc(MEASUREMENTS * sizeof(int));
            if (ticks == NULL)
            {
                err(EXIT_FAILURE, "malloc");
            }

            memset(ticks, 0, MEASUREMENTS * sizeof(int));
            int min_ticks;
            int max_ticks;
            long long ticks_all;
            struct timeval tv_start;
            struct timeval tv_stop;
            double time_delta_sec;

            sleep(SLEEP_TIME);

            gettimeofday(&tv_start, NULL);
            close(pipefd[0]);

            for (int j = 0; j < MEASUREMENTS; j++)
            {
                unsigned long long start = getrdtsc();

                ret = write(pipefd[1], buff, sizes[i]);
                if (ret != sizes[i])
                {
                    perror("write");
                    exit(EXIT_FAILURE);
                }

                unsigned long long stop = getrdtsc();
                ticks[j] = stop - start;
            }

            gettimeofday(&tv_stop, NULL);

            min_ticks = INT_MAX;
            max_ticks = INT_MIN;
            ticks_all = 0;
            for (int j = 0; j < MEASUREMENTS; j++)
            {
                if (min_ticks > ticks[j])
                {
                    min_ticks = ticks[j];
                }
                if (max_ticks < ticks[j])
                {
                    max_ticks = ticks[j];
                }
                ticks_all += ticks[j];
            }
            ticks_all -= min_ticks;
            ticks_all -= max_ticks;

            time_delta_sec = ((tv_stop.tv_sec - tv_start.tv_sec) + ((tv_stop.tv_usec - tv_start.tv_usec) / (1000.0 * 1000.0)));

            printf("PID:%d time: min:%d max:%d Ticks Avg without min/max:%f Ticks (for %d measurements) for %d Bytes (%.2f MB/s)\n",
                   pid, min_ticks, max_ticks,
                   (double)ticks_all / (MEASUREMENTS - 2.0), MEASUREMENTS, sizes[i],
                   ((double)sizes[i] * MEASUREMENTS) / (1024.0 * 1024.0 * time_delta_sec));

            close(pipefd[1]);
            free(ticks);
        }
        free(buff);
   }
   exit(EXIT_SUCCESS);
}