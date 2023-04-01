#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#define LIMIT 100000
#define LINE "This is a line to test the speed of the programming language and the different methods to code it. What is the best between python, c and c with threads ?\n"

#define N_CORE 4

struct input{
    char *fileName;
    char *line;
    size_t size;
    uint32_t start;
    uint32_t stop;
};

void *work(void *args){
    static int sid = 0;
    int id = sid; sid++;

    struct input *in = (struct input*) args;

    int fd = open(in->fileName, O_RDWR);

    lseek(fd, in->start * in->size, SEEK_SET);

    char c;
    for(uint32_t i = in->start; i < in->stop; i++){
//        printf("Thread %d\n", id);
        c = in->line[0] + id;
        write(fd, &c, sizeof(char));
        write(fd, &in->line[1], in->size - 1);
        fsync(fd);
//        usleep(500000);
    }

    close(fd);

    return NULL;
}

int main(void){

    clock_t start = clock();

    int code = 0;

    char *line = "0 is is a line to test the speed of the programming language and the different methods to code it. What is the best between python, c and c with threads ?\n";

    size_t size = sizeof(char) * strlen(line);
    // size_t fileSize = size * LIMIT;

    char *fileName = "use_write_unix_with_fsync.txt";

    int fd = open(fileName, O_CREAT | O_RDWR, 0777);
    if(fd < 0){
        printf("Error : open() !!\n");
        return 1;
    }

    // if(ftruncate(fd, fileSize) < 0){
    //     printf("Error : ftruncate() !!\n");
    //     code = 3;
    //     goto gclose;
    // }

    uint32_t i;
    pthread_t threads[N_CORE];
    struct input inputs[N_CORE];
    uint64_t step;
    for(i = 0, step = 0; i < N_CORE; i++){
        inputs[i].fileName = fileName;
        inputs[i].line = line;
        inputs[i].size = size;
        inputs[i].start = step;
        step += (uint32_t) LIMIT / N_CORE;
        if(i + 1 == N_CORE) step += (uint32_t) LIMIT % N_CORE;
        inputs[i].stop = step;
        pthread_create(&threads[i], NULL, work, (void*) &inputs[i]);
    }

    for(i = 0; i < N_CORE; i++){
        pthread_join(threads[i], NULL);
    }

    //gclose:;
    if(close(fd) < 0){
        printf("Error : close() !!\n");
        return 2;
    }

    printf("Time : %ld ticks\n", clock() - start);

    return code;
}