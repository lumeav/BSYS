# HW CHAP 29
## Getting started
Change the number of CPUs in sloppy.c to your current number of CPUs in line 15
```c
#define NUMCPUS <Current number of CPUs>
```

## Usage
Compile all files
```shell
make all
```
Using simple.c
```shell
./simple -h
```
Using sloppy.c
```shell
./sloppy -h
```
Using linkedList.c
```shell
./linkedList -h
```
## Generate the Graphs
Generate the graph for simple.c

```shell
bash simpleScript.sh
```
Generate the graph for sloppy.c where the number of threads increases but threshold stays the same

```shell
bash sloppyScriptThreads.sh
```
Generate the graph for sloppy.c where the size of the treshold increases but number of threads stays the same

```shell
bash sloppyScriptTresholds.sh
```