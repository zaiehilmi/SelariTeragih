import os
from time import sleep
from termcolor import colored

os.system('gcc -fopenmp ompw.c -o hai')
bebenang = [1, 2, 4, 8, 16, 32, 64]
f = open('out.txt', 'a')

for i in bebenang:
    cmd = f'export OMP_NUM_THREADS={i} && ./hai'

    # if i%2 == 0:
    print(colored('export', 'yellow'), f'OMP_NUM_THREADS={i}', colored('&&', 'green'), colored('./hai', 'yellow'))
    # f.write(f'\n=============OMP_NUM_THREADS={i}=============\n')
    f.write('[skr3308@hpdc auzaie]$ gcc -fopenmp ompw.c -o ompw')
    f.write(f'[skr3308@hpdc auzaie]$ {cmd}')
        # os.system(cmd)
    a = os.popen(cmd).readlines()
        
    for y in a:
        f.write(y)
        
    print('\n')
    sleep(5)

f.close