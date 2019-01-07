#define _GNU_SOURCE
#include <unistd.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <sys/syscall.h>
#include <pthread.h>

static volatile int done;

void *run_deadline(void *data)
{
    struct sched_attr attr;
    int x = 0, ret;
    unsigned int flags = 0;

    printf("deadline thread start %ld\n",
        gettid());

    attr.size = sizeof(attr);
    attr.sched_flags = 0;
    attr.sched_nice = 0;
    attr.sched_priority = 0;

    /* creates a 10ms/30ms reservation */
    attr.sched_policy = 6;
    attr.sched_runtime = 10 * 1000 * 1000;
    attr.sched_period  = 30 * 1000 * 1000;
    attr.sched_deadline= 30 * 1000 * 1000;

    ret = sched_setattr(0, &attr, flags);
    if (ret < 0) {
        done = 0;
        perror("sched_setattr");
        exit(-1);
    }

    while (!done) {
        x++;
    }
    return NULL;
}

int main (int argc, char **argv)
{
    pthread_t thread;

    printf("main thread [%ld]\n", gettid());
    pthread_create(&thread, NULL, run_deadline, NULL);
    sleep(10);
    done = 1;
    pthread_join(thread, NULL);
    printf("main dies [%ld]\n", gettid());
    return 0;
}
