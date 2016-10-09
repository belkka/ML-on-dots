# coding: utf-8
import numpy as np
from sklearn.cluster import KMeans


class params:
    K = 10
    dtype = int


with open("input.txt") as raw_data:
    X = np.loadtxt(raw_data, dtype=params.dtype)

robot = KMeans(n_clusters=params.K, init='k-means++', n_init=1,
               max_iter=1000, precompute_distances=False)

clusters = [list() for __ in xrange(params.K)]

for i, prediction in enumerate(robot.fit_predict(X)):
    clusters[prediction].append(i)

with open("output.txt", "w") as out:
    for i in xrange(params.K):
        out.write(" ".join(map(str, clusters[i])))
