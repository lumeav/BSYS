#!/bin/bash

file="sloppyTresholdsData"

if [ -f "$file" ] ; then
    command1="rm $file" 
    eval $command1
fi

program="./sloppy"
output=""

# Der Zaehler mit dem die Tresholds-Groesse bestimmt wird, wird quadratisch
# erhöht, da es in der Grafik im Buch auch so gemacht wurde
for ((i=1; i<=1024; i=i*2)); do
    command2="$program -l 2048 -t 4 -n $i >> $file"
    eval $command2
    echo $i >> $file
done

python="python sloppyTresholdsGraph.py"
eval $python
