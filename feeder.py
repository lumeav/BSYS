#!/usr/bin/env python3
from multiprocessing import Barrier
import argparse
import logging
import time
import signal
import sys
import threading
import queue

import collections

from animal import Dog, Cat, Mouse, State
from dish import Dishes

cats = []
dogs = []
mouse = []

root = logging.getLogger()
# you can use CRITICAL,ERROR,WARNING,INFO or DEBUG
root.setLevel(logging.WARNING)
handler = logging.StreamHandler(sys.stdout)
handler.setLevel(logging.WARNING)
formatter = logging.Formatter('%(levelname)8s:%(asctime)24s\t%(message)s')
handler.setFormatter(formatter)
root.addHandler(handler)


def init():
    parser = argparse.ArgumentParser(description='Tierfütterer')

    # Anzahl
    parser.add_argument('--cn', dest='cn', action='store', default=6, type=int,
                        help='Anzahl der Katzen. (Standard 6)')
    parser.add_argument('--dn', dest='dn', action='store', default=4, type=int,
                        help='Anzahl der Hunde. (Standard 4)')
    parser.add_argument('--mn', dest='mn', action='store', default=2, type=int,
                        help='Anzahl der Mäuse. (Standard 2)')
    parser.add_argument('--dish', dest='dish', action='store', default=2, type=int,
                        help='Anzahl der Futterschalen. (Default 2)')

    # Schlafzeit
    parser.add_argument('--ct', dest='ct', action='store', default=15, type=int,
                        help='Anzahl der Sekunden die eine Katze satt ist. (Standard 15)')
    parser.add_argument('--dt', dest='dt', action='store', default=10, type=int,
                        help='Anzahl der Sekunden die ein Hund satt ist. (Standard 10)')
    parser.add_argument('--mt', dest='mt', action='store', default=1, type=int,
                        help='Anzahl der Sekunden die eine Maus satt ist. (Standard 1)')

    # Essenszeit
    parser.add_argument('--ce', dest='ce', action='store', default=4, type=int,
                        help='Anzahl der Sekunden die eine Katze isst bis sie satt ist. (Standard 4)')
    parser.add_argument('--de', dest='de', action='store', default=2, type=int,
                        help='Anzahl der Sekunden die ein Hund isst bis er satt ist. (Standard 2)')
    parser.add_argument('--me', dest='me', action='store', default=1, type=int,
                        help='Anzahl der Sekunden die eine Maus isst bis sie satt ist. (Standard 1)')

    # Leben
    parser.add_argument('--cd', dest='cd', action='store', default=7, type=int,
                        help='Anzahl der Sekunden die eine Katze in ihrem Leben insgesamt hungern kann. (Standard 7)')
    parser.add_argument('--dd', dest='dd', action='store', default=4, type=int,
                        help='Anzahl der Sekunden die ein Hund in seinem Leben insgesamt hungern kann. (Standard 4)')
    parser.add_argument('--md', dest='md', action='store', default=2, type=int,
                        help='Anzahl der Sekunden die eine Maus in ihrem Leben insgesamt hungern kann. (Standard 2)')

    args = parser.parse_args()
    dishes = Dishes(args.dish)
    barrier = Barrier(args.cn+args.dn+args.mn+1)
    signal.signal(signal.SIGINT, signal_handler_exit)
    for i in range(0, args.cn):
        cats.append(Cat(dishes=dishes, satisfied_time_s=args.ct, eat_time_s=args.ce, life_time_s=args.cd, barrier=barrier))
    for i in range(0, args.dn):
        dogs.append(Dog(dishes=dishes, satisfied_time_s=args.dt, eat_time_s=args.de, life_time_s=args.dd, barrier=barrier))
    for i in range(0, args.mn):
        mouse.append(Mouse(dishes=dishes, satisfied_time_s=args.mt, eat_time_s=args.me, life_time_s=args.md, barrier=barrier))
    # Startline ------------------
    barrier.wait()
    print("All ready!")


def signal_handler_exit(sig, frame):
    in_the_end()
    sys.exit(0)


def in_the_end():
    # now we are waiting for all to die
    sum_lifetime = 0.
    try:
        for c in cats:
            c.join()
            sum_lifetime += c.get_lifetime()
        for d in dogs:
            d.join()
            sum_lifetime += d.get_lifetime()
        for m in mouse:
            m.join()
            sum_lifetime += m.get_lifetime()
    except:
        pass
    # this is your result.
    if sum_lifetime > 0.0:
        print("Lifetime:%f" % sum_lifetime)


def main():

    animal = [dogs,mouse,cats]
    animallist = []

    sat_que = collections.deque()
    strav_que = collections.deque()

    for a in animal:
        for ani in a:
            animallist.append(ani)


    size = len(animallist)

    for i in range(size):
        for j in range(i):
           if (animallist[j].get_remaining_status_times_s()[animallist[j].get_status()] > animallist[j+1].get_remaining_status_times_s()[animallist[j+1].get_status()]):
                tmp = animallist[j]
                animallist[j] = animallist[j+1]
                animallist[j+1] = tmp

    for a in animallist:
        sat_que.append(a)


    for i in range(0, 200):
        if len(strav_que) > 0:
            animal = strav_que.popleft()
            animal.goto_dishes()
        elif len(sat_que) > 0:
            animal = sat_que.popleft()
            animal.goto_dishes()

        animal.wakeup()
        time.sleep(0.1)

        removement = []

        for a in sat_que:
            if (State(a.get_status()) == State.STRAVING):
                removement.append(a)
                if (len(strav_que) < 1):
                    strav_que.append(a)
                else:
                    j = 0
                    t2 = a.get_remaining_status_times_s()[a.get_status()]
                    while (t2 > strav_que[j].get_remaining_status_times_s()[strav_que[j].get_status()]):
                        j = j + 1
                    strav_que.insert(j, a)

        for r in removement:
            sat_que.remove(r)

        if (State(animal.get_status()) == State.SATISFIED):
            t = animal.get_remaining_status_times_s()[animal.get_status()]
            if (len(sat_que) < 1):
                sat_que.append(animal)
            else:
                j = 0
                while (t > sat_que[j].get_remaining_status_times_s()[sat_que[j].get_status()]):
                    j = j + 1
                sat_que.insert(j, animal)









if __name__ == "__main__":
    init()
    main()
    in_the_end()
