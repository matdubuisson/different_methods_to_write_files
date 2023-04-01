#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>

#define LIMIT 100000
#define LINE "This is a line to test the speed of the programming language and the different methods to code it. What is the best between python, c and c with threads ?\n"

#define N_CORE 4

struct input{
    int fd;
    char *map;
    char *line;
    size_t size;
    uint32_t start;
    uint32_t stop;
};

void *work(void *args){
    static int sid = 0;
    int id = sid; sid++;

    struct input *in = (struct input*) args;
    
    for(uint32_t i = in->start; i < in->stop; i++){
        //printf("Thread %d\n", id);
        memcpy(in->map + (i * in->size), in->line, in->size);
        *(in->map + (i * in->size)) = in->line[0] + id; // To identify the thread
        //usleep(1000000);
    }

    return NULL;
}

int main(void){

    clock_t start = clock();

    int code = 0;

    char *line = "0 is is a line to test the speed of the programming language and the different methods to code it. What is the best between python, c and c with threads ?\n";

    size_t size = sizeof(char) * strlen(line);
    size_t fileSize = size * LIMIT;

    int fd = open("use_mmap_unix.txt", O_CREAT | O_RDWR, 0777);
    if(fd < 0){
        printf("Error : open() !!\n");
        return 1;
    }

    if(ftruncate(fd, fileSize) < 0){
        printf("Error : ftruncate() !!\n");
        code = 3;
        goto gclose;
    }

    // lseek(fd, fileSize - 1, SEEK_SET);
    // write(fd, "", sizeof(char));

    char *map = (char*) mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(map == MAP_FAILED){
        printf("Error : mmap() !!\n");
        code = 4;
        goto gmunmap;
    }

    uint32_t i;

    pthread_t threads[N_CORE];
    struct input inputs[N_CORE];
    uint64_t step;
    for(i = 0, step = 0; i < N_CORE; i++){
        inputs[i].fd = fd;
        inputs[i].map = map;
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

    if(msync(map, fileSize, MS_SYNC) < 0){
        printf("Error : msync() !!\n");
        code = 5;
    }

    gmunmap:;
    if(munmap(map, fileSize) < 0){
        printf("Error : munmap() !!\n");
        code = 5;
    }

    gclose:;
    if(close(fd) < 0){
        printf("Error : close() !!\n");
        return 2;
    }

    printf("Time : %ld ticks\n", clock() - start);

    return code;
}