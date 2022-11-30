import sys
from numpy import random

numaddr = int(sys.argv[1])
maxpage = 10

f = open("random-trace.txt", "w")

for i in range(numaddr):
    x = random.randint(maxpage)
    f.write(f'{x:d}\n')

f.close()