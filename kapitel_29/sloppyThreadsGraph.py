import sys
from numpy import *
import matplotlib.pyplot as plt

data = genfromtxt("sloppyThreadsData")

fig, ax = plt.subplots()
ax.plot(data[:,1], data[:,0] / 1000000, marker='o')
ax.set_title("Sloppy Counter")
ax.set_xlabel("Threads")
ax.set_ylabel("Time (ms)")
fig.savefig("sloppyThreadsGraph.png")
