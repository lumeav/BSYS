## 1)
## ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0 -c

RG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal:  492)
  VA  1: 0x00000061 (decimal:   97) --> SEGMENTATION VIOLATION (SEG1)
  VA  2: 0x00000035 (decimal:   53) --> SEGMENTATION VIOLATION (SEG0)
  VA  3: 0x00000021 (decimal:   33) --> SEGMENTATION VIOLATION (SEG0)
  VA  4: 0x00000041 (decimal:   65) --> SEGMENTATION VIOLATION (SEG1)

----------------------------------------------------------------------------------------------------

## ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1 -c

ARG seed 1
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x00000011 (decimal:   17) --> VALID in SEG0: 0x00000011 (decimal:   17)
  VA  1: 0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal:  492)
  VA  2: 0x00000061 (decimal:   97) --> SEGMENTATION VIOLATION (SEG1)
  VA  3: 0x00000020 (decimal:   32) --> SEGMENTATION VIOLATION (SEG0)
  VA  4: 0x0000003f (decimal:   63) --> SEGMENTATION VIOLATION (SEG0)

----------------------------------------------------------------------------------------------------

## ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2 -c

ARG seed 2
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x0000007a (decimal:  122) --> VALID in SEG1: 0x000001fa (decimal:  506)
  VA  1: 0x00000079 (decimal:  121) --> VALID in SEG1: 0x000001f9 (decimal:  505)
  VA  2: 0x00000007 (decimal:    7) --> VALID in SEG0: 0x00000007 (decimal:    7)
  VA  3: 0x0000000a (decimal:   10) --> VALID in SEG0: 0x0000000a (decimal:   10)
  VA  4: 0x0000006a (decimal:  106) --> SEGMENTATION VIOLATION (SEG1)

----------------------------------------------------------------------------------------------------

## 2)
## highest legal address segment 0:	19
## lowest legal address segment 1:	108

## lowest illegal address: 20
## highest illegal address: 107

./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0 -A 19 -c
./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0 -A 108 -c

./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0 -A 20 -c
./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0 -A 107 -c

----------------------------------------------------------------------------------------------------

## 3)
## ./segmentation.py -a 16 -p 128 -A "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15" -b 0 -l 2 -B 128 -L 2 -c

ARG seed 0
ARG address space size 16
ARG phys mem size 128

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 2

  Segment 1 base  (grows negative) : 0x00000080 (decimal 128)
  Segment 1 limit                  : 2

Virtual Address Trace
  VA  0: 0x00000000 (decimal:    0) --> VALID in SEG0: 0x00000000 (decimal:    0)
  VA  1: 0x00000001 (decimal:    1) --> VALID in SEG0: 0x00000001 (decimal:    1)
  VA  2: 0x00000002 (decimal:    2) --> SEGMENTATION VIOLATION (SEG0)
  VA  3: 0x00000003 (decimal:    3) --> SEGMENTATION VIOLATION (SEG0)
  VA  4: 0x00000004 (decimal:    4) --> SEGMENTATION VIOLATION (SEG0)
  VA  5: 0x00000005 (decimal:    5) --> SEGMENTATION VIOLATION (SEG0)
  VA  6: 0x00000006 (decimal:    6) --> SEGMENTATION VIOLATION (SEG0)
  VA  7: 0x00000007 (decimal:    7) --> SEGMENTATION VIOLATION (SEG0)
  VA  8: 0x00000008 (decimal:    8) --> SEGMENTATION VIOLATION (SEG1)
  VA  9: 0x00000009 (decimal:    9) --> SEGMENTATION VIOLATION (SEG1)
  VA 10: 0x0000000a (decimal:   10) --> SEGMENTATION VIOLATION (SEG1)
  VA 11: 0x0000000b (decimal:   11) --> SEGMENTATION VIOLATION (SEG1)
  VA 12: 0x0000000c (decimal:   12) --> SEGMENTATION VIOLATION (SEG1)
  VA 13: 0x0000000d (decimal:   13) --> SEGMENTATION VIOLATION (SEG1)
  VA 14: 0x0000000e (decimal:   14) --> VALID in SEG1: 0x0000007e (decimal:  126)
  VA 15: 0x0000000f (decimal:   15) --> VALID in SEG1: 0x0000007f (decimal:  127)

----------------------------------------------------------------------------------------------------

## 4)
## ./segmentation.py -a 100 -p 512 -b 0 -l 45 -B 100 -L 45 -s 0 -c

ARG seed 0
ARG address space size 100
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 45

  Segment 1 base  (grows negative) : 0x00000064 (decimal 100)
  Segment 1 limit                  : 45

Virtual Address Trace
  VA  0: 0x00000054 (decimal:   84) --> VALID in SEG1: 0x00000054 (decimal:   84)
  VA  1: 0x0000004b (decimal:   75) --> VALID in SEG1: 0x0000004b (decimal:   75)
  VA  2: 0x0000002a (decimal:   42) --> VALID in SEG0: 0x0000002a (decimal:   42)
  VA  3: 0x00000019 (decimal:   25) --> VALID in SEG0: 0x00000019 (decimal:   25)
  VA  4: 0x00000033 (decimal:   51) --> SEGMENTATION VIOLATION (SEG1)

----------------------------------------------------------------------------------------------------

## 5)
## ./segmentation.py -a 100 -p 512 -b 0 -l 0 -B 100 -L 0 -s 0 -c

ARG seed 0
ARG address space size 100
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 0

  Segment 1 base  (grows negative) : 0x00000064 (decimal 100)
  Segment 1 limit                  : 0

Virtual Address Trace
  VA  0: 0x00000054 (decimal:   84) --> SEGMENTATION VIOLATION (SEG1)
  VA  1: 0x0000004b (decimal:   75) --> SEGMENTATION VIOLATION (SEG1)
  VA  2: 0x0000002a (decimal:   42) --> SEGMENTATION VIOLATION (SEG0)
  VA  3: 0x00000019 (decimal:   25) --> SEGMENTATION VIOLATION (SEG0)
  VA  4: 0x00000033 (decimal:   51) --> SEGMENTATION VIOLATION (SEG1)

