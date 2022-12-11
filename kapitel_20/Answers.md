1.
    You just need one as you need the root (top level) page directory base register.

2.
    611c in binary 1 <- valid 1000 <- PDI 01000 <- page table offset 11100 <- offset
    5 top bits = 11000 that equals 24. 24 is the index in page directory.
    In 24 it says a1. a1 = 10100001. First bit 1 <- valid. 0100001 = 33.
    PDI = 01000 = 8.
    You then look in page 33 with the index 8. Which gives you b5.
    b5 = 10110101 = 1 <- valid 0110101 = 53.
    Then you concatonate 0110101 with the offest 11100 which gives you =
    011010111100 -> 6bc = physical address
    Now you look in page 53 with the index 28 (offset) which gives you 08.
    Which means the value is 08.

    7f6c in binary 11111 | 11011 | 01100
    11111 = 31. Index 31 gives ff. ff = 11111111 -> 1111111 = 127
    PDI = 27.
    Look in page 127 with index 27. Which gives you 7f.
    7f = 01111111 = 0 <- invalid 
    page table entry invalid

    

3.
    Because of the extra memory reference on a miss it will take longer to be handled,
    but I think it will lead to a few more misses because of more memory references.