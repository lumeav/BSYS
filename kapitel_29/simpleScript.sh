#!/bin/bash

file="simpleData"

if [ -f "$file" ] ; then
    command1="rm $file" 
    eval $command1
fi
program="./simple"

for ((i=0; i<=200; i++)); do
    command2="$program -l 10000 -t $i >> $file"
    eval $command2
    echo $i >> $file
done

python="python3 ./simpleGraph.py"
eval $python
