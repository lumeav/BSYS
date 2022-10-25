## aufgabe 1

segmentation fault (core dumped)  ./null.out

----------------------------------------------------------------------------------------------------

## aufgabe 2

Program received signal SIGSEGV, Segmentation fault.
0x000055555555517b in main () at null.c:9
9           printf("pInt: %i\n", *pInt);

----------------------------------------------------------------------------------------------------

## aufgabe3

==19512== Memcheck, a memory error detector
==19512== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==19512== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==19512== Command: ./null.out
==19512==
==19512== Invalid read of size 4
==19512==    at 0x10917B: main (null.c:9)
==19512==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==19512==
==19512==
==19512== Process terminating with default action of signal 11 (SIGSEGV): dumping core
==19512==  Access not within mapped region at address 0x0
==19512==    at 0x10917B: main (null.c:9)
==19512==  If you believe this happened as a result of a stack
==19512==  overflow in your program's main thread (unlikely but
==19512==  possible), you can try to increase the size of the
==19512==  main thread stack using the --main-stacksize= flag.
==19512==  The main thread stack size used in this run was 8388608.
==19512==
==19512== HEAP SUMMARY:
==19512==     in use at exit: 0 bytes in 0 blocks
==19512==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==19512==
==19512== All heap blocks were freed -- no leaks are possible
==19512==
==19512== For lists of detected and suppressed errors, rerun with: -s
==19512== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
zsh: segmentation fault (core dumped)  valgrind --leak-check=yes ./null.out

----------------------------------------------------------------------------------------------------

## aufgabe4

==21368== Memcheck, a memory error detector
==21368== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==21368== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==21368== Command: ./no_free.out
==21368==
==21368==
==21368== HEAP SUMMARY:
==21368==     in use at exit: 4 bytes in 1 blocks
==21368==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==21368==
==21368== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==21368==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==21368==    by 0x10914A: main (no_free.c:5)
==21368==
==21368== LEAK SUMMARY:
==21368==    definitely lost: 4 bytes in 1 blocks
==21368==    indirectly lost: 0 bytes in 0 blocks
==21368==      possibly lost: 0 bytes in 0 blocks
==21368==    still reachable: 0 bytes in 0 blocks
==21368==         suppressed: 0 bytes in 0 blocks
==21368==
==21368== For lists of detected and suppressed errors, rerun with: -s
==21368== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

----------------------------------------------------------------------------------------------------

## aufgabe5

==22490== Memcheck, a memory error detector
==22490== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==22490== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==22490== Command: ./int_array.out
==22490==
==22490== Invalid write of size 4
==22490==    at 0x109179: main (int_array.c:6)
==22490==  Address 0x4a541d0 is 0 bytes after a block of size 400 alloc'd
==22490==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==22490==    by 0x10916A: main (int_array.c:5)
==22490==
pInt: 0x4a54040
==22490==
==22490== HEAP SUMMARY:
==22490==     in use at exit: 0 bytes in 0 blocks
==22490==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==22490==
==22490== All heap blocks were freed -- no leaks are possible
==22490==
==22490== For lists of detected and suppressed errors, rerun with: -s
==22490== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

----------------------------------------------------------------------------------------------------

## aufgabe6

==24077== Memcheck, a memory error detector
==24077== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==24077== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==24077== Command: ./read_after_free.out
==24077==
==24077== Invalid read of size 4
==24077==    at 0x109195: main (read_after_free.c:8)
==24077==  Address 0x4a541cc is 396 bytes inside a block of size 400 free'd
==24077==    at 0x484426F: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==24077==    by 0x10918A: main (read_after_free.c:7)
==24077==  Block was alloc'd at
==24077==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==24077==    by 0x10916A: main (read_after_free.c:5)
==24077==
pInt[99]: 5
==24077==
==24077== HEAP SUMMARY:
==24077==     in use at exit: 0 bytes in 0 blocks
==24077==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==24077==
==24077== All heap blocks were freed -- no leaks are possible
==24077==
==24077== For lists of detected and suppressed errors, rerun with: -s
==24077== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

----------------------------------------------------------------------------------------------------

## aufgabe7

funny_value.c: In function ‘main’:
funny_value.c:9:5: warning: ‘free’ called on pointer ‘pInt’ with nonzero offset 4 [-Wfree-nonheap-object]
    9 |     free(&pInt[1]);
      |     ^~~~~~~~~~~~~~
funny_value.c:5:25: note: returned from ‘malloc’
    5 |     int *pInt = (int *) malloc(100 * sizeof(int));
      |                         ^~~~~~~~~~~~~~~~~~~~~~~~~

