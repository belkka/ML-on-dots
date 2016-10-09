# coding: utf-8
import numpy as np
import random


with open("input.txt") as raw_data:
    X = np.loadtxt(raw_data, dtype=int)

clusters = [list() for __ in xrange(10)]

for (i, x) in enumerate(X):
    clusters[random.randint(0, 9)].append(i)

for i in xrange(10):
    print " ".join(map(str, clusters[i]))
