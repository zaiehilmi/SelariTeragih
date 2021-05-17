import os
from time import sleep
from termcolor import colored

os.system('gcc -fopenmp 4_workshareOmp.c -o hai')
bebenang = [1, 2, 4, 8, 16, 32, 64]
f = open('namafailoutput.dat', 'a')
for i in bebenang:
    cmd = f'export OMP_NUM_THREADS={i} && ./hai'

    if i%2 == 0:
        print(colored('export', 'yellow'), f'OMP_NUM_THREADS={i}', colored('&&', 'green'), colored('./hai', 'yellow'))
        f.write(f'\n=============OMP_NUM_THREADS={i}=============\n')
        # os.system(cmd)
        a = os.popen(cmd).readlines()
        
        for y in a:
            f.write(y)
        
        print('\n')
        sleep(5)

f.close