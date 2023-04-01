#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <time.h>
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

    FILE *fd = fopen(in->fileName, "w");
    fclose(fd);

    char c;
    for(uint32_t i = in->start; i < in->stop; i++){
        fd = fopen(in->fileName, "a");
        fseek(fd, i * strlen(in->line), SEEK_SET);
        //printf("Thread %d\n", id);
        c = in->line[0] + id;
        fwrite(&c, 1, sizeof(char), fd);
        fwrite(&in->line[1], strlen(in->line) - 1, sizeof(char), fd);
        //#include <unistd.h>
        //usleep(500000);
        fclose(fd);
    }

    return NULL;
}

int main(void){

    clock_t start = clock();

    int code = 0;

    char *line = "0 is is a line to test the speed of the programming language and the different methods to code it. What is the best between python, c and c with threads ?\n";

    size_t size = sizeof(char) * strlen(line);

    char *fileName = "several_fopen_standard.txt";

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

    printf("Time : %ld ticks\n", clock() - start);

    return code;
}