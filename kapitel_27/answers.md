1. 
    It points to the correct lines of code.#
    It also gives me an address (data symbol, in this case balance) and the size.

2. 
    In each of those cases helgrind doesn't report any conflicts.

3. 
    They keep waiting for the unlock which neither one of them has.

4. 
    "lock order "0x10C040 before 0x10C080" violated"

5. 
    With the additional lock g there should not be any deadlock occuring however helgrind still
    falsely calls it an error.

6. 
    During this time the parent waits (spins), which may cause wasting CPU cycles leaving poor performance
    and inefficiency.

7.  
    It says that there is a data race on the "done" variable and the printf(). No, he should have used
    condition variables.

8. 
    It has better performance and is less error prone. Both.

9. 
    No, it doesn't report any errors.