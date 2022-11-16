1. First run with the flags -n 10 -H 0 -p BEST -s 0 to gener-
ate a few random allocations and frees. Can you predict what al-
loc()/free() will return? Can you guess the state of the free list after
each request? What do you notice about the free list over time?

    The memory gets split into multiple pieces of smaller chunks.


2. How are the results different when using a WORST fit policy to
search the free list (-p WORST)? What changes?

    The memory splits into even more pieces as it only grabs memory from the biggest chunk.
    However this leads to a longer searching time, as more and more pieces need to be iterated through.


3. What about when using FIRST fit (-p FIRST)? What speeds up
when you use first fit?

    The loading time speeds up, as it has to search through less elements.


4. For the above questions, how the list is kept ordered can affect the
time it takes to find a free location for some of the policies. Use
the different free list orderings (-l ADDRSORT, -l SIZESORT+,
-l SIZESORT-) to see how the policies and the list orderings in-
teract.

    SIZESORT- sorts the list in a descending order based on its size, so it operates the best with the WORST policy, 
    as it puts the biggest chunk of memory first.

    SIZESORT+ sorts the list in an ascending order based on its size, so it operates the best with the BEST and FIRST
    policy, as the policy looks for the best fitting chunk.

    ADDRSORT sorts the list based on its address in memory.


5. Coalescing of a free list can be quite important. Increase the number
of random allocations (say to -n 1000). What happens to larger
allocation requests over time? Run with and without coalescing
(i.e., without and with the -C flag). What differences in outcome do
you see? How big is the free list over time in each case? Does the
ordering of the list matter in this case?

    Over time larger allocation requests wont always be satisfied as the memory is too fragmented to allow such allocations.
    ADDRSORT tends to coalesce with ease however the other orderings seem to have problems with it.
    Coalescing reduces the elements from the free list from 31 down to just 1 element in some cases.
    The orderings only matter when coalescing is enabled or not. When it is not enabled the orderings do not matter to the size
    of the elements in the free list.


6. What happens when you change the percent allocated fraction -P
to higher than 50? What happens to allocations as it nears 100?
What about as the percent nears 0?

    The higher the percentage of allocation the higher the chance of having an unsuccessful allocation attempt.
    A percentage of 0% means, that it never allocates anything, that means the program doesn't work. 
    Therefore it needs to be above 0%. However the program alternates between allocating and freeing,
    as it always gets into the position of not having anything to free, given the low percentage of allocating.
    That's why the program ALWAYS allocates when there is nothing to free.


7. What kind of specific requests can you make to generate a highly-
fragmented free space? Use the -A flag to create fragmented free
lists, and see how different policies and options change the organi-
zation of the free list.

    python3 ./malloc.py -c -A +5,-0,+10,-1,+20,-2,+40,-3
    python3 ./malloc.py -c -A +5,-0,+10,-1,+20,-2,+40,-3 -l SIZESORT+ -C
    python3 ./malloc.py -c -A +5,-0,+10,-1,+20,-2,+40,-3 -l SIZESORT- -C
    python3 ./malloc.py -c -A +5,-0,+10,-1,+20,-2,+40,-3 -p FIRST -l SIZESORT- -C
    python3 ./malloc.py -c -A +5,-0,+10,-1,+20,-2,+40,-3 -p WORST -l SIZESORT- -C
    python3 ./malloc.py -c -A +5,-0,+10,-1,+20,-2,+40,-3 -p BEST -l SIZESORT- -C
    python3 ./malloc.py -c -A +5,-0,+10,-1,+20,-2,+40,-3 -p FIRST -l SIZESORT+ -C
    python3 ./malloc.py -c -A +5,-0,+10,-1,+20,-2,+40,-3 -p WORST -l SIZESORT+ -C
    python3 ./malloc.py -c -A +5,-0,+10,-1,+20,-2,+40,-3 -p BEST -l SIZESORT+ -C





