1. 
    Register dx will start off at value 0, meaning the sub instruction will subtract 1 off 0. Which means dx value will be set to -1. "test" will then compare
    value 0 with that of value dx. "jgte" will then jump if value 2 ist greater than or equal to value 1. Which means in this case it will not jump, as 
    -1 is smaller than and not equal to 0, therefore halting the the loop.

2. 
    This time we run everything with 2 threads and dx set to 3 in both of them. First thread 1 will run and loop through, decrementing dx with every loop down 
    to -1 (just as we've seen in the first question). It will then halt and thread 2 is now issued to be run, going through the same loop just as thread 1 does
    and then halts at dx value -1. In this case the presence of multiple threads does not affect the value of dx at any point nor do any races occur.

3. 
    Even with a smaller time interupt of 3, both thread 1 and thread 2 decrease their own register dx correctly. There are no data races.

4. 
    0 at the start and then 1 at the end after the increment.

5. 
    Each thread loops two times because we've set bx to 3 and the jump is set to "jump if greater than" (meaning it jumps at 2 and 1).
    The first initial start of the program will add 1 to ax and will then proceed to loop 2 times after. Meaning we're left with a value
    of 3 at the end of thread 1. Thread 2 will then proceed to do the same with the value saved from thread 1 meaning we're left with
    the value set to 6.

6. 
    The interrupt timing is crucial in this case. The timing should not occur before the value is saved (meaning at 1002: mov %ax, 2000).

7. 
    For:
    -i 1 value = 1
    -i 2 value = 1
    -i 3 value = 2
    So it seems i 3 gives you the correct answer.

8. 
    Running the program with more loops leads to a pattern of correct timing intervals.
    More precisely a multiple of -i 3 seems to always lead to the correct value at the end.

9. 
    .main
    test $1, %ax     # ax should be 1 (signaller) or 0 (waiter)
    je .signaller

    .waiter	
    mov  2000, %cx
    test $1, %cx
    jne .waiter
    halt

    .signaller
    mov  $1, 2000
    halt

    wait-for-me.s

    First the program runs thread 1 which tests if ax = 1 (which in this case it is). It will then continue to jump to signaller, which will set
    value 1 into memory location 2000 and then halt. Thread 2 runs now with ax = 0 tests and will not jump but instead go inside .waiter.
    From then on it will take whats placed in 2000 and will put it into cx (-> cx = 1). Afterwards it will jump to waiter again, if 
    cx is not equal to 1, in any other cases it will halt.

10. 
    Now thread 1 will go into waiter seeming to be endlessly looping (waiting) for thread 2 to end. After 100 instruction the timer interrupt
    will switch to thread 2 and set cx=1 therefore ending the loop in thread 1. The program is not using the CPU efficiently.
    A smaller time interrupt will make the program slightly more efficient.