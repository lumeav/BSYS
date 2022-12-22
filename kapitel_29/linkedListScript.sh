#!/bin/bash

file="linkedListData"

if [ -f "$file" ] ; then
    command1="rm $file" 
    eval $command1
fi
program="./linkedList"

for ((i=0; i<=200; i = i + 2)); do
    command2="$program -l 100 -t $i >> $file"
    eval $command2
    echo $i >> $file
done

python="python3 ./linkedListGraph.py"
eval $python
