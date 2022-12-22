import sys
from numpy import *
import matplotlib.pyplot as plt

data = genfromtxt("linkedListInsertData")

fig, ax = plt.subplots()
ax.plot(data[:,1], data[:,0] / 1000000, marker='o')
ax.set_title("Linked List Performance")
ax.set_xlabel("Inserts")
ax.set_ylabel("Time (ms)")
fig.savefig("linkedListInsertGraph.png")
