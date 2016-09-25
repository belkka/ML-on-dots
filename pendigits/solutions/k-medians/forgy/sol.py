# coding: utf-8
import numpy as np
import random


with open("input.txt") as raw_data:
    X = np.loadtxt(raw_data, dtype=int)

# ===============

clusters = [list() for __ in xrange(10)]

# Инициализация начальных центров

# Forgy method -- в качестве начальных центров кластеров
# выбираются случайные среди элементов данных

centers = np.array(random.sample(X, 10))  # случайные 10 элементов из списка  X


# ===============


def assignment_step():
    # этап распределения всех векторов в кластеры с ближайшими центрами

    global clusters
    clusters = [list() for __ in xrange(10)]  # опустошение кластеров

    for (i, x) in enumerate(X):
        clusters[np.argmin([((x - c) ** 2).sum() for c in centers])].append(i)


def update_step():
    # этап перерасчёта центров

    global centers
    centers = np.array([
                        np.median(np.array([X[i] for i in c]), axis=0)
                        for c in clusters
    ])


def vector_hash(vec):
    return hash(repr(vec))


def centers_hash(centers):
    return hash(repr(map(vector_hash, centers)))


# ==============

#print "Пожалуйста, понаблюдайте за появляющимися точками"

# повторяем этапы пока список центров не перестанет изменяться

prev_hash = None
curr_hash = centers_hash(centers)


while curr_hash != prev_hash:
    prev_hash = curr_hash

    assignment_step()
    update_step()

    curr_hash = centers_hash(centers)
    #print "."


# Готово

for i in xrange(10):
    print " ".join(map(str, clusters[i]))
