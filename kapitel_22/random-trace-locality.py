import sys
from numpy import random
from numpy.random.mtrand import shuffle

numaddr = int(sys.argv[1])
maxpage = 10
addr = []

hot = range(0, int(maxpage / 5))
cold = range(int(maxpage / 5), maxpage)

numhot = int(numaddr / 5)
numcold = numaddr - numhot

f = open("random-trace-locality.txt", "w")

for i in range(numcold):
    x = random.randint(0, hot[-1])
    # f.write(f'{x:d}\n')
    addr.append(x)

for i in range(numhot):
    x = random.randint(cold[0], cold[-1])
    # f.write(f'{x:d}\n')
    addr.append(x)

random.shuffle(addr)

for x in addr:
    f.write(f'{x:d}\n')

f.close()
