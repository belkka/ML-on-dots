# coding: utf-8
import numpy as np
import random


class params:
    K = 3
    dtype = float


with open("input.txt") as raw_data:
    X = np.loadtxt(raw_data, dtype=params.dtype)

clusters = [list() for __ in xrange(params.K)]

for (i, x) in enumerate(X):
    clusters[random.randint(0, params.K - 1)].append(i)

for i in xrange(params.K):
    print " ".join(map(str, clusters[i]))
