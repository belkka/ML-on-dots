# coding: utf-8
import numpy as np
import random


K = 3


with open("input.txt") as raw_data:
    X = np.loadtxt(raw_data)

clusters = [list() for __ in xrange(K)]

for (i, x) in enumerate(X):
    clusters[random.randint(0, K - 1)].append(i)

for i in xrange(K):
    print " ".join(map(str, clusters[i]))
