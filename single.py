import os
import time
# import tqdm

LIMIT = 10000
line = "This is a line to test the speed of the programming language and the different methods to code it. What is the best between python, c and c with threads ?\n"

start = time.time()
fd = os.open("python.txt", os.O_CREAT | os.O_TRUNC | os.O_WRONLY)
for i in range(LIMIT):
    os.write(fd, line.encode())
    os.fsync(fd)
os.close(fd)
    
print("Time taken : {0} seconds".format(time.time() - start))