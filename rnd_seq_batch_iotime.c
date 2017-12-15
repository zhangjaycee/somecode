#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>

#define FILENAME "fio_testdata"

unsigned long long td( struct timeval *t1, struct timeval *t2 )
{
    unsigned long long dt = t2->tv_sec * 1000000 + t2->tv_usec;
    return dt - t1->tv_sec * 1000000 - t1->tv_usec;
}

int main()
{
    struct timeval t0, t1;
    int fd = open(FILENAME, O_RDWR|O_DIRECT|O_SYNC);
    int i, n;
    char *buf, *buf2;
    posix_memalign(&buf,512,16384);
    int count_size;

    struct stat st;
    fstat(fd, &st);  
    printf("fd: %d, file size: %lu\n", fd, st.st_size);

    int MAX_P = 4000000;
    int times = 10;
    unsigned long long  r_seq[times * 3];

    srand(time(NULL));
    for (i=0; i < times * 3; i++){
        r_seq[i] = rand() % MAX_P;
        r_seq[i] *= 512;
        printf("r_seq = %lu\n", r_seq[i]);
    }
    /*
    float seq_16 = 0;
    float seq_8 = 0;
    float seq_4 = 0;
    */
    int seq_16 = 0;
    int seq_8 = 0;
    int seq_4 = 0;
    int times_i = times;
    while (times_i--) {
        int rnd_i = 0;
        //seq 16k  16k x 2500 = 40000k
        gettimeofday(&t0, NULL);
        srand(time(NULL));
        count_size = 0;
        for (i = 0; i < 2500; i++){
            n = pread(fd, buf, 16384, r_seq[rnd_i] + i*16384);
            count_size += n;
        }
        gettimeofday(&t1, NULL);
        seq_16 += td(&t0, &t1)/1000.0;
        printf("time(batch4, seq 16k): %f ms  total_size %d\n", td(&t0, &t1)/1000.0, count_size);

        //seq 8k  8k x 5000 = 40000k
        rnd_i++;
        gettimeofday(&t0, NULL);
        count_size = 0;
        for (i = 0; i < 5000; i++){
            n = pread(fd, buf, 8192, r_seq[rnd_i] + i*8192);
            count_size += n;
        }
        gettimeofday(&t1, NULL);
        seq_8 += td(&t0, &t1)/1000.0;
        //printf("time(batch2 seq 8k): %f ms  total_size %d\n", td(&t0, &t1)/1000.0, count_size);

        //seq 4k  4k x 10000 = 40000k
        rnd_i++;
        gettimeofday(&t0, NULL);
        srand(time(NULL));
        count_size = 0;
        for (i = 0; i < 10000; i++){
            n = pread(fd, buf, 4096, r_seq[rnd_i] + i*4096);
            count_size += n;
        }
        gettimeofday(&t1, NULL);
        seq_4 += td(&t0, &t1)/1000.0;
        //printf("time(batch1 seq 4k): %f ms  total_size %d\n", td(&t0, &t1)/1000.0, count_size);
    }
    printf("time(batch1 seq 16k): %f ms  \n", seq_16 * 1.0/times);
    printf("time(batch1 seq  8k): %f ms  \n", seq_8 * 1.0/times);
    printf("time(batch1 seq  4k): %f ms  \n", seq_4 * 1.0/times);
    


    // Random:

    int r[10000];

    //rnd 8k  8k x 5000 = 40000k = 40Mb
    srand(time(NULL));
    for (i = 0; i < 5000; i++){
        r[i] = rand() % MAX_P;
    }
    gettimeofday(&t0, NULL);
    count_size = 0;
    for (i = 0; i < 5000; i++){
        n = pread(fd, buf, 8192, r[i]*8192);
        count_size += n;
    }
    gettimeofday(&t1, NULL);
    printf("time(rand1 rand 8k): %f ms  total_size %d\n", td(&t0, &t1)/1000.0, count_size);


    //rnd 4k  4k x 10000 = 40000k = 40mb
    srand(time(NULL));
    for (i = 0; i < 10000; i++){
        r[i] = rand() % MAX_P;
    }
    gettimeofday(&t0, NULL);
    count_size = 0;
    for (i = 0; i < 10000; i++){
        n = pread(fd, buf, 4096, r[i]*4096);
        count_size += n;
    }
    gettimeofday(&t1, NULL);
    printf("time(rand1 rand 4k): %f ms  total_size %d\n", td(&t0, &t1)/1000.0, count_size);
    return 0;
}

