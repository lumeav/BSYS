#!/bin/bash

file="linkedListInsertData"

if [ -f "$file" ] ; then
    command1="rm $file" 
    eval $command1
fi
program="./linkedList"

for ((i=0; i<=50000; i = i + 10000)); do
    command2="$program -l $i -t 8 >> $file"
    eval $command2
    echo $i >> $file
done

python="python3 ./linkedListInsertGraph.py"
eval $python
