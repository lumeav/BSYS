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


def getShortestEatingTime(eating, animal):
    min = 100000        # just a big number
    for i in range(0, len(eating)):
        t = eating[i].get_remaining_status_times_s()[eating[i].get_status()]
        if t < min:
            min = t
            animal = eating[i]
    return animal


def orderInto(que, animal):
    t = animal.get_remaining_status_times_s()[animal.get_status()]
    if (len(que) < 1):
        que.append(animal)
    else:
        j = 0
        for j in range(0, len(que)):
            que[j].wakeup()
            if(t < que[j].get_remaining_status_times_s()[que[j].get_status()]):
                break
        que.insert(j, animal)

#ORDER INTO STRAV_QUE BY LIFETIME (ARRIVAL TIME)
def orderInto_fcfs(que, animal):
    t = animal.get_lifetime()
    if (len(que) < 1):
        que.append(animal)
    else:
        j = 0
        while (t < que[j].get_lifetime()):
            j = j + 1
            if (j == len(que)):
                break
        que.insert(j, animal)


def animalWouldKill(eating, animal):
        if (getattr(animal, 'ANIMAL_TYPE') == 1):  # If Cat
            for j in range(0, len(eating)):
                if (getattr(eating[j], 'ANIMAL_TYPE') == 0):    # Don't send if mouse is there
                    return True
                elif (j == len(eating) - 1):
                    return False
        elif (getattr(animal, 'ANIMAL_TYPE') == 2):  # If Dog
            for j in range(0, len(eating)):
                if (getattr(eating[j], 'ANIMAL_TYPE') == 1):    # Don't send if cat is there
                    return True
                elif (j == len(eating) - 1):
                    return False
        else:  # If Mouse
            return False


def main():

    ### SORT ANIMALS ASCENDING TO THEIR SATISFIED TIME AT BEGINNING

    animal = [dogs,mouse,cats]
    animallist = []
    animallist_fcfs = []
    numDishes = 0
    if (len(dogs) > 0):
        numDishes = len(dogs[0].dishes)
    elif (len(cats) > 0):
        numDishes = len(cats[0].dishes)
    elif (len(mouse) > 0):
        numDishes = len(mouse[0].dishes)

    sat_que = collections.deque()
    strav_que = collections.deque()
    eating = collections.deque()

    for a in animal:
        for ani in a:
            animallist.append(ani)
            #animallist_fcfs.append(ani) #FCFS NECESSARY

    size = len(animallist)
    #size = len(animallist_fcfs) #FCFS NECESSARY

    for i in range(size):
        for j in range(i):
           if (animallist[j].get_remaining_status_times_s()[animallist[j].get_status()] > animallist[j+1].get_remaining_status_times_s()[animallist[j+1].get_status()]):
                tmp = animallist[j]
                animallist[j] = animallist[j+1]
                animallist[j+1] = tmp
    
    # FOR LOOP ORDERING ANIMALS BY LIFETIME (ARRIVAL TIME) FCFS NECESSARY

    # for i in range(size):
    #     for j in range(i):
    #        if (animallist_fcfs[j].get_lifetime() > animallist_fcfs[j+1].get_lifetime()):
    #             tmp = animallist_fcfs[j]
    #             animallist_fcfs[j] = animallist_fcfs[j+1]
    #             animallist_fcfs[j+1] = tmp
    

    for a in animallist:
        sat_que.append(a)
    
    # for a in reversed(animallist_fcfs): #FCFS NECESSARY
    #     sat_que.append(a) #FCFS NECESSARY

    ### FEEDING LOOP

    for i in range(0, 100):
        ### FETCH FROM STARVING QUEUE IF NOT EMPTY
        if len(strav_que) > 0:
            animal = strav_que[0]              # GET MOST STARVING ANIMAL
            kill = False
            for x in range(0, len(strav_que)):
                animal = strav_que[x]
                if not (animalWouldKill(eating, animal)):
                    kill = False
                    break
                else:
                    kill = True


            if (not kill and len(eating) < numDishes):   # ANIMAL WOULDN'T KILL
                strav_que.remove(animal)
                if(animal.get_status() != State.DEAD):
                    rt = animal.goto_dishes()
                    if(not rt):
                        strav_que.appendleft(animal)
                    else:                                           # SEND ANIMAL TO DISH
                        orderInto(eating, animal)               # ADD EATING ANIMAL
                        #orderInto_fcfs(eating, animal) #FCFS NECESSARY
                        for a in eating:
                            with a.cv_lock:
                                while (State(a.get_status()) != State.EATING and State(a.get_status()) != State.DEAD):
                                    a.wakeup()
                                    a.condition.wait()


            if (len(eating) > 0):
                    eater = eating[0]      # GET SHORTEST REMAINING-EATING-TIME ANIMAL
                    if (len(eating) == numDishes):                     # JUST WAIT IF DISHES ARE FULL
                        eater.cv_lock.acquire()
                        while (eater.get_status() == State.EATING and State(animal.get_status()) != State.DEAD):    # WAIT WHILE ANIMAL EATING
                            eater.condition.wait()                     # WAKEUP SELF WHEN STATUS CHANGED
                        eater.cv_lock.release()
                        # PUT SATISFIED ANIMAL BACK INTO SATISFIED QUEUE
                        if (State(eater.get_status()) == State.SATISFIED):
                            eating.remove(eater)                           # REMOVE (not anymore) EATING ANIMAL
                            orderInto(sat_que, eater)
                            #sat_que.append(eater) #FCFS NECESSARY

                    removement = []
                    for a in eating:
                        with a.cv_lock:
                            if a.get_status() != State.EATING:
                                removement.append(a)
                                if a.get_status() != State.DEAD:
                                    if a.get_status() == State.SATISFIED:
                                        orderInto(sat_que, a)
                                        #sat_que.append(a) #FCFS NECESSARY
                                    elif a.get_status() == State.STRAVING:
                                        orderInto(strav_que, a)
                                        #orderInto_fcfs(strav_que, a) #FCFS NECESSARY
                    for r in removement:
                        eating.remove(r)


        ### CHECK IF AN ANIMAL IS STARVING

        if len(sat_que) > 0:

            a = sat_que.popleft()

            a.cv_lock.acquire()
            while (a.get_status() != State.STRAVING and a.get_status() != State.DEAD):      # WAIT WHILE SATISFIED
                a.wakeup()
                a.condition.wait()                          # WAKEUP WHEN STATUS CHANGED
            if (a.get_status() == State.STRAVING):
                orderInto(strav_que, a)
                #orderInto_fcfs(strav_que, a)
            a.cv_lock.release()






if __name__ == "__main__":
    init()
    main()
    in_the_end()