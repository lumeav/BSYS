#!/bin/bash

file="sloppyThreadsData"

if [ -f "$file" ] ; then
    command1="rm $file" 
    eval $command1
fi

program="./sloppy"

for ((i=0; i<=200; i++)); do
    command2="$program -l 10000 -t $i -n 1000000 >> $file"
    eval $command2
    echo $i >> $file
done

python="python3 ./sloppyThreadsGraph.py"
eval $python
