#
#Makefile
#

CC = gcc -g
CFLAGS = -Wall -Wextra -std=gnu11 -Wpedantic -pthread
RM = rm -f

TARGETS = \
    simple\
    sloppy\
    linkedList\
	
.Phony: all clean

all: $(TARGETS)

clean:
	$(RM) $(TARGETS) $(TARGETS).o simpleData sloppyTresholdsData sloppyThreadsData simpleGraph.png sloppyTresholdsGraph.png sloppyThreadsGraph.png
