# different_methods_to_write_files

racteur@rogy:~/Desktop/wf$ bash parse_methods.bash 
##
Test for writing 100000 lines in file :
##
Single thread in C :
Time : 220583 ticks
##
Single thread in C with SYNCING :
Time : 9416363 ticks
##
Multi threads in C with standard libraries where each thread opens ONLY ONCE the file :
Time : 50011 ticks
##
Multi threads in C with standard libraries where each thread opens SEVERAL TIMES the file :
Time : 1444070 ticks
##
Multi threads in C with unix libraries where each thread shares the same file descriptor :
Use of write function
Time : 587395 ticks
##
Multi threads in C with unix libraries where each thread shares the same file descriptor and SYNCING :
Use of write function and fsync
Time : 13307718 ticks
##
Multi threads in C with unix libraries where each thread shares the same file descriptor :
Use of mmap function
Time : 23780 ticks
##
-rw-rw-r-- 1 racteur racteur 15500000 apr  1 12:04 only_one_fopen_standard.txt
-rw-rw-r-- 1 racteur racteur 15499380 apr  1 12:04 several_fopen_standard.txt
-rwxrwxr-x 1 racteur racteur 15500000 apr  1 12:02 single_unix.txt
-rwxrwxr-x 1 racteur racteur 15500000 apr  1 12:04 single_unix_with_fsync.txt
-rwxrwxr-x 1 racteur racteur 15500000 apr  1 12:05 use_mmap_unix.txt
-rwxrwxr-x 1 racteur racteur 15500000 apr  1 12:04 use_write_unix.txt
-rwxrwxr-x 1 racteur racteur 15500000 apr  1 12:05 use_write_unix_with_fsync.txt
