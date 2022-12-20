2. 
    python3 ./x86.py -p flag.s -M flag,count -R ax,bx -c
    It will end with 0.

3. 
    python3 ./x86.py -p flag.s -M flag,count -R ax,bx -c -a bx=2,bx=2
    It just loops twice now flag still 0.

4. 
    python3 ./x86.py -p flag.s -M flag,count -R ax,bx -c -a bx=15,bx=15
    Interrupt frequencies 1-10 are bad; 11,15 are good.

5. 
    xchq %ax, mutex //This is the lock.
    mov $0,mutex //This is the unlock.

6. 
    python3 ./x86.py -p test-and-set.s -M mutex,count -R ax,bx -c -a bx=15,bx=15
    count is always the correct value no matter the interrupt frequency.

7. 
    python3 ./x86.py -p test-and-set.s -M mutex,count -R ax,bx -c -a bx=1,bx=1 -P 0101
    The correct thing occurs.

8. 
    cat peterson.s

9. 
    python3 ./x86.py -p peterson.s -M turn,count,flag -R ax,bx,cx -c -a bx=0,bx=1
    The code runs correctly as it should.

10. 
    python3 ./x86.py -p peterson.s -M turn,count,flag -R ax,bx,cx -c -a bx=0,bx=1 -P 0000011111
    Still works even though after the first 5 operations a timer interrupt took place.

11. 
    python3 ./x86.py -p ticket.s -M turn,count,ticket -R ax,bx,cx -c -a bx=1000,bx=1000
    It matches the code in the chapter. Yes it spins a lot.

12. 
    python3 ./x86.py -p ticket.s -M turn,count,ticket -R ax,bx,cx -c -t 10
    As you add more threads, the more threads are waiting for the unlock the more spinning will occur.

13. 
    python3 ./x86.py -p test-and-set.s -M mutex,count -R ax,bx -c -a bx=5,bx=5
    python3 ./x86.py -p yield.s -M mutex,count -R ax,bx -c -a bx=5,bx=5
    It saves one instruction. When the thread is yielding instead of spinning.

14. 
    cat test-and-test-and-set.s
    This will set mutex to 1 when lock is free. Which will avoid some writing.