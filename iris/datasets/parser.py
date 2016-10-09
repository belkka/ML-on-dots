# -*- coding: utf-8 -*-

cluster_names = {
    "Iris-setosa\n": "0",
    "Iris-versicolor\n": "1",
    "Iris-virginica\n": "2",
}

def parse():
    inp = open("input.txt", "w")
    ans = open("answers.txt", "w")

    with open("iris.data.shuffled", "r") as dataset:
        for line in dataset:
            arr = line.split(",")
            data, mark = arr[:-1], arr[-1]

            inp.write(" ".join(data) + "\n")
            if mark in cluster_names:
                ans.write(cluster_names[mark] + "\n")
            else:
                print "Error key:", repr(mark)

    inp.close()
    ans.close()


parse()
