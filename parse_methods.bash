#!/bin/bash

rm *.txt

echo "##"
echo "Test for writing 100000 lines in file :"

echo "##"
echo "Single thread in C :"
gcc -Werror -Wall single_unix.c -o prog -lpthread && ./prog

echo "##"
echo "Single thread in C with SYNCING :"
gcc -Werror -Wall single_unix_with_fsync.c -o prog -lpthread && ./prog

echo "##"
echo "Multi threads in C with standard libraries where each thread opens ONLY ONCE the file :"
gcc -Werror -Wall standard_multiple.c -o prog -lpthread && ./prog

echo "##"
echo "Multi threads in C with standard libraries where each thread opens SEVERAL TIMES the file :"
gcc -Werror -Wall standard_progressive_multiple.c -o prog -lpthread && ./prog

echo "##"
echo "Multi threads in C with unix libraries where each thread shares the same file descriptor :"
echo "Use of write function"
gcc -Werror -Wall normal_unix_multiple.c -o prog -lpthread && ./prog

echo "##"
echo "Multi threads in C with unix libraries where each thread shares the same file descriptor and SYNCING :"
echo "Use of write function and fsync"
gcc -Werror -Wall normal_unix_multiple_with_fsync.c -o prog -lpthread && ./prog

echo "##"
echo "Multi threads in C with unix libraries where each thread shares the same file descriptor :"
echo "Use of mmap function"
gcc -Werror -Wall mmap_unix_multiple.c -o prog -lpthread && ./prog

echo "##"
ls -l | grep txt