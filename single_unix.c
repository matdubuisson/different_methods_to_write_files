#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>

#define LIMIT 100000
#define LINE "This is a line to test the speed of the programming language and the different methods to code it. What is the best between python, c and c with threads ?\n"

int main(void){

    clock_t start = clock();

    int fd = open("single_unix.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);

    char *line = "This is a line to test the speed of the programming language and the different methods to code it. What is the best between python, c and c with threads ?\n";
    size_t size = sizeof(char) * strlen(line);

    for(uint32_t i = 0; i < LIMIT; i++){
        write(fd, line, size);
    }

    close(fd);

    printf("Time : %ld ticks\n", clock() - start);

    return 0;
}